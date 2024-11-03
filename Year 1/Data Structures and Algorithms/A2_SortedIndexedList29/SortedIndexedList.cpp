#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

int SortedIndexedList::removeFromKtoK(int k)
{
	int numberOfRemovedElements = 0;
	if (k < 0 || k == 0)
		throw std::exception("K should not be negative or zero");
	else
	{
		if (this->sizeOfList >= k)
		{
			while (k * numberOfRemovedElements - numberOfRemovedElements < this->sizeOfList)
			{
				//cout << k * numberOfRemovedElements - numberOfRemovedElements<<" ";
				this->remove(k * numberOfRemovedElements - numberOfRemovedElements);
				numberOfRemovedElements++;
			}
		}
		// else, nothing is changed
	}
	return numberOfRemovedElements;
}
//

SortedIndexedList::SortedIndexedList(Relation r) : head(nullptr), tail(nullptr), sizeOfList(0), relation(r)
//Implementation
{}

int SortedIndexedList::size() const {
	// Implementation
	return this->sizeOfList;
}
//O(1)

bool SortedIndexedList::isEmpty() const {
	// Implementation
	return this->sizeOfList == 0;
}
//O(1)

TComp SortedIndexedList::getElement(int i) const{
	// Implementation
	if (0 <= i && i < this->sizeOfList)
	{
		Node* current_element = this->head; // checked if head is null
		for (int pos = 0; pos < i; pos++)
		{
			current_element = current_element->getNext();
		}
		return current_element->getValueOfElement();
	}
	else
	{
		throw std::exception("Position is invalid");
	}
}
// O(i)

TComp SortedIndexedList::remove(int i) {
	// Implementation
	if (0 <= i && i < this->sizeOfList)
	{
		if (this->sizeOfList == 1)
		{
			TComp value = this->head->getValueOfElement();
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
			this->sizeOfList = 0;
			return value;
		}
		if (i == 0) //first element is the one we want to remove
		{
			Node* current_element = this->head;
			Node* next_crt_element = current_element->getNext();
			this->head = next_crt_element;
			next_crt_element->setPrev(nullptr);
			TComp value = current_element->getValueOfElement();
			delete current_element;
			this->sizeOfList--;
			return value;
		}
		if (i == this->sizeOfList - 1)
		{
			Node* current_element = this->tail;
			Node* previous_crt_element = current_element->getPrevious();
			this->tail = previous_crt_element;
			previous_crt_element->setNext(nullptr);
			TComp value = current_element->getValueOfElement();
			delete current_element;
			this->sizeOfList--;
			return value;
		}

		Node* current_element = this->head;
		for (int pos = 0; pos < i; pos++)
		{
			current_element = current_element->getNext();
		}
		Node* previous_crt_element = current_element->getPrevious();
		Node* next_crt_element = current_element->getNext();

		previous_crt_element->setNext(current_element->getNext());
		next_crt_element->setPrev(current_element->getPrevious());

		TComp value = current_element->getValueOfElement();
		delete current_element;
		this->sizeOfList--;
		return value;
	}
	else
	{
		throw std::exception("Position is invalid");
	}
}
// BC(i==0): Theta(1), WC(element before tail): Theta(this->sizeOfList-1) =>  Total case: Theta(this->sizeOfList-1)

int SortedIndexedList::search(TComp e) const {
	// Implementation
	Node* current_element = this->head;
	for (int pos = 0; pos < this->sizeOfList; pos++)
	{
		if (current_element != nullptr)
		{
			if (current_element->getValueOfElement() == e)
			{
				return pos;
			}
			current_element = current_element->getNext();

		}
	}
	return -1;
}
// BC(searched elem is on pos=0): Theta(1), WC: this->sizeOfList-1 => Total case: Theta(this->sizeOfList-1)

void SortedIndexedList::add(TComp e) {
	// Implementation

	// Create a new node with the given element
	Node* newNode = new Node(e);

	// If the list is empty, add the new node as the head and tail
	if (this->sizeOfList == 0) {
		

		this->head = newNode;
		this->tail = newNode;
		this->sizeOfList = 1;
		return;
	}

	// If the element should be inserted at the beginning of the list
	if (relation(e, this->head->getValueOfElement())) {
		newNode->setNext(head);
		this->head->setPrev(newNode);
		this->head = newNode;
		this->sizeOfList++;
		return;
	}

	// If the element should be inserted at the end of the list
	if (relation(this->tail->getValueOfElement(), e)) {
		this->tail->setNext(newNode);
		newNode->setPrev(this->tail);
		this->tail = newNode;
		this->sizeOfList++;
		return;
	}

	// If the element should be inserted in the middle of the list
	Node* currentNode = this->head->getNext();
	while (currentNode != nullptr) {
		if (relation(e, currentNode->getValueOfElement())) {
			newNode->setNext(currentNode);
			newNode->setPrev(currentNode->getPrevious());
			currentNode->getPrevious()->setNext(newNode);
			currentNode->setPrev(newNode);
			this->sizeOfList++;
			return;
		}
		currentNode = currentNode->getNext();
	}
}
// BC(empty/firstPos/lastPos): Theta(1), WC: Theta(this->sizeOfList-1)  => Total case: O(this->sizeOfList-1)

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
	Node* current_element = this->head;

	while (this->head != nullptr) {
		this->head = current_element->getNext();
		delete current_element;
		current_element = this->head;
	}

	//for (int i = 0; i < this->sizeOfList-1; i++)
	//{
	//	if (current_element == nullptr)
	//		return;
	//	if (current_element->getNext() == nullptr)
	//	{
	//		delete current_element;  // the tail
	//	}
	//	else
	//	{
	//		current_element = current_element->getNext();
	//		delete current_element->getPrevious();
	//		current_element->setPrev(nullptr);
	//	}
	//}

}
// O(this->length)
