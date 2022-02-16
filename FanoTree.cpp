#pragma once
#include "Fano.h"
#include "FanoTree.h"
/// ������� ������� ��� �������� ������
/**
* �������� ����������� ������� ��� �������� ������
@param list_s ���� ��������, �� ������� ��������� ������ ����
@return ������������ ��������� �� ������ �������
*/
Node* Tree::create_tree_main(list<SymbolRate>& list_s) {
	start = create_tree(list_s, list_s.begin(), list_s.end());
	return start;
}

/// ����������� ������� ��� �������� ������
/**
* ����� ������ ����� ���� �� ������� ���� (����� ���������
���������� �������� ������ ���� �������� ������ �����������
���������� �������� �����), � �������� ������ ��������� middle
�������. ����� ����� ����������� �� ��, ����� � ������� ����� ��
begin, �� end ��� ������ ���� �������. ���� ��� ���, �� ��������� ����
� ���� ���������, ���� ���, �� ���������� ���������� ���� �� �������, ��
������ ��� ������ [begin, middle) � ������� [middle, end) ������ lista
@param list_s ���� �������� ��� �������� ������
@param begin ������ ������� �� �������� ����� ������� ������
@param end ����� ������� �� �������� ����� ������� ������
@return ���������� ���� ����
*/
Node* Tree::create_tree(list<SymbolRate>& list_s, list<SymbolRate>::iterator begin, list<SymbolRate>::iterator end) {
	Node* leftNode = new Node;
	Node* rightNode = new Node;
	Node* resultNode;

	list<SymbolRate>::iterator middle = divide_srate(which_amount(begin, end, list_s), begin, end, list_s);

	list<SymbolRate>::iterator middle_s = middle;

	if (++middle_s != end || --middle_s != begin) {
		leftNode = create_tree(list_s, begin, middle);
		rightNode = create_tree(list_s, middle, end);

		resultNode = new Node(*leftNode, *rightNode);
	}
	else {
		delete leftNode;
		leftNode = nullptr;
		delete rightNode;
		rightNode = nullptr;

		resultNode = new Node(*leftNode, *rightNode, middle->symbol);
	}

	return resultNode;
}


/// ������� ��� �������� ���������� ������������� ��������, ������� ������ � ������ [begun_s, end_s)
/**
@param begin_s ������ lista, c �������� ���������� ������� ��� ������������
@param end_s ����� ������� ��� ������������
@param list_s ��� list, ������ ������� �������
@return ���������� ����� ���������� ���� �������� �� ������� [begun_s, end_s)
*/
int Tree::which_amount(list<SymbolRate>::iterator begin_s, list<SymbolRate>::iterator end_s, list<SymbolRate>& list_s) {
	int amount = 0;
	while (begin_s != end_s) {
		amount += begin_s->frequancy;
		begin_s++;
	}

	return amount;
}



/// ������� ��� ������� ���������������� lista �� ��������� ����
/**
* ����� �������� ���������� ������� ������� ������� �������, � ���������� � �����������
* ���������. �� ���� ����� �� ����� � ���� ����� �������� ��� ���� ������� �� �������, ��
* ����������� �� ����� + ��������� ������� ���������� ������������������ ���������. ���� ��
* �����������, �� ��������� ���� ������� � �����. ���� �����������, �� ����������� ����
@param amount_s ���������� �������� �� ������� [begun_s, end_s)
@param begin_s ������ ������� ��� �������
@param end_s ����� ������� ��� �������
@param list_s ��� list, ������� �� �����
@return ���������� �������� �� ������� �������
*/
list<SymbolRate>::iterator Tree::divide_srate(int amount_s, list<SymbolRate>::iterator begin_s,
	list<SymbolRate>::iterator end_s, list<SymbolRate>& list_s) {
	list<SymbolRate>::iterator middle;
	int sum = 0;
	for (middle = begin_s; (amount_s - sum) > middle->frequancy + sum; middle++) {
		sum += middle->frequancy;
	}
	return middle;
}

/// �����������
Tree::Tree() {
	start = new Node;
}

/// �������, ������������ ������ ������
Node* Tree::get_start_node() {
	return start;
}

/// ����������
Tree::~Tree() {
	if (start != nullptr) {
		start->~Node();
	}
}

/// ����������� ��� ���� ����������� ������
/**
* ������� ���� � �������� s
@param l ����� ����
@param r ������ ����
@param s ������
*/
Node::Node(Node& l, Node& r, char s) {
	if (&l == nullptr) {
		left = nullptr;
	}
	else {
		*left = l;
	}
	if (&r == nullptr) {
		right = nullptr;
	}
	else {
		*right = r;
	}
	symbol = s;
}

/// ���������� ��� ���� ��� �������(�������������� ����)
/**
@param l ����� ����
@param r ������ ����
*/
Node::Node(Node& l, Node& r) {
	left = new Node;
	right = new Node;
	if (&l == nullptr) {
		left = nullptr;
	}
	else {
		*left = l;
	}
	if (&r == nullptr) {
		right = nullptr;
	}
	else {
		*right = r;
	}
	symbol = -1;
}

/// ���������� �� ���������
Node::Node() {
	left = nullptr;
	right = nullptr;
}

/// �������� ������������
Node& Node::operator=(Node& a) {
	symbol = a.symbol;
	left = a.left;
	right = a.right;

	return *this;
}
/// ����������� �����������
Node::Node(Node& a) {
	left = a.left;
	right = a.right;
	symbol = a.symbol;
}
/// ����������
Node::~Node() {
	if (this != nullptr) {
		if (left != nullptr) {
			delete left;
		}

		if (right != nullptr) {
			delete right;
		}
	}
}