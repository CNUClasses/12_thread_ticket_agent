/*
 * Theatre.cpp
 *
 *  Created on: Nov 3, 2021
 *      Author: keith
 */

#include "Theatre.h"

namespace KP {

Theatre::Theatre(int capacity):capacity(capacity),numPeopleInThreatre(NONE) {
	
}

Theatre::~Theatre() {
}

bool Theatre::enter(int numPeople){
//	std::lock_guard<std::mutex> lck(m);
	if( (getnumPeopleInThreatre() + numPeople) > capacity)
		return false;
	
	numPeopleInThreatre += numPeople;
	return true;
}

} /* namespace KP */

