#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list), current(list.head) {
	// Implementation
}

void ListIterator::first(){
	// Implementation
	this->current = list.head;
}

void ListIterator::next(){
	// Implementation
	if (this->valid())
	{
		this->current = this->current->getNext();
	}
	else
	{
		throw std::exception("Invalid position of iterator");
	}
}

bool ListIterator::valid() const{
	// Implementation
	if (this->current == nullptr)
		return false;
	int positionOfElement = this->list.search(this->current->getValueOfElement());
	return positionOfElement < this->list.sizeOfList;
}

TComp ListIterator::getCurrent() const{
	// Implementation
	return this->current->getValueOfElement();
}


