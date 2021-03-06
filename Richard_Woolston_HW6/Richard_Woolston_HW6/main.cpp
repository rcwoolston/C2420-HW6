#include <iostream>
#include <string>
#include "MaxHeap.h"
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;

int BinarySearch(Element a[], int arraySize, string target);
int FindFirstIndex(Element a[], int arraySize, int foundIndex, string target);
int FindLastIndex(Element a[], int arraySize, int foundIndex, string target);
void CreateHeaps(Element a[], const vector<string> &searches,int numberOfReturns, int numOfRecords);

int main() {
	fstream fin;
	string tempString;
	int tempInt, test = 10, here = 0;
	bool done = false;
	char choice;

	fin.open("SortedWords.txt");

	fin >> tempString;

	//Create the initial array size from the first line of the file, then skip during any other time in the loop

	fin.seekg(0);
	fin >> tempString;
	int driverSize = 12;

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
	tempString = "ab";
	cout << "Returning top 4 words with " << tempString << endl;
	Element *TempFind = (*DriverHeap).FindTopMatches(4);
	int i = 0;
	while (i < 4) {
		cout<<(*(TempFind + i)).word<<"  ";
		i++;
	}

	cout << endl;

	cout << endl << endl << "Testing constructor with list of elements: " << endl;
	MaxHeap *DriverHeap2 = new MaxHeap(TempFind, 4, 5);

	cout << endl << "Printing out new heaps values";
	(*DriverHeap2).PrintHeap();

	cout << endl << endl;

	cout << endl << "Delete Max";
	temp = (*DriverHeap2).DeleteMax();
	cout << endl << "Removed Word: " << temp.word << "  Weight: " << temp.weight << endl;
	(*DriverHeap2).PrintHeap();

	cout << endl << endl << "Merging Drivers Together" << endl;
	//(*DriverHeap).Merge(*DriverHeap2);

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
	vector<string> prefixSearches;

	//Main Driver section
	while (!done) {
		string prefixes, holder;
		prefixSearches.clear();
		int value, first, last;
		bool searching = true, insert = false, splitting = true;
		int inputIndex = 0;
		cout << endl << endl << "MAIN MENU" << endl;
		cout << "S:  Search top words with one prefix or two prefixes " << endl;
		cout << "Q: Quit Search " << endl;
		cout << "CHOICE:  ";
		cin >> choice;

		choice = toupper(choice);

		switch (choice)
		{
		case 'S': cout << endl << endl << "Please enter your prefix or prefixes:  ";
			//cin >> prefixes;
			cin.ignore();
			std::getline(cin, prefixes);
			cout << "How many do you want to return: ";
			cin >> tempInt;

			while (splitting) {
				int space = prefixes.find_first_of(" ");
				int del = prefixes.find_first_of("&");
				if (space < del) {
					if (space > 0) {
						tempString = prefixes.substr(0, space);
						insert = true;
					}
				}
				else if (del < space) {
					if (del > 0) {
						tempString = prefixes.substr(0, del);
						insert = true;
					}
				}
				else if (space == -1 && del == -1) {
					insert = true;
					splitting = false;
					tempString = prefixes;
				}
				if (space == 0) {
					insert = false;
					holder.clear();
					here = 1;
					while (here < prefixes.length()) {
						holder.push_back(prefixes[here]);
						here++;
					}

					prefixes.clear();
					prefixes = holder;
				}
				else if (del == 0) {
					insert = false;
					holder.clear();
					here = 1;
					while (here < prefixes.length()) {
						holder.push_back(prefixes[here]);
						here++;
					}

					prefixes.clear();
					prefixes = holder;
				}
				if (tempString.compare(" ") != 0 && tempString.compare("&") != 0 && insert) {
					insert = false;
					prefixSearches.push_back(tempString);
					if (space != -1 && del != -1) {
						prefixes = prefixes.substr(tempString.length());
					}
				}
			}

			CreateHeaps(ElementArray, prefixSearches, tempInt,numOfRecords);

			break;
		case 'Q':
			cout << endl << "Exiting, Thank you for using autocomplete software developed by Richard Woolston" << endl;
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
		if (a[searchIndex].word.substr(0, target.length()).compare(target) > 0) {
			done = true;
			return (searchIndex - 1);
		}
		searchIndex++;
	}

	return 0;
}
void CreateHeaps(Element a[], const vector<string> &searches, int numberOfReturns, int numOfRecords) {
	int numOfPrefixes = searches.size(), position = 0, inputIndex = 0, here;
	Element *Subset, *insert;
	MaxHeap *Heap, *MergeHeap;
	bool valid = false, created = false;

	while (position < numOfPrefixes) {
		inputIndex = 0;
		int value = BinarySearch(a, numOfRecords, searches[position]);
		if (value == -1) {
			position++;
			if (!valid) {
				valid = false;
			}
			continue;
		}
		valid = true;
		int first = FindFirstIndex(a, numOfRecords, value, searches[position]);
		int last = FindLastIndex(a, numOfRecords, value, searches[position]);
		//Looping through to create insert
		Subset = new Element[(last - first)+1];
		here = first;
		while (here <= last) {
			insert = new Element();
			insert->word = a[here].word;
			insert->weight = a[here].weight;
			*(Subset + inputIndex) = *insert;
			inputIndex++;
			here++;
		}
		if (!created) {
			Heap = new MaxHeap(Subset, (last - first), ((last - first) + 1));
			created = true;
			//Heap->PrintHeap();
		}
		else {
			MergeHeap = new MaxHeap(Subset, (last - first), ((last - first) + 1));
			//Heap->PrintHeap();
			//MergeHeap->PrintHeap();
			Heap->Merge(*MergeHeap);
			//Heap->PrintHeap();
		}
		position++;
	}
	Subset = new Element[numberOfReturns];
	if (!valid) {
		cout << endl << endl << "No valid entries" << endl;
		return;
	}
	Subset = Heap->FindTopMatches(numberOfReturns);

	Heap = new MaxHeap(Subset, numberOfReturns, (numberOfReturns + 1));
	cout << endl << "Output for the prefixe(s)" << endl;
	Heap->FormattedPrinting();
}
