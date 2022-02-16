#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
class Buffer_decomp {
private:
	string* buf;
public:
	/// Конструктор
	Buffer_decomp() {
		buf = new string;
	}

	///  Функция для добавления нового символа в буффер
	/**
	* Добавляет новый символ (последовательность нулей и единиц) в буффер,
	* раскладнывая его на биты
	@param a Cимвол, которого нужно добавить в буффер
	*/
	void push(unsigned char a) {
		unsigned char mask = 1;
		mask = mask << (BAYT - 1);
		for (int i = 0; i < BAYT; i++, mask = mask >> 1) {
			int tmp;
			tmp = (int)(mask & a);
			if (tmp > 0) {
				buf->push_back('1');
			}
			else if (tmp == 0) {
				buf->push_back('0');
			}

		}
	}
	/// Возвращает адрес buf
	string* get_buf() {
		return buf;
	}
};
