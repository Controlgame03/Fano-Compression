#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "Fano.h"
#include "BitBufferForDecompress.h"
#include "MyExeption.h"
using namespace std;


/// ������� �������
/**
* �������, ��� ����������� ��� ������ ��������� �������,
* ������������ �������� �����
@param file_name ��� �����, ������� ����� �������
*/
void Fano::decompression(char* comp_file_name, char* out_file_name) {

	ifstream inFile(comp_file_name, 'b');
	if (!inFile.is_open()) {
		throw File_not_found(comp_file_name);
	}
	ofstream outFile(out_file_name);
	if (!outFile.is_open()) {
		throw File_not_found(out_file_name);
	}
	outFile.close();
	outFile.open(out_file_name, 'b');

	decomp_add_symbol(inFile); // ���������� ��������

	symbol_sort();
	create_tree();
	create_map_decomp();
	

	file_decompression(inFile, outFile);
}

/// �����, ����������� ����
/**
* �����, ����������� �������.������ ����������� ��������� ����
* ��������. ����� ����������� ���������� ���������� ��������.
* ����� ����� ���������� ���������� {������, ���������� ��� � �����}
@param inf ����, ������ ��������� �������
*/
void Fano::decomp_add_symbol(ifstream& inf) {
	int size;

	inf.seekg(0, ios_base::beg);
	inf >> symbolNumber;
	inf >> size;

	int i = 0;
	inf.get();
	do {
		SymbolRate symbol;
		symbol.symbol = inf.get();
		inf >> symbol.frequancy;
		SRate.push_back(symbol);

		inf.get();
		i++;
	} while (i < size);
}

/// ������� ��� ���������������� �����
/**
* ��������� ������� �� ����� � Buffer.
* ����� ����� ������� ������ ���������������
* ������ n �������� �� Buffer-a � ��������� ���
* � �������� ����
@param inf ���� ��� ������
@param outf ���� ��� ������
*/
void Fano::file_decompression(ifstream& inf, ofstream& outf) {
	Buffer_decomp buffr;

	for (int i = 0; !inf.eof(); i++) {
		unsigned char symbol_t = inf.get();
		buffr.push(symbol_t);
	}
	string* vec = buffr.get_buf();
	unsigned char a;
	int vec_it = 0;
	for (int i = 0; (i < symbolNumber) && (vec->size() >= 8); i++) {//������� ��������
		a = my_find(*vec, vec_it);
		outf << a;
	}
}


/// ������� ���������� �������� �� ����
/**
* ������� ������� ����� ������ �� map,
* ��� �������� ����� �������� �� Buffer, ������� ��
* Buffer[vec_it]. 
@param vec Buffer ��� ������
@param vec_it ��������� �� ������� � Buffer
*/
char Fano::my_find(string& vec, int& vec_it) {
	string tmp;
	for (int i = vec_it; i < vec.size(); i++) {
		tmp.push_back(vec[i]);
		map<string, char>::iterator it = fMap_decomp->find(tmp);
		if ((it) != fMap_decomp->end()) {
			vec_it = vec_it + it->first.size();
			return it->second;
		}
	}
	return -1;
}