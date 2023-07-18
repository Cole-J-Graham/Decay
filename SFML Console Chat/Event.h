#ifndef EVENT_H
#define EVENT_H
#include "Assets.h"

class Event
{
private:
	bool encounterInit;

public:
	//Constructors & Destructors
	Event();
	~Event();

	//Castle Events
	void spadeEncounter(Assets& assets);
};

#endif

