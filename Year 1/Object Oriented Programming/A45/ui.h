#pragma once
#include <iostream>
#include "services.h"
#define ADMINISTRATOR_MODE '1'
#define USER_MODE '2'
#define EXIT_MENU_OPTION 0
#define ADD_MENU_OPTION 1
#define REMOVE_MENU_OPTION 2
#define UPDATE_MENU_OPTION 3
#define DISPLAY_MENU_OPTION 4

#define ADD_TO_WATCHLIST_OPTION 1
#define SKIP_TUTORIAL_OPTION 2
#define SEE_WATCHLIST_OPTION 3

#define BACK_OUT_OF_WATCHLIST 0
#define DELETE_TUTORIAL_FROM_WATCHLIST_OPTION 1
#define LIKE_TUTORIAL_IN_WATCHLIST_OPTION 2
#define NEXT_TUTORIAL_OF_WATCHLIST 3

class Ui {
private:
	Services services;
public:
	//Ui();
	Ui(Services service) : services{ service } {};
	~Ui();
	void startUp();
	void printStartUpModes();
	void printAdminMenu();
	void printUserMenu();
	void printWatchlistMenu();
	void addTenEntries();
	void adminMode();
	void readTutorialInfo(std::string& titleOfTutorial, std::string& presenterName, Duration& durationOfTutorial, std::int32_t& numberOfLikes,
		std::string& linkOfTutorial);
	void readTutorialTitleAndNewInfo(std::string& titleOfTutorial, std::string& newPresenterName, Duration& newDurationOfTutorial,
		std::int32_t& newNumberOfLikes, std::string& newLinkOfTutorial);
	void addMenuOption();
	void removeMenuOption();
	void updateMenuOption();
	void displayAllMenuOption();
	void watchlistOptions(DynamicArray<TElem>&, bool&);
	void Ui::readPresenterNameOnly(std::string& presenterName);
};