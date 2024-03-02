#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//TODO - Implementation
	this->capacity = 3;
	this->length = 0;
	this->elements = new TElem[this->capacity];
	this->frequency = new int[this->capacity];
}
// Theta(1)

void Bag::filter(Condition cond)
{
	for (int i = 1; i <= this->length; i++)
	{
		if (!cond(this->elements[i]))
		{
			remove(this->elements[i]);
			i--;
		}
	}
}
// Best case: (all elems respect the cond) Theta(this->length);  
// Worst case: (no elements respect cond) Theta(this->length^2)
// Total case: O(this->length^2)

void Bag::add(TElem elem) {
	//TODO - Implementation
	if (this->capacity == this->length)
		throw exception();
	bool found = false;
	for (int i = 1; i <= this->length; i++) {
		if (this->elements[i] == elem)
		{
			found = true;
			this->frequency[i]++;
			break;
		}
	}
	if(found == false)
	{
		this->length++;
		if (this->length == this->capacity)
		{
			//resize
			this->capacity = 2 * this->capacity;
			TElem* new_elems = new TElem[this->capacity];
			int* new_frequency = new int[this->capacity];

			for (int i = 1; i <= this->length; i++)		//FIXIT - POSSIBLE MISTAKE WITH i=0 and not i=1
			{
				new_elems[i] = this->elements[i];
				new_frequency[i] = this->frequency[i];
			}
			delete(this->elements);
			delete(this->frequency);
			this->elements = new_elems;
			this->frequency = new_frequency;
		}
		// add element
		this->elements[length] = elem;
		this->frequency[length] = 1;
	}
}
//Best case: Theta(1); Worst case: Theta(this->length); Total case: O(this->length)

bool Bag::remove(TElem elem) {
	//TODO - Implementation
	
	for (int i = 1; i <= this->length; i++) {
		if (this->elements[i] == elem)
		{
			if (this->frequency[i] == 1)
			{
				//remove element at position i
				//for (int j = i; j <= this->length-1; j++)   //-1
				//{
				//	this->elements[j] = this->elements[j + 1];
				//	this->frequency[j] = this->frequency[j + 1];
				//}
				this->elements[i] = this->elements[length];
				this->frequency[i] = this->frequency[length];
				this->length--;
				return true;
			}
			else
			{
				this->frequency[i]--;
				return true;
			}
		}
	}
	//the element we want to remove is not in the bag
	return false;
}
//Best case: Theta(this->length); Worst case: Theta(this->length)   (not ^2?)   ; Total case: Theta(this->length)

bool Bag::search(TElem elem) const {
	//TODO - Implementation
	for (int i = 1; i <= this->length; i++)
		if (this->elements[i] == elem)
			return true;
	return false; 
}
//Best case: Theta(1); Worst case: Theta(this->length); Total case: O(this->length)

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	for (int i = 1; i <= this->length; i++)
		if (this->elements[i] == elem)
			return this->frequency[i];
	return 0; 
}
//Best case: Theta(1); Worst case: Theta(this->length); Total case: O(this->length)

int Bag::size() const {
	//TODO - Implementation
	//the sum of all frequencies
	int sum = 0;
	for (int i = 1; i <= this->length; i++) {
		//cout << "element " <<i<<",  " << this->elements[i] << " frequency " << this->frequency[i] << '\n';
		sum += this->frequency[i];
	}
	return sum;
}
//Best case: Theta(this->length); Worst case: Theta(this->length); Total case: Theta(this->length)

bool Bag::isEmpty() const {
	//TODO - Implementation
	if (this->length == 0)
		return true;
	else
		return false;
}
//Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - Implementation
	
	//for (int i = 1; i <= this->length; i++)
		//delete(this->elements[i]);
	delete[] this->elements;
	delete[] this->frequency;
}
//Theta(1)
