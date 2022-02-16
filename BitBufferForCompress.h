#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define BUFBAYT 512
#define BAYT 8
/// Класс, который записывает в файл символы
/**
* Принимает двоичные эквиваленты символов которые нужно
* записать в файл. Накапливает их и когда буффер заполняется
* записывает в файл, преобразовав первые 8 intов из буффера
* в один символ.
*/
class Buffer_comp {
private:
	vector<int>* buf;
	int kod_numb = 0;
public:
	/// Конструктор
	Buffer_comp() {
		buf = new vector<int>;
	}

	/// Функция для добавления нового символа в буффер
	/**
	* Добавляет новый символ (последовательность нулей и единиц) в буффер.
	* Если размер буффера станет больше чем константа BUFBAYT, то
	* вызывается функция записи в файл recording
	@param outf Файл для записи
	@param vec Код символа, которого нужно добавить в буффер
	*/
	void push_for_compress(ofstream& outf, vector<int>& vec) {
		for (int i = 0; i < vec.size(); i++) {
			if (buf->size() > BUFBAYT) {
				recording(outf);
			}
			buf->push_back(vec[i]);
		}
	}
	/// Функция очищения буффера
	/**
	*Очищает буффер. Добавляет нули на недостающие до
	* кратного 8 размеру буффера и записывает все символы в файл
	@outf Выходной файл
	*/
	void clean(ofstream& outf) {
		int finish = BAYT - (buf->size() % BAYT);
		for (int i = 0; i < finish; i++) {
			buf->push_back(0);
		}
		while (buf->size() != 0) {
			unsigned char simv = 0;
			for (int i = 0; i < BAYT; i++) {
				int tmp = (*buf)[0];
				tmp = tmp << (BAYT - i - 1);
				simv = (unsigned char)tmp | simv;
				buf->erase(buf->begin());
			}

			outf << simv;
			kod_numb++;

		}

	}
	/// Функция записи в файл
	/**
	* Записывает в файл символы, предварительно сформировав их из
	* превых 8 intов буффера. Формирует их благодаря сдвигу и маске.
	@param outf Выходной файл
	*/
	void recording(ofstream& outf) {
		int a;
		while ((a = (buf->size() - BUFBAYT)) > 0) {
			unsigned char simv = 0;
			for (int i = 0; i < BAYT; i++) {
				int tmp = (*buf)[0];
				tmp = tmp << (BAYT - i - 1);
				simv = (unsigned char)tmp | simv;
				buf->erase(buf->begin());
			}

			outf << simv;
			kod_numb++;
		}
	}
	/// Функция которая возващает kod_numb
	int getNumb() {
		return kod_numb;
	}
};