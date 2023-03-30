/*
 * Theatre.h
 *
 *  Created on: Nov 4, 2021
 *      Author: keith
 */

#ifndef THEATRE_H_
#define THEATRE_H_
#include <mutex>

namespace KP {
const int CAP =100;
const int NONE=0;

class Theatre {
private:
	std::mutex m_th;
	int capacity;  //how many people can hold
	int curr_numb_people;
public:
	Theatre(int cap=CAP);//
	virtual ~Theatre();
	bool enter(int numbpeople=1);
	int get_curr_numb_people();
};

} /* namespace KP */

#endif /* THEATRE_H_ */
