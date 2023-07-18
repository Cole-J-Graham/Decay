#include"World.h"

World world;

int main()
{
    while (!world.getStop())
    {
        world.bootUp();
    }

    return 0;
}
