#include "pch.h"

//function to get lowest free number in an array above 0
int arrayutil::lowestFreeNumber(int inputarray[], int asize){
	//defaults to 1
	int x = 1;
	//creates bool to check if loop should continue
	bool fail = true;
	//while fail is true continue to loop
	while (fail) {
		//sets fail to false
		fail = false;
		//loops through every value in the array passed
		for (int i = 0; i < asize; i++) {
			//checks to see if x matches the value in the array
			if (x == inputarray[i]) {
				//increases x by one
				x++;
				//sets fail back to true
				fail = true;
			}
		}
	}
	//returns x once the lowest value above 0 in the array has been found
	return x;
}
