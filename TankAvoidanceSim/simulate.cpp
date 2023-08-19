#include "pch.h"
#include "simulate.h"

//toggle to print avoidance information
const bool Adebug = false;

//function to set a simulation settings
void simulate::setSetting(int u, int x){
	//checks to make sure value isn't out of range
	if (u > 8 || u < 0) {
		//outputs appropriate error message
		std::cout << "Invalid Array Position\n";
		//exits function
		return;
	}
	else if (u == 8) {
		doubleSettings[0] = 0.95;
		doubleSettings[1] = 3.0;
		doubleSettings[2] = 2.15;
		doubleSettings[3] = 1.25;
		intSettings[0] = 79000;
		intSettings[1] = 81000;
		intSettings[2] = 0;
		intSettings[3] = 10000;
		std::cout << "Simulation Settings Reset\n";
	}
	//checks if value is within range to chance an integer setting
	else if (u > 3) {
		//shifts value down 4 to make intSettings array
		u -= 4;
		//makes sure value is postive - elementId(intSettings[2]) can be 0
		if (x <= 0 && u != 2) {
			std::cout << "Error cannot set setting to that value";
		}
		//sets value to value passed
		intSettings[u] = x;
	}
	//if value is within range + not in range of intSettings must be a doubleSetting
	else {
		//sets a double to the input integer
		double y = x;
		//makes sure value is postive
		if (x <= 0) {
			std::cout << "Error cannot set setting to that value";
		}
		//sets value to value passed divided by 100, this is so that numbers smaller than 1 can be passed by int - temporary solution?
		doubleSettings[u] = (y / 100);
	}
}

int simulate::getSetting(int u) const{
	//checks to make sure value isn't out of range
	if (u > 7 || u < 0) {
		//outputs appropriate error message
		std::cout << "Invalid Array Position\n";
		//exits function
		return 0;
	}
	//checks if value is within range to chance an integer setting
	else if (u > 3) {
		//shifts value down 4 to make intSettings array
		u -= 4;
		//sets value to value passed
		return intSettings[u];
	}
	//if value is within range + not in range of intSettings must be a doubleSetting
	else {
		//sets a double to the input integer
		double y = doubleSettings[u] * 100;
		//sets value to value passed divided by 100, this is so that numbers smaller than 1 can be passed by int - temporary solution?
		return y;
	}
}

//function to run simulation
void simulate::runsim(unit target){

	//creates empty variable to store damage of each attack
	double attackDamage;
	//function to store total damage taken
	double damageTaken = 0;
	//variable that stores what round enrage modifiers should take place
	double enrage = intSettings[3] * doubleSettings[0];
	//saves base attack speed to new variable so not modify saved value
	double attackSpeed = doubleSettings[1];
	//sets to base attack modifier
	double attackModifier = 1;

	//loops until enrage
	for (int i = 0; i < enrage; i++) {
		//calculates attack damage with random value for man and min damage
		attackDamage = ((intSettings[0] + (rand() % (intSettings[1] - intSettings[0]))) / attackSpeed) * attackModifier;
		//uses hit function to get the real damage taken after avoidance values from unit
		damageTaken += target.hit(attackDamage, intSettings[2]);
	}
	//sets attackspeed to enrage value
	attackSpeed = doubleSettings[2];
	//sets attack damage modifier to enrage value
	attackModifier = doubleSettings[3];
	//loops for remaining rounds
	for (int i = 0; i < (intSettings[3] - enrage); i++) {
		//calculates attack damage with random value for man and min damage
		attackDamage = ((intSettings[0] + (rand() % (intSettings[1] - intSettings[0]))) / attackSpeed) * attackModifier;
		//uses hit function to get the real damage taken after avoidance values from unit
		damageTaken += target.hit(attackDamage, intSettings[2]);

	}
	//averages damage taken over every round and outputs it, this allows the random low chance values like dodge and parry to impact the average damage taken
	//each round is averaged to the damage every 1 second, while not 100% accurate this allows for a better average with the most impact being on error range
	std::cout << (damageTaken / intSettings[3]) << " dTps\n";

	//will print avoidance information of unit tested if toggle is set to true (this toggle is found at the top of "simulate.cpp"
	if (Adebug) target.printAvoidance();

}
