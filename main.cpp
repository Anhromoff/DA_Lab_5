#include "SuffixTree.h"

int main(int argc, char *argv[]) 
{
    string text, pattern;
	int pattern_number = 0;
    cin >> text;
    SuffixTree suffix_tree(text);

	//suffix_tree.DisplayTree();
	//cout << endl;

    while (cin >> pattern) suffix_tree.Search(pattern, ++pattern_number);
}