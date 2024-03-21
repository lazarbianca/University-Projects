//#include <iostream>
#include <fstream>
#include "ui.h"

Ui::~Ui() {}

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
	std::cout << "==============Choose option:==============\n";
	std::cout << "0. Exit\n";
	std::cout << "1. Add to watchlist\n";  //adds it to user watchlist
	std::cout << "2. Skip tutorial\n";
	std::cout << "3. See your watchlist\n";
	std::cout << "4. Open file to see watchlist\n";
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

void Ui::watchlistOptions(std::vector<TElem>& watchlistData, bool& watchlistMode)
{
	std::for_each(watchlistData.begin(), watchlistData.end(), [&](auto& data) {
		if (watchlistMode) {
			std::cout << "\n" << data << "\n";
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
				try
				{
					this->services.removeElementFromWatchlistService(data);
					std::cout << "Deleted successfully!\n";
				}
				catch (ValidationExceptionInherited& exception)
				{
					std::cout << exception.what();
				}
				break;
			}
			case LIKE_TUTORIAL_IN_WATCHLIST_OPTION:
			{
				//like tutorial = update tutorial with nr likes ++
				auto currentTutorial = TElem(data);  // copy of current tutorial 
				currentTutorial.setNumberOfLikesOfTutorial(currentTutorial.getNumberOfLikesOfTutorial() + 1);
				this->services.updateTutorialService(currentTutorial);
				this->services.updateTutorialInWatchlistService(currentTutorial);
				break;
			}
			default:
				break;
			}
		}
		});
}

void Ui::userModeOptions(std::vector<TElem>& allData, bool& continueBrowsing)
{
	std::for_each(allData.begin(), allData.end(), [&](auto& data) {
		if (continueBrowsing)
		{
			std::cout << "\n=====================================================";
			std::cout << "\n" << data << "\n";
			data.playTutorial();
			printUserMenu();
			int userOption;
			std::cout << "Enter option: ";
			std::cin >> userOption;

			switch (userOption)
			{
			case EXIT_MENU_OPTION:
			{
				continueBrowsing = false;
				//save the watchlist in the correct file format
				try
				{
					this->services.exportWatchlist();
				}
				catch(std::runtime_error& exception)
				{
					std::cout << exception.what();
				}
				break;
			}
			case ADD_TO_WATCHLIST_OPTION:
			{
				//1. Add to watchlist
				this->services.addElementToWatchlistService(data);
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

				std::vector<TElem> watchlistData;
				bool watchlistMode = true;
				while (watchlistMode)
				{
					watchlistData = this->services.getWatchlistDataService();
					watchlistOptions(watchlistData, watchlistMode);
					if (watchlistData.size() == 0)
					{
						std::cout << "No tutorials in watchlist\n";
						watchlistMode = false;
					}
				}
				break;
			}
			case DISPLAY_WATCHLIST:
			{
				this->services.displayWatchlist();  //what
				break;
			}
			default:
				break;
			}
		}
		});
}

bool Ui::checkIfGivenPresenterAppears(std::vector<TElem>& allData, std::string givenPresenter)
{
	auto iterator = std::find_if(allData.begin(), allData.end(),
		[givenPresenter](const TElem& currentTutorial) { return currentTutorial.getPresenterNameOfTutorial() == givenPresenter; });
	if (iterator == allData.end())
		return false;
	return true;
}

bool Ui::chooseFileType(int& fileType)
{
	WatchlistExporter* currentExporter = nullptr;
	if (fileType == 1)
	{
		currentExporter = new CSVExporter();
		this->services.setExporter(currentExporter);
		return true;
	}
	else if (fileType == 2)
	{
		currentExporter = new HTMLExporter();
		this->services.setExporter(currentExporter);
		return true;
	}
	else
		return false;
}


void Ui::startUp()
{
	//addTenEntries();
	//writeCurrentDataInFile();
	this->services.readFromFile();
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
				this->services.writeToFile();
				break;
			}
			case ADD_MENU_OPTION:
			{
				//add
				Tutorial tutorialToAdd;
				bool isTutorialValid = true;
				std::cout << "Enter the tutorial in the format: \ntitle, presenter, minutes:seconds, likes, link\n";
				std::cin.get();
				try {
					std::cin >> tutorialToAdd;
					TutorialValidator::validate(tutorialToAdd);
				}
				catch (std::out_of_range& exception)		//validates input
				{
					std::cout << exception.what();
					isTutorialValid = false;
				}
				catch (std::invalid_argument& exception)	//validates input
				{
					std::cout << exception.what();
					isTutorialValid = false;
				}
				catch (ValidationExceptionInherited& exception)
				{
					std::cout << exception.what();
					isTutorialValid = false;
				}
				catch (std::exception& exception)
				{
					std::cout << exception.what();
					isTutorialValid = false;
				}

				if (!isTutorialValid)
					std::cout << "\nInvalid Tutorial!\n";
				else
				{
					try {
						this->services.addElementService(tutorialToAdd.getTitleOfTutorial(), tutorialToAdd.getPresenterNameOfTutorial(), tutorialToAdd.getDuration(), tutorialToAdd.getNumberOfLikesOfTutorial(), tutorialToAdd.getLink());
						std::cout << "\nTutorial Added Successfully.\n";
					}
					catch (ValidationExceptionInherited& exception)
					{
						std::cout << exception.what();
					}
				}
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
				try
				{
					this->services.removeElementService(toRemoveTutorial);
					std::cout << "\nTutorial Removed Successfully.\n";
				}
				catch (ValidationExceptionInherited& exception)
				{
					std::cout << exception.what();
				}
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
				try {
					this->services.updateTutorialService(tutorialToUpdate);
					std::cout << "\nTutorial updated successfully.\n";
				}
				catch (ValidationExceptionInherited& exception)
				{
					std::cout << exception.what();
				}
				break;
			}
			case DISPLAY_MENU_OPTION:
			{
				//display
				//std::vector<TElem> allData = this->services.getAllDataService();
				for (auto& data : this->services.getAllDataService())
				{
					std::cout << data << "\n";
				}
				//std::for_each(allData.begin(), allData.end(), [](auto& data) {std::cout << data.toString(); });
				break;
			}
			default:
				break;
			}
		}
		break;
	case USER_MODE: {
		std::cout << "Choose file you want to store your watchlist in:\n1. CSV\n2. HTML\n";
		int fileType;
		std::cin >> fileType;
		if(chooseFileType(fileType) == false)
		{
			while (chooseFileType(fileType) == false)    //fileType != 1 && fileType != 2
			{
				std::cout << "Choose either 1 for CSV or 2 for HTML\n";
				std::cin >> fileType;
				chooseFileType(fileType);
			}
		}
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
		std::vector<TElem> allData;
		allData = this->services.getAllDataService();
		if (givenPresenter == "")
		{
			//we show all tutorials, one by one
			bool continueBrowsing = true;
			while (continueBrowsing)
			{
				userModeOptions(allData, continueBrowsing);
			}
		}
		else
		{	//there is a presenterName by which we filter
			bool foundGivenPresenterNameInTutorialsList = checkIfGivenPresenterAppears(allData, givenPresenter);
			while (!foundGivenPresenterNameInTutorialsList)  // nor empty string
			{
				std::cout << "Given presenter does not exist! Try again: \n";
				readPresenterNameOnly(givenPresenter);
				foundGivenPresenterNameInTutorialsList = checkIfGivenPresenterAppears(allData, givenPresenter);
			}
			std::vector<TElem> dataFilteredByPresenterName;
			std::copy_if(allData.begin(), allData.end(), std::back_inserter(dataFilteredByPresenterName),
				[&](const auto& currentElement) { return currentElement.getPresenterNameOfTutorial() == givenPresenter; });
			bool continueBrowsing = true;
			while (continueBrowsing)
			{
				userModeOptions(dataFilteredByPresenterName, continueBrowsing);
			}
		}
	}
				  break;
	default:
		break;
	}
}
