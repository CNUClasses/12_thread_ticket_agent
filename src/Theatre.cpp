/*
 * Theatre.cpp
 *
 *  Created on: Mar 30, 2023
 *      Author: keith
 */

#include "Theatre.h"

Theatre::~Theatre() {
}

Theatre::Theatre(int capacity):capacity(capacity),num_people_in_theatre(0) {

}

bool Theatre::enter(){
	std::lock_guard<std::mutex> lck(m);
	if(isfull())
		return false;

	num_people_in_theatre++;
	return true;
}

