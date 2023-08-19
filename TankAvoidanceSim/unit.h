#include "pch.h"
#include "item.h"

#pragma once
class unit{
public:
	//sets item on the player to be equal to the item passed to the function
	//item to change is determined by the passed item's slotId, slot is for rings and trinkets
	void setItem(item newItem, int slot);
	//function to setitem directly by index
	void setItemDirect(item newItem, int i);
	//function to getitem directly by index
	item getItemDirect(int i) const;
	//function to unequip item
	void unequipItem(int slotId);
	//function to update avoidance stats
	void updateStats();
	//returns damage taken from a hit, damage is the raw damage amount, elementId is the element type (physical, arcane, fire, etc.) - can return 0
	double hit(double damage, int elementId);
	//returns hp regenerated every tick from hp5
	double regen();
	//prints avoidance stats
	void printAvoidance();
	//prints equipped items
	void printEquipped();
	//constructor
	unit();
	//constuctor to load loadout
	unit(item[17]);

	//returns classid - unused
	//int getClass();
	//return raceid - unused
	//int getRace();
	//updates all stats
	//sets class - unused
	//void setClass(int cI);
	//sets race - unused
	//void setRace(int rI);
	//prints avoidance stats

private:
	//all values set to default level 80 stats with no items against a level 83 mob
	//defense stats
	double phyDamageReduction = 1.07;
	double missChance = 4.4;
	double critHitChance = 5.6;
	double dodgeChance = 4.4;
	double parryChance = 0;
	double blockChance = 0;
	double blockValue = 0;
	double hp5 = 12;

	//stores item values, start with 17 empty items
	//item Ids
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
	//Ring2 = 11 //from here the ids no longer match slot ids
	//Trinket = 12
	//Trinket2 = 13
	//Weapon Slot = 14
	//Off Hand Slot = 15
	//Relic/Idol/Sigil/Ammo = 16
	item items[17];

	//Class Ids - unused
	//Paladin = 0
	//Warrior = 1
	//Druid = 2
	//Death Knight = 3
	//int classId = 0;
	//Race Ids - unused
	//Human = 0
	//Dwarf = 1
	//Night Elf = 2
	//Gnome = 3
	//Draenei = 4
	//Orc = 5
	//Troll = 6
	//Tauren = 7
	//Undead = 8
	//Blood Elf = 9
	//int raceId = 0;

	//offensive stats - unused
	//double meleeHit = 0;
	//double spellHit = 0;
	//double expertise = 0;
	//double meleeCrit = 5.22;
	//double meleeHaste = 0;

	//resistances - unused
	//double arcaneResist = 0;
	//double fireResist = 0;
	//double natureResist = 0;
	//double frostResist = 0;
	//double shadowResist = 0;

};

