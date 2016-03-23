#include <iostream>
#include <string>
#include "MaxHeap.h"
#include <fstream>


using namespace std;

int main() {
	fstream fin;
	string tempString;
	int tempInt;
	MaxHeap *Heap;
	bool created = false;


	fin.open("SortedWords.txt");

	while (!fin.eof()) {
		fin >> tempString;

		if (!created) {
			//Create the initial array size from the first line of the file, then skip during any other time in the loop
			Heap = new MaxHeap((stoi(tempString) + 1));
			created = true;
			continue;
		}

		fin >> tempInt;

		Element *temp = new Element(tempString, tempInt);

		(*Heap).Insert(*temp);

	}

	fin.close();


	return 0;

}