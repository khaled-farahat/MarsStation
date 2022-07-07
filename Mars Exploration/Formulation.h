#ifndef _Formulation_H_ 
#define _Formulation_H_

#include "Events.h"

class Formulation : public Events
{
private:
 char TYP; // Type of mission
 int TLOC; // Target location (km)
 int MDUR; // Days of mission duration
 int SIG; // Mission significance
public:
 Formulation(char typ, int ed, int id, int tloc, int mdur, int sig); //constructor
 virtual void Execute(MarsStation*station); //To Execute Formulation Event
 ~Formulation(); //destructor
};
#endif