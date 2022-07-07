#pragma once
#include"mission.h"
class rover
{
 char rt;//rover type
 int sp;// speed
 int chd;// checkup duration
 int nom;// no. missions
 int Nbefocheck; // no. missions before checkup
 int daybefocheckup; // the day before checkup
 int ID;//ID of rover
 mission* currentmission;//pointer to the current mission (the mission being done by the rover now)

public:
 rover(char rot=' ',int nck=0,int spe=0 , int ched=0, int nomi=0); // rover default constructer
 ~rover(); // rover destructer
 void setrovertype(char rot); // setter for the rover type
 void setspeed(int spe); // setter for speed
 void setcheckupduration(int chd); // setter for checkup duration
 void setnomissions(int nom); // setter for no. missions
 void setDayBeforeCheckup(int day); // setter for the day before checkup
 void setID(int); // setter for the rover id 
 void setmission(mission*); // setter for the mission to assign it to the rover

 char getrovertype(); // getter for the rover type
 int getNumBeforeCheck(); // getter for no. missions before checkup
 int getspeed(); // getter for speed
 int getcheckupduration(); // getter for checkup duration
 int getnomissions(); // getter for no. missions
 int getDayBeforeCheckup();  // getter for the day before checkup
 int getDayAfterCheckup(); // getter for the day after checkup
 int getID();
 mission*& getmission(); // getter for the mission assigned to the rover now

};