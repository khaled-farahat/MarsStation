#include<iostream>
#include"MarsStation.h"
using namespace std;


int main ()
{
	MarsStation*station=new MarsStation;
	station->run();


	delete station;

	

return 0;
}

