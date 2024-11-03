#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
	//SortedMultiMap list; //reference to the SLLA object that the iterator is iterating over
	int currentElementIndex; //the index of the element that the iterator is currently pointing to
	int currentIndexOfValue; //the index of the value within the current key's slla
	const SortedMultiMap::SLLA* currentSLLA;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

