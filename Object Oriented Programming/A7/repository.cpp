#include <fstream>
#include "repository.h"

Repository::Repository()
{}

Repository::~Repository()
{}

int Repository::getRepoSize() const
{
	return this->dynamicArrayOfTutorials.size();
}

void Repository::addElementToRepo(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link)
{
	//std::cout << "Address of Repository object in add: " << &(*this) << std::endl;
	Tutorial newTutorial(title, presenterName, duration, numberOfLikes, link);
	RepositoryValidator::checkDuplicates(this->dynamicArrayOfTutorials, newTutorial); //throws exc if tutorial exists
	this->dynamicArrayOfTutorials.push_back(newTutorial);
}

void Repository::removeElementFromRepo(Tutorial& element)
{
	auto foundTutorial = findPositionOfElementByTitle(element.getTitleOfTutorial());
	RepositoryValidator::checkExistence(this->dynamicArrayOfTutorials, element); //throws exception if element does not exist
	this->dynamicArrayOfTutorials.erase(foundTutorial);
}

Tutorial& Repository::getElementAtPositionInRepo(const int index)
{
	return this->dynamicArrayOfTutorials.at(index);
}

std::vector<Tutorial>::iterator Repository::findPositionOfElementByTitle(const std::string& title)
{
	auto position = std::find_if(this->dynamicArrayOfTutorials.begin(), this->dynamicArrayOfTutorials.end(),
		[title](const Tutorial& currentTutorial) {return currentTutorial.getTitleOfTutorial() == title; });
	return position;
}

void Repository::updateTutorialAtPosition(Tutorial tutorialToUpdate)
{
	RepositoryValidator::checkExistence(this->dynamicArrayOfTutorials, tutorialToUpdate);
	auto position = findPositionOfElementByTitle(tutorialToUpdate.getTitleOfTutorial());
	std::for_each(position, position + 1, [&](Tutorial& oldTutorial) {
		oldTutorial.setPresenterNameOfTutorial(tutorialToUpdate.getPresenterNameOfTutorial());
		oldTutorial.setDurationOfTutorial(tutorialToUpdate.getDuration());
		oldTutorial.setNumberOfLikesOfTutorial(tutorialToUpdate.getNumberOfLikesOfTutorial());
		oldTutorial.setLinkOfTutorial(tutorialToUpdate.getLink());
		});
}

std::vector<Tutorial> Repository::getAllDataFromRepo()
{
	return this->dynamicArrayOfTutorials;
}

void Repository::readTutorialsFromFile()
{
	//std::cout << "Address of Repository object in readTutorialsFromFile: " << &(*this) << std::endl;
	std::ifstream fin("textfile.txt");
	if (!fin.is_open())
	{
		std::cout << "Error opening file\n";
		return; // wasn't able to open file
	}

	Tutorial currentTutorial{};
	while (fin >> currentTutorial)
	{
		std::cout << currentTutorial << std::endl;
		this->dynamicArrayOfTutorials.push_back(currentTutorial);
	}
	fin.close();
}

void Repository::appendTutorialToFile(const Tutorial& tutorialToSave)
{
	std::ofstream fileDescriptor("textfile.txt", std::ios::app);  // will append data
	if (!fileDescriptor.is_open())
		return;
	fileDescriptor << tutorialToSave;

	fileDescriptor.close();
}

void Repository::writeCurrentDataInFile()
{
	//std::cout << "Address of Repository object in writeCurrentDataInFile: " << &(*this) << std::endl;

	std::ofstream fout("textfile.txt"); //file will be overwritten
	if (!fout.is_open())
	{
		std::cout << "Error opening file\n";
		return;
	}
	for (auto& currentTutorial : this->dynamicArrayOfTutorials)
	{
		fout << currentTutorial;
	}
	fout.close();
}
