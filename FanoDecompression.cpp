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


/// Главная функция
/**
* Функция, где происходнят все вызовы остальных функций,
* формирование названия файла
@param file_name Имя файла, которое нужно считать
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

	decomp_add_symbol(inFile); // считывание символов

	symbol_sort();
	create_tree();
	create_map_decomp();
	

	file_decompression(inFile, outFile);
}

/// Метод, считывающий файл
/**
* Метод, считывающий символы.Сперва считывается количесво всех
* символов. Потом считывается количество уникальных символов.
* После этого происходит считывание {символ, количество его в файле}
@param inf Файл, откуда считываем символы
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

/// Функция для разархивирования файла
/**
* Считываем символы из файла в Buffer.
* После этого находим символ соответствующий
* первым n символам из Buffer-a и вставляем его
* в выходной файл
@param inf Файл для чтения
@param outf Файл для записи
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
	for (int i = 0; (i < symbolNumber) && (vec->size() >= 8); i++) {//счетчик символов
		a = my_find(*vec, vec_it);
		outf << a;
	}
}


/// Функция нахождения элемента по коду
/**
* Функция находит такой символ из map,
* код которого равен символам из Buffer, начиная из
* Buffer[vec_it]. 
@param vec Buffer для чтения
@param vec_it Указатель на позицию в Buffer
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