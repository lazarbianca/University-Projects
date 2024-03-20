#pragma once
#include <string>
#include "Tutorial.h"

class ValidationExceptionInherited : public std::exception
{
private:
	std::string messageException;

public:
	ValidationExceptionInherited(std::string _message);
	const char* what() const noexcept override;
};

class InputValidator
{
public:
	static void validateIntegers(int currentField);
};

class TutorialValidator
{
public:
	static void validate(const Tutorial& tutorialToValidate);
};

class RepositoryValidator
{
public:
	static void checkDuplicates(const std::vector<Tutorial>& dynamicArrayOfTutorials, const Tutorial& tutorialToCheck);
	static void checkExistence(const std::vector<Tutorial>& dynamicArrayOfTutorials, const Tutorial& tutorialToCheck);
};