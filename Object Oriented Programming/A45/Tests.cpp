#include "Tutorial.h"
#include "DynamicArray.h"
#include "repository.h"
#include "services.h"

void testDynamicArray()
{
	DynamicArray<TElem> dynamicArrayOfTutorials;
	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
	Duration duration(minutes, seconds);
	Tutorial tutorialToAdd(title, presenterName, duration, numberOfLikes, link);

	assert(dynamicArrayOfTutorials.getLength() == 0);
	dynamicArrayOfTutorials.addElement(tutorialToAdd);
	assert(dynamicArrayOfTutorials.getLength() == 1);

	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getTitleOfTutorial().compare(title) == 0);
	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getPresenterNameOfTutorial().compare(presenterName) == 0);
	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getDuration().getMinutes() == minutes);
	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getDuration().getSeconds() == seconds);
	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getNumberOfLikesOfTutorial() == numberOfLikes);
	assert(dynamicArrayOfTutorials.getElementAtPosition(0).getLink().compare(link) == 0);

	dynamicArrayOfTutorials.removeElementAtPosition(1);
	assert(dynamicArrayOfTutorials.getLength() == 0);
}

void testAddService()
{
	//Repository repo = Repository();
	//Services service(repo);
	Services service;
	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
	Duration duration(minutes, seconds);

	Tutorial tutorialToAdd(title, presenterName, duration, numberOfLikes, link);
	assert(service.getLengthService() == 0);
	assert(service.addElementService(title, presenterName, duration, numberOfLikes, link) == 1);
	assert(service.getLengthService() == 1);
	assert(service.addElementService(title, presenterName, duration, numberOfLikes, link) == 0);

	assert(service.getElementAtPositionService(0).getTitleOfTutorial().compare(title) == 0);
	assert(service.getElementAtPositionService(0).getPresenterNameOfTutorial().compare(presenterName) == 0);
	assert(service.getElementAtPositionService(0).getDuration().getMinutes() == minutes);
	assert(service.getElementAtPositionService(0).getDuration().getSeconds() == seconds);
	assert(service.getElementAtPositionService(0).getNumberOfLikesOfTutorial() == numberOfLikes);
	assert(service.getElementAtPositionService(0).getLink().compare(link) == 0);
}

void testRemoveService()
{
	//Repository repo = Repository();
	//Services service(repo);
	Services service;
	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
	Duration duration(minutes, seconds);

	Tutorial tutorialToRemove(title, presenterName, duration, numberOfLikes, link);

	assert(service.getLengthService() == 0);
	assert(service.addElementService(title, presenterName, duration, numberOfLikes, link) == 1);
	assert(service.getLengthService() == 1);
	assert(service.removeElementService(tutorialToRemove) == 1);
	assert(service.getLengthService() == 0);
	assert(service.removeElementService(tutorialToRemove) == 0);
}

void testUpdateService()
{
	//Repository repo = Repository();
	//Services service(repo);
	Services service;
	std::string title = "Fun with C++", presenterName = "Bjarne Stroustrup", link = "youtube.com";
	std::int32_t numberOfLikes = 320000, minutes = 59, seconds = 5;
	Duration duration(minutes, seconds);

	Tutorial tutorialToUpdate(title, presenterName, duration, numberOfLikes, link);
	assert(service.addElementService(title, presenterName, duration, numberOfLikes, link) == 1);
	service.getElementAtPositionService(0).setPresenterNameOfTutorial("Nikola Tesla");
	assert(service.updateTutorialService(tutorialToUpdate) == 1);
}