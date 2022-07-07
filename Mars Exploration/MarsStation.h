#ifndef _MarsStation_
#define _MarsStation_
#include"Node.h"
#include"LinkedList.h"
#include"PriorityNode.h"
#include"PriorityQueue.h"
#include"Queue.h"
#include "rover.h"
#include"Queue.h"
#include "mission.h"
#include "Events.h"
#include"UI.h"

#include <fstream>
#include<string>
#include<windows.h>
class MarsStation
{
private:
	UI*ui; //Pointer For User Interface
	Queue<Events*> Eventsqueue; //Queue of Events
	Queue<rover*> Erovers;     //Queue of Emergency Rovers
	Queue<rover*> Mrovers;    //Queue of Mountainous Rovers
	Queue<rover*> Provers;    //Queue of Polar Rovers
	Queue<rover*> InCheckrovers;  //List of CheckUp Rovers
	PriorityQueue<rover*> InExecrovers;  //Priority Queue for in execution rovers so which rover finish first get out first
	PriorityQueue<mission*> Emergmissions; //Priority Queue for Emergency Mission so the most Important mission be in the top 
	Queue<mission*> polarmissions; //Queue for polar mission
	Queue<mission*> Mountmissions; // Queue for Mountainous missions
	Queue<mission*> Compmissions; // Queue for Completed missions
	Queue<rover*> PInCheckUp; //Queue for Polar rovers that in checkup
	Queue<rover*> EInCheckUp; //Queue for Emergency rovers that in checkup
	Queue<rover*> MInCheckUp; //Queue for Mountainous rovers that in checkup
	string Ipfile; //Name of Input file
	string Opfile; //Name of Output file 

protected:
int numMrovers , numProvers , numErovers , speedMrovers ,  speedProvers ,speedErovers , numbefocheck ;//integers to store data from Input file
int CheckMdur , CheckPdur , CheckEdur , AutoP , numofEvents ;
float AutoPromoted; //float to count number of AutoPromoted Missions & get its precentage



   
public:
	MarsStation(); //Constructor of MarsStation
	

	void ExecutEvents(int day); // function to Execute events
	void InsertinMountQueue(mission*); // function to insert Mountainous Missions in Mountainous Queue 
	void InsertinPolarQueue(mission*);//function to insert Polar Missions in Mountainous Queue
	void InsertinEmergqueue(mission*); //function to insert Emergency Missions in Mountainous Queue
	void PromoteEvent(int id); //function to promote Mountainous Mission to Emergency Mission
	void CancelEvent(int id); //fumction to cancel Mountainous Mission
	void ExecuteEmergMission(int day); //function to Execute Emergency missions
	void ExecuteMountmission(int day); //function to Execute Mountainous missions
	void ExecutePolarMission(int day); //function to Execute Polar missions
	void GetFromInExecute(int day); //function to get rovers from its missions
	void GetFromCheckUp(int day); //function to  get rovers from checkup
	void AutoPromote(int day); //function to auto promote Mountainous missions
	int getnumofWaitingMissions(); //function to get number of waited mission of the day
	int getnumofInExecution();  //function to get number of mission in execution of the day
	int getnumofAvailableRover(); //function to get number of available rovers of the day
	int getnumofIncheckUpRover();  //function to get number of rover in checkup
	int getnumofCompletedMission(); //function to get number of completed missions
	void run(); //function that run project
	void readinputfile();//function that Read input file
	void PrintOutPutFile(); //function that produce output file 



	~MarsStation(); // Destructor of MarsStation

};
#endif