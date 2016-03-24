#include <iostream>
#include <string>
#include "MaxHeap.h"
#include <fstream>
#include <vector>


using namespace std;

template<typename T, typename P>
T remove_if(T beg, T end, P pred)
{
	T dest = beg;
	for (T itr = beg; itr != end; ++itr)
		if (!pred(*itr))
			*(dest++) = *itr;
	return dest;
}

int main() {
	fstream fin;
	string tempString;
	int tempInt, test = 10, here = 0;
	MaxHeap *Heap;
	bool done = false;
	char choice;
	vector<string> prefixesVector;

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
	int driverSize = 15;

	cout << endl << endl<<"DRIVER CODE" << endl;
	cout << endl << "Creating Instance";
	MaxHeap *DriverHeap = new MaxHeap(driverSize);
	(*DriverHeap).PrintHeap();
	cout << endl<<"Inserting "<< driverSize<<" examples";
	here = 0;
	while (here < driverSize) {
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
	temp = (*DriverHeap).DeleteMax();
	cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;
	(*DriverHeap).PrintHeap();
	temp = (*DriverHeap).DeleteMax();
	cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;
	(*DriverHeap).PrintHeap();

	cout << endl << "Find Top Matches: " << endl;
	tempString = "a";
	cout << "Returning top 5 words with " << tempString << endl;
	Element *TempFind = (*DriverHeap).FindTopMatches(5, tempString);
	int i = 0;
	while (i < 5) {
		cout<<(*(TempFind + i)).word<<"  ";
		i++;
	}

	cout << endl;

	cout << endl << endl << "Testing constructor with list of elements: " << endl;
	MaxHeap *DriverHeap2 = new MaxHeap(TempFind, 5, 10);

	cout << endl << "Printing out new heaps values";
	(*DriverHeap2).PrintHeap();

	cout << endl << endl;
	tempString = "o";
	cout << "Returning top 3 words with " << tempString << endl;
	TempFind = (*DriverHeap).FindTopMatches(3, tempString);
	i = 0;
	while (i < 3) {
		cout << (*(TempFind + i)).word << "  ";
		i++;
	}

	cout << endl << "Delete Max";
	temp = (*DriverHeap).DeleteMax();
	cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;
	(*DriverHeap2).PrintHeap();
	temp = (*DriverHeap).DeleteMax();
	cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;
	(*DriverHeap2).PrintHeap();


	(*DriverHeap).PrintHeap();

	cout << endl << endl << "Merging Drivers Together" << endl;
	(*DriverHeap).Merge(*DriverHeap2);

	(*DriverHeap).PrintHeap();



	//Main Driver section
	while (!done) {
		string prefixes;
		int value;
		bool searching = true;
		cout << endl << endl << "MAIN MENU" << endl;
		cout << "S:  Search top words with one prefix or two prefixes " << endl;
		cout << "Q: Quit Search " << endl;
		cin >> choice;

		choice = toupper(choice);

		switch (choice)
		{
		case 'S': cout << endl << endl << "Please enter your prefix or prefixes:  ";
			cin >> prefixes;
			cout << endl << "How many do you want to return: ";
			cin >> tempInt;
			while (searching) {
				value = prefixes.find('&');
				if (value == -1) {
					prefixesVector.push_back(prefixes);
					searching = false;
				}
				else {
					prefixesVector.push_back(prefixes.substr(0, (value)));
					prefixes = prefixes.substr((value + 1),prefixes.length());
				}
			}
			here = 0;
			while (here < prefixesVector.size()) {
				tempString = prefixesVector[here];

				here++;
			}
			break;
		case 'Q':
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

