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

int Services::addElementService(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link)
{
	return this->repository.addElementToRepo(title, presenterName, duration, numberOfLikes, link);
}

int Services::addElementToWatchlistService(TElem element)
{
	return this->watchlist.addElementToRepo(element.getTitleOfTutorial(), element.getPresenterNameOfTutorial(), 
		element.getDuration(), element.getNumberOfLikesOfTutorial(), element.getLink());
}

int Services::removeElementService(TElem& element)
{
	return this->repository.removeElementFromRepo(element);
}

int Services::removeElementFromWatchlistService(TElem& element)
{
	return this->watchlist.removeElementFromRepo(element);
}

DynamicArray<TElem> Services::getAllDataService()
{
	return this->repository.getAllDataFromRepo();
}

DynamicArray<TElem> Services::getWatchlistDataService()
{
	return this->watchlist.getAllDataFromRepo();
}

int Services::updateTutorialService(Tutorial tutorialToUpdate)
{
	return this->repository.updateTutorialAtPosition(tutorialToUpdate);
}

int Services::updateTutorialInWatchlistService(Tutorial tutorialToUpdate)
{
	return this->watchlist.updateTutorialAtPosition(tutorialToUpdate);
}

//void testAddService()
//{
//	Repository repo = Repository();
//	Services service(repo);
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToAdd(title, presenterName, duration, numberOfLikes, link);
//	assert(repo.getRepoSize() == 0);
//	assert(repo.addElementToRepo(title, presenterName, duration, numberOfLikes, link) == 1);
//	assert(repo.getRepoSize() == 1);
//	assert(repo.addElementToRepo(title, presenterName, duration, numberOfLikes, link) == 0);
//	
//	assert(repo.getElementAtPositionInRepo(0).getTitleOfTutorial().compare(title) == 0);
//	assert(repo.getElementAtPositionInRepo(0).getPresenterNameOfTutorial().compare(presenterName) == 0);
//	assert(repo.getElementAtPositionInRepo(0).getDuration().getMinutes() == minutes);
//	assert(repo.getElementAtPositionInRepo(0).getDuration().getSeconds() == seconds);
//	assert(repo.getElementAtPositionInRepo(0).getNumberOfLikesOfTutorial() == numberOfLikes);
//	assert(repo.getElementAtPositionInRepo(0).getLink().compare(link) == 0);
//}
//
//void testRemoveService()
//{
//	Repository repo = Repository();
//	Services service(repo);
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToRemove(title, presenterName, duration, numberOfLikes, link);
//
//	assert(repo.getRepoSize() == 0);
//	assert(repo.addElementToRepo(title, presenterName, duration, numberOfLikes, link) == 1);
//	assert(repo.getRepoSize() == 1);
//	assert(repo.removeElementFromRepo(tutorialToRemove) == 1);
//	assert(repo.getRepoSize() == 0);
//	assert(repo.removeElementFromRepo(tutorialToRemove) == 0);
//}
//
//void testUpdateService()
//{
//	Repository repo = Repository();
//	Services service(repo);
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToUpdate(title, presenterName, duration, numberOfLikes, link);
//	assert(repo.addElementToRepo(title, presenterName, duration, numberOfLikes, link) == 1);
//	repo.getElementAtPositionInRepo(0).setPresenterNameOfTutorial("Nikola Tesla");
//	assert(repo.updateTutorialAtPosition(tutorialToUpdate) == 1);
//}
