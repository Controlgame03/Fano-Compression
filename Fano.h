#pragma once
#include <list>
#include <iostream>
#include <map>
#include <vector>
#include "FanoTree.h"

using namespace std;

#define ONE_ELEMENT 1

/// ���������, �������� � ���� {������, ��� ���������� � �����}
/**
@param symbol ��� ������
@param frequancy ������� ������������� ������� � �����
*/
struct SymbolRate {
	char symbol;
	int frequancy;
};


/// ������� �����, ������� ��������� ����� ���������������� ��������
/**
* �����, ������� ��������� � list �������, �� List� ��������� ������ � �.�.
* � ����� ������ ��������� ������� � ���� ������������ �����
@param symbolNumber ���������� ��������
@param SRate ���� ��������
@param fanoTree ������ ����
@param fMap_comp Map, �������� � ���� {������, ��� ��� ����} ��� ���������
@param fMap_comp Map, �������� � ���� {������, ��� ��� ����} ��� ������������
*/
class Fano {
private:
	int symbolNumber;//���������� ��������
	list<SymbolRate> SRate;//���� ��������
	Tree* fanoTree;//������ ����
	map<char, vector<int>>* fMap_comp;
	map<string, char>* fMap_decomp;

public:
	Fano();

	void compression(char* file_name);
	void decompression(char* comp_file_name, char* out_file_name);

	void create_tree();
	void create_map_comp();
	void create_map_decomp();
	void symbol_sort();
	void comp_add_symbol(char);
	void pred_compression(ofstream& outf);
	void file_compression(ifstream& inf, ofstream& outf);
	void decomp_add_symbol(ifstream& inf);
	void file_decompression(ifstream& inf, ofstream& outf);
	char my_find(string& vec, int& vec_it);

	~Fano();
};


