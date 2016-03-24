#include <iostream>
#include <string>
#include "MaxHeap.h"
#include <fstream>
#include <vector>


using namespace std;

int BinarySearch(Element a[], int arraySize, string target);
int FindFirstIndex(Element a[], int arraySize, int foundIndex, string target);
int FindLastIndex(Element a[], int arraySize, int foundIndex, string target);

int main() {
	fstream fin;
	string tempString;
	int tempInt, test = 10, here = 0;
	bool done = false;
	char choice;
	vector<string> prefixesVector;

	fin.open("SortedWords.txt");

	fin >> tempString;

	//Create the initial array size from the first line of the file, then skip during any other time in the loop

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


	// Read in and create the array of elements
	fin.seekg(0);
	fin >> tempInt;
	Element *ElementArray = new Element[(tempInt+1)];

	int numOfRecords = tempInt+1;

	//Loop through and generate the array
	here = 0;
	while (!fin.eof() && here < numOfRecords) {
		fin >> tempString >> tempInt;

		Element* tempElement = new Element(tempString, tempInt);

		ElementArray[here] = *tempElement;

		here++;
	}

	//Main Driver section
	while (!done) {
		string prefixes;
		prefixesVector.clear();
		int value, first, last;
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
			value = BinarySearch(ElementArray, numOfRecords, prefixes);
			first = FindFirstIndex(ElementArray, numOfRecords, value, prefixes);
			last = FindLastIndex(ElementArray, numOfRecords, value, prefixes);
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

int BinarySearch(Element a[], int arraySize, string target) {
	bool found = false;

	int low = 0;
	int high = arraySize - 1;

	while (low <= high) {
		int mid = (low + high) / 2;

		if (0 < a[mid].word.substr(0,target.length()).compare(target)) {
			high = mid - 1;
		}
		else if (0 > a[mid].word.substr(0, target.length()).compare(target)) {
			low = mid + 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}
int FindFirstIndex(Element a[], int arraySize, int foundIndex, string target) {
	bool done = false;
	int searchIndex = foundIndex - 1;

	while (!done && searchIndex >= 0){
		if (a[searchIndex].word.substr(0,target.length()).compare(target) < 0) {
			done = true;
			return (searchIndex + 1);
		}
		searchIndex--;
	}

	return 0;
}

int FindLastIndex(Element a[], int arraySize, int foundIndex, string target) {
	bool done = false;
	int searchIndex = foundIndex + 1;

	while (!done && searchIndex < arraySize) {
		if (a[searchIndex].word.substr(0, target.length()).compare(target) < 0) {
			done = true;
			return (searchIndex - 1);
		}
		searchIndex++;
	}

	return 0;
}
