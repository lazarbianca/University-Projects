#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <stdexcept>


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	//TODO - Implementation
	visited = new int[col.mapCapacity]();
	for (int i = 0; i < col.mapCapacity; i++)
	{
		this->visited[i] = 0;
	}
	indexOfCurrentElement = 0;
	currentChain = 0;    // the hash index we are currently iterating over
	while (currentChain < col.mapCapacity && col.elements[currentChain].first == NULL_TVALUE)
		currentChain++;
	indexOfCurrentElement = currentChain;
	visited[indexOfCurrentElement] = 1;
}
// Theta(mapCapacity)

TElem MultiMapIterator::getCurrent() const{
	//TODO - Implementation
	if (!valid()) {
		throw std::runtime_error("Invalid iterator state");
	}

	return std::make_pair(col.elements[indexOfCurrentElement].first, col.elements[indexOfCurrentElement].second);
}
// Theta(1)

bool MultiMapIterator::valid() const {
	//TODO - Implementation
	return currentChain < col.mapCapacity && indexOfCurrentElement >= 0 && indexOfCurrentElement < col.mapCapacity && col.elements[currentChain].first != NULL_TVALUE;
}
// Theta(1)

void MultiMapIterator::next() {
	//TODO - Implementation
	if (!valid()) {
		throw std::runtime_error("Invalid iterator state");
	}

	if (col.next[indexOfCurrentElement] == NULL_TVALUE)
	{
		// find the next non-null element that is unvisited
		currentChain++;
		while (currentChain < col.mapCapacity && (col.elements[currentChain].first == NULL_TVALUE || visited[currentChain] == 1))
		{
			currentChain++;
		}
		indexOfCurrentElement = currentChain;
		visited[indexOfCurrentElement] = 1;
	}
	else
	{
		// currentChain stays unmodified
		if (visited[col.next[indexOfCurrentElement]] == 1)
		{
			// we have already visited that chain; go to the next one like above
			currentChain++;
			while (currentChain < col.mapCapacity && (col.elements[currentChain].first == NULL_TVALUE || visited[currentChain] == 1))
				currentChain++;
			indexOfCurrentElement = currentChain;
			visited[indexOfCurrentElement] = 1;
		}
		else 
		{
			indexOfCurrentElement = col.next[indexOfCurrentElement];
			visited[indexOfCurrentElement] = 1;
		}
	}
}
// Best case: Theta(1), Worst case: Theta(mapCapacity)

void MultiMapIterator::first() {
	//TODO - Implementation
	// return an iterator to the first non empty position
	for (int i = 0; i < col.mapCapacity; i++)
	{
		this->visited[i] = 0;
	}
	indexOfCurrentElement = 0;
	while (col.elements[indexOfCurrentElement] == NULL_TELEM && indexOfCurrentElement < col.mapCapacity)
	{
		indexOfCurrentElement++;
	}
	currentChain = indexOfCurrentElement;
	visited[indexOfCurrentElement] = 1;
}
// Theta(mapCapacity)

