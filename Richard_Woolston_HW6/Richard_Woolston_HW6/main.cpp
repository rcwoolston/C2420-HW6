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
	bool done = false;
	char choice;

	fin.open("SortedWords.txt");

	fin >> tempString;

	//Create the initial array size from the first line of the file, then skip during any other time in the loop
	Heap = new MaxHeap(stoi(tempString));


	while (!fin.eof() &&(here<test)) {
		fin >> tempString;
		fin >> tempInt;

		Element *temp = new Element(tempString, tempInt);

		(*Heap).Insert(*temp);
		here++;
	}

	//fin.close();

	(*Heap).PrintHeap();

	while (false) {
		Element temp = (*Heap).DeleteMax();

		cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;

		(*Heap).PrintHeap();
	}

	fin.seekg(0);
	fin >> tempString;

	cout << endl << endl<<"DRIVER CODE" << endl;
	cout << endl << "Creating Instance";
	MaxHeap *DriverHeap = new MaxHeap(7);
	(*DriverHeap).PrintHeap();
	cout << endl<<"Inserting 7 examples";
	here = 0;
	while (here < 7) {
		fin >> tempString;
		fin >> tempInt;

		Element *temp = new Element(tempString, tempInt);

		(*DriverHeap).Insert(*temp);
		(*DriverHeap).PrintHeap();
		here++;
	}

	cout << endl << "Delete Max";
	Element temp = (*DriverHeap).DeleteMax();
	cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;
	(*DriverHeap).PrintHeap();
	cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;
	(*DriverHeap).PrintHeap();
	cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;
	(*DriverHeap).PrintHeap();

	cout << endl << "Find Top Matches: " << endl;
	tempString = "a";
	Element *TempFind = (*DriverHeap).FindTopMatches(2, tempString);
	int i = 0;
	while (i < 2) {
		cout<<(*(TempFind + i)).word;
		i++;
	}

	//Main Driver section
	while (!done) {

		cout << endl << endl << "MAIN MENU" << endl;
		cout << "S:  Search top words with one prefix or two prefixes " << endl;
		cout << "Q: Quit Search " << endl;
		cout << "E: Exit" << endl;
		cin >> choice;

		choice = toupper(choice);

		switch (choice)
		{
		case 'E':
			cout << endl << "Exiting" << endl;
			done = true;
			break;
		default: cout << endl << "Invalid choice" << endl;
			break;
		}

	}

	fin.close();

	return 0;
}

