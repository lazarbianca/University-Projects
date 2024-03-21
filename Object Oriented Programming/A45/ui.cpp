#include <iostream>
#include "ui.h"

//Ui::Ui(){}

//Ui::Ui(Services service)
//{}

Ui::~Ui()
{
}

void Ui::printStartUpModes()
{
	std::cout << "===============Choose mode:===============\n";
	std::cout << "1. Administrator\n";
	std::cout << "2. User\n";
}

void Ui::printAdminMenu()
{
	std::cout << "Choose option:\n";
	std::cout << "0. Exit\n";
	std::cout << "1. Add a tutorial\n";
	std::cout << "2. Remove a tutorial\n";
	std::cout << "3. Update a tutorial\n";
	std::cout << "4. Display all tutorials\n";
}

void Ui::printUserMenu()
{
	// Tutorial: tutorialName
	// Presenter: presenterName
	// Duration: minutes:seconds
	// Nr of likes: 123456789
	// Link: -------------------------
	//
	// 1. See tutorials with a given presenter
	// 2. Add to watchlist
	// 3. Skip tutorial
	// 4. Delete tutorial from watchlist
	//		Like the tutorial? Y/N
	// 5. See the watchlist
	//circular!

	//>std::cout << "1. Browse tutorials with a given presenter\n"; //one by one, if empty=>all, play first tutorial in browser
	std::cout << "==============Choose option:==============\n";
	std::cout << "0. Exit\n";
	std::cout << "1. Add to watchlist\n";  //adds it to user watchlist
	std::cout << "2. Skip tutorial\n";
	std::cout << "3. See your watchlist\n";
	//std::cout << "4. Delete tutorial from watchlist\n";
	//>Like it?
}

void Ui::printWatchlistMenu()
{
	std::cout << "0. Back\n";
	std::cout << "1. Delete tutorial\n";
	std::cout << "2. Like tutorial\n";
	std::cout << "3. Next\n";
}

void Ui::addTenEntries()
{
	Duration currentTutorialDuration(83, 4);
	this->services.addElementService("C++ Tutorial for Beginners - Learn C++ in 1 Hour", "Programming with Mosh", currentTutorialDuration
		, 37000, "https://youtu.be/ZzaPdXTrSb8");
	currentTutorialDuration.setMinutes(241);
	currentTutorialDuration.setSeconds(18);
	this->services.addElementService("C++ Tutorial for Beginners - Full Course", "freeCodeCamp.org", currentTutorialDuration
		, 260000, "https://youtu.be/vLnPwxZdW4Y");
	currentTutorialDuration.setMinutes(360);
	currentTutorialDuration.setSeconds(0);
	this->services.addElementService("C++ Full Course for free", "Bro Code", currentTutorialDuration
		, 35000, "https://youtu.be/-TkoO8Z07hI");
	this->services.addElementService("Dummy Tutorial For Checking Filter By Presenter Name", "Bro Code", currentTutorialDuration, 53000, "https://youtu.be/-TkoO8Z07hI");
	currentTutorialDuration.setMinutes(1861);
	currentTutorialDuration.setSeconds(30);
	this->services.addElementService("C++ Programming Course - Beginner to Advanced", "freeCodeCamp.org", currentTutorialDuration
		, 103000, "https://youtu.be/8jLOx1hD3_o");
	currentTutorialDuration.setMinutes(2);
	currentTutorialDuration.setSeconds(46);
	this->services.addElementService("C++ in 100 Seconds", "Fireship", currentTutorialDuration
		, 51000, "https://youtu.be/MNeX4EGtR5Y");
	currentTutorialDuration.setMinutes(15);
	currentTutorialDuration.setSeconds(53);
	this->services.addElementService("Introducere în programare - tutorial C++ - cursul 1", "Videotutorial.ro", currentTutorialDuration
		, 7600, "https://youtu.be/JjY9U9lu37I");
	currentTutorialDuration.setMinutes(7);
	currentTutorialDuration.setSeconds(6);
	this->services.addElementService("Car Game in C++ for Beginners | Easy Console Games Coding Tutorial", "Angulars", currentTutorialDuration
		, 23000, "https://youtu.be/X4LyyvGLABg");
	currentTutorialDuration.setMinutes(9);
	currentTutorialDuration.setSeconds(32);
	this->services.addElementService("C++ Programming Tutorial 1 - Intro to C++", "Caleb Curry", currentTutorialDuration
		, 10000, "https://youtu.be/OTroAxvRNbw");
	currentTutorialDuration.setMinutes(4);
	currentTutorialDuration.setSeconds(47);
	this->services.addElementService("Bjarne Stroustrup: Why I Created C++ | Big Think", "Big Think", currentTutorialDuration
		, 47000, "https://youtu.be/JBjjnqG0BP8");
	currentTutorialDuration.setMinutes(8);
	currentTutorialDuration.setSeconds(13);
	this->services.addElementService("How to REALLY learn C++", "The Cherno", currentTutorialDuration
		, 24000, "https://youtu.be/_zQqN5OYCCM");
}

void Ui::adminMode()
{
}

void Ui::readTutorialInfo(std::string& titleOfTutorial, std::string& presenterName, Duration& durationOfTutorial, std::int32_t& numberOfLikes,
	std::string& linkOfTutorial)
{
	std::int32_t minutesDurationOfTutorial;
	std::int32_t secondsDurationOfTutorial;
	
	std::cout << "Enter information about the tutorial\n";
	std::cout << "title: ";

	std::cin.get();
	std::getline(std::cin, titleOfTutorial);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "Invalid input!\n";
	}

	std::cout << "presenter name: ";
	std::getline(std::cin, presenterName);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "Invalid input!\n";
	}

	//std::cin.get();
	std::cout << "duration: minutes ";
	std::cin >> minutesDurationOfTutorial;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "Invalid input!\n";
		std::cin.clear();
	}

	std::cout << "duration: seconds ";
	std::cin >> secondsDurationOfTutorial;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "Invalid input!\n";
	}

	durationOfTutorial.setMinutes(minutesDurationOfTutorial);
	durationOfTutorial.setSeconds(secondsDurationOfTutorial);

	std::cout << "number of likes: ";
	std::cin >> numberOfLikes;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "Invalid input!\n";
	}

	std::cout << "link of tutorial : ";
	std::cin >> linkOfTutorial;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "Invalid input!\n";
	}
}

void Ui::readTutorialTitleAndNewInfo(std::string& titleOfTutorial, std::string& newPresenterName, Duration& newDurationOfTutorial,
	std::int32_t& newNumberOfLikes, std::string& newLinkOfTutorial)
{
	std::int32_t minutesDurationOfTutorial;
	std::int32_t secondsDurationOfTutorial;
	std::cout << "Enter the title of the tutorial you want to update: ";

	std::cin.get();
	std::getline(std::cin, titleOfTutorial);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "FAIL";
	}

	std::cout << "Enter the new information - \npresenter name: ";
	std::getline(std::cin, newPresenterName);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "FAIL";
	}

	std::cout << "duration: minutes ";
	std::cin >> minutesDurationOfTutorial;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "FAIL";
	}

	std::cout << "duration: seconds ";
	std::cin >> secondsDurationOfTutorial;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "FAIL";
	}

	newDurationOfTutorial.setMinutes(minutesDurationOfTutorial);
	newDurationOfTutorial.setSeconds(secondsDurationOfTutorial);

	std::cout << "number of likes: ";
	std::cin >> newNumberOfLikes;

	std::cout << "link of tutorial : ";
	std::cin >> newLinkOfTutorial;
}

void Ui::removeMenuOption()
{
}

void Ui::updateMenuOption()
{
}

void Ui::displayAllMenuOption()
{
}

void Ui::watchlistOptions(DynamicArray<TElem> &watchlistData, bool &watchlistMode)
{
	for (int i = 0; i < watchlistData.getLength(); i++)
	{
		std::cout << "\n=====================================================";
		std::cout << "\n" << watchlistData.getElementAtPosition(i).toString() << "\n";
		int userWatchlistOption;
		std::cout << "Enter option: ";
		printWatchlistMenu();
		std::cin >> userWatchlistOption;

		switch (userWatchlistOption)
		{
		case BACK_OUT_OF_WATCHLIST:
		{
			watchlistMode = false;
			break;
		}
		case DELETE_TUTORIAL_FROM_WATCHLIST_OPTION:
		{
			//remove tutorial from watchlist
			if (this->services.removeElementFromWatchlistService(this->services.getElementAtPositionInWatchlistService(i)) == 1)
				std::cout << "Deleted successfully!\n";
			else
				std::cout << "Couldn't delete tutorial.\n";
			break;
		}
		case LIKE_TUTORIAL_IN_WATCHLIST_OPTION:
		{
			//like tutorial = update tutorial with nr likes ++
			TElem currentTutorial = this->services.getElementAtPositionInWatchlistService(i);
			currentTutorial.setNumberOfLikesOfTutorial(currentTutorial.getNumberOfLikesOfTutorial() + 1);
			this->services.updateTutorialService(currentTutorial);
			this->services.updateTutorialInWatchlistService(currentTutorial);
			break;
		}
		default:
			break;
		}
	}
	
}

void Ui::readPresenterNameOnly(std::string& presenterName)
{
	std::cout << "Enter presenter name: ";
	//std::cin.get();
	std::getline(std::cin, presenterName);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "Invalid input!\n";
	}
}

void Ui::startUp()
{
	addTenEntries();
	bool continue_run = true;
	char mode;
	this->printStartUpModes();
	std::cin >> mode;
	switch (mode)
	{
	case EXIT_MENU_OPTION:
		std::cout << "Bye";
		break;
	case ADMINISTRATOR_MODE:
		while (continue_run)
		{
			// admin
			printAdminMenu();
			int administratorOption;
			//std::cin.get();
			std::cin >> administratorOption;
			switch (administratorOption)
			{
			case EXIT_MENU_OPTION:
			{
				continue_run = false;
				break;
			}
			case ADD_MENU_OPTION:
			{
				//add
				std::string titleOfTutorial, presenterName, linkOfTutorial;
				std::int32_t numberOfLikes;
				Duration durationOfTutorial;
				readTutorialInfo(titleOfTutorial, presenterName, durationOfTutorial, numberOfLikes, linkOfTutorial);
				if (this->services.addElementService(titleOfTutorial, presenterName, durationOfTutorial, numberOfLikes, linkOfTutorial) == 1)
					std::cout << "\nTutorial Added Successfully.\n";
				else
					std::cout << "\nTutorial Already Exists\n";
				break;
			}
			case REMOVE_MENU_OPTION:
			{
				//remove
				std::string titleOfTutorial;
				Duration nullDuration = Duration(0, 0);
				std::cout << "Enter the title of the tutorial you want to remove: ";
				std::cin.get();
				std::getline(std::cin, titleOfTutorial);
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cout << "Invalid input!\n";
					break;
				}
				Tutorial toRemoveTutorial = Tutorial(titleOfTutorial, "", nullDuration, 0, "");
				if (this->services.removeElementService(toRemoveTutorial) == 1)
				{
					std::cout << "\nTutorial Removed Successfully.\n";
				}
				else
					std::cout << "\nTutorial Does Not Exist.\n";
				break;
			}
			case UPDATE_MENU_OPTION:
			{
				//update
				std::string titleOfTutorial, presenterName, linkOfTutorial;
				std::int32_t numberOfLikes;
				Duration durationOfTutorial;
				readTutorialTitleAndNewInfo(titleOfTutorial, presenterName, durationOfTutorial, numberOfLikes, linkOfTutorial);
				Tutorial tutorialToUpdate = Tutorial(titleOfTutorial, presenterName, durationOfTutorial, numberOfLikes, linkOfTutorial);
				if (this->services.updateTutorialService(tutorialToUpdate) == 1)
					std::cout << "\nTutorial updated successfully.\n";
				else
					std::cout << "\nTutorial update failed.\n";
				break;
			}
			case DISPLAY_MENU_OPTION:
			{
				//display
				DynamicArray<TElem> allData = this->services.getAllDataService();
				for (int i = 0; i < allData.getLength(); i++)
				{
					std::cout << allData.getElementAtPosition(i).toString();
				}
				break;
			}
			default:
				break;
			}
		}
		break;
	case USER_MODE: {
		std::cout << "Browse tutorials by a given presenter:\n";
		std::cout << "Enter presenter name: ";
		std::string givenPresenter;
		std::cin.get();
		std::getline(std::cin, givenPresenter);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Invalid input!\n";
			break;
		}
		DynamicArray<TElem> allData;
		allData = this->services.getAllDataService();
		if (givenPresenter == "")
		{
			//we show all tutorials, one by one
			bool continueBrowsing = true;
			while (continueBrowsing)
			{
				for (int i = 0; i < allData.getLength() && continueBrowsing; i++)
				{
					std::cout << "\n=====================================================";
					std::cout << "\n" << allData.getElementAtPosition(i).toString() << "\n";
					allData.getElementAtPosition(i).playTutorial();
					printUserMenu();
					int userOption;
					std::cout << "Enter option: ";
					std::cin >> userOption;

					switch (userOption)
					{
					case EXIT_MENU_OPTION:
					{
						continueBrowsing = false;
						break;
					}
					case ADD_TO_WATCHLIST_OPTION:
					{
						//1. Add to watchlist
						this->services.addElementToWatchlistService(allData.getElementAtPosition(i));
						break;
					}
					case SKIP_TUTORIAL_OPTION:
					{
						//2. Skip tutorial
						break;
					}
					case SEE_WATCHLIST_OPTION:
					{
						//3. See your watchlist

						DynamicArray<TElem> watchlistData;
						bool watchlistMode = true;
						while (watchlistMode)
						{
							watchlistData = this->services.getWatchlistDataService();
							watchlistOptions(watchlistData, watchlistMode);
							if (watchlistData.getLength() == 0)
							{
								std::cout << "No tutorials in watchlist\n";
								watchlistMode = false;
							}
						}
						break;
					}
					default:
						break;
					}
				}
			}
		}
		else
		{	//there is a presenterName by which we filter
			bool foundGivenPresenterNameInTutorialsList = false;
			//check if given presenter appears
			for (int i = 0; i < allData.getLength(); i++)
			{
				if (allData.getElementAtPosition(i).getPresenterNameOfTutorial() == givenPresenter)
					foundGivenPresenterNameInTutorialsList = true;
			}
			while (!foundGivenPresenterNameInTutorialsList)  // nor empty string
			{
				std::cout << "Given presenter does not exist! Try again: \n";
				readPresenterNameOnly(givenPresenter);
				//check again if the new presenter name appears in array
				for (int i = 0; i < allData.getLength(); i++)
				{
					if (allData.getElementAtPosition(i).getPresenterNameOfTutorial() == givenPresenter)
						foundGivenPresenterNameInTutorialsList = true;
				}
			}


			
			DynamicArray<TElem> dataFilteredByPresenterName;
			for (int i = 0; i < allData.getLength(); i++)
			{
				if (allData.getElementAtPosition(i).getPresenterNameOfTutorial() == givenPresenter)
					dataFilteredByPresenterName.addElement(allData.getElementAtPosition(i));
			}

			bool continueBrowsing = true;
			while (continueBrowsing)
			{
				for (int i = 0; i < dataFilteredByPresenterName.getLength() && continueBrowsing; i++)
				{
					std::cout << "\n=====================================================";
					std::cout << "\n" << dataFilteredByPresenterName.getElementAtPosition(i).toString() << "\n";
					dataFilteredByPresenterName.getElementAtPosition(i).playTutorial();
					printUserMenu();
					int userOption;
					std::cout << "Enter option: ";
					std::cin >> userOption;

					switch (userOption)
					{
					case EXIT_MENU_OPTION:
					{
						continueBrowsing = false;
						break;
					}
					case ADD_TO_WATCHLIST_OPTION:
					{
						//1. Add to watchlist
						this->services.addElementToWatchlistService(dataFilteredByPresenterName.getElementAtPosition(i));
						break;
					}
					case SKIP_TUTORIAL_OPTION:
					{
						//2. Skip tutorial
						break;
					}
					case SEE_WATCHLIST_OPTION:
					{
						//3. See your watchlist
						DynamicArray<TElem> watchlistData;
						bool watchlistMode = true;
						while (watchlistMode)
						{
							watchlistData = this->services.getWatchlistDataService();
							watchlistOptions(watchlistData, watchlistMode);
							if (watchlistData.getLength() == 0)
							{
								std::cout << "No tutorials in watchlist\n";
								watchlistMode = false;
							}
						}
						break;
					}
					default:
						break;
					}
				}
			}
		}
	}
		break;
	default:
		break;
	}
}
