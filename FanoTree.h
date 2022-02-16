#pragma once
#pragma once
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include "Fano.h"
using namespace std;

struct SymbolRate;

/// ����� ��� ������ ���� ������
/**
* ������ � ���� -1 ��� ���� ���� ��������������,
* �� ���� �� ����� � �����, ��� ��������� ������.
* ������ � ���� ������, ���� ���� ���� ��������
@param left ��������� �� ����� ���� (������ ����)
@param right ��������� �� ������ ���� (������� ����)
@param symbol ������, ������� ��������� � ����
*/
class Node {
private:
	Node* left;
	Node* right;
	char symbol;
public:
	Node(Node& l, Node& r, char s);
	Node(Node& l, Node& r);
	Node();
	Node& operator=(Node& a);
	Node(Node& a);
	~Node();

	/// �����, ������������ ������, ������� ��������� � ���� ���� 
	char getSymbol() {
		return symbol;
	}
	/// �����, ������������ ������ ���� ����� ����
	Node* getLeft() {
		return left;
	}
	/// �����, ������������ ������� ���� ����� ����
	Node* getRight() {
		return right;
	}
};

/// ����� ������ ����
/**
* ������ ������� �� �����, ������� ������ ���� ������ (�������� ����),
* ���� -1 (�������������� ����). ����� �� lista �������� ������� �����������
* � ������ ����, � ����� ���� ������ ����������� � map, ��� �������� �����������
* ��������
@param start ����� ���������� ����
@param fanoMap Map, ��� ��������� {������, ��� �������� ���������� ����}
@param vec_create_map ������ ������ ��� ������� create_map
@param flag_create_map ���� ������ ��� ������� create_map
*/
class Tree {
private:
	Node* start;
	map<char, vector<int>>* fano_map_comp;
	map<string, char>* fano_map_decomp;
	vector<int> vec_create_map_comp; // ����� ��� ��������
	int flag_create_map = 0; // ���� ��� ��������. �����
	//��� ���� ����� ������� ��� map ��� ������������� ��� ����� �������
	string vec_create_map_decomp;
public:
	Tree();

	Node* create_tree_main(list<SymbolRate>& list_s);

	Node* create_tree(list<SymbolRate>& list_s, list<SymbolRate>::iterator begin, list<SymbolRate>::iterator end);

	int which_amount(list<SymbolRate>::iterator begin_s, list<SymbolRate>::iterator end_s, list<SymbolRate>& list_s);

	list<SymbolRate>::iterator divide_srate(int amount_s, list<SymbolRate>::iterator begin_s,
		list<SymbolRate>::iterator end_s, list<SymbolRate>& list_s);

	Node* get_start_node();

	void create_map_comp(Node*);
	void create_map_decomp(Node*);
	/// ���������� ��������� �� map
	map<char, vector<int>>* get_map_comp() {
		return fano_map_comp;
	}
	/// ���������� ��������� �� map
	map<string, char>* get_map_decomp() {
		return fano_map_decomp;
	}

	~Tree();
};