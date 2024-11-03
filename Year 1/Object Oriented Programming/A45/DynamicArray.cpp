//#include <cassert>
//#include "DynamicArray.h"
//
//DynamicArray::DynamicArray(int capacity)
//{
//	this->length = 0;
//	this->capacity = capacity;
//	this->elements = new TElem[capacity];
//}
//
//DynamicArray::DynamicArray(const DynamicArray& dynamicArrayToBeCopied)
//{
//	this->length = dynamicArrayToBeCopied.length;
//	this->capacity = dynamicArrayToBeCopied.capacity;
//	this->elements = new TElem[this->capacity];
//	for (int i = 0; i < this->length; i++)
//		this->elements[i] = dynamicArrayToBeCopied.elements[i];
//}
//
//DynamicArray::~DynamicArray()
//{
//	delete[] this->elements;
//	//this->elements = NULL;
//}
//
//int DynamicArray::getLength() const
//{
//	return this->length;
//}
//
//TElem& DynamicArray::getElementAtPosition(int index) const
//{
//	return this->elements[index];
//}
//
//void DynamicArray::addElement(const TElem& element)
//{
//	if (this->length == this->capacity)
//		this->resize();
//	this->elements[this->length] = element;
//	this->length++;
//}
//
//void DynamicArray::removeElementAtPosition(int index)
//{
//	for (int i = index; i < this->length - 1; i++)
//		this->elements[i] = this->elements[i + 1];
//	this->length--;
//}
//
//DynamicArray& DynamicArray::operator=(const DynamicArray& dynamicArray)
//{
//	if (&dynamicArray == this)
//		return *this;
//	this->length = dynamicArray.length;
//	this->capacity = dynamicArray.capacity;
//
//	delete[] this->elements;
//
//	this->elements = new TElem[this->capacity];
//	for (int i = 0; i < this->length; i++)
//	{
//		this->elements[i] = dynamicArray.elements[i];
//	}
//	return *this;
//}
//
//void DynamicArray::resize()
//{
//	this->capacity *= 2;
//	TElem* newDynamicArray = new TElem[this->capacity];
//	for (int i = 0; i < this->length; i++)
//		newDynamicArray[i] = this->elements[i];
//
//	delete[] this->elements;
//	this->elements = newDynamicArray;
//}
//
//void testDynamicArray()
//{
//	DynamicArray dynamicArrayOfTutorials;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds=5;
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
