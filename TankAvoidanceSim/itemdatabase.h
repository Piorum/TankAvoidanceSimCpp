#include "pch.h"
#include "item.h"

#pragma once
class itemdatabase{
public:
	//adds an item to the saved items array
	void additem(item);
	//function to return item with certain id
	item getitem(int) const;
	//funciton to get item direction with array index
	item getitemdirect(int) const;
	//function to return total items
	int gettotal() const;
	//function to print out all items saved, int is for sorting options
	void printitems(int) const;
	//constructor
	itemdatabase();
private:
	//stores the amount of items doubles for array size
	int itemtotal = 0;
	//stores all the item ids in order with the items array
	int* ids;
	//stores all the item objects
	item* items;
};

