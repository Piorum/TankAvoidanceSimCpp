#include "pch.h"
#include "itemdatabase.h"

//function to add an item to the database
void itemdatabase::additem(item newItem){
	//checks to see if item already exists to avoid duplicates
	for (int i = 0; i < itemtotal; i++) {
		//checks if newitem is equal to item in database
		if (items[i] == newItem) {
			//outputs error message
			std::cout << "Item already exists\n";
			//returns
			return;
		}
	}
	//arrayutil object
	arrayutil amanip;
	//creates a temp item and ids array to store all the items and ids
	item* tempitems;
	tempitems = new item[itemtotal];
	int* tempids;
	tempids = new int[itemtotal];
	//fills tempitems array with all the currently stored items
	for (int i = 0; i < itemtotal; i++) {
		tempitems[i] = items[i];
		tempids[i] = ids[i];
	}
	//deletes old item and id arrays
	delete[] items;
	delete[] ids;
	//creates new bigger item and id arrays
	items = new item[itemtotal + 1];
	ids = new int[itemtotal + 1];
	//fills new arrays
	for (int i = 0; i < itemtotal; i++) {
		items[i] = tempitems[i];
		ids[i] = tempids[i];
	}
	//gets the itemId to save to ids
	int newItemId = newItem.getitemId();
	//loops through every value in the id array
	for (int i = 0; i < itemtotal; i++) {
		//checks if newItemId matches one of the ids already present (this would happen if user tried to make two items with the same id)
		if (newItemId == ids[i]) {
			//sets id to the lowest free id
			newItem.setitemId(amanip.lowestFreeNumber(ids, itemtotal));
		}
	}
	//checks if itemId is set to default
	if (newItemId == -1) {
		//gets the lowest free number in the ids array and sets itemId to that
		newItem.setitemId(amanip.lowestFreeNumber(ids, itemtotal));
	}
	//adds new item to the larger items array at the last spot (itemtotal has not been increased yet so this is not out of range)
	items[itemtotal] = newItem;
	//adds new id to the ids array (not out of range for same reason)
	ids[itemtotal] = newItem.getitemId();
	//increases itemtotal
	itemtotal++;
	//cleanup
	delete[] tempitems;
	delete[] tempids;
}

//function to return item correlating to pass id
item itemdatabase::getitem(int id) const{
	//loops for all values in the ids array
	for (int i = 0; i < itemtotal; i++) {
		//checks if value in ids array matches value passed
		if (ids[i] == id) {
			//returns item correlating to id pass (ids and items array are stored in parralell so this works)
			return items[i];
		}
	}
	//if no id stored matched value passed sends error message and returns empty object (this object is created by constructor)
	std::cout << "error no item with that id\n";
	return items[0];
}

item itemdatabase::getitemdirect(int i) const{
	if (i < 0 || i >(itemtotal - 1)) {
		std::cout << "error index out of range";
		return items[0];
	}
	return items[i];
}

int itemdatabase::gettotal() const{
	return itemtotal;
}

//function to print all items in the database
void itemdatabase::printitems(int sort) const{
	//loops for all values in the items array
	for (int i = 0; i < itemtotal; i++) {
		//uses item printitem function to print values of every item in the items array
		items[i].printItem();
	}
}

//constructor
itemdatabase::itemdatabase(){
	//creates an empty item with slot type of none and itemid of 0 (this is not normally possible)
	item empty(16, 0);
	//sets items array to a size of 1
	items = new item[1];
	//sets ids array to size of 1
	ids = new int[1];
	//sets first item in the items array to the empty item
	items[0] = empty;
	//gets itemid off empty object and sets it to the first value in ids
	ids[0] = empty.getitemId();
	//increases itemtotal to 1
	itemtotal = 1;
}

