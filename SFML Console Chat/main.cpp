#include"World.h"

World world;
sf::RenderWindow window;

int main()
{
    while (!world.getStop())
    {
        world.bootUp();
    }

    return 0;
}
