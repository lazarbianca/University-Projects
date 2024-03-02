#include <exception>
#include <iostream>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

BagIterator::BagIterator(const Bag& c): bag(c)
{
	//TODO - Implementation
	this->current = 1;
	this->count = 1;
}
//the first position we start from (should be 1)
//Theta(1)

void BagIterator::first() {
	//TODO - Implementation
	this->current = 1;
	this->count = 1;
}
//Theta(1)

void BagIterator::next() {
	//TODO - Implementation
	if (this->current <= this->bag.length)
	{
		if (this->bag.frequency[this->current] <= this->count)
			// FIXIT! How do i make sure i went through current element all frequency[i] number of times??
			// Modified; added a private var for count
		{
			this->current++;
			this->count = 0;
			//continue; stay on current element
		}
		//else
		//{
			this->count++;
		//}
	}
	else
		throw exception();
}
// 1 2 3
// 2 1 2
// 2 1 1

int BagIterator::getCount() {
	return this->count;
}
int BagIterator::getFrequency() {
	return this->bag.frequency[this->current];
}

bool BagIterator::valid() const {
	//TODO - Implementation
	if (this->current <= this->bag.length)
		return true;
	else
		return false;
}
//Theta(1)


TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
	if (this->valid())
	{
		return this->bag.elements[this->current];
	}
	else
		throw exception();
}
//Theta(1)
