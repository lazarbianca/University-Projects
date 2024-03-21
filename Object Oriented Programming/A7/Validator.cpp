#include "Validator.h"

ValidationExceptionInherited::ValidationExceptionInherited(std::string _message) : messageException{ _message }
{
}

const char* ValidationExceptionInherited::what() const noexcept
{
	return messageException.c_str();
}

void InputValidator::validateIntegers(int currentField)
{

}

void TutorialValidator::validate(const Tutorial& tutorialToValidate)
{
	std::string errors;
	if (0 >= tutorialToValidate.getDuration().getMinutes())
		errors += std::string("The minutes cannot be negative or zero!\n");
	if (0 >= tutorialToValidate.getDuration().getSeconds() || tutorialToValidate.getDuration().getSeconds() > 60)
		errors += std::string("The seconds cannot be negative or over 60!\n");
	//USE STOI WITH CATCH EXCEPTIONS IN VALIDATE INPUT
	//if (std::isdigit(tutorialToValidate.getNumberOfLikesOfTutorial()) == 0)
	//	errors += std::string("The number of likes has to be a number!");
	if (tutorialToValidate.getLink().find('.') == std::string::npos)
		errors += std::string("The tutorial link must have a domain! (.com)\n");

	if (errors.size() > 0)
		throw ValidationExceptionInherited(errors);
}

void RepositoryValidator::checkDuplicates(const std::vector<Tutorial>& dynamicArrayOfTutorials, const Tutorial& tutorialToCheck)
{
	// throws exception if tutorialToCheck already exists in dynamicArrayOfTutorials (for add)
	for (const auto& currentTutorial : dynamicArrayOfTutorials)
	{
		if (currentTutorial.getTitleOfTutorial() == tutorialToCheck.getTitleOfTutorial())
			throw ValidationExceptionInherited("The tutorial already exists, cannot add it!\n");
	}
}

void RepositoryValidator::checkExistence(const std::vector<Tutorial>& dynamicArrayOfTutorials, const Tutorial& tutorialToCheck)
{
	// throws exception if tutorialToCheck does not exist in dynamicArrayOfTutorials (for remove, update)
	bool found = false;
	for (const auto& currentTutorial : dynamicArrayOfTutorials)
	{
		if (currentTutorial.getTitleOfTutorial() == tutorialToCheck.getTitleOfTutorial())
		{
			found = true;
			break;
		}
	}
	if (!found)
		throw ValidationExceptionInherited("The searched for tutorial does not exist!\n");
}

