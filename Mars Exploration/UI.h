#ifndef _UI_H_
#define _UI_H_

#include<iostream>
#include<string>
using namespace std;
#include"mission.h"
#include"rover.h"
#include"PriorityQueue.h"
#include"Queue.h"

class UI
{
public:
	UI();//constructor
	void PrintString(string ); //to print string in console
	void PrintNum(int);  //to print number on console
	bool WaitEnter();  //wait enter from user
	void NewLine();  //create new line
	//print line of waited missions
	void PrintWaitedMissions(PriorityQueue<mission*>&Emergmissions,Queue<mission*>&polarmissions, Queue<mission*>&Mountmissions );
	//print in execution missions & rovers line
	void PrintIn_Execution(PriorityQueue<rover*>&InExecrovers);
	//print available rovers line
	void PrintAvailableRovers(Queue<rover*>&Erovers,Queue<rover*>&Mrovers,Queue<rover*>&Provers);
	//print in checkup rovers line
	void PrintInCheckUpRovers(Queue<rover*> &PInCheckUp,Queue<rover*> &EInCheckUp,Queue<rover*> &MInCheckUp);
	//print completed missions line
	void PrintCompletedMissions(Queue<mission*> &Compmissions);
	//get integer from user
	void GetInt(int&x);
~UI();//destructor
};
#endif