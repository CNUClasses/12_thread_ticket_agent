// Thread_TicketAgent.cpp : Defines the entry point for the console application.
//


#include <vector>
#include <iostream>
#include <thread>         // std::thread
#include <sstream>
#include <time.h>
#include <mutex>
#include <chrono>
#include <vector>
#include "Theatre.h"

using namespace std;

//*************************************** global values, live for life of process*************************
const int TOTAL_NUMB_TICKETS = 200000;
const int TOTAL_TICKET_AGENTS =20;
const int NUMB_THEATRES = 2;
int numTickets = TOTAL_NUMB_TICKETS;	//accessible from anywhere if you use extern (ie extern numTickets; in other file)
mutex m;
mutex m_r;
//set up the theatres	
KP::Theatre threatre1(TOTAL_NUMB_TICKETS/NUMB_THEATRES);
KP::Theatre threatre2(TOTAL_NUMB_TICKETS/NUMB_THEATRES);


//because using m_r, can have 1 thread reporting while another 
//decrements numTickets (increases concurrency)
//void report(int i){
//	lock_guard<mutex> lck(m_r);
//	cout<<" agent "<<i<<" sold a ticket"<<endl;
//}
//because using m_r, can have 1 thread reporting while another 
//decrements numTickets (increases concurrency)
void report(int i, string s){
	lock_guard<mutex> lck(m_r);
	cout<<" agent "<<i<<":"<<s<<endl;
}

bool enterTheatre(){
	if(!threatre1.enter())
		if(!threatre2.enter())
			return false;
	return true;
}
//sell until all gone
void sellAsManyAsPossible( int agent){
	while (true){	
		//snooze for a bit, get at least 1 ms and yield the time slice to boot
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		
//		report(agent, "about to sell ticket");		
		{
			lock_guard<mutex> lck(m);
			if(numTickets>0)
				--numTickets;
			else
				break;
		}

		//choose a theatre
		if(!enterTheatre())
			report(agent, "OH NO! customer could not get in!");			
		//if you have the following line and do not protect the theatre.enter() method
		//then you get the right result for numPeopleInThreatre.  Comment out following line you do not
//		report(agent, "sold a ticket");
	}
}

int main()
{	
	thread t1(sellAsManyAsPossible,1);
	thread t2(sellAsManyAsPossible,2);
	thread t3(sellAsManyAsPossible,3);
	thread t4(sellAsManyAsPossible,4);

	t2.join();
	t1.join();
	t3.join();
	t4.join();
	
	cout<<"Number Tickets Remaining "<<numTickets<<endl;
	
	cout<<"theatre1 contains "<<threatre1.getnumPeopleInThreatre()<<" people"<<endl;
	cout<<"theatre2 contains "<<threatre2.getnumPeopleInThreatre()<<" people"<<endl;
	return 0;
}


//start with below and wind up with above
//void sellAsManyAsPossible( int agent){
//	while (numTickets>0){	
//		//snooze for a bit, get at least 1 ms and yield the time slice to boot
//		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
//		
//		cout<<" agent "<<i<<" sold a ticket"<<endl;
//		
//		--numTickets;
//	}
//}
//
//int main()
//{
//	sellAsManyAsPossible(1);
//	
//	cout<<endl<<"Number Tickets Remaining "<<numTickets<<endl;
//	return 0;
//}


//may be a use case for raw mutexes? 
//but likely hard to guarantee unlock called
//void fun1(){
//	m.lock();
//}
//
//void fun2(){
//	m.unlock();
//}

