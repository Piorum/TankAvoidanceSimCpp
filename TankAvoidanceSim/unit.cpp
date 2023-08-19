#include "pch.h"
#include "unit.h"

//function to get the health regen per second of the unit
double unit::regen(){
	return ( hp5 / 5.0 );
}

//function to print avoidance information
void unit::printAvoidance(){
	//prints every value with some text to help identify which value belongs to what variable
	std::cout << "phyDamageReduction: " << phyDamageReduction << "\n";
	std::cout << "missChance: " << missChance << "\n";
	std::cout << "critHitChance: " << critHitChance << "\n";
	std::cout << "dodgeChance: " << dodgeChance << "\n";
	std::cout << "parryChance: " << parryChance << "\n";
	std::cout << "blockChance: " << blockChance << "\n";
	std::cout << "blockValue: " << blockValue << "\n";
	std::cout << "hp5: " << hp5 << "\n";
}

//function to print the item information of all items equipped
void unit::printEquipped(){
	//to check if nothing is equipped
	bool none = true;
	//loops for the amount of items in the items array
	for (int i = 0; i < 17; i++) {
		//checks to see if the item in each slot is an empty item
		if (items[i].getSlot() != 16) {
			//uses items printItem function to print the information of the item in the items array
			items[i].printItem();
			//sets nothing equipped check to false
			none = false;
		}
	}
	if (none) {
		std::cout << "No Items Equipped\n";
	}
}

//constructor - unused
unit::unit(){
}

//constructor takes a items array with 17 items as input
unit::unit(item loadout[17]){
	//loops for all of the values in the items array
	for (int i = 0; i < 17; i++) {
		//sets the correlating items array value to the item in the passed items array
		items[i] = loadout[i];
	}

}

//function to set one of the items on the unit
void unit::setItem(item newItem, int slot){
	//gets slotId from passed item
	int slotId = newItem.getSlot();
	//slotId is parrallel with items array up to 9 so if its within that range set the items[slotId] item to the passed item
	if (slotId < 10 && slotId >= 0) {
		items[slotId] = newItem;
	}
	//switch case for values that are not parallel
	switch(slotId){
		//ring, slot to change between ring 1 and ring 2
		case 10:
			//sets ring slot selected to pass item
			items[10 + slot] = newItem;
			break;
		//trinket, slot to change between trinket 1 and trinket 2
		case 11:
			//sets trinket slot selected to passed item
			items[12 + slot] = newItem;
			break;
		//one-handed weapon
		case 12:
			//sets weapon slot to passed item
			items[14] = newItem;
			break;
		//two-handed weapon
		case 13:
			//sets weapons slot to passed item
			items[14] = newItem;
			//checks to see if there is an off-hand equiped
			if (items[15].getSlot() != 16) {
				//sets offhand to empty object if there is (cannot have off-hand and 2-handed weapon
				items[15].setSlot(16);
				items[15].resetStats();
			}
			break;
		//off-hand
		case 14:
			//sets offhand slot to passed item
			items[15] = newItem;
			//checks to see if there is a two-hand weapon equiped
			if (items[14].getSlot() == 13) {
				//sets weapon to empty object if there is (cannot have 2-handed weapon and off-hand)
				items[14].setSlot(16);
				items[14].resetStats();
			}
			break;
		//relic
		case 15:
			//sets relic slot to passed item
			items[16] = newItem;
			break;
		//default case if id is out of range - unused
		default:

			break;
	}

	//updates avoidance values now that stats have changed
	updateStats();
}

void unit::setItemDirect(item newItem, int i){
	items[i] = newItem;
}

item unit::getItemDirect(int i) const{
	if (i < 0 || i > 16) {
		std::cout << "error value outside of index range";
		return items[0];
	}
	return items[i];
}

//function to unequip item in a certain slot
void unit::unequipItem(int slotId){
	//creates empty item to replace item in slot
	item empty;
	//changes item slot correlated to the value passed to the empty item
	items[slotId] = empty;
	//updates avoidance values now that stats have changed
	updateStats();
}

//function to update all avoidance stats
void unit::updateStats() {
	//majority of these numbers are guesses based off in-game data

	//array to store total stats
	int totalStats[17];
	//initializes all values to 0
	//adds values from every item to the respectice totalstat
	//checks if stat is negative (this could possibly allow you to divide by 0)
	for (int i = 0; i < 17; i++) {
		totalStats[i] = 0;
		for (int i2 = 0; i2 < 17; i2++) {
			totalStats[i] += items[i2].getStat(i);
		}
		if (totalStats[i] < 0) {
			totalStats[i] = 0;
		}
	}
	//this is just based off the armor
	//(armor / (armor + 16635)) * 100
	phyDamageReduction = (totalStats[0] / (totalStats[0] + 16635.0)) * 100.0;
	//number is an estimate
	//base 4.4% chance for enemy to miss
	//miss = ( defense * 0.007 )
	missChance = 4.4 + (totalStats[5] * 0.007);
	//enemy crit chance = base(5.6%) - (resil * 0.0106) + (defense * 0.04)
	critHitChance = 5.6 - ((totalStats[10] * 0.0106) + (totalStats[5] * 0.04));
	if (critHitChance < 0) {
		critHitChance = 0;
	}
	//base 4.4% dodge chance - numbers below are estimates
	//dodge = base + ( defense * 0.007 ) + ( agility * 0.017 ) + ( dodge * 0.022 )
	dodgeChance = 4.4 + (totalStats[5] * 0.007) + (totalStats[2] * 0.017) + (totalStats[9] * 0.022);
	//base 5% parry chance with a weapon
	//cannot parry without weapon
	if (items[14].getSlot() != 16) {
		//base + ( parry * 0.022 ) + ( ( (defense + 400) - 415 ) * 0.04 )
		parryChance = 5.0 + (totalStats[8] * 0.022) + (((totalStats[5] + 400) - 415) * 0.04);
	}
	else {
		parryChance = 0;
	}
	//cannot block without a shield
	if (items[15].getSlot() != 16) {
		//base 5% + ( blockRating * 0.061 ) + ( defense * 0.008 )
		blockChance = 5.0 + (totalStats[7] * 0.061) + (totalStats[5] * 0.008);
		//( block * 1.216 ) + ( strength * 0.049 )
		blockValue = (totalStats[6] * 1.216) + (totalStats[1] * 0.049);
	}
	else {
		blockChance = 0;
		blockValue = 0;
	}
	//( spirit * 0.118 )
	//base hp5 is 12
	hp5 = 12 + (totalStats[4] * 0.118);
}

//function to run a damage number by all avoidance values
double unit::hit(double damage, int elementId) {
	//variable to store total damage amount
	double total = 0.0;
	//adds passed variable
	total += damage;

	//generates random numbers to check if enemy misses/gets paried/dodged/blocked or crits then reduces damage by the correct reduction amount
	if (rand() % 1001 < missChance * 10){
		return 0;
	} else if (rand() % 1001 < dodgeChance * 10) {
		return 0;
	}
	else if (rand() % 1001 < parryChance * 10) {
		return 0;
	}
	else if (rand() % 1001 < blockChance * 10) {
		total -= blockValue;
		if (total < 0) {
			return 0;
		}
	}
	if (rand() % 1001 < critHitChance * 10) {
		total *= 2;
	}
	//only physical damage is used right now
	switch (elementId) {
	case 0:
		total -= (total * (phyDamageReduction / 100));
		break;
	}

	//returns final value
	return total;
}

/* - unused functions
//function to return classId
int unit::getClass() {
	//returns classId
	return classId;
}

//function to return raceId
int unit::getRace() {
	//returns raceId
	return raceId;
}

//function to set classId
void unit::setClass(int cI){
	//sets classId to the passed value
	classId = cI;
}

//function to set raceId
void unit::setRace(int rI){
	//sets raceId to the passed value
	raceId = rI;
}
*/
