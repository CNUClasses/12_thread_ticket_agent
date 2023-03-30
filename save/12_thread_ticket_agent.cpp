// Thread_TicketAgent.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <iostream>
#include <thread>         // std::thread
#include <sstream>
#include <time.h>
#include <mutex>
#include <chrono>
#include <atomic>
#include "Theatre.h"
using namespace std;
const int TOTAL_NUMB_TICKETS = 200;
const int TOTAL_TICKET_AGENTS =20;
atomic<int> numTickets(TOTAL_NUMB_TICKETS);	//accessible from anywhere if you use extern (ie extern numTickets; in other file)
 
mutex m;
mutex m1;

KP::Theatre th1(TOTAL_NUMB_TICKETS/2);
KP::Theatre th2(TOTAL_NUMB_TICKETS/2);

void report(int agent,int numTickets){
	lock_guard<mutex> lck(m1);
	cout<<"Agent "<<agent<<" numbtickets left="<<numTickets<<endl;
}

void report1(string s){
	lock_guard<mutex> lck(m1);
	cout<<s<<numTickets<<endl;
}

//start with below and wind up with above
void sellAsManyAsPossible( int agent){
	int numsold=0;
	
	while(true){
		report(agent, numTickets);
		
		lock_guard<mutex> lck(m);
		if(numTickets==0)
			break;
		
		numTickets--;
		numsold++;
		
		if(!th1.enter(1))
			if(!th2.enter(1))
				report1(to_string(agent)+"BUMMER, oversold");

		report(agent,numTickets);
	}
	lock_guard<mutex> lck(m);
	cout<<"Agent "<<agent<<" LEAVING, sold "<<numsold<<" tickets"<<endl;
}

int main()
{
	thread t1(sellAsManyAsPossible, 1);
	thread t2(sellAsManyAsPossible, 2);
	thread t3(sellAsManyAsPossible, 3);
	
	sellAsManyAsPossible( 4);
	
	t2.join();
	t1.join();
	t3.join();
	
	cout<<endl<<"Number Tickets Remaining "<<numTickets<<endl;
	return 0;
}


//may be a use case for raw mutexes? 
//but likely hard to guarantee unlock called
//void fun1(){
//	m.lock();
//}
//
//void fun2(){
//	m.unlock();
//}

