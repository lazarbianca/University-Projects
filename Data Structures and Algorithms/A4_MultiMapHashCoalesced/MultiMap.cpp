#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

int hashFunction(int mapCapacity ,TKey currentKey)
{
	return abs(currentKey) % mapCapacity;
}

void MultiMap::resize()
{
	int newMapCapacity = 2 * mapCapacity;
	TElem* newElems = new TElem[newMapCapacity]();
	int* newNext = new int[newMapCapacity]();
	this->mapCapacity = newMapCapacity;
	for (int i = 0; i < this->mapCapacity; i++)
	{
		newElems[i] = NULL_TELEM;
		newNext[i] = NULL_TVALUE;
	}
	int newFirstFree = 0;
	h = &hashFunction;

	for (int i = 0; i < mapSize - 1; i++) {
		int positionToAdd = this->h(this->mapCapacity, this->elements[i].first);
		// check if the position is taken
		if (newElems[positionToAdd].first != NULL_TVALUE)
		{
			newElems[newFirstFree].first = this->elements[i].first;
			newElems[newFirstFree].second = this->elements[i].second;
			// find which key to link to (through the next array)
			while (newNext[positionToAdd] != NULL_TVALUE)
			{
				positionToAdd = newNext[positionToAdd];  // this->next[positionToAdd];
			}
			newNext[positionToAdd] = newFirstFree;
			// find the next free position
			newFirstFree++;
			while (newElems[newFirstFree].first != NULL_TVALUE)
				newFirstFree++;
		}
		else
		{
			// position is free
			newElems[positionToAdd].first = this->elements[i].first;
			newElems[positionToAdd].second = this->elements[i].second;
			if (newFirstFree == positionToAdd)
			{
				newFirstFree++;
				while (newElems[newFirstFree].first != NULL_TVALUE)
					newFirstFree++;
			}
		}
	}
	this->elements = newElems;
	this->next = newNext;
	this->firstFree = newFirstFree;
	//cout << "	Done resizing\n";
	//delete[] newElems;
	//delete[] newNext;
}
// Theta(mapCapacity)


TKey MultiMap::maxKey() const
{
	TKey maxValue = NULL_TKEY;
	MultiMapIterator it = this->iterator();
	while (it.valid())
	{
		if (it.getCurrent().first > maxValue)
		{
			maxValue = it.getCurrent().first;
		}
		it.next();
	}
	return maxValue;
}
// Theta(mapSize)


MultiMap::MultiMap() {
	// Implementation
	mapCapacity = 10;
	mapSize = 0;
	elements = new TElem[mapCapacity]();
	next = new int[mapCapacity]();
	h = &hashFunction;
	for (int i = 0; i < this->mapCapacity; i++)
	{
		this->elements[i] = NULL_TELEM;
		this->next[i] = NULL_TVALUE;
	}
	firstFree = 0;
}
// Theta(mapCapacity)


void MultiMap::add(TKey c, TValue v) {
	// Implementation
	int positionToAdd = this->h(this->mapCapacity, c);
	this->mapSize++;
	// check if the position is taken
	if (this->elements[positionToAdd].first != NULL_TVALUE)
	{
		if (mapSize > mapCapacity)
		{
			//resize and rehash
			resize();
		}
		// position is not free
		this->elements[firstFree].first = c;
		this->elements[firstFree].second = v;
		// find which key to link to (through the next array)
		while (this->next[positionToAdd] != NULL_TVALUE)
		{
			positionToAdd = this->next[positionToAdd];
		}
		this->next[positionToAdd] = firstFree;
		// find the next free position
		if (mapCapacity == mapSize)
		{
			firstFree = mapSize;
		}
		else {
			firstFree++;
			while (this->elements[firstFree].first != NULL_TVALUE)
				firstFree++;
		}
	}
	else
	{
		// position is free
		this->elements[positionToAdd].first = c;
		this->elements[positionToAdd].second = v;
		if (mapCapacity == mapSize)
		{
			firstFree = mapSize;
		}
		else {
			if (firstFree == positionToAdd)
			{
				firstFree++;
				while (this->elements[firstFree].first != NULL_TVALUE)
					firstFree++;
			}
		}
	}
}
// Best case: Theta(1),					Worst case: Theta(mapCapacity)			Total case: O(mapCapacity)
// when the hashed position is free; when map is full, h(k)=0 and every k key has k+1 as next


bool MultiMap::remove(TKey c, TValue v) {
	// Implementation
	int i = this->h(this->mapCapacity, c);
	int j = NULL_TVALUE;	  // previous node of i
	// find the key to be removed and its previous
	while (i != NULL_TVALUE && (this->elements[i].first != c || this->elements[i].second != v))
	{
		j = i;
		i = this->next[i];
	}
	if(i==NULL_TVALUE)
		return false;  // key does not exist
	else
	{
		// find another key that hashes to i
		// find the next elements from i =>
		bool isOver = false;	// will become true when nothing hashes to i
		do
		{
			int positionToCheck = this->next[i];
			int previousPosition = i;
			while (positionToCheck != NULL_TVALUE && this->h(this->mapCapacity, this->elements[positionToCheck].first) != i)
			{
				previousPosition = positionToCheck;
				positionToCheck = this->next[positionToCheck];
			}
			if (positionToCheck == NULL_TVALUE)
				isOver = true;
			else
			{
				this->elements[i].first = this->elements[positionToCheck].first;
				this->elements[i].second = this->elements[positionToCheck].second;
				j = previousPosition;
				i = positionToCheck;
			}
		} while (!isOver);
		// remove the key from position i
		if (j == NULL_TVALUE)
		{
			// parse the table to check if i has any previous element
			// find i's predecessors, the elems towards => i
			int idx = 0;
			while (idx < this->mapCapacity && j == NULL_TVALUE)
			{
				if (this->next[idx] == i)
					j = idx;
				else
					idx++;
			}
		}
		if (j != NULL_TVALUE)
		{
			// j != NULL_TVALUE
			this->next[j] = this->next[i];
		}
		this->elements[i] = NULL_TELEM;
		this->next[i] = NULL_TVALUE;
		if (this->firstFree > i)
			this->firstFree = i;
		mapSize--;
		return true;
	}
}
// Best case: Theta(1), Worst case: Theta(mapCapacity), Total case: O(mapCapacity)
// k is first added key; when map is full, all keys are linked and k does not exist


vector<TValue> MultiMap::search(TKey c) const {
	// Implementation
	vector<TValue> associatedValues;
	int current = this->h(this->mapCapacity, c);
	while (this->next[current] != NULL_TVALUE )
	{
		if (this->elements[current].first == c)
		{
			associatedValues.push_back(this->elements[current].second);
		}
		current = this->next[current];
	}
	// we exit the loop too soon (?)
	if (this->elements[current].first == c)
		associatedValues.push_back(this->elements[current].second);
	return associatedValues;
} 
// Best case: Theta(1), Worst case: Theta(mapCapacity), Total case: O(mapCapacity)


int MultiMap::size() const {
	// Implementation
	return this->mapSize;
}
// Theta(1)


bool MultiMap::isEmpty() const {
	// Implementation
	/*bool empty = true;
	for (int i = 0; i < this->mapCapacity; i++)
	{
		if (this->elements[i].first != NULL_TVALUE)
			empty = false;
	}
	return empty;
	// Theta(mapCapacity) always
	*/
	if (this->mapSize == 0)
		return true;
	return false;
}
// Theta(1)


MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	//TODO - Implementation
	delete[] this->elements;
	delete[] this->next;
}

