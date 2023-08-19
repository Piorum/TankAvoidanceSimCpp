#include "pch.h"
#include "unit.h"

#pragma once
class simulate{
public:

	//sets setting takes array position and value to set
	void setSetting(int, int);

	//fucntion to get settings value as int
	int getSetting(int) const;

	void runsim(unit target); //Runs simulation with the saved parameters

private:

	//settings
	//enragePercentage = 0
	//savedattackSpeed = 1
	//enrageattackSpeed = 2
	//enrageattackModifier = 3
	double doubleSettings[4] = { 0.95, 3.0, 2.15, 1.25 };

	//settings2
	//minDamage = 0
	//maxDamage = 1
	//elementId = 2
	//rounds = 3
	int intSettings[4] = { 79000, 81000, 0, 10000 };

};

