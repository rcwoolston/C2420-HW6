#include <iostream>
#include <string>
#include "MaxHeap.h"
#include <fstream>


using namespace std;

int main() {
	fstream fin;
	string tempString;
	int tempInt, test = 10, here = 0;
	MaxHeap *Heap;

	fin.open("SortedWords.txt");

	fin >> tempString;

	//Create the initial array size from the first line of the file, then skip during any other time in the loop
	Heap = new MaxHeap((stoi(tempString) + 1));


	while (!fin.eof() &&(here<test)) {
		fin >> tempString;
		fin >> tempInt;

		Element *temp = new Element(tempString, tempInt);

		(*Heap).Insert(*temp);
		here++;
	}

	fin.close();

	(*Heap).PrintHeap();


	//Element temp = (*Heap).DeleteMax();

	(*Heap).PrintHeap();

	return 0;

}