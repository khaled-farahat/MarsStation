#include"UI.h"

UI::UI()
{
}

UI::~UI()
{
}


void UI::PrintNum(int X)
{
  cout<<X; 
}

void UI::PrintString(string x)
{
	cout<<x;
}

bool UI ::WaitEnter()
{
	string enter;
	getline(cin , enter);
	return enter.empty();

}

void UI::NewLine()
{
	cout<<endl;
}


void UI ::GetInt(int&x)
{
  cin>>x;
}

//give function the needed queues by referance as it will empty & refill it to print waited missions
void UI:: PrintWaitedMissions(PriorityQueue<mission*>&Emergmissions,Queue<mission*>&polarmissions, Queue<mission*>&Mountmissions )
{
	Queue<mission*>Etemp;
	 cout<<"[";
	
	 while(!Emergmissions.isEmpty()) //emptying queue of emergency mission
	 {
		 mission*emison;
		 Emergmissions.dequeue(emison);
		 cout<<emison->getid();        //print ID of mission
	     if(!Emergmissions.isEmpty())
			 cout<<",";
		 Etemp.enqueue(emison);

	 }
	 cout<<"]  ";
	 while(!Etemp.isEmpty()) //refill queue to prevent data loss
	 {
		 mission*emison;
		 Etemp.dequeue(emison);
		 float priority=emison->Getpriority();
		 Emergmissions.enqueue(emison, priority);
	 }

	 cout<<"(";
	 while(!polarmissions.isEmpty()) //emptying polar queue
	 {
		  mission*emison;
		 polarmissions.dequeue(emison);
		 cout<<emison->getid();       //print ID
		 if(!polarmissions.isEmpty())
			 cout<<",";
		 Etemp.enqueue(emison);
	 }
	 cout<<")  ";
	  while(!Etemp.isEmpty()) //refill polar queue
	  {
	    mission*pmison;
		Etemp.dequeue(pmison);
		polarmissions.enqueue(pmison);
	  }
	  cout<<"{";
	   while(!Mountmissions.isEmpty())  //emptying Mountainous queue
	 {
		  mission*emison;
		 Mountmissions.dequeue(emison);
		 cout<<emison->getid();        //print ID
		 if(!Mountmissions.isEmpty())
			 cout<<",";
		 Etemp.enqueue(emison);
	 }
	   cout<<"}";
	    while(!Etemp.isEmpty())  //refill mountainous queue
	  {
	    mission*pmison;
		Etemp.dequeue(pmison);
		Mountmissions.enqueue(pmison);
	  }
}

void UI ::PrintIn_Execution(PriorityQueue<rover*>&InExecrovers) //take priority queue of in execution rovers from MarsStation
{
	//emptying queue 3 times to print data in orderd way & refill every time
	Queue<rover*>temp;
	cout<<"[";
	while(!InExecrovers.isEmpty()) 
	{
		rover*rov;
		InExecrovers.dequeue(rov);
		if(rov->getrovertype()=='E')
		{
			cout<<rov->getmission()->getid()<<"/"<<rov->getID();
			if(!InExecrovers.isEmpty())
				cout<<",";
			temp.enqueue(rov);
		}
		else
			temp.enqueue(rov);
	}
	cout<<"]  ";
	while(!temp.isEmpty())
	{
	   rover*rov;
       temp.dequeue(rov);
	   float priority=-(rov->getmission()->getFinishDay());
	   InExecrovers.enqueue(rov , priority);
	}

	cout<<"(";
	while(!InExecrovers.isEmpty())
	{
		rover*rov;
		InExecrovers.dequeue(rov);
		if(rov->getrovertype()=='P')
		{
			cout<<rov->getmission()->getid()<<"/"<<rov->getID();
			if(!InExecrovers.isEmpty())
				cout<<",";
			temp.enqueue(rov);
		}
		else
			temp.enqueue(rov);
	}
	cout<<")  ";
	while(!temp.isEmpty())
	{
	   rover*rov;
       temp.dequeue(rov);
	   float priority=-(rov->getmission()->getFinishDay());
	   InExecrovers.enqueue(rov , priority);
	}

	cout<<"{";
	while(!InExecrovers.isEmpty())
	{
		rover*rov;
		InExecrovers.dequeue(rov);
		if(rov->getrovertype()=='M')
		{
			cout<<rov->getmission()->getid()<<"/"<<rov->getID();
			if(!InExecrovers.isEmpty())
				cout<<",";
			temp.enqueue(rov);
		}
		else
			temp.enqueue(rov);
	}
	cout<<"}  ";
	while(!temp.isEmpty())
	{
	   rover*rov;
       temp.dequeue(rov);
	   float priority=-(rov->getmission()->getFinishDay());
	   InExecrovers.enqueue(rov , priority);
	}
}
//take queue of emergency rovers , mountainous rover , polar rover from MarsStation
void UI::PrintAvailableRovers(Queue<rover*>&Erovers,Queue<rover*>&Mrovers,Queue<rover*>&Provers)
{
	Queue<rover*>temp;
	cout<<"[";
	while(!Erovers.isEmpty()) //emptying emergency queue to print data
	{
	    rover*rov;
		Erovers.dequeue(rov);
		int x=rov->getID();
		cout<<x;
		if(!Erovers.isEmpty())
			cout<<",";
		temp.enqueue(rov);
	}
	cout<<"]  ";

	while(!temp.isEmpty()) //refill queue
	{
		rover*rov;
		temp.dequeue(rov);
		Erovers.enqueue(rov);
	}

	cout<<"(";
	while(!Provers.isEmpty()) //emptying polar rover queue to print data 
	{
	    rover*rov;
		Provers.dequeue(rov);
		int x=rov->getID();
		cout<<x;
		if(!Provers.isEmpty())
			cout<<",";
		temp.enqueue(rov);
	}
	cout<<")  ";

	while(!temp.isEmpty())  //refill queue
	{
		rover*rov;
		temp.dequeue(rov);
		Provers.enqueue(rov);
	}

	cout<<"{";
	while(!Mrovers.isEmpty())  //emptying mountainous rover queue to print data
	{
	    rover*rov;
		Mrovers.dequeue(rov);
		int x=rov->getID();
		cout<<x;
		if(!Mrovers.isEmpty())
			cout<<",";
		temp.enqueue(rov);
	}
	cout<<"}  ";

	while(!temp.isEmpty()) //refill queur
	{
		rover*rov;
		temp.dequeue(rov);
	    Mrovers.enqueue(rov);
	}



}


//take checkup queue of polar , emergency & Mountainous rovers 
void UI:: PrintInCheckUpRovers(Queue<rover*>& PInCheckUp,Queue<rover*>& EInCheckUp,Queue<rover*>& MInCheckUp)
{
	//empty & refill each queue to print data
	Queue<rover*>temp;
  cout<<"[";
  while(!EInCheckUp.isEmpty())
  {
	  rover*rov;
	  EInCheckUp.dequeue(rov);
	  cout<<rov->getID();
	  if(EInCheckUp.isEmpty())
		  cout<<",";
	  temp.enqueue(rov);
  }
  cout<<"]  ";

  while(!temp.isEmpty())
  {
	  rover*rov;
	  temp.dequeue(rov);
	  EInCheckUp.enqueue(rov);
  }

  cout<<"(";
  while(!PInCheckUp.isEmpty())
  {
	  rover*rov;
	  PInCheckUp.dequeue(rov);
	  cout<<rov->getID();
	  if(PInCheckUp.isEmpty())
		  cout<<",";
	  temp.enqueue(rov);
  }
  cout<<")  ";

  while(!temp.isEmpty())
  {
	  rover*rov;
	  temp.dequeue(rov);
	  PInCheckUp.enqueue(rov);
  }

  cout<<"{";
  while(!MInCheckUp.isEmpty())
  {
	  rover*rov;
	  MInCheckUp.dequeue(rov);
	  cout<<rov->getID();
	  if(MInCheckUp.isEmpty())
		  cout<<",";
	  temp.enqueue(rov);
  }
  cout<<"}  ";

  while(!temp.isEmpty())
  {
	  rover*rov;
	  temp.dequeue(rov);
	  MInCheckUp.enqueue(rov);
  }

}

//take completed mission queue from mars station
void UI::PrintCompletedMissions(Queue<mission*>&Compmissions)
{
	//emptying queue 3 times to print in ordered way & refill it each time
	Queue<mission*>temp;
	cout<<"[";
	while(!Compmissions.isEmpty())
	{
		mission*mison;
		Compmissions.dequeue(mison);
		if(mison->getmissiontype()=='E')
		{
			cout<<mison->getid()<<",";
			temp.enqueue(mison);
		}
		else
			temp.enqueue(mison);
	}
	cout<<"]  ";
	while(!temp.isEmpty())
	{
		mission*mison;
		temp.dequeue(mison);
		Compmissions.enqueue(mison);
	}

	cout<<"(";
	while(!Compmissions.isEmpty())
	{
		mission*mison;
		Compmissions.dequeue(mison);
		if(mison->getmissiontype()=='P')
		{
			cout<<mison->getid()<<",";
			temp.enqueue(mison);
		}
		else
			temp.enqueue(mison);
	}
	cout<<")  ";
	while(!temp.isEmpty())
	{
		mission*mison;
		temp.dequeue(mison);
		Compmissions.enqueue(mison);
	}

	cout<<"{";
	while(!Compmissions.isEmpty())
	{
		mission*mison;
		Compmissions.dequeue(mison);
		if(mison->getmissiontype()=='M')
		{
			cout<<mison->getid()<<",";
			temp.enqueue(mison);
		}
		else
			temp.enqueue(mison);
	}
	cout<<"}  ";
	while(!temp.isEmpty())
	{
		mission*mison;
		temp.dequeue(mison);
		Compmissions.enqueue(mison);
	}

}