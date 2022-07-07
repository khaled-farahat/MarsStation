#include "Cancellation.h"
#include "MarsStation.h"
//initializing data members
Cancellation::Cancellation(int ed, int id) :Events(ed, id)
{
}
void Cancellation:: Execute(MarsStation*station)
{
	station->CancelEvent(ID); //calling function (Cancel) from MarsStation Class
}

Cancellation::~Cancellation()
{}