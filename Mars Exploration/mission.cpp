 #include "mission.h"

mission::~mission()
{

}
mission::mission(int fod,int id , int tlo, int mdu, int si, char ty )
{
	waitedT=0; // default value
	// the mission constructor calls the setters to give the data members their values
 setformulationday( fod);
 setid(id);
 settargetlocation( tlo);
 setmissionduration( mdu);
 setsignificance( si);
 setmissiontype( ty);

}


void mission::setformulationday(int fod)
{
 if (fod > 0) // formulation day can not be less than 0
 {
  fd = fod;
 }
 else 
 {
  return;
 }

}
void mission::setid(int ID)
{id=ID; }
void mission::settargetlocation(int tlo)
{
 if (tlo > 0) // target location can not be less than 0
 {
  tl = tlo;
 }
 else
 {
  return;
 }

}
void mission::setmissionduration(int mdu)
{
 if (mdu > 0)// mission duration can not be less than 0
 {
  md=mdu;
 }
 else
 {
  return;
 }

}
void mission::setsignificance(int si)
{
 if (si > 0) // significance can not be less than 0
 {
  s = si;
 }
 else
 {
  return;
 }

}
void mission::setmissiontype(char ty)
{
 if (ty != 'E' && ty != 'P'&& ty!='M') // checks the mission type if it is not emergency or polar or mountanious it does not accept them
 {
  return;
 }
 else
 {
  mt = ty;
 }

}
void mission::setwaitedtime()
{
	waitedT=dayexecut-fd; // the mission waited for no. days equal the day it has
	// been executed in minus its formulation day
}
void mission::setdayexecution(int CURday)
{
	dayexecut=CURday;
}

void mission::setTimeOfExecution(int speed)
{
	TimeExecut=int ((ceil((2*tl/speed)/25)))+md ; // time of execution is the time the rover takes
	// to go to the location which is the target location divided by speed but we multiply by 2 
	// because the rover has to go , execute the mission and return , after that we divide by 25 
	// because the day on mars is 25 hrs and take the ceil of all that and add the mission duration to it
}

void mission::setFinishDay()
{
	finishday=float(ceil(TimeExecut+dayexecut));
	// the mission will be finished in the day that equals the summation of its execution day and
	// the time it has taken to be executed
}


int  mission::getformulationday()
{
 return fd;
}
int mission::gettargetlocation()
{
 return tl;
}
int  mission::getmissionduration()
{
 return md;
}
int mission::getsignificance()
{
 return s;
}
char mission::getmissiontype()
{
 return mt;
}
int mission :: getid()
{
	return id;
}
void mission::setPriority()
{
 priority= ((float(2*md)/(3*tl))*100*s);
 // the priority of the mission increases highly with its significance so we assumed its multiplied by
 //100 and also increases with the mission duration as a mission takes a long time is highly important 
 // we we assumed that target location may decrease the priority of the mission
}

float mission::Getpriority()
{
	return priority;
}

int mission::getwaitedtime()
{
	return waitedT;
}

float mission:: getFinishDay()
{
  return finishday;
}

int mission::getTimeofExecution()
{
	return TimeExecut;
}

void mission::setCurrentWaitedDays(int day)
{
	waitedT=day-fd; // this function is used to know how many days the missions waited till the current
	//day not till execution
}


