/*
 * Theatre.h
 *
 *  Created on: Mar 30, 2023
 *      Author: keith
 */

#ifndef THEATRE_H_
#define THEATRE_H_
#include <mutex>

class Theatre {
public:
	virtual ~Theatre();
	Theatre(int capacity);
	bool enter();
private:

	bool isfull(){return num_people_in_theatre==capacity;}
	const int capacity;
	int num_people_in_theatre;
	std::mutex m;

};

#endif /* THEATRE_H_ */
