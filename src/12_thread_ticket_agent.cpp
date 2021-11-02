// Thread_TicketAgent.cpp : Defines the entry point for the console application.
//


#include <vector>
#include <iostream>
#include <thread>         // std::thread
#include <sstream>
#include <time.h>
#include <mutex>
#include <chrono>

using namespace std;

//*************************************** global values, live for life of process*************************
const int TOTAL_NUMB_TICKETS = 200000;
const int TOTAL_TICKET_AGENTS =20;
int numTickets = TOTAL_NUMB_TICKETS;	//accessible from anywhere if you use extern (ie extern numTickets; in other file)
mutex m;
mutex m_r;

//because using m_r, can have 1 thread reporting while another 
//decrements numTickets (increases concurrency)
void report(int i){
	lock_guard<mutex> lck(m_r);
	cout<<" agent "<<i<<" sold a ticket"<<endl;
}
//sell until all gone
void sellAsManyAsPossible( int agent){
	while (true){	
		//snooze for a bit, get at least 1 ms and yield the time slice to boot
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		
		report(agent);
		
		lock_guard<mutex> lck(m);
		if(numTickets>0)
			--numTickets;
		else
			break;		
	}
}

int main()
{
	thread t1(sellAsManyAsPossible,1);
	thread t2(sellAsManyAsPossible,2);
	thread t3(sellAsManyAsPossible,3);

	t2.join();
	t1.join();
	t3.join();
	
	cout<<endl<<"Number Tickets Remaining "<<numTickets<<endl;
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

