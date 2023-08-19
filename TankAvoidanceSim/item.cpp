#include "pch.h"
#include "item.h"

//function to reset all stats to 0
void item::resetStats(){
	//loops through every stat and sets to 0
	for (int i = 0; i < 16; i++) {
		stats[i] = 0;
	}
}

//function to set slotId
void item::setSlot(int sI){
	//sets slotId to passed variable
	slotId = sI;
}

//function to set stat value
void item::setStat(int sI, int sV){
	//sets the stat correlating to the statid passed to the stat value passed
	stats[sI] = sV;
}

//function to set itemId
void item::setitemId(int iI){
	//sets itemId to the value passed
	itemId = iI;
}

//returns slotId
int item::getSlot() const {
	//returns slotId
	return slotId;
}

//returns stat value
int item::getStat(int sI) const {
	//returns stat value of the stat correlated to the statId passed
	return stats[sI];
}

//return itemId
int item::getitemId() const {
	//returns itemId
	return itemId;
}

//prints all the value of the item in a ordered fashion
void item::printItem() const {
	//creates console util object
	consoleutil console;
	//creates stringtoid object
	stringtoid idconverter;
	//creates string to hold output
	std::string outputString = "";
	//outputs the itemId and then the slotId passed through the stringtoid object to get the stringname correlated to the slotId saved
	outputString += std::to_string(itemId) + " | " + idconverter.slotidr(slotId) + " ";
	//loops through every value in the stat array
	for (int i = 0; i < 16; i++) {
		//checks if the stat value saved in the stat array is not 0
		if (stats[i] != 0) {
			//passes the statid through the stringtoid object to get the stringname correlated to that statid, prints it and then the value of that stat
			outputString += idconverter.statidr(i) + ":" + std::to_string(stats[i]) + " ";
		}
	}
	//outputs newline after printing all stats
	outputString += "\n";
	//prints to console
	console.print(outputString);
}

//function to overload == operator to compare two items
bool item::operator==(const item& u) const {
	if (slotId != u.getSlot()) {
		return false;
	}
	for (int i = 0; i < 16; i++) {
		if (stats[i] != u.getStat(i)) {
			return false;
		}
	}
	return true;
}

//constructor that takes statId and itemId
item::item(int sI, int iI){
	//sets itemId
	setitemId(iI);
	//sets slotId
	setSlot(sI);
	//initializes all stats to 0
	resetStats();
}

//constructor that takes slotId
item::item(int sI){
	//sets slotId
	setSlot(sI);
	//initializes all stats to 0
	resetStats();
}

item::item(){
	//initializes all stats to 0
	resetStats();
}
