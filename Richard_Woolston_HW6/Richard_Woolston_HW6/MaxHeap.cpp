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
}

void MaxHeap::PercolateDown(int i) {

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
