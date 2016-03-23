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
			//Element *temp = new Element();
			//*temp = H[parentIndex];
			//H[parentIndex] = H[i];
			//H[i] = *temp;
			Swap(H[i], H[parentIndex]);
			PercolateUp(parentIndex);
		}
		else if (H[parentIndex].weight == H[i].weight) {
			heapSize--;
		}
	}
}

Element MaxHeap::DeleteMax() {
	Element *temp = new Element();

	*temp = H[1];
	H[1] = H[heapSize];
	
	heapSize--;

	PercolateDown(1);

	return *temp;
}

void MaxHeap::PercolateDown(int i) {
	
	if (i < heapSize) {
		int leftChildIndex = Left(i);
		int rightChildIndex = Right(i);

		//Weight of the current index is smaller then both children
		if (H[leftChildIndex].weight > H[i].weight && H[rightChildIndex].weight > H[i].weight) {
			//Find out which child is larger
			//Is left child larger
			if (H[leftChildIndex].weight > H[rightChildIndex].weight) {
				Swap(H[i], H[leftChildIndex]);
				PercolateDown(leftChildIndex);
			}
			else { //Right child is larger
				Swap(H[i], H[rightChildIndex]);
				PercolateDown(rightChildIndex);
			}
		}
		else { // Test to see if one of the childermn is larger
			if (H[leftChildIndex].weight > H[i].weight) {
				Swap(H[i], H[leftChildIndex]);
				PercolateDown(leftChildIndex);
			}
			else if (H[rightChildIndex].weight > H[i].weight) {
				Swap(H[i], H[rightChildIndex]);
				PercolateDown(rightChildIndex);
			}
		}
	}
	else {
		system("pause");
	}

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

void MaxHeap::Swap(Element &a, Element &b) {
	Element *temp = new Element();
	*temp = a;
	a = b;
	b = *temp;
}
