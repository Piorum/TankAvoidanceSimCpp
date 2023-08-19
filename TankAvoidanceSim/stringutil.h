#pragma once
class stringutil
{
public:
	//function to convert string to int -- ascii only
	int toint(std::string inputString);
	//function to remove spaces from a string - ascii only
	std::string removespaces(std::string inputString);
	//converts string to all lowercase letters - ascii only
	std::string tolower(std::string inputString);
	//gets the lenght of a std c++ string
	int len(std::string inputString);
};

