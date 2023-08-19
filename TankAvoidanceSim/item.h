#include "pch.h"
#include "stringtoid.h"

#pragma once
class item{
public:
	//resets stats to 0
	void resetStats();
	//sets slot id (takes slotId)
	void setSlot(int sI);
	//set stat (takes statId, statValue)
	void setStat(int sI, int sV);
	//sets itemId
	void setitemId(int iI);
	//returns slotId
	int getSlot() const;
	//returns stat of a certain id
	int getStat(int sI) const;
	//returns item id
	int getitemId() const;
	//prints item information
	void printItem() const;
	//overloading == operator to compare slotId and stats
	bool operator==(const item&) const;
	//constructors
	//requires slotId and itemId
	item(int sI, int iI);
	//requires slotId
	item(int sI);
	item();
private:
	//slot Ids - stores the slotid
	//Helm = 0
	//Neck = 1
	//Shoulder = 2
	//Back = 3
	//Chest = 4
	//Wrist = 5
	//Hand = 6
	//Waist = 7
	//Leg = 8
	//Foot = 9
	//Ring = 10
	//Trinket = 11
	//Weapon = 12
	//Two-Handed Weapon = 13
	//Off Hand = 14
	//Relic/Idol/Sigil/Ammo = 15
	//Misc or None = 16
	int slotId = 16;

	//StatsArray - Stores all the stat values
	//Armor = 0
	//Strength = 1
	//Agility = 2
	//Intellect = 3
	//Spirit = 4
	//Defense = 5
	//Block = 6
	//Block Rating = 7
	//Parry = 8
	//Dodge = 9
	//Resilience = 10
	//Melee Hit = 11
	//Spell Hit = 12
	//Expertise = 13
	//Melee Crit Rating = 14
	//Spell Crit Rating = 15
	int stats[16];

	//stores item id
	int itemId = -1;
};

