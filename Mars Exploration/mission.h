#pragma once

#include <iostream>
using namespace std;

class mission
{
 int fd;//Formulation Day
 char mt;//mission type
 int tl;//target location
 int md;//mission duration
 int s;// significane
 int id; //ID of mission
 int dayexecut; //day of execution
 float finishday; //the day taht mission will finish
 int TimeExecut; //time of execution of mission
 int waitedT; //waited type
 float priority; //Priority of mission
public:
 mission(int fod=0,int id=0, int tlo =0, int mdu =0, int si=0 , char ty=' '); // mission default constructor
 ~mission();// mission destructor
 void setformulationday(int fod); //setter for formulation day
 void settargetlocation(int tlo); //setter for target location
 void setmissionduration(int mdu); //setter for mission duration
 void setsignificance(int si); //setter for significance
 void setmissiontype(char ty); //setter for mission type
 void setid(int ID); //setter for ID
 void setPriority(); //setter for Priority
 void setwaitedtime(); //setter for Waited time
 void setdayexecution(int day); //setter to day of execution of mission
 void setTimeOfExecution(int speed); //setter for time taken to execute mission
 void setCurrentWaitedDays(int day); //setter for current waited time
 void setFinishDay(); //setter for the day that mission is finished

 int  getformulationday(); //getter for formulation day
 int  gettargetlocation();//getter for target location
 int  getmissionduration();//getter for mission duration
 int  getsignificance();//getter for significance
 int  getid();//getter for ID
 int  getwaitedtime();//getter for Waited time
 int getTimeofExecution();//getter for time taken to execute mission
 float  getFinishDay();//getter for the day that mission is finished
 float Getpriority();//getter for Priority
 char getmissiontype();//getter for mission type
};