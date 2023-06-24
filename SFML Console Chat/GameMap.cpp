#include "World.h"

//Functions
void World::questOne()
{
	this->userInput();
	this->initialized = true;
	this->questone = true;
	text.setString("Quest One Starting Success... Press 1 to continue");
	switch (this->unicode) {
	case 49:
		text.setString("You begin to run away");
		break;
	}
}

