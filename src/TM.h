/*
 * TM.h
 *
 *  Created on: Mar 30, 2023
 *      Author: keith
 */

#ifndef TM_H_
#define TM_H_
#include <mutex>

class TM {
public:
	TM();
	virtual ~TM();
	void add();

	int num_tickets_sold;
	std::mutex m;
};

#endif /* TM_H_ */
