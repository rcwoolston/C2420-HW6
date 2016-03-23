#include <string>
#include <iostream>
#include "MaxHeap.h"

using namespace std;

MaxHeap::MaxHeap(int arraySize) {
	(*this).arraySize = (arraySize+1);
	heapSize = 0;

	H = new Element[(*this).arraySize];
}

MaxHeap::MaxHeap(Element *A, int heapSize, int arraySize) {

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
			Swap(H[i], H[parentIndex]);
			PercolateUp(parentIndex);
		}
		else if (H[parentIndex].weight == H[i].weight) {
			heapSize--;
		}
	}
}

Element MaxHeap::DeleteMax() {

	if (heapSize >= 1) {
		Element *temp = new Element();

		*temp = H[1];
		H[1] = H[heapSize];

		heapSize--;

		PercolateDown(1);

		return *temp;
	}
}

void MaxHeap::PercolateDown(int i) {

	int leftChildIndex = Left(i);
	int rightChildIndex = Right(i);
	
	if (leftChildIndex < heapSize && rightChildIndex <= heapSize) {
		
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
		cout <<endl<<"Last Word: " << H[i].word << "  Weight: " << H[i].weight << endl;
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

Element* MaxHeap::FindTopMatches(int count, string match) {
	Element* TopMatchs;
	TopMatchs = new Element[count];
	int here = 0, searchIndex=1;

	while (here < count && searchIndex <= heapSize) {
		int compareValue = H[searchIndex].word.find(match);
		if (compareValue == 0) {
			Element *temp = new Element(H[searchIndex].word, H[searchIndex].weight);
			*(TopMatchs + here) = *temp;
			here++;
		}
		searchIndex++;
	}

	return TopMatchs;
}

int MaxHeap::GetHeapSize() {
	return heapSize;
}

void MaxHeap::Merge(const MaxHeap &newHeap) {
	int newSize = (*this).arraySize + newHeap.arraySize;

	//Create the new array
	MaxHeap *MergedHeap = new MaxHeap(newSize);

	// Add already held objects;
	int here = 0;
	while (here < (*this).heapSize) {
		Element *temp = new Element((*this).H[here].word, (*this).H[here].weight);
		(*MergedHeap).Insert(*temp);
		here++;
	}

	//Add other heap
	here = 0;
	while (here < newHeap.heapSize) {
		Element *temp = new Element((*this).H[here].word, (*this).H[here].weight);
		(*MergedHeap).Insert(*temp);
		here++;
	}

	(*this).H = (*MergedHeap).H;
}
