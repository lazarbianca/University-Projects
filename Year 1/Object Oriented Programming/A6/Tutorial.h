#pragma once

#include <string>
#include "Duration.h"

class Tutorial
{
private:
	std::string titleOfTutorial;
	std::string presenterNameOfTutorial;
	Duration durationOfTutorial;
	std::int32_t numberOfLikesOfTutorial;
	std::string linkOfTutorial;

public:
	// default constructor for a tutorial
	Tutorial();
	// constructor with parameters
	Tutorial(const std::string& titleOfTutorial, const std::string presenterNameOfTutorial,
		const Duration& durationOfTutorial, const std::int32_t numberOfLikesOfTutorial,
		const std::string linkOfTutorial);

	//Tutorial(const Tutorial&);
	// destructor
	//~Tutorial();
	std::string getTitleOfTutorial() const {
		return titleOfTutorial;
	}
	void setTitleOfTutorial(std::string newTitle);
	std::string getPresenterNameOfTutorial() const {
		return presenterNameOfTutorial;
	}
	void setPresenterNameOfTutorial(std::string newPresenterName);
	Duration getDuration() const {
		return durationOfTutorial;
	}
	void setDurationOfTutorial(Duration newDuration);
	std::int32_t getNumberOfLikesOfTutorial() const {
		return numberOfLikesOfTutorial;
	}
	void setNumberOfLikesOfTutorial(std::int32_t newNumberOfLikes);
	std::string getLink() const {
		return linkOfTutorial;
	}

	//overload ==
	void setLinkOfTutorial(std::string newLink);

	// Plays the current tutorial (corresponding to the source link) in browser
	void playTutorial();

	// returns a string with the Tutorial's data
	std::string toString();

};
bool checkTutorialEquality(const Tutorial tutorial1, const Tutorial tutorial2);
