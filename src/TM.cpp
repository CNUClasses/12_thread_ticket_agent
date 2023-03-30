/*
 * TM.cpp
 *
 *  Created on: Mar 30, 2023
 *      Author: keith
 */

#include "TM.h"

//how many tickets did we actually sell
TM::TM():num_tickets_sold(0){}

void TM::add(){
	std::lock_guard<std::mutex> lck(m);
	num_tickets_sold++;
}

TM::~TM() {
	// TODO Auto-generated destructor stub
}

