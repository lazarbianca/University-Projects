//#include "Tutorial.h"
//#include <vector>
//#include <algorithm>
//#include <assert.h>
//#include "repository.h"
//#include "services.h"
//#include "ui.h"
//#include "Tests.h"
//// The function declarations are found in the "Tests" header
//
//void testDynamicArray()
//{
//	std::vector<TElem> dynamicArrayOfTutorials;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//	Tutorial tutorialToAdd(title, presenterName, duration, numberOfLikes, link);
//
//	assert(dynamicArrayOfTutorials.size() == 0);
//	dynamicArrayOfTutorials.push_back(tutorialToAdd);
//	assert(dynamicArrayOfTutorials.size() == 1);
//
//	assert(dynamicArrayOfTutorials.at(0).getTitleOfTutorial().compare(title) == 0);
//	assert(dynamicArrayOfTutorials.at(0).getPresenterNameOfTutorial().compare(presenterName) == 0);
//	assert(dynamicArrayOfTutorials.at(0).getDuration().getMinutes() == minutes);
//	assert(dynamicArrayOfTutorials.at(0).getDuration().getSeconds() == seconds);
//	assert(dynamicArrayOfTutorials.at(0).getNumberOfLikesOfTutorial() == numberOfLikes);
//	assert(dynamicArrayOfTutorials.at(0).getLink().compare(link) == 0);
//
//	dynamicArrayOfTutorials.erase(dynamicArrayOfTutorials.begin());
//	assert(dynamicArrayOfTutorials.size() == 0);
//}
//
//void testAddService()
//{
//	Services service;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToAdd(title, presenterName, duration, numberOfLikes, link);
//	assert(service.getLengthService() == 0);
//	assert(service.addElementService(title, presenterName, duration, numberOfLikes, link) == 1);
//	assert(service.getLengthService() == 1);
//	assert(service.addElementService(title, presenterName, duration, numberOfLikes, link) == 0);
//
//	assert(service.getElementAtPositionService(0).getTitleOfTutorial().compare(title) == 0);
//	assert(service.getElementAtPositionService(0).getPresenterNameOfTutorial().compare(presenterName) == 0);
//	assert(service.getElementAtPositionService(0).getDuration().getMinutes() == minutes);
//	assert(service.getElementAtPositionService(0).getDuration().getSeconds() == seconds);
//	assert(service.getElementAtPositionService(0).getNumberOfLikesOfTutorial() == numberOfLikes);
//	assert(service.getElementAtPositionService(0).getLink().compare(link) == 0);
//}
//
//void testRemoveService()
//{
//	//Repository repo = Repository();
//	//Services service(repo);
//	Services service;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToRemove(title, presenterName, duration, numberOfLikes, link);
//
//	assert(service.getLengthService() == 0);
//	assert(service.addElementService(title, presenterName, duration, numberOfLikes, link) == 1);
//	assert(service.getLengthService() == 1);
//	assert(service.removeElementService(tutorialToRemove) == 1);
//	assert(service.getLengthService() == 0);
//	assert(service.removeElementService(tutorialToRemove) == 0);
//}
//
//void testUpdateService()
//{
//	//Repository repo = Repository();
//	//Services service(repo);
//	Services service;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToUpdate(title, presenterName, duration, numberOfLikes, link);
//	assert(service.addElementService(title, presenterName, duration, numberOfLikes, link) == 1);
//	service.getElementAtPositionService(0).setPresenterNameOfTutorial("Nikola Tesla");
//	assert(service.updateTutorialService(tutorialToUpdate) == 1);
//
//	Tutorial nonExistentTutorialCheck = Tutorial("Baking brownies", "Nina", duration, 12345, "youtube.com");
//	assert(service.updateTutorialService(nonExistentTutorialCheck) == 0);
//}
//
//void addDataManually(std::vector<TElem>& manuallyEnteredCheckData)
//{
//	Tutorial currentTutorial;
//	Duration currentTutorialDuration(83, 4);
//	currentTutorial = Tutorial("C++ Tutorial for Beginners - Learn C++ in 1 Hour", "Programming with Mosh", currentTutorialDuration
//		, 37000, "https://youtu.be/ZzaPdXTrSb8");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(241);
//	currentTutorialDuration.setSeconds(18);
//	currentTutorial = Tutorial("C++ Tutorial for Beginners - Full Course", "freeCodeCamp.org", currentTutorialDuration
//		, 260000, "https://youtu.be/vLnPwxZdW4Y");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(360);
//	currentTutorialDuration.setSeconds(0);
//	currentTutorial = Tutorial("C++ Full Course for free", "Bro Code", currentTutorialDuration
//		, 35000, "https://youtu.be/-TkoO8Z07hI");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorial = Tutorial("Dummy Tutorial For Checking Filter By Presenter Name", "Bro Code", currentTutorialDuration, 53000, "https://youtu.be/-TkoO8Z07hI");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(1861);
//	currentTutorialDuration.setSeconds(30);
//	currentTutorial = Tutorial("C++ Programming Course - Beginner to Advanced", "freeCodeCamp.org", currentTutorialDuration
//		, 103000, "https://youtu.be/8jLOx1hD3_o");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(2);
//	currentTutorialDuration.setSeconds(46);
//	currentTutorial = Tutorial("C++ in 100 Seconds", "Fireship", currentTutorialDuration
//		, 51000, "https://youtu.be/MNeX4EGtR5Y");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(15);
//	currentTutorialDuration.setSeconds(53);
//	currentTutorial = Tutorial("Introducere în programare - tutorial C++ - cursul 1", "Videotutorial.ro", currentTutorialDuration
//		, 7600, "https://youtu.be/JjY9U9lu37I");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(7);
//	currentTutorialDuration.setSeconds(6);
//	currentTutorial = Tutorial("Car Game in C++ for Beginners | Easy Console Games Coding Tutorial", "Angulars", currentTutorialDuration
//		, 23000, "https://youtu.be/X4LyyvGLABg");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(9);
//	currentTutorialDuration.setSeconds(32);
//	currentTutorial = Tutorial("C++ Programming Tutorial 1 - Intro to C++", "Caleb Curry", currentTutorialDuration
//		, 10000, "https://youtu.be/OTroAxvRNbw");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(4);
//	currentTutorialDuration.setSeconds(47);
//	currentTutorial = Tutorial("Bjarne Stroustrup: Why I Created C++ | Big Think", "Big Think", currentTutorialDuration
//		, 47000, "https://youtu.be/JBjjnqG0BP8");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//
//	currentTutorialDuration.setMinutes(8);
//	currentTutorialDuration.setSeconds(13);
//	currentTutorial = Tutorial("How to REALLY learn C++", "The Cherno", currentTutorialDuration
//		, 24000, "https://youtu.be/_zQqN5OYCCM");
//	manuallyEnteredCheckData.push_back(currentTutorial);
//}
//
//void testGetAllDataService()
//{
//	Services service;
//	std::vector<TElem> manuallyEnteredCheckData;
//	addDataManually(manuallyEnteredCheckData);
//	
//	service.addTenEntriesService();
//	std::vector<TElem> returnedRepoData = service.getAllDataService();
//	
//	bool isEqual = true;
//	if (manuallyEnteredCheckData.size() == returnedRepoData.size())
//	{
//		// use foreach
//		if (!std::equal(manuallyEnteredCheckData.begin(), manuallyEnteredCheckData.end(), returnedRepoData.begin(), checkTutorialEquality))
//			isEqual = false;
//	}
//	else
//		isEqual = false;
//	assert(isEqual == true);
//
//	std::vector<TElem> emptyVectorForCheckingInequality;
//	isEqual = true;
//	if (emptyVectorForCheckingInequality.size() != returnedRepoData.size())
//	{
//		isEqual = false;
//	}
//	assert(isEqual == false);
//
//	std::vector<TElem> badDataSameSizeVectorForCheckingInequality(manuallyEnteredCheckData.size());
//	std::copy(manuallyEnteredCheckData.begin(), manuallyEnteredCheckData.end(), badDataSameSizeVectorForCheckingInequality.begin());
//	badDataSameSizeVectorForCheckingInequality[0].setTitleOfTutorial("How to draw portraits in charcoal");
//	isEqual = true;
//	if (badDataSameSizeVectorForCheckingInequality.size() == returnedRepoData.size())
//	{
//		// use foreach
//		if (!std::equal(badDataSameSizeVectorForCheckingInequality.begin(), badDataSameSizeVectorForCheckingInequality.end(), returnedRepoData.begin(), checkTutorialEquality))
//			isEqual = false;
//	}
//	else
//		isEqual = false;
//	assert(isEqual == false);
//}
//
//void testTutorial()
//{
//	Duration durationOfTutorial = Duration(45, 14);
//	Tutorial tutorialToTestStringConversion = Tutorial("Anatomy 101", "Dr. Netter", durationOfTutorial, 10005, "wikipedia.com");
//	std::string expectedResultOfStringConversion = "Title: Anatomy 101\nBy: Dr. Netter\nduration: 45:14\nlikes: 10005\nlink: wikipedia.com\n\n";
//	std::string resultOfStringConversion = tutorialToTestStringConversion.toString();
//	assert(expectedResultOfStringConversion == tutorialToTestStringConversion.toString());
//}
//
//void testAddToWatchlistService()
//{
//	Services service;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToAdd(title, presenterName, duration, numberOfLikes, link);
//	assert(service.getWatchlistLengthService() == 0);
//	assert(service.addElementToWatchlistService(tutorialToAdd) == 1);
//	assert(service.getWatchlistLengthService() == 1);
//	assert(service.addElementToWatchlistService(tutorialToAdd) == 0);
//
//	assert(checkTutorialEquality(service.getElementAtPositionInWatchlistService(0),tutorialToAdd) == true);
//}
//
//void testRemoveFromWatchlistService()
//{
//	Services service;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToAdd(title, presenterName, duration, numberOfLikes, link);
//	service.addElementToWatchlistService(tutorialToAdd);
//	assert(service.getWatchlistLengthService() == 1);
//	assert(service.removeElementFromWatchlistService(tutorialToAdd) == 1);
//	assert(service.getWatchlistLengthService() == 0);
//	assert(service.removeElementFromWatchlistService(tutorialToAdd) == 0);
//}
//
//void testUpdateWatchlistService()
//{
//	Services service;
//	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
//	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
//	Duration duration(minutes, seconds);
//
//	Tutorial tutorialToUpdate(title, presenterName, duration, numberOfLikes, link);
//	assert(service.addElementToWatchlistService(tutorialToUpdate) == 1);
//	service.getElementAtPositionInWatchlistService(0).setPresenterNameOfTutorial("Nikola Tesla");
//	assert(service.updateTutorialInWatchlistService(tutorialToUpdate) == 1);
//
//	Tutorial nonExistentTutorialCheck = Tutorial("Baking brownies", "Nina", duration, 12345, "youtube.com");
//	assert(service.updateTutorialInWatchlistService(nonExistentTutorialCheck) == 0);
//}
//
//void testGetWatchlistDataService()
//{
//	Services service;
//	Duration durationOfTutorial = Duration(34, 55);
//	Tutorial tutorialManuallyEnteredInWatchlist = Tutorial("Anatomy 101", "Dr. Netter", durationOfTutorial, 10005, "wikipedia.com");
//	std::vector<TElem> manuallyEnteredCheckData;
//	manuallyEnteredCheckData.push_back(tutorialManuallyEnteredInWatchlist);
//
//	service.addElementToWatchlistService(tutorialManuallyEnteredInWatchlist);
//	std::vector<TElem> returnedRepoData = service.getWatchlistDataService();
//
//	bool isEqual = true;
//	if (manuallyEnteredCheckData.size() == returnedRepoData.size())
//	{
//		if (!std::equal(manuallyEnteredCheckData.begin(), manuallyEnteredCheckData.end(), returnedRepoData.begin(), checkTutorialEquality))
//			isEqual = false;
//	}
//	else
//		isEqual = false;
//	assert(isEqual == true);
//
//
//	std::vector<TElem> emptyVectorForCheckingInequality;
//	isEqual = true;
//	if (emptyVectorForCheckingInequality.size() != returnedRepoData.size())
//	{
//		isEqual = false;
//	}
//	assert(isEqual == false);
//
//
//	std::vector<TElem> badDataSameSizeVectorForCheckingInequality(manuallyEnteredCheckData.size());
//	std::copy(manuallyEnteredCheckData.begin(), manuallyEnteredCheckData.end(), badDataSameSizeVectorForCheckingInequality.begin());
//	badDataSameSizeVectorForCheckingInequality[0].setTitleOfTutorial("How to draw portraits in charcoal");
//	isEqual = true;
//	if (badDataSameSizeVectorForCheckingInequality.size() == returnedRepoData.size())
//	{
//		if (!std::equal(badDataSameSizeVectorForCheckingInequality.begin(), badDataSameSizeVectorForCheckingInequality.end(), returnedRepoData.begin(), checkTutorialEquality))
//			isEqual = false;
//	}
//	assert(isEqual == false);
//}
//
//void testAll()
//{
//	testDynamicArray();
//	//testAddService();
//	testRemoveService();
//	testUpdateService();
//	//testGetAllDataService();
//	// the size in the beginning will no longer be zero if we read from file in repo constructor
//	//testTutorial();
//	// toString will fail because i changed input/output format
//	testAddToWatchlistService();
//	testRemoveFromWatchlistService();
//	testUpdateWatchlistService();
//	testGetWatchlistDataService();
//}
//
