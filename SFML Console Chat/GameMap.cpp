#include "World.h"

//Functions
void World::questOne()
{
    if (questone == true) {
        text.setString("Quest One Starting Success... Press 1 to continue");

        switch (unicode) {
        case 49:
            playerInput = "";
            text.setString("You begin to run away");
            break;
        }
    }
}

