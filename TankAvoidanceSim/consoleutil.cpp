#include "pch.h"

//function to clear the console
void consoleutil::clear(){
	//sends system call to clear the console - this method should work for multiple OS
	std::system("clear || cls");
}

//function to pause the program
void consoleutil::pause(){
	//sends system call to pause
	std::system("pause");
}

void consoleutil::print(std::string u){
	std::cout << u;
}

void consoleutil::print(int u){
	std::cout << u;
}

//function to get string input
std::string consoleutil::input(){
	//creating a stringutil object to manip inputString
	stringutil sconv;
	//creates empty string to store the input
	std::string inputString;
	//uses getline to store input to the string variable
	std::getline(std::cin, inputString);
	if (inputString == "") {
		return "error";
	}
	//trys to convert input to int (this will be -1 if no numbers are present)
	int i = sconv.toint(inputString);
	//checks to see if value is within range, non integers will default to -1 and pass
	if (i  > 1000000 || i < -1) {
		std::cout << "Value out of range\n";
		return "error";
	}
	//returns variable
	return inputString;
}
