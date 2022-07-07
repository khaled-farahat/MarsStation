 #include "Formulation.h"
#include"MarsStation.h"
//initializing data members
Formulation::Formulation(char typ, int ed, int id, int tloc, int mdur, int sig) :Events(ed, id)
{
 TYP = typ;
 TLOC = tloc;
 MDUR = mdur;
 SIG = sig;
}

void Formulation::Execute(MarsStation*station)
{
	mission*NM=new mission(ED ,ID ,TLOC ,MDUR ,SIG ,TYP);
	if (TYP=='M') // if it's a mountainous mission
	{
		station->InsertinMountQueue(NM);
		// call to formulate mountainous mission
	}
	if(TYP=='P') // if it's a polar mission
	{
		station->InsertinPolarQueue(NM);
		// call to formulate Polar mission
	}
	if(TYP=='E') // if it's an emergency mission
	{
		station->InsertinEmergqueue(NM);
		// call to formulate Emergency mission
	}
}

Formulation::~Formulation()
{}