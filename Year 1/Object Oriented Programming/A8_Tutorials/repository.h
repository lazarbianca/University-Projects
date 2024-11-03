#pragma once
#include <vector>
#include <algorithm>
#include "Tutorial.h"
#include "Validator.h"

// The thing that gets you the data; not the data itself
// it might get the data from a vector, a database, a file etc...

class Repository {
private:
	std::vector<Tutorial> dynamicArrayOfTutorials;

public:
	// default constructor
	//Repository(DynamicArray* dynamic_array);   // : dynamicArrayOfTutorials{ dynamic_array } {}
	Repository();
	//Repository(const Repository&);
	~Repository();
	int getRepoSize() const;
	// adds a Tutorial to the repository
	void addElementToRepo(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link);
	// removes an element from repo; returns true if it was removed successfully, false otherwise
	void removeElementFromRepo(Tutorial& element);
	Tutorial& getElementAtPositionInRepo(const int index);
	std::vector<Tutorial>::iterator findPositionOfElementByTitle(const std::string& title);
	void updateTutorialAtPosition(Tutorial tutorialToUpdate);
	std::vector<Tutorial> getAllDataFromRepo();

	void readTutorialsFromFile();
	void appendTutorialToFile(const Tutorial& tutorialToSave);
	void writeCurrentDataInFile();
};
