#include "services.h"
#include <cassert>

Services::Services(Repository repo)
{
	this->repository = repo;
}
//Services::~Services(){}

int Services::getLengthService()
{
	return this->repository.getRepoSize();
}

int Services::getWatchlistLengthService()
{
	return this->watchlist.getRepoSize();
}

TElem Services::getElementAtPositionService(int position)
{
	return this->repository.getElementAtPositionInRepo(position);
}

TElem Services::getElementAtPositionInWatchlistService(int position)
{
	return this->watchlist.getElementAtPositionInRepo(position);
}

bool Services::addElementService(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link)
{
	return this->repository.addElementToRepo(title, presenterName, duration, numberOfLikes, link);
}

bool Services::addElementToWatchlistService(TElem element)
{
	return this->watchlist.addElementToRepo(element.getTitleOfTutorial(), element.getPresenterNameOfTutorial(), 
		element.getDuration(), element.getNumberOfLikesOfTutorial(), element.getLink());
}

bool Services::removeElementService(TElem& element)
{
	return this->repository.removeElementFromRepo(element);
}

bool Services::removeElementFromWatchlistService(TElem& element)
{
	return this->watchlist.removeElementFromRepo(element);
}

std::vector<TElem> Services::getAllDataService()
{
	return this->repository.getAllDataFromRepo();
}

std::vector<TElem> Services::getWatchlistDataService()
{
	return this->watchlist.getAllDataFromRepo();
}

bool Services::updateTutorialService(Tutorial tutorialToUpdate)
{
	return this->repository.updateTutorialAtPosition(tutorialToUpdate);
}

bool Services::updateTutorialInWatchlistService(Tutorial tutorialToUpdate)
{
	return this->watchlist.updateTutorialAtPosition(tutorialToUpdate);
}

void Services::addTenEntriesService()
{
	Duration currentTutorialDuration(83, 4);
	this->addElementService("C++ Tutorial for Beginners - Learn C++ in 1 Hour", "Programming with Mosh", currentTutorialDuration
		, 37000, "https://youtu.be/ZzaPdXTrSb8");
	currentTutorialDuration.setMinutes(241);
	currentTutorialDuration.setSeconds(18);
	this->addElementService("C++ Tutorial for Beginners - Full Course", "freeCodeCamp.org", currentTutorialDuration
		, 260000, "https://youtu.be/vLnPwxZdW4Y");
	currentTutorialDuration.setMinutes(360);
	currentTutorialDuration.setSeconds(0);
	this->addElementService("C++ Full Course for free", "Bro Code", currentTutorialDuration
		, 35000, "https://youtu.be/-TkoO8Z07hI");
	this->addElementService("Dummy Tutorial For Checking Filter By Presenter Name", "Bro Code", currentTutorialDuration, 53000, "https://youtu.be/-TkoO8Z07hI");
	currentTutorialDuration.setMinutes(1861);
	currentTutorialDuration.setSeconds(30);
	this->addElementService("C++ Programming Course - Beginner to Advanced", "freeCodeCamp.org", currentTutorialDuration
		, 103000, "https://youtu.be/8jLOx1hD3_o");
	currentTutorialDuration.setMinutes(2);
	currentTutorialDuration.setSeconds(46);
	this->addElementService("C++ in 100 Seconds", "Fireship", currentTutorialDuration
		, 51000, "https://youtu.be/MNeX4EGtR5Y");
	currentTutorialDuration.setMinutes(15);
	currentTutorialDuration.setSeconds(53);
	this->addElementService("Introducere în programare - tutorial C++ - cursul 1", "Videotutorial.ro", currentTutorialDuration
		, 7600, "https://youtu.be/JjY9U9lu37I");
	currentTutorialDuration.setMinutes(7);
	currentTutorialDuration.setSeconds(6);
	this->addElementService("Car Game in C++ for Beginners | Easy Console Games Coding Tutorial", "Angulars", currentTutorialDuration
		, 23000, "https://youtu.be/X4LyyvGLABg");
	currentTutorialDuration.setMinutes(9);
	currentTutorialDuration.setSeconds(32);
	this->addElementService("C++ Programming Tutorial 1 - Intro to C++", "Caleb Curry", currentTutorialDuration
		, 10000, "https://youtu.be/OTroAxvRNbw");
	currentTutorialDuration.setMinutes(4);
	currentTutorialDuration.setSeconds(47);
	this->addElementService("Bjarne Stroustrup: Why I Created C++ | Big Think", "Big Think", currentTutorialDuration
		, 47000, "https://youtu.be/JBjjnqG0BP8");
	currentTutorialDuration.setMinutes(8);
	currentTutorialDuration.setSeconds(13);
	this->addElementService("How to REALLY learn C++", "The Cherno", currentTutorialDuration
		, 24000, "https://youtu.be/_zQqN5OYCCM");
}
