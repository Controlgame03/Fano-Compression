#include <iostream>
#include <fstream>
#include "Fano.h"
#include "Windows.h"
#include "MyExeption.h"
using namespace std;


int main(int argc, char* argv[]) {
	try {
		setlocale(LC_ALL, "Russian");
		Fano fano;
		if (argv[1][0] == 'c') {
			fano.compression(argv[2]);
		}
		else if (argv[1][0] == 'd') {
			fano.decompression(argv[2], argv[3]);
		}
		else {
			throw Command_not_recognized();
		}
		return 0;
	}
	catch (Command_not_recognized) {
		cout << "Command not recognized" << '\n';
		cout << "Example format: \nKURSOVAYA.exe decompress test.fano test_arch.bmp";

	}
	catch (File_not_found a) {
		cout << '"' << a.file_name << '"' << "is not found";
	}
	
}