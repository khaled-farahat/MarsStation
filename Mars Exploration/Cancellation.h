 #include"Events.h"
class Cancellation : public Events
{
public:
 Cancellation(int ed, int id); //constructor
 void Execute(MarsStation*station); //function to execute cancellation event
 ~Cancellation(); //destructor
};