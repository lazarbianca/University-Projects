#include <Windows.h>
#include "Tutorial.h"

Tutorial::Tutorial()
{
	titleOfTutorial = "";
	presenterNameOfTutorial = "";
	durationOfTutorial = Duration();
	numberOfLikesOfTutorial = 0;
	linkOfTutorial = "";
}

Tutorial::Tutorial(const std::string& title, const std::string presenterName, const Duration& duration, const std::int32_t numberOfLikes, const std::string link) :
	titleOfTutorial{ title }, presenterNameOfTutorial{ presenterName }, durationOfTutorial{ duration }, numberOfLikesOfTutorial{ numberOfLikes }, linkOfTutorial{ link }
{}

void Tutorial::setTitleOfTutorial(std::string newTitle)
{
	this->titleOfTutorial = newTitle;
}

void Tutorial::setPresenterNameOfTutorial(std::string newPresenterName)
{
	this->presenterNameOfTutorial = newPresenterName;
}

void Tutorial::setDurationOfTutorial(Duration newDuration)
{
	this->durationOfTutorial = newDuration;
}

void Tutorial::setNumberOfLikesOfTutorial(std::int32_t newNumberOfLikes)
{
	this->numberOfLikesOfTutorial = newNumberOfLikes;
}

void Tutorial::setLinkOfTutorial(std::string newLink)
{
	this->linkOfTutorial = newLink;
}

void Tutorial::playTutorial()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::string Tutorial::toString() const
{
	return this->titleOfTutorial + "," + this->presenterNameOfTutorial + "," + std::to_string(this->durationOfTutorial.getMinutes()) + ":"
		+ std::to_string(this->durationOfTutorial.getSeconds()) + "," + std::to_string(this->numberOfLikesOfTutorial) + ","
		+ this->linkOfTutorial;
}

// not a class function
std::vector<std::string> tokenize(std::string str, char delimiter)
{
	std::vector<std::string> resultOfTokenization;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		resultOfTokenization.push_back(token);

	return resultOfTokenization;
}

std::istream& operator>>(std::istream& stream, Tutorial& currentTutorial)
{
	std::string inputLine;
	std::getline(stream, inputLine);

	std::vector<std::string> tokens = tokenize(inputLine, ',');
	if (tokens.size() != SIZE_OF_TUTORIAL_INPUT_TOKENS_VECTOR)
	{
		// make sure data is valid
		return stream;
	}
	
	// split the duration token into minutes and seconds
	std::vector<std::string> durationTokens = tokenize(tokens[INDEX_OF_DURATION_TOKEN], ':');
	if (durationTokens.size() != SIZE_OF_DURATION_TOKENS_VECTOR) 
	{
		return stream;
	}
	// convert the minutes and seconds strings to integers
	int minutes = std::stoi(durationTokens[0]);
	int seconds = std::stoi(durationTokens[1]);

	// create a Duration object with the extracted minutes and seconds
	Duration durationInput(minutes, seconds);


	// Set the member variables of the provided Tutorial object
	currentTutorial.setTitleOfTutorial(tokens[0]);
	currentTutorial.setPresenterNameOfTutorial(tokens[1]);
	currentTutorial.setDurationOfTutorial(durationInput);
	currentTutorial.setNumberOfLikesOfTutorial(std::stoi(tokens[3]));
	currentTutorial.setLinkOfTutorial(tokens[4]);

	// Return the input stream to allow chaining of >> operators
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Tutorial& currentTutorial)
{
	stream << currentTutorial.toString();
	return stream;
}

bool checkTutorialEquality(const Tutorial tutorial1, const Tutorial tutorial2)
{
	return tutorial1.getTitleOfTutorial() == tutorial2.getTitleOfTutorial() &&
		tutorial1.getPresenterNameOfTutorial() == tutorial2.getPresenterNameOfTutorial() &&
		tutorial1.getNumberOfLikesOfTutorial() == tutorial2.getNumberOfLikesOfTutorial() &&
		tutorial1.getLink() == tutorial2.getLink() &&
		tutorial1.getDuration().getMinutes() == tutorial2.getDuration().getMinutes() &&
		tutorial1.getDuration().getSeconds() == tutorial2.getDuration().getSeconds();
}
