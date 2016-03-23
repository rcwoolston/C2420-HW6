#pragma once
#include <string>

using namespace std;


class Element {
public:
	string word;
	int weight;
	Element() {
		word = "";
		weight = -1;
	}
	Element(string thisWord, int thisWeight) {
		word = thisWord;
		weight = thisWeight;
	}

	int GetWeight() {
		return weight;
	}

};
class MaxHeap {
private:  int arraySize;      // the size of the array, index from 0 to array_size-1  
		  int heapSize ;       // number of elements in the heap; heapSize is smaller than arraySize  
		  Element * H ;       // elements of heap are in H[1]…H[heapSize], cell at index 0 is not used  
		  int Left(int i) ;      // return the index of the left child of node i  
		  int Right(int i) ;    // return the index of the right child of node i  
		  int Parent(int i) ;  // return the index of the parent of node i  
		  void PercolateDown(int) ;  // DownHeap method.  It will be called in MaxHeap and DeleteMax  

public:  MaxHeap(int arraySize = 30);  // Generate an empty heap with the default array size of 30. 
		 //MaxHeap(Element *A, int heapSize, int arraySize) ;  // A contains a sequence of elements 
		 //~MaxHeap() ;   
		 void Insert(const Element &a) ;   // Insert a new element containing word and its weight             
		 //Element DeleteMax();    // Find, return, and remove the element with the maximum weight  
		 //void PrintHeap();   // Print the heap in tree structure; each node containing word and weight  
		 //void Merge(const MaxHeap &newHeap) ;  // Merge with another heap to form a larger heap  
		 //Element * FindTopMatches(int count) ;  // return top “count” matching words based on weights
};

