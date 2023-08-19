#include "pch.h"

#pragma once
class stringtoid{
public:
	//converts setting name to number in settings array
	int settingsid(std::string);
	//converts string to correct item id - itemid is the slot a certain item should go in the unit items array
	int itemid(std::string);
	//converts string to correct stat id - stat id is the id for stats on items
	int statid(std::string);
	//converts string to correct slot id - slot id is the item type on items
	int slotid(std::string);
	//converts item id to string
	std::string itemidr(int);
	//converts stat id to string
	std::string statidr(int);
	//converts slot id to string
	std::string slotidr(int);
private:
	//stores all names of settings in lowercase no spaces
	std::string settingsIdnames[9] = { "enragepercentage", "baseattackspeed", "enrageattackspeed", "enrageattackmodifier", "mindamage", "maxdamage", "elementid", "rounds", "reset"};
	//stores all the names of item slots in lowercase no spaces
	std::string itemIdnames[17] = { "helm", "neck", "shoulder", "back", "chest", "wrist", "hand", "waist", "leg", "foot", "ring", "ring2", "trinket", "trinket2", "weapon", "offhand", "relic"};
	//stores all the names of slots in lowercase no spaces
	std::string slotIdnames[17] = { "helm", "neck", "shoulder", "back", "chest", "wrist", "hand", "waist", "leg", "foot", "ring", "trinket", "weapon", "2hweapon", "offhand", "relic", "none"};
	//stores all the names of stats in lowercase no spaces
	std::string statIdnames[16] = { "armor", "strength", "agility", "intellect", "spirit", "defense", "block", "blockrating", "parry", "dodge", "resilience", "meleehit", "spellhit", "expertise", "meleecritrating", "spellcritrating"};
};

