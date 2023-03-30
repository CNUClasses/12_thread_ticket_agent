/*
 * Theatre.cpp
 *
 *  Created on: Nov 4, 2021
 *      Author: keith
 */

#include "Theatre.h"

namespace KP {

Theatre::Theatre(int cap):capacity(cap),curr_numb_people(NONE) {
}

Theatre::~Theatre() {
}

bool Theatre::enter(int numbpeople){
	std::lock_guard<std::mutex> lck(m_th);
	//if code looks like the following then you get deadlock 
	//if( (get_curr_numb_people() + numbpeople)<=capacity){
	//show how to suspend process to see where deadlock has occurred
	if( (curr_numb_people + numbpeople)<=capacity){
		curr_numb_people+=numbpeople;
		return true;
	}
	return false;
}
int Theatre::get_curr_numb_people(){
	std::lock_guard<std::mutex> lck(m_th);
	return curr_numb_people;};

} /* namespace KP */
