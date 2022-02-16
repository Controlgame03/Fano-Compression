#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define BUFBAYT 512
#define BAYT 8
/// �����, ������� ���������� � ���� �������
/**
* ��������� �������� ����������� �������� ������� �����
* �������� � ����. ����������� �� � ����� ������ �����������
* ���������� � ����, ������������ ������ 8 int�� �� �������
* � ���� ������.
*/
class Buffer_comp {
private:
	vector<int>* buf;
	int kod_numb = 0;
public:
	/// �����������
	Buffer_comp() {
		buf = new vector<int>;
	}

	/// ������� ��� ���������� ������ ������� � ������
	/**
	* ��������� ����� ������ (������������������ ����� � ������) � ������.
	* ���� ������ ������� ������ ������ ��� ��������� BUFBAYT, ��
	* ���������� ������� ������ � ���� recording
	@param outf ���� ��� ������
	@param vec ��� �������, �������� ����� �������� � ������
	*/
	void push_for_compress(ofstream& outf, vector<int>& vec) {
		for (int i = 0; i < vec.size(); i++) {
			if (buf->size() > BUFBAYT) {
				recording(outf);
			}
			buf->push_back(vec[i]);
		}
	}
	/// ������� �������� �������
	/**
	*������� ������. ��������� ���� �� ����������� ��
	* �������� 8 ������� ������� � ���������� ��� ������� � ����
	@outf �������� ����
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
	/// ������� ������ � ����
	/**
	* ���������� � ���� �������, �������������� ����������� �� ��
	* ������ 8 int�� �������. ��������� �� ��������� ������ � �����.
	@param outf �������� ����
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
	/// ������� ������� ��������� kod_numb
	int getNumb() {
		return kod_numb;
	}
};