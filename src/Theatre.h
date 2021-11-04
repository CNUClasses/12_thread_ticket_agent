/*
 * Theatre.h
 *
 *  Created on: Nov 3, 2021
 *      Author: keith
 */

#ifndef THEATRE_H_
#define THEATRE_H_
#include <mutex>
namespace KP {
const int NONE=0;

class Theatre {
private:
	std::mutex m;
	int capacity;
	int numPeopleInThreatre;
public:
	Theatre(int capacity);
	virtual ~Theatre();
	bool enter(int numPeople=1);
	int getnumPeopleInThreatre(){return numPeopleInThreatre;};
};

} /* namespace KP */

#endif /* THEATRE_H_ */
