#pragma once
#include <string>

using namespace std;


class Element {
	string word;
	int priority;
	Element(string thisWord, int thisPriority) {
		word = thisWord;
		priority = thisPriority;
	}
};

