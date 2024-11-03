#pragma once
#include <cassert>
#include "Tutorial.h"

//typedef Tutorial TElem;
template <typename TElem>
class DynamicArray {
private:
	TElem* elements;
	int capacity;
	int length;
	int id_of_array;

public:
	// default constructor
	DynamicArray(int capacity = 10);
	// copy constructor
	DynamicArray(const DynamicArray&);
	//destructor
	~DynamicArray();
	int getLength() const;
	// return element at a given index
	TElem& getElementAtPosition(int index) const;
	// add element to DynamicArray
	void addElement(const TElem& element);
	// remove element at a specified index in DynamicArray
	void removeElementAtPosition(int index);
	// assignment operator for a DynamicArray
	DynamicArray& operator=(const DynamicArray&);
	void setID(int newID);


private:
	void resize();
};
void testDynamicArray();


template <typename TElem>
DynamicArray<TElem>::DynamicArray(int capacity)
{
	this->length = 0;
	this->capacity = capacity;
	this->elements = new TElem[capacity];
}

template <typename TElem>
DynamicArray<TElem>::DynamicArray(const DynamicArray& dynamicArrayToBeCopied)
{
	this->length = dynamicArrayToBeCopied.length;
	this->capacity = dynamicArrayToBeCopied.capacity;
	this->elements = new TElem[this->capacity];
	for (int i = 0; i < this->length; i++)
		this->elements[i] = dynamicArrayToBeCopied.elements[i];
}

template <typename TElem>
DynamicArray<TElem>::~DynamicArray()
{
	delete[] this->elements;
	//this->elements = NULL;
}

template <typename TElem>
int DynamicArray<TElem>::getLength() const
{
	return this->length;
}

template <typename TElem>
TElem& DynamicArray<TElem>::getElementAtPosition(int index) const
{
	return this->elements[index];
}

template <typename TElem>
void DynamicArray<TElem>::addElement(const TElem& element)
{
	if (this->length == this->capacity)
		this->resize();
	this->elements[this->length] = element;
	this->length++;
}

template <typename TElem>
void DynamicArray<TElem>::removeElementAtPosition(int index)
{
	for (int i = index; i < this->length - 1; i++)
		this->elements[i] = this->elements[i + 1];
	this->length--;
}

template<typename TElem>
inline DynamicArray<TElem>& DynamicArray<TElem>::operator=(const DynamicArray& dynamicArrayToBeAssigned)
{
	if (this != &dynamicArrayToBeAssigned) {
		delete[] this->elements;
		this->length = dynamicArrayToBeAssigned.length;
		this->capacity = dynamicArrayToBeAssigned.capacity;
		this->elements = new TElem[this->capacity];
		for (int i = 0; i < this->length; i++) {
			this->elements[i] = dynamicArrayToBeAssigned.elements[i];
		}
	}
	return *this;
}

template<typename TElem>
inline void DynamicArray<TElem>::setID(int newID)
{
	this->id_of_array = newID;
}

template <typename TElem>
void DynamicArray<TElem>::resize()
{
	this->capacity *= 2;
	TElem* newDynamicArray = new TElem[this->capacity];
	for (int i = 0; i < this->length; i++)
		newDynamicArray[i] = this->elements[i];

	delete[] this->elements;
	this->elements = newDynamicArray;
}


//template <typename TElem>
//void testDynamicArray()
//{
//	DynamicArray<TElem> dynamicArrayOfTutorials;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//	Tutorial tutorialToAdd(title, presenterName, duration, numberOfLikes, link);
//
//	assert(dynamicArrayOfTutorials.getLength() == 0);
//	dynamicArrayOfTutorials.addElement(tutorialToAdd);
//	assert(dynamicArrayOfTutorials.getLength() == 1);
//
//	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getTitleOfTutorial().compare(title) == 0);
//	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getPresenterNameOfTutorial().compare(presenterName) == 0);
//	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getDuration().getMinutes() == minutes);
//	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getDuration().getSeconds() == seconds);
//	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getNumberOfLikesOfTutorial() == numberOfLikes);
//	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getLink().compare(link) == 0);
//
//	dynamicArrayOfTutorials.removeElementAtPosition(1);
//	assert(dynamicArrayOfTutorials.getLength() == 0);
//}

