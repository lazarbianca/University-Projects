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
	bool addElementService(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link);
	bool addElementToWatchlistService(TElem element);
	bool removeElementService(TElem& element);
	bool removeElementFromWatchlistService(TElem& element);
	std::vector<TElem> getAllDataService();
	std::vector<TElem> getWatchlistDataService();
	bool updateTutorialService(Tutorial tutorialToUpdate);
	bool updateTutorialInWatchlistService(Tutorial tutorialToUpdate);

	void addTenEntriesService();
};