#include "Events.h"
Events::Events()
{
}


 Events::~Events()
{
	
}

unsigned int Events::getDay() const
{
	return day;
}
unsigned int Events::getTime()const
{
	return time;
}
void Events::setDay(int d)
{
	day = d;
}
void Events::setTime(int t)
{
	//ADDED 5/26
	if (t < 5)
		t = 5;
	time = t;
}