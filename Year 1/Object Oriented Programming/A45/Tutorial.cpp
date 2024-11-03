#include <Windows.h>
#include "Tutorial.h"

Tutorial::Tutorial()
{
	titleOfTutorial = "";
	presenterNameOfTutorial = "";
	durationOfTutorial = Duration();
	numberOfLikesOfTutorial = 0;
	linkOfTutorial = "";
}

Tutorial::Tutorial(const std::string& title, const std::string presenterName, const Duration& duration, const std::int32_t numberOfLikes, const std::string link) :
	titleOfTutorial{ title }, presenterNameOfTutorial{ presenterName }, durationOfTutorial{ duration }, numberOfLikesOfTutorial{ numberOfLikes }, linkOfTutorial{ link }
{}

//Tutorial::Tutorial(const Tutorial& tutorialToBeCopied)
//{
//	titleOfTutorial = tutorialToBeCopied.titleOfTutorial;
//	presenterNameOfTutorial = tutorialToBeCopied.presenterNameOfTutorial;
//	durationOfTutorial = tutorialToBeCopied.durationOfTutorial;
//	numberOfLikesOfTutorial = tutorialToBeCopied.numberOfLikesOfTutorial;
//	linkOfTutorial = tutorialToBeCopied.linkOfTutorial;
//}

//Tutorial::~Tutorial()
//{
//}

void Tutorial::setTitleOfTutorial(std::string newTitle)
{
	this->titleOfTutorial = newTitle;
}

void Tutorial::setPresenterNameOfTutorial(std::string newPresenterName)
{
	this->presenterNameOfTutorial = newPresenterName;
}

void Tutorial::setDurationOfTutorial(Duration newDuration)
{
	this->durationOfTutorial = newDuration;
}

void Tutorial::setNumberOfLikesOfTutorial(std::int32_t newNumberOfLikes)
{
	this->numberOfLikesOfTutorial = newNumberOfLikes;
}

void Tutorial::setLinkOfTutorial(std::string newLink)
{
	this->linkOfTutorial = newLink;
}

void Tutorial::playTutorial()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::string Tutorial::toString()
{
	return "Title: " + this->titleOfTutorial + "\nBy: " + this->presenterNameOfTutorial +
		"\nduration: " + std::to_string(this->durationOfTutorial.getMinutes()) + ":"
		+ std::to_string(this->durationOfTutorial.getSeconds()) + "\nlikes: " + std::to_string(this->numberOfLikesOfTutorial) 
		+ "\nlink: " + this->linkOfTutorial + '\n' + '\n';

}
