#include "rover.h"
rover:: rover  (char rot, int nck, int spe, int ched, int nomi)
{
 currentmission=nullptr;// initially there is no mission assigned to the rover
 nom=0;// the rover has not done any mission yet
 ID=0; // default value for ID 
 Nbefocheck=nck;
 // the rover constructor calls the setters to give the data members their values
 setrovertype(rot);
 setspeed(spe);
 setcheckupduration(ched);
 setnomissions(nomi);
}
rover::~rover()
{

}
void rover::setrovertype(char rot)
{
 if (rot != 'E' && rot != 'P'&&rot!='M') // checks the rover type if it is not emergency or polar or mountanious it does not accept them
 {
  return;
 }
 else
 {
  rt = rot;
 }

}
void rover::setspeed(int spe)
{
 if (spe > 0) // speed can not be less than 0
 {
  sp = spe;
 }
 else
 {
  return;
 }

}
void rover::setcheckupduration(int ched)
{
 if (ched > 0) // checkup duration can not be less than 0
 {
  chd = ched;
 }
 else
 {
  return;
 }

}
void rover::setnomissions(int nomi)
{
 if (nomi >=0)
 {
  nom = nomi;
 }
 else
 {
  return;
 }

}
void rover::setmission(mission*CurMission)
{
	currentmission=CurMission; //sets the current mission with the given mission
}

char rover::getrovertype()
{
 return rt;
}
int rover::getspeed()
{
 return sp;
}
int rover::getcheckupduration()
{
 return chd ;
}
int rover::getnomissions()
{
 return nom;
}
mission*& rover:: getmission()
{
	return currentmission;
}


int rover::getNumBeforeCheck()
{
  return Nbefocheck;
}

void rover :: setDayBeforeCheckup(int day)
{
  daybefocheckup=day;
}

int rover::getDayBeforeCheckup()
{
	return daybefocheckup;
}

int rover :: getDayAfterCheckup()
{
	return (daybefocheckup+chd);
}

void rover ::setID(int id)
{
	ID=id;
}

int rover::getID()
{
	return ID;
}