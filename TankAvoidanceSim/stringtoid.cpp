#include "pch.h"
#include "stringtoid.h"

//string util object used to manipulate strings
stringutil sconverter;

int stringtoid::settingsid(std::string inputString){
	//error flag of -1
	int id = -1;
	//converts input to lowercase to avoid case sensitivity and removes spaces
	inputString = sconverter.removespaces(sconverter.tolower(inputString));
	//loops through all itemIdnames until it finds the correct one or returns error flag if none match
	for (int i = 0; i < 9; i++) {
		if (settingsIdnames[i] == inputString) id = i;
	}
	//returns id
	return id;
}

int stringtoid::itemid(std::string inputString){
	//error flag of -1
	int id = -1;
	//converts input to lowercase to avoid case sensitivity and removes spaces
	inputString = sconverter.removespaces(sconverter.tolower(inputString));
	//loops through all itemIdnames until it finds the correct one or returns error flag if none match
	for (int i = 0; i < 16; i++) {
		if (itemIdnames[i] == inputString) id = i;
	}
	//returns id
	return id;
}

int stringtoid::statid(std::string inputString){
	//error flag of -1
	int id = -1;
	//converts input to lowercase to avoid case sensitivity and removes spaces
	inputString = sconverter.removespaces(sconverter.tolower(inputString));
	//loops through all statIdnames until it finds the correct one or returns error flag if none match
	for (int i = 0; i < 16; i++) {
		if (statIdnames[i] == inputString) id = i;
	}
	//returns id
	return id;
}

//converts inputstring to correct slotid
int stringtoid::slotid(std::string inputString){
	//error flag of -1
	int id = -1;
	//converts input to lowercase to avoid case sensitivity and removes spaces
	inputString = sconverter.removespaces(sconverter.tolower(inputString));
	//loops through all slotIdnames until it finds the correct one or returns error flag if none match
	for (int i = 0; i < 16; i++) {
		if (slotIdnames[i] == inputString) id = i;
	}
	//returns id
	return id;
}

std::string stringtoid::itemidr(int u) {
	//checks to see if int is within range
	if (u < 0 || u > 15) {
		return "error";
	}
	//returns stringname associated with that id
	return itemIdnames[u];
}

std::string stringtoid::statidr(int u) {
	//checks to see if int is within range
	if (u < 0 || u > 15) {
		return "error";
	}
	//returns stringname associated with that id
	return statIdnames[u];
}

std::string stringtoid::slotidr(int u){
	//checks to see if int is within range
	if (u < 0 || u > 16) {
		return "error";
	}
	//returns stringname associated with that id
	return slotIdnames[u];
}
