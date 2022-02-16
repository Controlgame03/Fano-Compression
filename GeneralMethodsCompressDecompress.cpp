#include "Fano.h"
#include "FanoTree.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;


/// Метод для сортировки символов в таблице символов
/**
* Метод вызывает стандартную функцию сортировки для lista
*/
void Fano::symbol_sort() {
	SRate.sort();
}


/// Оператор < для двух символов
/**
* Сравнение происходит по частоте встречаемости символа в файле
@param a Первый символ
@param b Второй символ
@return Возвращается 0, если a > b. Возвращается 1, если a < b.
*/
bool operator<(SymbolRate& a, SymbolRate& b) {
	return a.frequancy < b.frequancy;
}


/// Конструктор для главного класса
Fano::Fano() {
	symbolNumber = 0;
	fanoTree = new Tree;
}


/// Функция для создания map, где храняться символы и их эквиваленты
/**
* Функция вызывает одноименную функцию в Tree
*/
void Fano::create_map_comp() {
	fanoTree->create_map_comp(fanoTree->get_start_node());
	fMap_comp = fanoTree->get_map_comp();
}
/// Функция для создания map, где храняться символы и их эквиваленты
/**
* Функция вызывает одноименную функцию в Tree
*/
void Fano::create_map_decomp() {
	fanoTree->create_map_decomp(fanoTree->get_start_node());
	fMap_decomp = fanoTree->get_map_decomp();
}

/// Метод, заполняет map символами и их двоичнами эквивалентами кодирования
/**
* Метод работает рекурсивно. На каждой глубине проверяется не является
* ли текущая вершина листом дерева (то есть содержит ли в себе символ) или
* посредственной вершиной с значением -1. Если это посредственная вершина, то сначала
* добавляется 0 в буфер кодов (vector<int>) и рассматривается левая вершина, то
* есть вызывается рекурсивно функция для левой вершины. После заполнения всех вершин,
* прародителем которого является левая вершина "0" удаляется из буфера и добавляется
* "1". После этого рассматриваются все вершины прародителем которых является правая вершина
* После заполнения всех символов являющихся детями этого узла, функция заканчивается
* и переходит на глкбину на 1 выше этой. Если узел является листом дерева, то для него
* фиксируется текущее значение буфера и это и станет кодом этого символа. Первое добавление в
* map создает само map и после этого надобность в создании map исчезает, поэтому здесь
* используется flag, который позволяет только один раз создавать map
@param position Текущий узел, который нужно рассмотреть
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

/// Метод для создания дерева Фано
/**
* Вызывает функцию для создания дерева в классе Tree
*/
void Fano::create_tree() {
	fanoTree->create_tree_main(SRate);
}


/// Деструктор
Fano::~Fano() {
	delete fanoTree;
}