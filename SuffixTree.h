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

	// ����������� ��� �������
    Node(Node* link, int start, int* end) : 
		Node(link, start, end, -1) 
	{ }

	// ����������� � ��������
    Node(Node* link, int start, int* end, int ind) : 
		suffix_link(link), 
		start(start), 
		end(end), 
		suffix_index(ind) 
	{ }

private:
    map<char, Node*> children; // ������������� ������ �����
    Node* suffix_link;		   // ���������� ������
    int start;                 // ����� ������� ������� ������� � ������
    int *end;				   // ����� ���������� ������� ������� � ������
    int suffix_index;		   // ����� ��������
};

class SuffixTree
{
public:
    SuffixTree(string& text);			  // �����������
    void BuildSuffixTree();				  // ���������� ������
    //void PrintTree(Node *node, int lvl); 
	void DisplayTree();
    void Search(string& pat, int patNum); // �����
    ~SuffixTree();						  // ����������

private:
    void ExtendSuffixTree(int pos);				   // ���������� ������
    void DeleteSuffixTree(Node* node);			   // �������� ������
    void CountIndex(Node* node, vector<int>& vec); //
    int EdgeLength(Node *node);					   // ������� ����� ����� � �������
	void Display(Node *node);

    Node* root = new Node(nullptr, -1, new int(-1)); // ������
    Node *last_new_node = nullptr;
    Node *active_node = nullptr;

    string text; // �����

    int active_edge = -1;
    int active_length = 0;
    int remaining_suffix_count = 0;
    int leaf_end = -1;
};