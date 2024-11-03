#include "repository.h"

int Repository::getRepoSize() const
{
	return this->dynamicArrayOfTutorials.size();
}

bool Repository::addElementToRepo(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link)
{
	Tutorial newTutorial(title, presenterName, duration, numberOfLikes, link);
	if (this->findPositionOfElementByTitle(title) == this->dynamicArrayOfTutorials.end()) {
		this->dynamicArrayOfTutorials.push_back(newTutorial);
		return true;}
	else
		return false;}

bool Repository::removeElementFromRepo(Tutorial& element)
{
	auto foundTutorial = findPositionOfElementByTitle(element.getTitleOfTutorial());
	if (foundTutorial != this->dynamicArrayOfTutorials.end()) {
		this->dynamicArrayOfTutorials.erase(foundTutorial);
		return true;
	}
	return false;
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

bool Repository::updateTutorialAtPosition(Tutorial tutorialToUpdate)
{
	auto position = findPositionOfElementByTitle(tutorialToUpdate.getTitleOfTutorial());
	if (position != this->dynamicArrayOfTutorials.end()) {
		std::for_each(position, position + 1, [&](Tutorial& oldTutorial) {
			oldTutorial.setPresenterNameOfTutorial(tutorialToUpdate.getPresenterNameOfTutorial());
			oldTutorial.setDurationOfTutorial(tutorialToUpdate.getDuration());
			oldTutorial.setNumberOfLikesOfTutorial(tutorialToUpdate.getNumberOfLikesOfTutorial());
			oldTutorial.setLinkOfTutorial(tutorialToUpdate.getLink());
			});
		return true;
	}
	return false;


	//OR

	//auto position = findPositionOfElementByTitle(tutorialToUpdate.getTitleOfTutorial());
	//if (position != this->dynamicArrayOfTutorials.end()) {
	//	auto& element = *position;
	//	std::transform(&element, &element + 1, &element, [&](Tutorial& t) {
	//		t.setPresenterNameOfTutorial(tutorialToUpdate.getPresenterNameOfTutorial());
	//		t.setDurationOfTutorial(tutorialToUpdate.getDuration());
	//		t.setNumberOfLikesOfTutorial(tutorialToUpdate.getNumberOfLikesOfTutorial());
	//		t.setLinkOfTutorial(tutorialToUpdate.getLink());
	//		return t;
	//		});
	//	return 1;
	//}
	//return 0;


	//idk if this is still needed but just to be safe
	// bool Tutorial::operator==(const Tutorial & other) const
	//{
	//	return this->titleOfTutorial == other.titleOfTutorial;
	//}
}

std::vector<Tutorial> Repository::getAllDataFromRepo()
{
	return this->dynamicArrayOfTutorials;
}
