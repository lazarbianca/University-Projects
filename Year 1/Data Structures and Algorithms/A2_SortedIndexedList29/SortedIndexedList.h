#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

class SortedIndexedList {
private:
	friend class ListIterator;
	friend class Node;
private:
	class Node {
		TComp element;
		Node* previous;
		Node* next;
	public:
		//default constructor
		Node() :element(NULL_TCOMP), previous(nullptr), next(nullptr) {}

		//parametrised constructor
		Node(TComp givenElement) {
			this->element = givenElement;
			this->previous = nullptr;
			this->next = nullptr;
		}

		TComp getValueOfElement()
		{
			return this->element;
		}

		Node* getPrevious()
		{
			return this->previous;
		}

		Node* getNext()
		{
			return this->next;
		}

		void setPrev(Node* prevNode)
		{
			this->previous = prevNode;
		}

		void setNext(Node* nextNode)
		{
			this->next = nextNode;
		}

		void setValue(TComp newValue)
		{
			this->element = newValue;
		}

	};
	//Representation
	Node* head;
	Node* tail;
	int sizeOfList;
	Relation relation;

public:

	//removes every kth element from the SortedList. If the SortedList contains less than k elements, it is not changes 
	//returns the number of removed elements
	//throws an exception if k is negative or 0 
	int removeFromKtoK(int k);

	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element in the sortedList (to the corresponding position)
	void add(TComp e);

	//Node* findPositionOfInsertion(TComp elem);


	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();

};
