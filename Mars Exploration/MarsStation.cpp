#include <iostream>
using namespace std;

#include"MarsStation.h"
#include"Formulation.h"
#include"Cancellation.h"
#include"Promotion.h"

MarsStation::MarsStation()
{
	AutoPromoted=0; //intialize AutoPromoted by 0
	ui=new UI;  //create object of user interface
}

void MarsStation::ExecutEvents(int day)
{
  Events*CurrentEvent;
  while(Eventsqueue.peek(CurrentEvent)) //see if there is Event in the Queue
  {
	  if(CurrentEvent->getEventday()>day) // if its day large than current day return
		  return;
	  CurrentEvent->Execute(this);        //if its day equal to current day execute it 
	  Eventsqueue.dequeue(CurrentEvent);
	  delete CurrentEvent;                //then delete it

  
  }
}

void MarsStation::InsertinMountQueue(mission*NMmission)
{
  Mountmissions.enqueue(NMmission);   //insert Mountainous mission in its queue
}

void MarsStation::InsertinPolarQueue(mission*NPmission)
{
	polarmissions.enqueue(NPmission);  //insert polar mission in its queue
}

void MarsStation::InsertinEmergqueue(mission*NEmission)
{
 NEmission->setPriority();  //set priority
 float prio =NEmission->Getpriority(); 
 Emergmissions.enqueue(NEmission,prio); //insert Emergency mission with its priority
}

void MarsStation::PromoteEvent(int id)
{
	Queue<mission*>temp; 
	mission*mis;
	while(!Mountmissions.isEmpty()) //search in the queue of Mountainous missions for the specific Mission to promote it
	{
		Mountmissions.dequeue(mis);
		if(mis->getid()==id)
		{
		 mis->setmissiontype('E'); //change its type
		  mis->setPriority();
		  float prio= mis->Getpriority(); 
		  Emergmissions.enqueue(mis,prio); //insert it with its priority

		
		}
		else
	temp.enqueue(mis);
	
	
	}

	while(!temp.isEmpty()) //refill the Mountaious queue again
	{
	  temp.dequeue(mis);
	  Mountmissions.enqueue(mis);
	}
  
}

void MarsStation::CancelEvent(int id)
{
	Queue<mission*>temp;
	mission*mis;
	while(!Mountmissions.isEmpty())//search in the queue of Mountainous missions for the specific Mission to cancel it
	{
		Mountmissions.dequeue(mis); 
		if(mis->getid()==id)
		{
			delete mis; //delete it after finding it
		}
		else
	       temp.enqueue(mis);
	
	
	}

	while(!temp.isEmpty()) //refill queue of mountainous mission
	{
	  temp.dequeue(mis);
	  Mountmissions.enqueue(mis);
	}
  
}

void MarsStation::ExecuteEmergMission(int day)
{
	mission*mison;
	while(Emergmissions.peek(mison)) //see the mission on the peek to execute it
	{
		rover*rov;

		if(Erovers.dequeue(rov)) //first see if there is rover in list(queue) of emergency rovers
		{
			mison->setdayexecution(day);  //set day that mission executed in 
			mison->setTimeOfExecution(rov->getspeed()); //set time of execution by getting rover speed 
			mison->setFinishDay(); // set the day that mission will finish in
			mison->setwaitedtime(); //set waited time
			rov->setnomissions(rov->getnomissions()+1); // increase number of mission done by rover
			rov->setmission(mison); //set mission to rover
			float priority=-(mison->getFinishDay()); // get finishday as priority of rover 
			InExecrovers.enqueue(rov , priority); // insert it in queue of in execution mission
			Emergmissions.dequeue(mison); //remove mission from Emergency queue
		}
		else if(Mrovers.dequeue(rov)) //then see Mountainous rover if there is no emergency rover
		{
		  mison->setdayexecution(day);//set day that mission executed in
			mison->setTimeOfExecution(rov->getspeed());//set time of execution by getting rover speed
			mison->setFinishDay();// set the day that mission will finish in
			mison->setwaitedtime();//set waited time
			rov->setnomissions(rov->getnomissions()+1);// increase number of mission done by rover
			rov->setmission(mison);//set mission to rover
		    float priority=-(mison->getFinishDay());// get finishday as priority of rover
			InExecrovers.enqueue(rov , priority);// insert it in queue of in execution mission
			Emergmissions.dequeue(mison);//remove mission from Emergency queue
		}
		else if(Provers.dequeue(rov))//finally if there is no Mountainous or Emergency rover execute it by polar rover
		{
		  mison->setdayexecution(day);//set day that mission executed in
			mison->setTimeOfExecution(rov->getspeed());//set time of execution by getting rover speed
			mison->setFinishDay();// set the day that mission will finish in
			mison->setwaitedtime();//set waited time
			rov->setnomissions(rov->getnomissions()+1);// increase number of mission done by rover
			rov->setmission(mison);//set mission to rover
			float priority=-(mison->getFinishDay());// get finishday as priority of rover
			InExecrovers.enqueue(rov , priority);// insert it in queue of in execution mission
			Emergmissions.dequeue(mison);//remove mission from Emergency queue
		}
		else //if there is no available rovers return
			return;
	}

}

void MarsStation::ExecuteMountmission(int day)
{
	mission*mison;
	while(Mountmissions.peek(mison))
	{
		rover*rov;
		if(Mrovers.dequeue(rov)) //first see if there is Mountainous rover
		{                            //steps of setting mission to rover same as Emergency
			mison->setdayexecution(day);
			mison->setTimeOfExecution(rov->getspeed());
			mison->setFinishDay();
			mison->setwaitedtime();
			rov->setnomissions(rov->getnomissions()+1);
			rov->setmission(mison);
			float priority=-(mison->getFinishDay());
			InExecrovers.enqueue(rov , priority);
			Mountmissions.dequeue(mison);
		}
		else if(Erovers.dequeue(rov)) // then Emergency rover
		{
		  mison->setdayexecution(day);
			mison->setTimeOfExecution(rov->getspeed());
			mison->setFinishDay();
			mison->setwaitedtime();
			rov->setnomissions(rov->getnomissions()+1);
			rov->setmission(mison);
		    float priority=-(mison->getFinishDay());
			InExecrovers.enqueue(rov , priority);
			Mountmissions.dequeue(mison);
		}
		else  //if there is no rovers return
			return;
	}
}

void MarsStation::ExecutePolarMission(int day)
{
	mission*mison;
	while(polarmissions.peek(mison)) //executed only by polar rovers
	{
		rover*rov;
		if(Provers.dequeue(rov))
		{
			mison->setdayexecution(day);
			mison->setTimeOfExecution(rov->getspeed());
			mison->setFinishDay();
			mison->setwaitedtime();
			rov->setnomissions(rov->getnomissions()+1);
			rov->setmission(mison);
			float priority=-(mison->getFinishDay());
			InExecrovers.enqueue(rov , priority);
			polarmissions.dequeue(mison);
		}
		else
			return;
	}
}

void MarsStation::GetFromInExecute(int day)
{
	rover*rov;
	while(InExecrovers.peek(rov)) //see the rover in the peek of Inexecution rovers
	{
		if(rov->getmission()->getFinishDay()<=day) //if its finish day less than or equal current day then it have to get out from list
		{
			                                     //see its type to return to its list
		  if(rov->getrovertype()=='E') 
		  {
			  mission*mison;
			  mison =rov->getmission(); //get mission from rover
			  Compmissions.enqueue(mison); //to insert it in completed missions
			  rov->setDayBeforeCheckup(int(mison->getFinishDay())); //every time set that day to make sure if it will go for checkup or not
			  rov->setmission(nullptr); //set mission by null to set rover to another mission
			  InExecrovers.dequeue(rov);  //remove rover from In execution rover
			  if(rov->getnomissions()==rov->getNumBeforeCheck())  //check if it done number of mission needed to go to checkup 
			  {
				  rov->setnomissions(0);  //set mission done by zero for the next checkup
				  EInCheckUp.enqueue(rov);  // insert it in the Emergency queue of rovers in checkup
			  }
			  else
			  Erovers.enqueue(rov);  //if it will not go to checkup return it to its list
		  }
		 if(rov->getrovertype()=='M')
		  {
			  mission*mison;
			  mison =rov->getmission();  //get mission from rover
			  Compmissions.enqueue(mison); //to insert it in completed missions
			  rov->setDayBeforeCheckup(int(mison->getFinishDay()));  //every time set that day to make sure if it will go for checkup or not
			  rov->setmission(nullptr);  //set mission by null to set rover to another mission
			  InExecrovers.dequeue(rov); //remove rover from In execution rover
			  if(rov->getnomissions()==rov->getNumBeforeCheck())  //check if it done number of mission needed to go to checkup
			  {
				  rov->setnomissions(0);  //set mission done by zero for the next checkup
				  MInCheckUp.enqueue(rov); // insert it in the Mountainous queue of rovers in checkup
			  }
			  else
			  
			  Mrovers.enqueue(rov); //if it will not go to checkup return it to its list
		  }
		 if(rov->getrovertype()=='P')
		  {
			  mission*mison;
			  mison =rov->getmission(); //get mission from rover
			  Compmissions.enqueue(mison); //to insert it in completed missions
			  rov->setDayBeforeCheckup(int(mison->getFinishDay())); //every time set that day to make sure if it will go for checkup or not
			  rov->setmission(nullptr);  //set mission by null to set rover to another mission
			  InExecrovers.dequeue(rov);  //remove rover from In execution rover
			  if(rov->getnomissions()==rov->getNumBeforeCheck()) //check if it done number of mission needed to go to checkup
			  {
				  rov->setnomissions(0); //set mission done by zero for the next checkup
				  PInCheckUp.enqueue(rov);  // insert it in the polar queue of rovers in checkup
			  }
			  else
			  
			  Provers.enqueue(rov); //if it will not go to checkup return it to its list
		  }
		}
		else
			return;
	
	
	}
}

void MarsStation::GetFromCheckUp(int day)
{
	rover*rov;
	while(EInCheckUp.peek(rov)) //see the peek of Emergency checkup list
	{
		if(rov->getDayAfterCheckup()>day) //if the day that will finish checkup bigger than current day
		{
			break;  //break to see others lists
		}
		else
		{
			EInCheckUp.dequeue(rov); //else then get it out of list 
			Erovers.enqueue(rov); //and insert it to its list
		}
	}
	rover*rov1;
	while(MInCheckUp.peek(rov1)) //see peek of Mountainous checkup list
	{
		if(rov1->getDayAfterCheckup()>day)  //if the day that will finish checkup bigger than current day
		{
			break; //break to see other list
		}
		else
		{
			MInCheckUp.dequeue(rov1); //remove it from checkup list
			Mrovers.enqueue(rov1);  //and insert it to its list
		}
	}

	rover*rov2;
	while(PInCheckUp.peek(rov2))  //see peek of polar checkup list
	{
		if(rov2->getDayAfterCheckup()>day)  //if the day that will finish checkup bigger than current day
		{
			break; //get out of loop
		}
		else
		{
			PInCheckUp.dequeue(rov2);  //remove from checkup
			Provers.enqueue(rov2);  //return to its list
		}
	}
}


void MarsStation::AutoPromote(int day)
{
	Queue<mission*>temp;

	while(!Mountmissions.isEmpty()) //traverse in the Mountainous mission to see which of them will be auto promoted
	{
		mission*mis;
		Mountmissions.dequeue(mis);
		mis->setCurrentWaitedDays(day); //set waited days till now
		if(mis->getwaitedtime()>AutoP) //if waited days more than auto promoted days promote it 
		{
			AutoPromoted++; //increase autopromoted mission
		    mis->setmissiontype('E'); //set its type to emergency
		  mis->setPriority(); //set its priority
		  float prio= mis->Getpriority();  //get priority
		  Emergmissions.enqueue(mis,prio);  //to insert it in emergency list 
		}
		else
			temp.enqueue(mis); //insert removed mission in another queue to prevent data loss

	}
	while (!temp.isEmpty())  //return mission to its original queue
	{
		mission*mis;
		temp.dequeue(mis);
		Mountmissions.enqueue(mis);
	}


}

int MarsStation::getnumofWaitingMissions() //we will traverse in queues of mission and every mission found increase 
{                                          //the waited missions by 1
	 Queue<mission*>Etemp;
   int WaitingMissions=0;
	 while(!Emergmissions.isEmpty())
	 {
		 mission*emison;
		 Emergmissions.dequeue(emison);
		 WaitingMissions++;
		 Etemp.enqueue(emison);

	 }
	 while(!Etemp.isEmpty())
	 {
		 mission*emison;
		 Etemp.dequeue(emison);
		 float priority=emison->Getpriority();
		 Emergmissions.enqueue(emison, priority);
	 }


	 while(!polarmissions.isEmpty())
	 {
		  mission*emison;
		 polarmissions.dequeue(emison);
		 WaitingMissions++;
		 Etemp.enqueue(emison);
	 }
	 
	  while(!Etemp.isEmpty())
	  {
	    mission*pmison;
		Etemp.dequeue(pmison);
		polarmissions.enqueue(pmison);
	  }
	  
	   while(!Mountmissions.isEmpty())
	 {
		  mission*emison;
		 Mountmissions.dequeue(emison);
		 WaitingMissions++;
		 Etemp.enqueue(emison);
	 }
	   
	    while(!Etemp.isEmpty())
	  {
	    mission*pmison;
		Etemp.dequeue(pmison);
		Mountmissions.enqueue(pmison);
	  }
  return WaitingMissions;
}


int MarsStation::getnumofInExecution() //traverse in priority queue of inexecution rovers to count 
{                                      //all rovers in execution
	Queue<rover*>temp;
  int InExecut=0;
	while(!InExecrovers.isEmpty()) //we empty the queue and put data in another queue to prevent loss of data
	{
		rover*rov;
		InExecrovers.dequeue(rov);
		InExecut++;
			temp.enqueue(rov);
	}
	while(!temp.isEmpty())
	{
	   rover*rov;
       temp.dequeue(rov);
	   float priority=-(rov->getmission()->getFinishDay());
	   InExecrovers.enqueue(rov , priority);
	}
 return InExecut;
}

int MarsStation:: getnumofAvailableRover() //traverse in all queue of rovers to get number of rovers
{                     //every time we empty a queue we put data in a temp queue to return the data to 
	Queue<rover*>temp; //its original queue
	int AvailableRovers=0;
	while(!Erovers.isEmpty()) //emptying emergency rovers queue
	{
	    rover*rov;
		Erovers.dequeue(rov);
		AvailableRovers++;
		temp.enqueue(rov);
	}

	while(!temp.isEmpty()) //refill emergency rover queue
	{
		rover*rov;
		temp.dequeue(rov);
		Erovers.enqueue(rov);
	}

	
	while(!Provers.isEmpty()) //emptying polar rovers queue
	{
	    rover*rov;
		Provers.dequeue(rov);
		AvailableRovers++;
		temp.enqueue(rov);
	}

	while(!temp.isEmpty()) //refill polar rover queue
	{
		rover*rov;
		temp.dequeue(rov);
		Provers.enqueue(rov);
	}

	while(!Mrovers.isEmpty()) //emptying mountainous rovers queue
	{
	    rover*rov;
		Mrovers.dequeue(rov);
		AvailableRovers++;
		temp.enqueue(rov);
	}

	while(!temp.isEmpty()) //refill mountainous rover queue
	{
		rover*rov;
		temp.dequeue(rov);
	    Mrovers.enqueue(rov);
	}

 return AvailableRovers;

}

int MarsStation::getnumofIncheckUpRover() //like we get number of available rovers we get number of rovers in checkup
{
  Queue<rover*>temp;
  int InCheckup=0;
  while(!EInCheckUp.isEmpty())  //emptying emergency rovers in checkup to get their number
  {
	  rover*rov;
	  EInCheckUp.dequeue(rov);
	  InCheckup++;
	  temp.enqueue(rov);
  }

  while(!temp.isEmpty())  //refill queue
  {
	  rover*rov;
	  temp.dequeue(rov);
	  EInCheckUp.enqueue(rov);
  }

  while(!PInCheckUp.isEmpty())  //emptying polar rovers in checkup to get their number
  {
	  rover*rov;
	  PInCheckUp.dequeue(rov);
	  InCheckup++;
	  temp.enqueue(rov);
  }

  while(!temp.isEmpty()) //refill queue
  {
	  rover*rov;
	  temp.dequeue(rov);
	  PInCheckUp.enqueue(rov);
  }

  while(!MInCheckUp.isEmpty())  //emptying mountainous rovers in checkup to get their number
  {
	  rover*rov;
	  MInCheckUp.dequeue(rov);
	  InCheckup++;
	  temp.enqueue(rov);
  }

  while(!temp.isEmpty()) //refill queue
  {
	  rover*rov;
	  temp.dequeue(rov);
	  MInCheckUp.enqueue(rov);
  }

 return InCheckup;
}


int MarsStation::getnumofCompletedMission()
{
	Queue<mission*>temp;
	int CompletedMissions=0;
	while(!Compmissions.isEmpty()) // emptying completed missions queue to get their number
	{
		mission*mison;
		Compmissions.dequeue(mison);
		CompletedMissions++;
			temp.enqueue(mison);
	}

	while(!temp.isEmpty())  //refill queue
	{
		mission*mison;
		temp.dequeue(mison);
		Compmissions.enqueue(mison);
	}

 return CompletedMissions; 
}



void MarsStation::run()
{
	readinputfile();
	ui->PrintString("Write: 1 for Interactive mode, 2 for Step-By-Step Mode , 3 for Silent Mode:   ");
	int day =1;
	int X;
	ui->GetInt(X);
 if(X==1)
  {  //we finish simulation
  //when queue of events , execution rovers , emergency missions , mountainous missions , polar missions all are empty 
	while(!Eventsqueue.isEmpty()|| !InExecrovers.isEmpty() || ! Emergmissions.isEmpty() ||!Mountmissions.isEmpty() || !polarmissions.isEmpty())
	{ 
		AutoPromote(day);
		ExecutEvents(day);
		GetFromCheckUp(day);
		GetFromInExecute(day);
		ExecuteEmergMission(day);
		ExecutePolarMission(day);
		ExecuteMountmission(day);

	
		ui->PrintString("Current Day:"); ui->PrintNum(day); ui->NewLine();

		ui->PrintNum(getnumofWaitingMissions());
		ui->PrintString(" Waiting Missions:");
	
		ui->PrintWaitedMissions(Emergmissions,polarmissions,Mountmissions );
		
		ui->NewLine();
		
		ui->PrintString("--------------------------"); ui->NewLine();
		ui->PrintNum(getnumofInExecution());
		ui->PrintString(" In-Execution Missions/Rovers:");
		
		ui->PrintIn_Execution(InExecrovers);
		
		ui->NewLine();
		ui->PrintString("--------------------------"); ui->NewLine();
	    ui->PrintNum(getnumofAvailableRover());
		ui->PrintString(" Available Rovers: ");
		
		ui->PrintAvailableRovers(Erovers,Mrovers,Provers);
	
		ui->NewLine(); ui->PrintString("--------------------------"); ui->NewLine();
		ui->PrintNum(getnumofIncheckUpRover());
		ui->PrintString(" In-Checkup Rovers: ");
	
		ui->PrintInCheckUpRovers(PInCheckUp, EInCheckUp,MInCheckUp);
		
		ui->NewLine(); ui->PrintString("--------------------------"); ui->NewLine();
		ui->PrintNum(getnumofCompletedMission());
		ui->PrintString(" Completed Missions: ");
		
		ui->PrintCompletedMissions(Compmissions);
	
		ui->NewLine(); ui->PrintString("--------------------------"); ui->NewLine();

	    ui->PrintString("Press Enter to Go to next day");
		ui->NewLine();
		if (ui->WaitEnter())
		day++;

	}
  
	PrintOutPutFile();
  }

 if(X==2)
  {
	while(!Eventsqueue.isEmpty()|| !InExecrovers.isEmpty() || ! Emergmissions.isEmpty() ||!Mountmissions.isEmpty() || !polarmissions.isEmpty())
	{
		AutoPromote(day);
		ExecutEvents(day);
		GetFromCheckUp(day);
		GetFromInExecute(day);
		ExecuteEmergMission(day);
		ExecutePolarMission(day);
		ExecuteMountmission(day);

		ui->PrintString("Current Day:"); ui->PrintNum(day); ui->NewLine();

		ui->PrintNum(getnumofWaitingMissions());
		ui->PrintString(" Waiting Missions:");
	
		ui->PrintWaitedMissions(Emergmissions,polarmissions,Mountmissions );
		
		ui->NewLine();
		
		ui->PrintString("--------------------------"); ui->NewLine();
		ui->PrintNum(getnumofInExecution());
		ui->PrintString(" In-Execution Missions/Rovers:");
		
		ui->PrintIn_Execution(InExecrovers);
		
		ui->NewLine();
		ui->PrintString("--------------------------"); ui->NewLine();
	    ui->PrintNum(getnumofAvailableRover());
		ui->PrintString(" Available Rovers: ");
		
		ui->PrintAvailableRovers(Erovers,Mrovers,Provers);
	
		ui->NewLine(); ui->PrintString("--------------------------"); ui->NewLine();
		ui->PrintNum(getnumofIncheckUpRover());
		ui->PrintString(" In-Checkup Rovers: ");
	
		ui->PrintInCheckUpRovers(PInCheckUp, EInCheckUp,MInCheckUp);
		
		ui->NewLine(); ui->PrintString("--------------------------"); ui->NewLine();
		ui->PrintNum(getnumofCompletedMission());
		ui->PrintString(" Completed Missions: ");
		
		ui->PrintCompletedMissions(Compmissions);
	
		ui->NewLine(); ui->PrintString("--------------------------"); ui->NewLine();

		day++;
		Sleep(1000);
	}
  
	PrintOutPutFile();
  }

 if(X==3)
  {
	  ui->PrintString("Silent Mode");
	  ui->NewLine();
	  ui->PrintString("Simulation Starts...");
	  ui->NewLine();
	while(!Eventsqueue.isEmpty()|| !InExecrovers.isEmpty() || ! Emergmissions.isEmpty() ||!Mountmissions.isEmpty() || !polarmissions.isEmpty())
	{
		AutoPromote(day);
		ExecutEvents(day);
		GetFromCheckUp(day);
		GetFromInExecute(day);
		ExecuteEmergMission(day);
		ExecutePolarMission(day);
		ExecuteMountmission(day);

		
		day++;
	
	}
  
	PrintOutPutFile();
	ui->PrintString("Simulation ends, Output file created");
	ui->NewLine();
  }


}


 void MarsStation::readinputfile()
{

  ifstream Input ("mars.txt");

	  if(Input.is_open())
	  {
		  Input>>numMrovers>>numProvers>>numErovers>>speedMrovers>>speedProvers>>speedErovers;  //take informations of file in created variables
		  Input>>numbefocheck>>CheckMdur>>CheckPdur>>CheckEdur>>AutoP>>numofEvents;            

		  int i=0 ;
		  int j=0;
		  int k=0;

		  for( i=1 ; i<numMrovers+1; i++)
		  {
			  rover* newRover = new rover('M',numbefocheck , speedMrovers , CheckMdur );
			  newRover->setID(i);
			  Mrovers.enqueue(newRover);
		  }

	      for( j=i ; j<numProvers+numMrovers+1; j++)
		  {
			  rover* newRover = new rover('P', numbefocheck,speedProvers , CheckPdur );
			  newRover->setID(j);
			  Provers.enqueue(newRover);
		  }
		  for( k=j ; k<numErovers+numProvers+numMrovers+1; k++)
		  {
			  rover* newRover = new rover('E',numbefocheck ,speedErovers , CheckEdur );
			  newRover->setID(k);
			  Erovers.enqueue(newRover);
		  }
	  
	      for(int i=0; i<numofEvents;i++) //we read equal to number of events
		  {
			  char typofevent;
			  Input>>typofevent;
			  Events* NewEvent;
			  if(typofevent=='F') //if type of event formulation
			  {
				  char TYP;
				  int ED , ID , TargetLoc , MDUR , SIG;
				  Input>>TYP >>ED >> ID >>TargetLoc>>MDUR>>SIG; //taking data of event
				  if(TYP=='M')     //creating event depend of its type
				  {
				    NewEvent=new Formulation ('M' ,ED , ID , TargetLoc, MDUR , SIG);
				  }
				  if(TYP=='P')
				  {
					  NewEvent=new Formulation ('P' ,ED , ID , TargetLoc, MDUR , SIG);
				  }
				  if(TYP=='E')
				  {
					  NewEvent=new Formulation ('E' ,ED , ID , TargetLoc, MDUR , SIG);
				  }

			  }

			  if(typofevent=='P') //if type of event promotion
			  {
			    int ED , ID;
				Input>>ED>>ID;
				NewEvent=new Promotion(ED , ID);
			  }
			  if(typofevent=='X')  //if type of event cancellation
			  {
				  int ED , ID;
				Input>>ED>>ID;
				NewEvent=new Cancellation(ED , ID);
			  }
			  Eventsqueue.enqueue(NewEvent);

		  }
	  
	  }

}

 void MarsStation::PrintOutPutFile()
 {
	 ofstream OutPutFile("OutPut.txt");
	 int total_waited=0; //to store total waited time
	 int total_execution=0; //to store total execution time
	 int numM_mission=0;  //to store number of completed mountainous missions
	 int numP_mission=0;  //to store number of completed polar missions
	 int numE_mission=0; //to store number of completed emergency missions
	 OutPutFile<<"CD  ID  FD  WD  ED "<<endl;
	 mission*mison;
if(OutPutFile.is_open())
{
	 while(Compmissions.dequeue(mison))  
	 {
		 if(mison->getmissiontype()=='M')
		 {
			 numM_mission++;
		 }
		 if(mison->getmissiontype()=='P')
		 {
			 numP_mission++;
		 }
		 if(mison->getmissiontype()=='E')
		 {
			 numE_mission++;
		 }


		 total_execution= total_execution+mison->getTimeofExecution();
		 total_waited=total_waited+mison->getwaitedtime();

		 OutPutFile<<mison->getFinishDay()<<"  "<<mison->getid()<<"   "<<int (mison->getformulationday())<<"   ";
		 OutPutFile<<mison->getwaitedtime()<<"   "<<mison->getTimeofExecution()<<endl;

		 delete mison;
		 mison=nullptr;
	 
	 }
	 OutPutFile<<"........................"<<endl;
	 OutPutFile<<"........................"<<endl;

	 OutPutFile<<"Mission: "<<numM_mission+numP_mission+numE_mission<<" ";
	 OutPutFile<<"["<<"M: "<<numM_mission<<", "<<"P: "<<numP_mission<<", "<<"E: "<<numE_mission<<"]"<<endl;
	 OutPutFile<<"Rovers: "<<numMrovers+numProvers+numErovers<<" ";
	 OutPutFile<<"["<<"M: "<<numMrovers<<", "<<"P: "<<numProvers<<", "<<"E: "<<numErovers<<"]"<<endl;
	 OutPutFile<<"Avg Waited = "<<float(total_waited)/(numM_mission+numP_mission+numE_mission)<<",  ";
	 OutPutFile<<"Avg Exec = "<<float(total_execution)/(numM_mission+numP_mission+numE_mission)<<endl;
	 OutPutFile<<"Auto-promoted: "<<(AutoPromoted/(numM_mission+AutoPromoted))*100<<"%";
}
 }

 MarsStation::~MarsStation()
 {
	 delete ui;
 }