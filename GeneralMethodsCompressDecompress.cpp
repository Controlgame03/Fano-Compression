#include "Fano.h"
#include "FanoTree.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;


/// ����� ��� ���������� �������� � ������� ��������
/**
* ����� �������� ����������� ������� ���������� ��� lista
*/
void Fano::symbol_sort() {
	SRate.sort();
}


/// �������� < ��� ���� ��������
/**
* ��������� ���������� �� ������� ������������� ������� � �����
@param a ������ ������
@param b ������ ������
@return ������������ 0, ���� a > b. ������������ 1, ���� a < b.
*/
bool operator<(SymbolRate& a, SymbolRate& b) {
	return a.frequancy < b.frequancy;
}


/// ����������� ��� �������� ������
Fano::Fano() {
	symbolNumber = 0;
	fanoTree = new Tree;
}


/// ������� ��� �������� map, ��� ��������� ������� � �� �����������
/**
* ������� �������� ����������� ������� � Tree
*/
void Fano::create_map_comp() {
	fanoTree->create_map_comp(fanoTree->get_start_node());
	fMap_comp = fanoTree->get_map_comp();
}
/// ������� ��� �������� map, ��� ��������� ������� � �� �����������
/**
* ������� �������� ����������� ������� � Tree
*/
void Fano::create_map_decomp() {
	fanoTree->create_map_decomp(fanoTree->get_start_node());
	fMap_decomp = fanoTree->get_map_decomp();
}

/// �����, ��������� map ��������� � �� ��������� ������������� �����������
/**
* ����� �������� ����������. �� ������ ������� ����������� �� ��������
* �� ������� ������� ������ ������ (�� ���� �������� �� � ���� ������) ���
* �������������� �������� � ��������� -1. ���� ��� �������������� �������, �� �������
* ����������� 0 � ����� ����� (vector<int>) � ��������������� ����� �������, ��
* ���� ���������� ���������� ������� ��� ����� �������. ����� ���������� ���� ������,
* ������������ �������� �������� ����� ������� "0" ��������� �� ������ � �����������
* "1". ����� ����� ��������������� ��� ������� ������������ ������� �������� ������ �������
* ����� ���������� ���� �������� ���������� ������ ����� ����, ������� �������������
* � ��������� �� ������� �� 1 ���� ����. ���� ���� �������� ������ ������, �� ��� ����
* ����������� ������� �������� ������ � ��� � ������ ����� ����� �������. ������ ���������� �
* map ������� ���� map � ����� ����� ���������� � �������� map ��������, ������� �����
* ������������ flag, ������� ��������� ������ ���� ��� ��������� map
@param position ������� ����, ������� ����� �����������
*/
void Tree::create_map_comp(Node* position) {
	if (position->getLeft() == nullptr && position->getRight() == nullptr) {
		if (flag_create_map == 0) {
			fano_map_comp = new map<char, vector<int>>;
			flag_create_map = 1;
		}
		fano_map_comp->insert(pair<char, vector<int>>(position->getSymbol(), vec_create_map_comp));
	}
	else {
		vec_create_map_comp.push_back(0);
		create_map_comp(position->getLeft());
		vec_create_map_comp.pop_back();

		vec_create_map_comp.push_back(1);
		create_map_comp(position->getRight());
		vec_create_map_comp.pop_back();
	}
}
void Tree::create_map_decomp(Node* position) {
	if (position->getLeft() == nullptr && position->getRight() == nullptr) {
		if (flag_create_map == 0) {
			fano_map_decomp = new map<string, char>;
			flag_create_map = 1;
		}
		fano_map_decomp->insert(pair<string, char>(vec_create_map_decomp, position->getSymbol()));
	}
	else {
		vec_create_map_decomp.push_back('0');
		create_map_decomp(position->getLeft());
		vec_create_map_decomp.pop_back();

		vec_create_map_decomp.push_back('1');
		create_map_decomp(position->getRight());
		vec_create_map_decomp.pop_back();
	}
}

/// ����� ��� �������� ������ ����
/**
* �������� ������� ��� �������� ������ � ������ Tree
*/
void Fano::create_tree() {
	fanoTree->create_tree_main(SRate);
}


/// ����������
Fano::~Fano() {
	delete fanoTree;
}