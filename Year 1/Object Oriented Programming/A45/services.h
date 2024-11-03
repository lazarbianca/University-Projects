#pragma once
#include "repository.h"

typedef Tutorial TElem;
class Services {
private:
	Repository repository;
	Repository watchlist;

public:
	Services(Repository repo);// : repository{ repo } {}

	Services() {};
	~Services() {};

	Repository getRepo() const { return repository; }
	//Watchlist getWatchlist() const { return watchlist; }

	int getLengthService();
	int getWatchlistLengthService();
	TElem getElementAtPositionService(int position);
	TElem getElementAtPositionInWatchlistService(int position);
	int addElementService(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link);
	int addElementToWatchlistService(TElem element);
	int removeElementService(TElem& element);
	int removeElementFromWatchlistService(TElem& element);
	DynamicArray<TElem> getAllDataService();
	DynamicArray<TElem> getWatchlistDataService();
	int updateTutorialService(Tutorial tutorialToUpdate);
	int updateTutorialInWatchlistService(Tutorial tutorialToUpdate);

	//void startWatchlist();
	//void nextTutorialWatchlist();
};
void testAddService();
void testRemoveService();
void testUpdateService();