#pragma once
#include "repository.h"
#include "WatchlistExporter.h"

// Does the business logic part (application specific)
// Does not care HOW the repo got the data (nor where from)

typedef Tutorial TElem;
class Services {
private:
	Repository repository;
	Repository watchlist;
	WatchlistExporter* exporter;

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
	void addElementService(const std::string& title, const std::string& presenterName, const Duration& duration, const std::int32_t& numberOfLikes, const std::string& link);
	void addElementToWatchlistService(TElem element);
	void removeElementService(TElem& element);
	void removeElementFromWatchlistService(TElem& element);
	std::vector<TElem> getAllDataService();
	std::vector<TElem> getWatchlistDataService();
	void updateTutorialService(Tutorial tutorialToUpdate);
	void updateTutorialInWatchlistService(Tutorial tutorialToUpdate);

	void addTenEntriesService();
	void readFromFile();
	void writeToFile();

	void setExporter(WatchlistExporter* chosenExporter)
	{
		this->exporter = chosenExporter;
	}
	void exportWatchlist()
	{
		this->exporter->writeWatchlistToFile(this->watchlist);
	}
	void displayWatchlist()
	{
		this->exporter->displayWatchlist(this->watchlist);
	}
};