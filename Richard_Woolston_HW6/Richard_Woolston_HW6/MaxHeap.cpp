#include <string>
#include <iostream>
#include "MaxHeap.h"

using namespace std;

MaxHeap::MaxHeap(int arraySize) {
	arraySize = arraySize;
	heapSize = 0;

	H = new Element[arraySize];
}

void MaxHeap::Insert(const Element &a) {
	heapSize++;
	H[heapSize] = a;

	int i = heapSize;

	PercolateUp(i);
}

void MaxHeap::PercolateUp(int i) {
	int parentIndex;
	

	if (i != 1) {
		parentIndex = Parent(i);
		if (H[parentIndex].weight < H[i].weight) {
			Element *temp = new Element();
			*temp = H[parentIndex];
			H[parentIndex] = H[i];
			H[i] = *temp;
			PercolateUp(parentIndex);
		}
		else if (H[parentIndex].weight == H[i].weight) {
			heapSize--;
		}
	}
}

void MaxHeap::PercolateDown(int i) {

}

void MaxHeap::PrintHeap() {
	int hereIndex = 1;
	cout << endl << endl << "Printing Heap" << endl;
	while (hereIndex <= heapSize) {
		cout <<"Index: "<<hereIndex<< " Parent Index: "<< Parent(hereIndex) <<"  Word: " << H[hereIndex].word << "  Weight: " << H[hereIndex].weight << endl;
		hereIndex++;
	}
}

int MaxHeap::Parent(int i) {
	return (i / 2);
}

int MaxHeap::Left(int i) {
	return (i * 2);
}

int MaxHeap::Right(int i) {
	return ((i * 2) + 1);
}
