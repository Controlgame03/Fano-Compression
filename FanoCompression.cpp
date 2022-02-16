#include <iostream>
#include <fstream>
#include <string>
#include "Fano.h"
#include "MyExeption.h"
#include "BitBufferForCompress.h"
using namespace std;


/// ������� �������
/**
* �������, ��� ����������� ��� ������ ��������� �������,
* ������������ �������� �����
@param file_name ��� �����, ������� ����� �������
*/
void Fano::compression(char* file_name) {
	ifstream inFile(file_name, 'b');
	if (!inFile.is_open()) {
		throw File_not_found(file_name);
	}
	string out_file_name;
	int i;
	for (i = 0; file_name[i] != '.'; i++) {
		out_file_name.push_back(file_name[i]);
	}
	for (char tmp[10] = ".fano", i = 0; tmp[i] != '\0'; i++) {
		out_file_name.push_back(tmp[i]);
	}
	
	ofstream outFile(out_file_name);
	

	outFile.close();
	outFile.open(out_file_name, 'b');
	
	for (unsigned char s = inFile.get(); !inFile.eof(); s = inFile.get()) { // ���������� �������� � list
		comp_add_symbol(s);
	}
	symbol_sort(); // ���������� list� �� �����������

	create_tree(); // �������� ������ ����
	create_map_comp(); // �������� map, ��� ��������� ������ - ��� �������������
	//�������� ��� �� ��������� ����
	inFile.close();
	inFile.open(file_name, 'b');//�������� � �������� �����,
	//��� ���� ����� ������ ������� ����

	pred_compression(outFile); //���� � ���� ������ �������������� ����������
	// ��� ����, ����� ����� ���� ����� ������������� ����
	file_compression(inFile, outFile); //���� ����������� �����
}


/// ����� ���������� ������ ������� � list
/**
* ����� ��������� ������ � list. ���� ������ ��� ��� � liste,
* �� ������������� ������� �������, ���� ������� �� ���� � liste,
* �� ����������� ����� ���� � ���� ��������, ������� �������������� � 1
@param symbol ����� ������ ��� ���������� � list ��������
*/
void Fano::comp_add_symbol(char symbol) {
	symbolNumber++; //����������� ���������� ���� �������� 
	for (list<SymbolRate>::iterator it = SRate.begin(); it != SRate.end(); it++) { //��������� �� listy
		if (it->symbol == symbol) {// � ���� ������� ��� ����� ������
			it->frequancy++; // �� ������ ����������� ������� ����� ������� �� 1
			return;
		}
	}
	SymbolRate symbol_s;// ���� �� �������, �� ������� ����� ����
	symbol_s.symbol = symbol;
	symbol_s.frequancy = ONE_ELEMENT;
	SRate.push_back(symbol_s);
}


/// ����� ��� ����������� � �������� ���� �������������� ����������
/**
* ���������� ���������� �������� � �������� �����,
* ���������� ���������� �������� � �����, � ������ ����� ������ ���������� ������
* � ������� ��� �� ����������� � �����
@param outf �������� ����
*/
void Fano::pred_compression(ofstream& outf) {
	outf << (symbolNumber) << '\n';
	outf << (SRate.size()) << '\n';

	for (list<SymbolRate>::iterator it = SRate.begin(); it != SRate.end(); it++) {
		outf << it->symbol << (it->frequancy) << '\n';
	}
}

/// ������� ��� ����������� �����
/**
* ��������� ������ �� ����� ����� ������� ��� �������� ���������� �
* map�, ����� ����� ��������� �������� ��������� � ����������� buffer.
* �� ��� ���������� ������������� ���������� �������� ����������� ������������������
* 0 � 1 � ���� ������ � ������� � ����. ����� ����������� �������� �������,
* ������� ������� ������
@param inf ���� ��� ������
@param outf ���� ��� ������
*/
void Fano::file_compression(ifstream& inf, ofstream& outf) {
	unsigned char a;
	//vector<char> buf;
	Buffer_comp buffr;
	a = inf.get();
	while (!inf.eof()) {
		map<char, vector<int>>::iterator simv = fMap_comp->find(a);
		buffr.push_for_compress(outf, simv->second);
		a = inf.get();
	}
	buffr.clean(outf);
}