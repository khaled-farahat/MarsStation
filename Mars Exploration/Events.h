#pragma once
#ifndef _EVENTS_H_
#define _EVENTS_H_
class MarsStation; //forward declaration

class Events
{
protected:
 int ID; // ID number for missions
 int ED; // Event Day
public:
 Events(int ed, int id); //constructor
 int getEventday(); //getter for Evemt day
 virtual void Execute(MarsStation*station) = 0; //pure virtual function (Excute Events)
 virtual ~Events(); //destructor
};
#endif