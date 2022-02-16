#pragma once
#include <list>
#include <iostream>
#include <map>
#include <vector>
#include "FanoTree.h"

using namespace std;

#define ONE_ELEMENT 1

/// Структура, хранящая в себе {символ, его количество в файле}
/**
@param symbol Сам символ
@param frequancy Частота встречаемости символа в файле
*/
struct SymbolRate {
	char symbol;
	int frequancy;
};


/// Главный класс, который управляет всеми преобразованиями обьектов
/**
* Класс, который добавляет в list символы, из Listа формирует дерево и т.д.
* В конце концов управляет записью в файл получившихся кодов
@param symbolNumber количество символов
@param SRate лист символов
@param fanoTree Дерево Фано
@param fMap_comp Map, хранящий в себе {символ, его код Фано} для архивации
@param fMap_comp Map, хранящий в себе {символ, его код Фано} для разархивации
*/
class Fano {
private:
	int symbolNumber;//количество символов
	list<SymbolRate> SRate;//лист символов
	Tree* fanoTree;//дерево Фано
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


