#include <iostream>
#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d), currentElementIndex(0), currentSLLA(nullptr), currentIndexOfValue(-1) {
	// Implementation
	//currentElementIndex = d.mapHead;
	currentElementIndex = map.mapHead;
	if (currentElementIndex != -1) {
		currentSLLA = map.mapValues[currentElementIndex];
		currentIndexOfValue = currentSLLA->headOfCurrentSLLA;
	}
	/*else {
		currentSLLA = nullptr;
		currentIndexOfValue = -1;
	}*/
}
//Theta(1)

void SMMIterator::first() {
	//TODO - Implementation
	if (map.mapHead != -1)
	{
		// there is at least one element in the smm
		currentElementIndex = map.mapHead;
		currentSLLA = map.mapValues[currentElementIndex];
		currentIndexOfValue = currentSLLA->headOfCurrentSLLA;
	}
}
//Theta(1)

void SMMIterator::next() {
	// Implementation
	if (!valid()) {
		throw std::exception();
	}

	currentIndexOfValue = currentSLLA->nextIndices[currentIndexOfValue];
	if (currentIndexOfValue == -1) {
		currentElementIndex = map.mapNextIndices[currentElementIndex];
		if (currentElementIndex == -1) {
			return;
		}
		currentSLLA = map.mapValues[currentElementIndex];
		currentIndexOfValue = currentSLLA->headOfCurrentSLLA;
	}
}
//Theta(1)

bool SMMIterator::valid() const {
	// Implementation
	//cout << "Current element index for validation: " << currentElementIndex << " and the map capacity: " << map.mapCapacity << " and now the current index of value: " << currentIndexOfValue << "\n\n";
	return currentElementIndex >= 0 && currentElementIndex < map.mapCapacity
		&& currentSLLA != nullptr;
}

TElem SMMIterator::getCurrent() const {
	// Implementation
	if (!valid()) {
		throw std::exception();
	}

	TKey key = map.mapKeys[currentElementIndex];
	TValue value = currentSLLA->values[currentIndexOfValue];
	return std::make_pair(key, value);
}
