#pragma once
#include "Fano.h"
#include "FanoTree.h"
/// Главная функция для создания дерева
/**
* Вызывает рекурсивную функцию для создания дерева
@param list_s Лист символов, из которых создается дерево Фано
@return Возвращается указатель на первую вершину
*/
Node* Tree::create_tree_main(list<SymbolRate>& list_s) {
	start = create_tree(list_s, list_s.begin(), list_s.end());
	return start;
}

/// Рекурсивная функция для создания дерева
/**
* Метод сперва делит лист по правилу Фано (чтобы суммарное
количество символов справа было примерно равным суммароному
количеству символов слева), в качестве еления выступает middle
вершина. После этого проверяется на то, чтобы в участке листа от
begin, до end был только один элемент. Если это так, то создается узел
с этим элементом, если нет, то рекурсивно вызывается сама же функция, но
только для левого [begin, middle) и правого [middle, end) частей lista
@param list_s Лист символов для создания дерева
@param begin Начало участка из которого нужно сделать дерево
@param end Конец участка из которого нужно сделать дерево
@return возвращвет один узел
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


/// Функция для подсчета количества встречаемости символов, которые входят в учаток [begun_s, end_s)
/**
@param begin_s Начало lista, c которого начинается участок для суммирования
@param end_s Конец участка для суммирования
@param list_s Сам list, откуда берутся символы
@return Возвращвет сумму количества всех символов на участке [begun_s, end_s)
*/
int Tree::which_amount(list<SymbolRate>::iterator begin_s, list<SymbolRate>::iterator end_s, list<SymbolRate>& list_s) {
	int amount = 0;
	while (begin_s != end_s) {
		amount += begin_s->frequancy;
		begin_s++;
	}

	return amount;
}



/// Функция для деления отсортированного lista по алгоритму Фано
/**
* Метод суммиует количество каждого символа начиная сначала, и сравнивает с оставшимися
* символами. То есть когда мы хотим в нашу сумму добавить еще один элемент мы смотрим, не
* превосходит ли сумма + следующий элемент количество непросуммированных элементов. Если не
* превосходит, то добавляем этот элемент в сумму. Если превосходит, то заканчиваем цикл
@param amount_s количество символов на участке [begun_s, end_s)
@param begin_s начало участка для деления
@param end_s конец участка для деления
@param list_s сам list, который мы делим
@return Возвращает итератор на средний элемент
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

/// Конструктор
Tree::Tree() {
	start = new Node;
}

/// Функция, возвращающая начало дерева
Node* Tree::get_start_node() {
	return start;
}

/// Деструктор
Tree::~Tree() {
	if (start != nullptr) {
		start->~Node();
	}
}

/// Конструктор для узла содержащего символ
/**
* Создает узел с символом s
@param l Левый узел
@param r Правый узел
@param s Символ
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

/// Конструкор для узла без символа(промежуточного узла)
/**
@param l Левый узел
@param r Правый узел
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

/// Конструкор по умолчанию
Node::Node() {
	left = nullptr;
	right = nullptr;
}

/// Оператор присваивания
Node& Node::operator=(Node& a) {
	symbol = a.symbol;
	left = a.left;
	right = a.right;

	return *this;
}
/// Конструктор копирования
Node::Node(Node& a) {
	left = a.left;
	right = a.right;
	symbol = a.symbol;
}
/// Деструктор
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