#pragma once

/// Класс для исключений
/**
* Класс вызывается когда неправильно вызвана программа
*/
class Command_not_recognized {

};

/// Класс для исключений
/**
* Класс вызывается, когда не найден файл 
*/
class File_not_found {
public:
	char* file_name;
	File_not_found(char* a) {
		file_name = a;
	}
};
