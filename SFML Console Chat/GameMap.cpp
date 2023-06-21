#include "World.h"

//Functions
void World::questOne()
{
	text.setString("Quest One Starting Success...");
	switch (event.text.unicode) {
	case '2':
		text.setString("You begin to run away");
		break;
	}
}

