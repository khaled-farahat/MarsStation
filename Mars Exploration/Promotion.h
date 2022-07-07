#pragma once 
#include "Events.h"

class Promotion : public Events
{
public:
 Promotion(int ed, int id); //constructor
virtual void Execute(MarsStation*station); //to execute promotion event
~Promotion(); //destructor
};