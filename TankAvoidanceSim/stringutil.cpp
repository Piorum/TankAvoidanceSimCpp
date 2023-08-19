#include "pch.h"

//function to convert string to int without errors
//ascii only, only positive numbers with no characters
int stringutil::toint(std::string inputString){
	//defaults to error flag
	int output = -1;
	//gets input length
	int length = len(inputString);
	//checks if any any value is outside of ascii number range
	for (int i = 0; i < length; i++) {
		if (inputString[i] > 57 || inputString[i] < 48) {
			//returns error flag if char is found
			return output;
		}
	}
	//converts output to string, this will crash if a char is in the string so that why its checked for first
	output = std::stoi(inputString); //string
	//returns int
	return output;
}

//function that removes all spaces from input string and returns the modified string
//ascii only
std::string stringutil::removespaces(std::string inputString) {
	//creates empty variable to store modified outputstring
	std::string outputString;

	//loops through every value in inputstring until it gets to the end flag
	for (int i = 0; inputString[i] != '\0'; i++) {
		//if the char stored is not a space (ascii value) that adds to the outputstring
		if (inputString[i] != 32) {
			outputString += inputString[i];
		}
	}

	//returns string without spaces
	return outputString;
}

//function that takes string as an input and converts each uppercase character to lowercase then returns the string
//ascii only
std::string stringutil::tolower(std::string inputString) {
	int counter;

	//finds length of string and creates a loop to check every value
	for (counter = 0; counter < len(inputString); counter++) {
		//checking if the value is in range of uppercase letters
		if (inputString[counter] < 91 && inputString[counter] > 64) {
			//adds 32 to change ascii value to the lowercase equivilant
			inputString[counter] += 32;
		}
	}

	//returns modified inputstring
	return inputString;
}

//function to get length of a string
int stringutil::len(std::string inputString) {
	//sets counter
	int i;
	//loops adding 1 to the counter untill inputString reaches the end character
	for (i = 0; inputString[i] != '\0'; i++) {
	}
	//sets length to the amount of characters counted
	int length = i;
	//returns length
	return length;
}