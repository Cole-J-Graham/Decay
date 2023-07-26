#ifndef EVENT_H
#define EVENT_H
#include "Assets.h"

class Event
{
private:

public:
	bool encounterInit;
	bool encounterInitTwo;

	int dialogue;

	//Constructors & Destructors
	Event();
	~Event();

	//Core Functions
	void reInitialize(Assets& assets);

	//Castle Events
	void spadeEncounter(Assets& assets);
};

#endif

