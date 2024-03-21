#pragma once
#include <vector>
#include <algorithm>
#include "Tutorial.h"

class Repository {
private:
	std::vector<Tutorial> dynamicArrayOfTutorials;

public:
	// default constructor
	//Repository(DynamicArray* dynamic_array);   // : dynamicArrayOfTutorials{ dynamic_array } {}
	//Repository();
	//Repository(const Repository&);
	~Repository() {};
	int getRepoSize() const;
	// adds a Tutorial to the repository
	bool addElementToRepo(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link);
	// removes an element from repo; returns true if it was removed successfully, false otherwise
	bool removeElementFromRepo(Tutorial& element);
	Tutorial& getElementAtPositionInRepo(const int index);
	std::vector<Tutorial>::iterator findPositionOfElementByTitle(const std::string& title);
	bool updateTutorialAtPosition(Tutorial tutorialToUpdate);
	std::vector<Tutorial> getAllDataFromRepo();
};
