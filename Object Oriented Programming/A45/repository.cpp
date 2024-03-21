#include "repository.h"

//Repository::Repository(DynamicArray* dynamic_array)
//{
//	this->dynamicArrayOfTutorials = dynamic_array;
//}

//Repository::Repository(){}

//Repository::~Repository(){}

int Repository::getRepoSize() const
{
	return this->dynamicArrayOfTutorials.getLength();
}

int Repository::addElementToRepo(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link)
{
	Tutorial newTutorial(title, presenterName, duration, numberOfLikes, link);
	if (this->findPositionOfElementByTitle(title) == -1) {
		this->dynamicArrayOfTutorials.addElement(newTutorial);
		return 1;
	}
	else
		return 0;
}

int Repository::removeElementFromRepo(Tutorial& element)
{
	bool found = false;
	for (int i = 0; i < this->getRepoSize(); i++)
	{
		if (this->dynamicArrayOfTutorials.getElementAtPosition(i).getTitleOfTutorial() == element.getTitleOfTutorial())
		{
			found = true;
			this->dynamicArrayOfTutorials.removeElementAtPosition(i);
			return 1;
		}
	}
	if (found == false)
	{
		return 0;
	}
}

Tutorial& Repository::getElementAtPositionInRepo(const int index)
{
	return this->dynamicArrayOfTutorials.getElementAtPosition(index);
	//return this->dynamic_array->getElementAtPosition(index);
}

int Repository::findPositionOfElementByTitle(const std::string& title)
{
	for (int i = 0; i < this->dynamicArrayOfTutorials.getLength(); i++)
	{
		if (this->dynamicArrayOfTutorials.getElementAtPosition(i).getTitleOfTutorial().compare(title) == 0)
			return i;
	}
	return -1;
}

int Repository::updateTutorialAtPosition(Tutorial tutorialToUpdate)
{
	int position = this->findPositionOfElementByTitle(tutorialToUpdate.getTitleOfTutorial());
	if (position != -1)
	{
		/*Tutorial& tutorial = this->getElementAtPositionInRepo(position);
		tutorial.setPresenterNameOfTutorial(tutorialToUpdate.getPresenterNameOfTutorial());
		tutorial.setDurationOfTutorial(tutorialToUpdate.getDuration());
		tutorial.setNumberOfLikesOfTutorial(tutorialToUpdate.getNumberOfLikesOfTutorial());
		tutorial.setLinkOfTutorial(tutorialToUpdate.getLink());*/
		this->getElementAtPositionInRepo(position).setPresenterNameOfTutorial(tutorialToUpdate.getPresenterNameOfTutorial());
		this->getElementAtPositionInRepo(position).setDurationOfTutorial(tutorialToUpdate.getDuration());
		this->getElementAtPositionInRepo(position).setNumberOfLikesOfTutorial(tutorialToUpdate.getNumberOfLikesOfTutorial());
		this->getElementAtPositionInRepo(position).setLinkOfTutorial(tutorialToUpdate.getLink());
		return 1;
	}
	return 0;
}



DynamicArray<Tutorial> Repository::getAllDataFromRepo()
{
	return this->dynamicArrayOfTutorials;
}
