#include "pch.h"
#include "simulate.h"
#include "itemdatabase.h"

void exitf();
void simulatef(simulate& standard, unit& player);
void listitemsf(itemdatabase& items);
void listequippedf(unit& player);
void equipitemf(itemdatabase& items, unit& player);
void unequipitemf(unit& player);
void createitemf(itemdatabase& items);
void settingsf(simulate& standard);

void load(itemdatabase& items, unit& player, simulate& standard);
void save(itemdatabase& items, unit& player, simulate& standard);

int main() {
	
	//test toggles
	//toggle to enable menu testing
	const bool testmenu = true;

	//initialize 'itemdatabase'
	itemdatabase items;
	//initialize unit object player (with default contructor all items will be of type none with no stats)
	unit player;
	//initialize standard simulation
	simulate standard;

	//initializing various utility classes
	stringutil sconverter;
	consoleutil console;
	stringtoid idconverter;

	//seed rng
	srand(time(NULL));

	load(items, player, standard);

	//test menu
	if(testmenu){
		//creates string to store input
		std::string inputString;
		//continous loop until input matches exot
		while (inputString != "exit") {
			//prompts for inputs
			std::cout << "Input - Exit / Simulate / List Items / List Equipped / Equip Item / Unequip Item / Create Item / Settings: ";
			//removes all spaces and makes input completely lowercase
			inputString = sconverter.removespaces(sconverter.tolower(console.input()));

			//option for exiting
			if (inputString == "exit") {
				save(items, player, standard);
				exitf();
			}
			//option for simulation
			else if (inputString == "simulate") {
				simulatef(standard, player);
			}
			//option for listing items
			else if (inputString == "listitems") {
				listitemsf(items);
			}
			//option for listing equipped items
			else if (inputString == "listequipped") {
				listequippedf(player);
			}
			//option for equiping item
			else if (inputString == "equipitem") {
				equipitemf(items, player);
			}
			//option for unequiping an item
			else if (inputString == "unequipitem") {
				unequipitemf(player);
			}
			//option for creating an item
			else if (inputString == "createitem") {
				createitemf(items);
			}
			//option for settings
			else if (inputString == "settings") {
				settingsf(standard);
			}
			//condition for if input does not match any if
			else {
				std::cout << "Invalid Command\n";
			}
			//uses consoleutil object to pause after any operation is complete before clearing the console
			console.pause();
			console.clear();
		}
	}

	return 0;
}

void exitf(){
	//lets user know the program is exiting
	std::cout << "\nExiting...\n";
	//saving should go here
}

void simulatef(simulate& standard, unit& player){
	//runs 3 simulations using standard settings on the default player
	standard.runsim(player);
	standard.runsim(player);
	standard.runsim(player);
}

void listitemsf(itemdatabase& items){
	//prompt for sorting option here
	//runs the function printitems for the items itemdatabase object
	items.printitems(0);
}

void listequippedf(unit& player){
	//runs the function printequipped for the player unit object
	player.printEquipped();
}

void equipitemf(itemdatabase& items, unit& player){
	//utility object
	stringutil sconverter;
	consoleutil console;
	//creates varibles to store item id and slot id, slot id defaults to 0
	int iI;
	int sI = 0;
	//prompts for input
	std::cout << "\nInput itemId: "; //The value you need to input is found at the left of items when you listitems
	//gets input, changes to lowercase, removes all spaces, and converts to integer
	iI = sconverter.toint(sconverter.removespaces(sconverter.tolower(console.input())));
	//checks to see if itemId is error flag (this means toint from the stringutil object failed to find any integers in the string)
	if (iI != -1) {
		//creates a tempitem
		item tempitem;
		//gets the item correlated to the id value input, will default to empty item
		tempitem = items.getitem(iI);
		//checks to see if an item is a ring or a trinket
		if (tempitem.getSlot() == 10 || tempitem.getSlot() == 11) {
			//prompts for user input
			std::cout << "\nSlot 0 or 1: "; //This should only appear if you try to equip a ring or trinket, 0 for 1st ring/trinket, 1 for 2nd
			//gets input for the slot
			sI = sconverter.toint(sconverter.removespaces(sconverter.tolower(console.input())));
			//if return is out of the range defaults back to 0
			if (sI < 0 || sI > 1) {
				//sends error message
				std::cout << "Invalid Slot, defaulting to 0\n";
				//resets to 0
				sI = 0;
			}
		}
		//checks if item is not an empty item (16)
		if (tempitem.getSlot() != 16) {
			//equips default player with tempitem and selected slot (default 0, only matters for rings and trinkets)
			player.setItem(tempitem, sI);
			//output to let user know operation completed successfully
			std::cout << "Item Equipped\n";
		}
		//error for if the item is empty
		else {
			std::cout << "Id Error, Empty\n";
		}
	}
	//error for if it couldn't find an item with that id
	else {
		std::cout << "No Item With That Id or Invalid Input\n";
	}
}

void unequipitemf(unit& player){
	stringutil sconverter;
	consoleutil console;
	stringtoid idconverter;
	//prompts for input
	std::cout << "Input - Slot Name (Not Id): "; //this value should be a itemId (helm/offhand) all values can be found in "stringtoid.h"
	//the exceptions are 2hweapon should be weapon, and ring/trinket could be ring2/trinket2 instead
	//creates empty variable to store input
	std::string slotN;
	//gets input removes spaces and makes lowercase
	slotN = sconverter.removespaces(sconverter.tolower(console.input()));
	//creates a in variable to store the slot id, slot id is converted from input string using stringtoid object 
	int id = idconverter.itemid(slotN);
	//checks for error flag
	if (id != -1) {
		//unequips item from the slot requested
		player.unequipItem(id);
		//output to confirm operation was successful
		std::cout << "Slot Emptied\n";
	}
	//error for if id did not pass error flag (this most likely means the slot name given was not recognized)
	else {
		std::cout << "Invalid Slot Name\n";
	}
}

void createitemf(itemdatabase& items){
	stringutil sconverter;
	consoleutil console;
	stringtoid idconverter;
	std::string inputString;
	//gets value to check for errors
	int dbsize = items.gettotal();
	//prompt for user input
	std::cout << "Input - Slot Name (Not Id): "; //this value should be a slotid (helm/weapon/2hweapon) all values can be found in "stringtoid.h"
	//creates empty variable to store user input
	std::string slotN;
	//gets user input removes spaces and makes all lowercase
	slotN = sconverter.removespaces(sconverter.tolower(console.input()));
	//uses a stringtoid object to convert input string to the correct slotid number
	int slotid = idconverter.slotid(slotN);
	//checks for error flag
	if (slotid != -1) {
		//creates variable to store itemId (defaults to 1)
		int itemid = 1;
		//prompts for user input
		std::cout << "Input - Item Id or Skip: "; //this should be a integer, using an id that is already taken won't work
		//stores input to inputString removes all spaces and converts to all lowercase
		inputString = sconverter.removespaces(sconverter.tolower(console.input()));
		//checks if the input string was skip
		if (inputString != "skip") {
			//stores itemid to variables after using stringutil object to convert the inputstring to int
			itemid = sconverter.toint(inputString);
		}
		//creates a tempitem with the slotid and itemid input
		//if user skipped itemid it will default to 1 and then be changed to the lowest id avaiable above 1
		item tempitem(slotid, itemid);
		//creates loop to deal with inputting stat values
		while (inputString != "done") {
			//prompts user to input stat name
			std::cout << "Input - Stat Name (Not Id) or Done: "; //this should be a statId (armor/strength) values can be found in "stringtoid.h"
			//gets input removes all spaces and sets to lowercase
			inputString = sconverter.removespaces(sconverter.tolower(console.input()));
			//checks to see if user input the exit word
			if (inputString != "done") {
				//prompts for user to input stat value
				std::cout << "Input - Stat Value: "; //this should be an integer between 1-1,000,000
				//converts the previous user input to the statid value using stringtoid object
				int statid = idconverter.statid(inputString);
				//checks for error flag
				if (statid != -1) {
					//gets user input removes all spaces sets to lowercase and converts input to integer
					int statvalue = sconverter.toint(sconverter.removespaces(sconverter.tolower(console.input())));
					//checks to see if stat value input is above acceptable range
					if (statvalue > 0) {
						//sets stat input to the stat value input
						tempitem.setStat(statid, statvalue);
					}
					else {
						//outputs error if stat value is outside of accepted range
						//toint will default to -1 if no integers are present in input and so will be out of range
						std::cout << "Invalid Stat Value\n";
					}
				}
				//error for if the stat name input was not recognized
				else {
					std::cout << "Invalid Stat Name\n";
				}
			}
			//loop continues if user did not input "done" and allows more than one stat to be added to the item
		}
		//adds the item after the user is done inputting stats
		items.additem(tempitem);
		//checks if size increased
		if (items.gettotal() > dbsize) {
			//output to confirm operation completed successfully
			std::cout << "Item Added\n";
		}
		else {
			//outputs error if size did not increase
			std::cout << "Adding Item Failed\n";
		}
	}
	//error for if slot name input was not recognized 
	else {
		std::cout << "Invalid Slot Name\n";
	}
}

void settingsf(simulate& standard){
	stringutil sconverter;
	consoleutil console;
	stringtoid idconverter;
	//prompts for input
	std::cout << "\nInput settings name: "; //this should be a settingsId values can be found in "stringtoid.h"
	//gets input, changes to lowercase, removes all spaces, and converts to settingsid value
	int settingid = idconverter.settingsid(sconverter.removespaces(sconverter.tolower(console.input())));
	//checks for reset flag
	if (settingid == 8) {
		standard.setSetting(settingid, 1);
	}
	//check to see if conversion failed
	else if (settingid != -1) {
		//prompt for input
		std::cout << "Input setting value (for doubles input value x 100): "; //this should be an integer between 1-1,000,000
		//gets input changes to lowercase, removes spaces, and changes to int
		int x = sconverter.toint(sconverter.removespaces(sconverter.tolower(console.input())));
		//checks for error flag
		if (x != -1) {
			//changes settings with values given
			standard.setSetting(settingid, x);
			//cannot confirm but outputs confirmation that program tried to change value
			std::cout << "Attempted Stat Change\n";
		}
		else {
			//outputs error message
			std::cout << "Invalid Value";
		}
	}
	else {
		//outputs error message
		std::cout << "Invalid Setting Name\n";
	}
}

//function to load savefile
void load(itemdatabase& items, unit& player, simulate& standard) {

	//attempts to open safefile
	std::ifstream file("saveinfo.txt");
	//checks if file is good
	if (!file.good()) {
		//creates file if it does not exist
		std::ofstream file2("saveinfo.txt");
		//this sets the itemtotal to 0 and player loadout to all empty objects
		//this makes it so itemarray loop will be skipped over - itemdatabase always starts with an empty object at itemid 0
		for (int i = 0; i < 18; i++) {
			file2 << 0 << " ";
		}
		//this gets the default simulation settings and stores those to the savefile
		for (int i = 0; i < 8; i++) {
			file2 << standard.getSetting(i) << " ";
		}
		//savefile endflag
		file2 << -999;
	}
	//clears ifstream object to refresh it
	file.clear();
	//reopens savefile
	file.open("saveinfo.txt");

	//creates a stringstream to save the file buffer to
	//this allows the information to be access one piece at a time seperate by " "
	std::stringstream buffer;
	buffer << file.rdbuf();

	//creates and gets itemTotal from buffer, first save value
	int itemTotal;
	buffer >> itemTotal;

	//This loop will all items to the item array
	for (int i = 0; i < itemTotal; i++) {
		//creates temp item object to store item information
		item temp;
		//creates two variables to hold values from the buffer
		int x;
		int y;
		//gets and sets values from the buffer
		buffer >> x;
		buffer >> y;
		//runs a loop until it finds endflag for stats, -1 in the x position signifies not to add any more stats
		while (x != -1) {
			//checks for savefile endflag
			if (x == -999 || y == -999) {
				//outputs appropriate error message
				std::cout << "Error Save File Corrupted - Please Delete";
				//exit - flag 2
				exit(2);
			}
			//checks to make sure value with be within stats array bounds
			if (x > 15 || x < 0) {
				//outputs appropriate error message
				std::cout << "Error Save File Corrupted - Please Delete";
				//exit - flag 3
				exit(3);
			}
			//sets stat on temp item object
			temp.setStat(x, y);
			//gets next two values from the buffer
			buffer >> x;
			buffer >> y;
		}
		//after adding stats is done loads new value over -1 end flag, this is the slotId
		buffer >> x;
		//checks for savefile endflag
		if (x == -999 || y == -999) {
			//outputs appropriate error message
			std::cout << "Error Save File Corrupted - Please Delete";
			//exit - flag 4
			exit(4);
		}
		//sets slotId and itemId values of temp objects
		temp.setSlot(x);
		temp.setitemId(y);
		//checks if object is a none object, itemdatabase only needs one of these will skip
		if (x != 16) {
			//adds temp item to the itemdatabase, this will copy the item to the itemdatabase array
			items.additem(temp);
		}
	}

	//This loop will load the saved player loadout
	for (int i = 0; i < 17; i++) {
		//creating variable to store buffer information
		int x;
		//sets value from buffer into x
		buffer >> x;
		//checking for savefile endflag
		if (x == -999) {
			//outputs appropriate error message
			std::cout << "Error Save File Corrupted - Please Delete";
			//exit - flag 5
			exit(5);
		}
		//uses special class function to bypass setItem and access unit item array directly by index (i)
		//getitem gets the item with (x) itemId from the itemdatabase
		//setItem would likely work fine here but this bypasses a few edge case issues
		player.setItemDirect(items.getitem(x), i);
	}

	//This loop will load all the saved simulation settings
	for (int i = 0; i < 8; i++) {
		//creating variable to store buffer information
		int x;
		//sets value from buffer into x
		buffer >> x;
		//checking for savefile endflag
		if (x == -999) {
			//outputs appropriate error message
			std::cout << "Error Save File Corrupted - Please Delete";
			//exit - flag 6
			exit(6);
		}
		//sets setting (i) to value (x)
		//setSetting function will do most of the work here
		standard.setSetting(i, x);
	}

	//creating variable to store buffer information
	int x;
	//sets value from buffer into x
	buffer >> x;
	//checking for savefile endflag - the endflag should be here
	if (x != -999) {
		//outputs appropriate error message
		std::cout << "\nSave File Corruption Detected\n";
		//if program hasn't crashed here there is no reason to exit
	}

	//closes savefile
	file.close();
}

void save(itemdatabase& items, unit& player, simulate& standard) {

	//removing old save file
	std::remove("saveinfo.txt");
	//creating new savefile to write to
	std::ofstream file("saveinfo.txt");

	//saving itemtotal
	int itemtotal = items.gettotal();
	//itemtotal will be one less because the first empty item won't be saved
	//itemdatabase always starts with it
	file << (itemtotal - 1) << " ";
	
	//looping through all items
	//i starts at 1 is because items[0] in itemdatabase is always an empty item that it starts with
	for (int i = 1; i < itemtotal; i++) {
		//creates temp item to store item in
		item temp;
		//uses special function to access itemdatabase items array directly by index
		//this bypasses needing to use itemids for the items which can't be accessed by the program
		temp = items.getitemdirect(i);
		//this loop gets all the stat values from the item object
		for (int i = 0; i < 16; i++) {
			//variable to stop stat value
			int sV = temp.getStat(i);
			//if the value is not 0 saves to the file
			if (sV != 0) {
				//saved statId (i) and the statvalue (sV) to the file
				file << i << " " << sV << " ";
			}
		}
		//after all stats have been saved adds stats end flag, itemId, and slotId
		file << -1 << " " << temp.getitemId() << " " << temp.getSlot() << " ";
	}

	//looping through every item stored by the unit object, this is the player loadout
	for (int i = 0; i < 17; i++) {
		//uses special function to direct access unit items array by index (i)
		//gets the itemId of the item stored in each slot stores that (this is all that is needed to reload player loadout later)
		file << player.getItemDirect(i).getitemId() << " ";
	}

	//looping through all simulation settings
	for (int i = 0; i < 8; i++) {
		//gets the value of each setting to store to the savefile
		//getSetting does most of the work here
		file << standard.getSetting(i) << " ";
	}

	//adding end flag and outputting that save was done
	file << -999;
	std::cout << "Savefile Created";

}
