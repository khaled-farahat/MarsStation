 #include "Events.h"


//initializing data members
Events::Events(int ed, int id)
{
 ID = id;
 ED = ed;
}

int Events ::getEventday()
{
	return ED;
}

Events::~Events()
{

}