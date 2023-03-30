#include <thread>
#include <iostream>
#include "TM.h"
#include "Theatre.h"
using namespace std;

const int START_WITH=5000;
int num_tickets=START_WITH;
TM tm1;
std::mutex m1;
std::mutex report_mutex;
Theatre t1(2500);
Theatre t2(2500);

void report(int agentid,string s){
	std::lock_guard<std::mutex> lck(report_mutex);
	cout<<"Agent "<<agentid<<":"<<s<<endl;
}

//write class to show how many tickets are really sold
void selltickets(int agentid){
	report(agentid,"starting shift");
	while(true){
		{
			std::lock_guard<std::mutex> lck(m1);
			if(num_tickets==0)
				break;

			num_tickets--;
		}

		//enter theatre
		if(!t1.enter())
			if(!t2.enter())
				report(agentid,"OH NO we are oversold!");

		tm1.add();
		report(agentid,"sold a ticket");
	}
	report(agentid,"ending shift");
}

int main() {
	thread t1(selltickets,1);
	thread t2(selltickets,2);
	thread t3(selltickets,3);

	t2.join();
	t1.join();
	t3.join();

	cout<<"think we sold "<<(START_WITH-num_tickets)<<" tickets"<<endl;
	cout<<"Actually sold "<<tm1.num_tickets_sold<<" tickets"<<endl;

	return 0;
}
