 #include "Promotion.h"
#include"MarsStation.h"

//initializing data members
Promotion::Promotion(int ed, int id) :Events(ed, id)
{
}
void Promotion::Execute(MarsStation*station)
{
	 station->PromoteEvent(ID); // Calling Promote function from MarsStation class
}
Promotion::~Promotion()
{}