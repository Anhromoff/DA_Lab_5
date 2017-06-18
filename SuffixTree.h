#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#define TERMINATION_SYMBOL '$'

using namespace std;

class SuffixTree;

class Node 
{
public:
    friend SuffixTree;

	// конструктор без индекса
    Node(Node* link, int start, int* end) : 
		Node(link, start, end, -1) 
	{ }

	// конструктор с индексом
    Node(Node* link, int start, int* end, int ind) : 
		suffix_link(link), 
		start(start), 
		end(end), 
		suffix_index(ind) 
	{ }

private:
    map<char, Node*> children; // ассоциативный массив детей
    Node* suffix_link;		   // суффиксная ссылка
    int start;                 // номер первого символа вершины в тексте
    int *end;				   // номер последнего символа вершины в тексте
    int suffix_index;		   // номер суффикса
};

class SuffixTree
{
public:
    SuffixTree(string& text);			  // конструктор
    void BuildSuffixTree();				  // построение дерева
    //void PrintTree(Node *node, int lvl); 
	void DisplayTree();
    void Search(string& pat, int patNum); // поиск
    ~SuffixTree();						  // деструктор

private:
    void ExtendSuffixTree(int pos);				   // расширение дерева
    void DeleteSuffixTree(Node* node);			   // удаление дерева
    void CountIndex(Node* node, vector<int>& vec); //
    int EdgeLength(Node *node);					   // подсчет длины слова в вершине
	void Display(Node *node);

    Node* root = new Node(nullptr, -1, new int(-1)); // корень
    Node *last_new_node = nullptr;
    Node *active_node = nullptr;

    string text; // текст

    int active_edge = -1;
    int active_length = 0;
    int remaining_suffix_count = 0;
    int leaf_end = -1;
};