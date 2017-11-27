// Thread_TicketAgent.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <thread>         // std::thread
#include <sstream>
#include <time.h>
#include <mutex>
#include <chrono>

const int TOTAL_NUMB_TICKETS = 200;
const int TOTAL_TICKET_AGENTS =20;
const int TICKETS_PER_AGENT =10;
const int SLEEP_DURATION_IN_MILLISECONDS =10;

using namespace std;


//*************************************** global value, live for life of process*************************
int numTickets = TOTAL_NUMB_TICKETS;	//accessible from anywhere if you use extern (ie extern numTickets; in other file)
//static int numTickets;				//also global but only accessible in this file (compilation unit)
//*************************************** functions ****************************

//only sell 10 per agent
void sell_10_Each(int agent){
	for (int i = 0; i < TICKETS_PER_AGENT; i++)
	{
		--numTickets;
		cout<<"Agent "<<agent<<" sold 1 ticket"<<endl;
	}
}
void sequential(){

	//need some ticketagents
	vector<int> myAgents;
	for(int i=0; i<TOTAL_TICKET_AGENTS;i++)
		myAgents.push_back(i);
	
	//------- start timer --------
	clock_t start, finish;
	start = clock();


	for (int i = 0; i < TOTAL_TICKET_AGENTS; i++)
	{
		sell_10_Each( i);
	}
	
	//------- stop timer --------
	finish = clock();
	cout<<endl<<"Total clock cycles = "<<(finish - start)<<endl;
	cout<<endl<<"Number Tickets Remaining "<<numTickets<<endl;
}

//*************************************** Where synchronization will happen eventually *************************

//sell until all gone-----------------BAD
//void sellAsManyAsPossible( int agent){
//	while (numTickets>0){	
//		//snooze for a bit, get at least 1 ms and yield the time slice to boot
//		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
//
//		cout<<"Agent "<<agent<<" sold 1 ticket"<<endl;
//		--numTickets;										//*************move these 2 around		
//	}
//}

std::mutex gMyMutex;

////sell until all gone -----------------BETTER
//void sellAsManyAsPossible( int agent){
//	while (numTickets>0){		
//		gMyMutex.lock();
		//snooze for a bit, get at least 1 ms and yield the time slice to boot
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
//
//		if ( numTickets>0){
//			--numTickets;										//*************move these 2 around		
//			cout<<"Agent "<<agent<<" sold 1 ticket"<<endl;
//		}
//		gMyMutex.unlock();
//	}
//}

////sell until all gone -----------------BEST cant forget to unlock
void sellAsManyAsPossible( int agent){
	while (numTickets>0){		
		std::lock_guard<std::mutex> guard(gMyMutex);
		//snooze for a bit, get at least 1 ms and yield the time slice to boot
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if ( numTickets>0){
			--numTickets;										//*************move these 2 around		
			cout<<"Agent "<<agent<<" sold 1 ticket"<<endl;
		}
}
}

//more natural but output may be jumbled
void concurrent(){
	//note that this is stack based and shared between threads
	//stack based variables exist in the stack frame if the function returns
	//the frame is removed and all local vars go out of scope.  If the thread is
	//still alive and has a pointer to a local var that went out of scope then its a dangling
	//pointer, it points to nothing although the thread does not know this.
	//Solution : data should be static (precede var name with static) or global (outside a function)
	//int numbTickets = TOTAL_NUMB_TICKETS;

	//need some ticketagents
	vector<int> myAgents;
	for(int i=0; i<TOTAL_TICKET_AGENTS;i++)
		myAgents.push_back(i);

	//------- start timer --------
	clock_t start, finish;
	start = clock();

	//create the threads
	std::vector<std::thread> threads;
	for(int i = 0; i < TOTAL_TICKET_AGENTS; ++i){
		threads.push_back(std::thread(sellAsManyAsPossible,myAgents[i]));	//*************CHANGE HERE
	}

	//wait for all threads to finish
	//what if you dont join and just exit?
	//program crashes 
	std::vector<std::thread>::iterator itr;
	for ( itr = threads.begin(); itr != threads.end(); ++itr )
		itr->join();
 
	//doing above with plain iterator
    //for(auto& thread : threads)
    //    thread.join();

	//------- stop timer --------
	finish = clock();
	cout<<endl<<"Total clock cycles = "<<(finish - start)<<endl;
	cout<<endl<<"Number Tickets Remaining "<<numTickets<<endl;
}

int main()
{
	sequential();
//	concurrent();	
	return 0;
}


