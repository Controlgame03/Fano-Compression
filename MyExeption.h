#pragma once

/// ����� ��� ����������
/**
* ����� ���������� ����� ����������� ������� ���������
*/
class Command_not_recognized {

};

/// ����� ��� ����������
/**
* ����� ����������, ����� �� ������ ���� 
*/
class File_not_found {
public:
	char* file_name;
	File_not_found(char* a) {
		file_name = a;
	}
};
