#pragma once
#include "DynamicArray.h"
#include "Tutorial.h"

class Repository {
private:
	DynamicArray<Tutorial> dynamicArrayOfTutorials;

public:
	// default constructor
	//Repository(DynamicArray* dynamic_array);   // : dynamicArrayOfTutorials{ dynamic_array } {}
	//Repository();
	//Repository(const Repository&);
	~Repository() {};
	int getRepoSize() const;
	// adds a Tutorial to the repository
	int addElementToRepo(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link);
	// removes an element from repo; returns true if it was removed successfully, false otherwise
	int removeElementFromRepo(Tutorial& element);
	Tutorial& getElementAtPositionInRepo(const int index);
	int findPositionOfElementByTitle(const std::string& title);
	int updateTutorialAtPosition(Tutorial tutorialToUpdate);
	DynamicArray<Tutorial> getAllDataFromRepo();
};
