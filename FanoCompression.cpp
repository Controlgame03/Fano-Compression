#include <iostream>
#include <fstream>
#include <string>
#include "Fano.h"
#include "MyExeption.h"
#include "BitBufferForCompress.h"
using namespace std;


/// Главная функция
/**
* Функция, где происходнят все вызовы остальных функций,
* формирование названия файла
@param file_name Имя файла, которое нужно считать
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
	
	for (unsigned char s = inFile.get(); !inFile.eof(); s = inFile.get()) { // добавление символов в list
		comp_add_symbol(s);
	}
	symbol_sort(); // сортировка listа по возраствнию

	create_tree(); // создание дерева Фано
	create_map_comp(); // создание map, где храниться символ - его эквивалентный
	//двоичный код по алгоритму Фано
	inFile.close();
	inFile.open(file_name, 'b');//открытие и закрытие файла,
	//для того чтобы заного считать файл

	pred_compression(outFile); //ввод в файл вывода дополнительной информации
	// для того, чтобы можно было потом раскодировать файл
	file_compression(inFile, outFile); //само кодирование файла
}


/// Метод добавления нового символа в list
/**
* Метод добавляет символ в list. Если символ уже был в liste,
* то увеличивается счетчик символа, если символа не было в liste,
* то добавляется новый узел с этим символом, счетчик приравнивается к 1
@param symbol Новый символ для добавления в list Символов
*/
void Fano::comp_add_symbol(char symbol) {
	symbolNumber++; //увеличиваем количество всех символов 
	for (list<SymbolRate>::iterator it = SRate.begin(); it != SRate.end(); it++) { //пробегаем по listy
		if (it->symbol == symbol) {// и если находим там новый символ
			it->frequancy++; // то просто увеличиваем счетчик этого символа на 1
			return;
		}
	}
	SymbolRate symbol_s;// если не находим, то создаем новый узел
	symbol_s.symbol = symbol;
	symbol_s.frequancy = ONE_ELEMENT;
	SRate.push_back(symbol_s);
}


/// Метод для записывания в выходной файл дополнительной информации
/**
* Записывает количество символов в исходном файле,
* количество уникальных символов в файле, и следом через пробел записывает символ
* и сколько раз он встречается в файле
@param outf Выходной файл
*/
void Fano::pred_compression(ofstream& outf) {
	outf << (symbolNumber) << '\n';
	outf << (SRate.size()) << '\n';

	for (list<SymbolRate>::iterator it = SRate.begin(); it != SRate.end(); it++) {
		outf << it->symbol << (it->frequancy) << '\n';
	}
}

/// Функция для кодирования файла
/**
* Считываем символ из файла потом находим его двоичный эквивалент в
* mapе, после этого найденное значение добавляем в специальный buffer.
* Он при достижении определенного количества символов преобразует последовательность
* 0 и 1 в один символ и запишет в файл. После считываения вызываем функцию,
* которая очистит буффер
@param inf Файл для чтения
@param outf Файл для записи
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