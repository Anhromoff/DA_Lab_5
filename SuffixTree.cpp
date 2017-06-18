#include "SuffixTree.h"

SuffixTree::SuffixTree(string& str) : text(str) 
{
    text += TERMINATION_SYMBOL;
    BuildSuffixTree();
}

void SuffixTree::Display(Node* p)
{
	static int level = 0;
	level++;
	if (p->start == -1) printf("\\_<root>");
	else printf("_<%d, %d>[%d]", p->start, *p->end, p->suffix_index);

	for (int i=0; i<p->children.size();i++)
	{
		if (p->children[i])
		{
			printf("\n");
			for (int j = 0; j<level; j++) printf("   ");
			printf("\\");
			Display(p->children[i]);
		}
	}
	level--;
}

void SuffixTree::DisplayTree()
{
	Display(root);
}

int SuffixTree::EdgeLength(Node *node) 
{
    return *(node->end) - (node->start) + 1;
}

void SuffixTree::ExtendSuffixTree(int pos) 
{
    leaf_end = pos;
    remaining_suffix_count++;
    last_new_node = nullptr;
    while (remaining_suffix_count) 
	{
        if (!active_length) active_edge = pos;

        auto find = active_node->children.find(text[active_edge]);

        if (find == active_node->children.end()) 
		{
            active_node->children.insert(make_pair(text[active_edge], new Node(root, pos, &leaf_end, pos - remaining_suffix_count + 1)));
            if (last_new_node) 
			{
                last_new_node->suffix_link = active_node;
                last_new_node = nullptr;
            }
        }
        else 
		{
            Node* next = find->second;
            int edge_length = EdgeLength(next);

            if (active_length >= edge_length) 
			{
                active_edge += edge_length;
                active_length -= edge_length;
                active_node = next;
                continue;
            }
            if (text[next->start + active_length] == text[pos]) 
			{
                if (last_new_node && active_node != root) last_new_node->suffix_link = active_node;
                active_length++;
                break;
            }

            Node* split = new Node(root, next->start, new int(next->start + active_length - 1));

            active_node->children[text[active_edge]] = split;
            next->start += active_length;
            split->children.insert(make_pair(text[pos], new Node(root, pos, &leaf_end, pos - remaining_suffix_count + 1)));
            split->children.insert(make_pair(text[next->start], next));
            if (last_new_node) last_new_node->suffix_link = split;
            last_new_node = split;
        }
        remaining_suffix_count--;
        if (active_node == root && active_length > 0) 
		{
            active_length--;
            active_edge = pos - remaining_suffix_count + 1;
        }
        else if (active_node != root) active_node = active_node->suffix_link;
    }
}

void SuffixTree::CountIndex(Node* node, vector<int>& vec) 
{
    if (!node) return;
    for (auto it: node->children) CountIndex(it.second, vec);
    if (node->suffix_index != -1) vec.push_back(node->suffix_index);
}

void SuffixTree::BuildSuffixTree() 
{
    active_node = root;
    size_t lenSize = text.length();
    for (size_t i = 0; i < lenSize; i++) ExtendSuffixTree(i);
}

void SuffixTree::Search(string& pat, int patNum)
{
    Node* current = root;
    for (auto it = pat.begin(); it != pat.end();) 
	{
        auto find = current->children.find(*it);
        if (find != current->children.end()) 
		{
            current = find->second;
			for (int j = current->start; j <= *current->end && it != pat.end(); j++, ++it)
			{
				if (text[j] != *it) return;
			} 
        }
        else return;
    }
    bool flag = false;
    cout << patNum << ": ";
    vector<int> ind;
    CountIndex(current, ind);
    sort(ind.begin(), ind.end());
    for (auto it: ind) 
	{
        cout << (flag ? ", " : "") << it + 1;
        flag = true;
    }
    cout << endl;
}

void SuffixTree::DeleteSuffixTree(Node* node) 
{
    for (auto it : node->children) DeleteSuffixTree(it.second);
    if (node->suffix_index == -1) delete node->end;
    delete node;
}

SuffixTree::~SuffixTree() 
{
    DeleteSuffixTree(root);
}
