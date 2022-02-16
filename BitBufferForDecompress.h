#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
class Buffer_decomp {
private:
	string* buf;
public:
	/// �����������
	Buffer_decomp() {
		buf = new string;
	}

	///  ������� ��� ���������� ������ ������� � ������
	/**
	* ��������� ����� ������ (������������������ ����� � ������) � ������,
	* ������������ ��� �� ����
	@param a C�����, �������� ����� �������� � ������
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
	/// ���������� ����� buf
	string* get_buf() {
		return buf;
	}
};
