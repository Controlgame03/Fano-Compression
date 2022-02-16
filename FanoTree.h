#pragma once
#pragma once
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include "Fano.h"
using namespace std;

struct SymbolRate;

/// Класс для одного узла дерева
/**
* Хранит в себе -1 это этот узел посредственный,
* то есть он ведет к листу, где храниться символ.
* Хранит в себе символ, если этот узел основной
@param left Указатель на левый узел (левого сына)
@param right Указатель на правый узел (правого сына)
@param symbol Символ, который храниться в узле
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

	/// Метод, возвращающий символ, который храниться в этом узле 
	char getSymbol() {
		return symbol;
	}
	/// Метод, возвращающий левого сына этого узла
	Node* getLeft() {
		return left;
	}
	/// Метод, возвращающий правого сына этого узла
	Node* getRight() {
		return right;
	}
};

/// Класс дерева Фано
/**
* Дерево состоит из узлов, которые хранят либо символ (основные узлы),
* либо -1 (посредственные узлы). Класс из lista символов сначало преобразует
* в дерево Фано, а потом само дерево преобразует в map, где хранятся эквиваленты
* символов
@param start Адрес начального узла
@param fanoMap Map, где храниться {символ, его двоичный эквивалент Фано}
@param vec_create_map Буффер нужный для функции create_map
@param flag_create_map Флаг нужный для функции create_map
*/
class Tree {
private:
	Node* start;
	map<char, vector<int>>* fano_map_comp;
	map<string, char>* fano_map_decomp;
	vector<int> vec_create_map_comp; // буфер для рекурсии
	int flag_create_map = 0; // флаг для рекурсии. Нужен
	//для того чтобы создать сам map без использования еще одной функции
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
	/// Возвращает указатель на map
	map<char, vector<int>>* get_map_comp() {
		return fano_map_comp;
	}
	/// Возвращает указатель на map
	map<string, char>* get_map_decomp() {
		return fano_map_decomp;
	}

	~Tree();
};