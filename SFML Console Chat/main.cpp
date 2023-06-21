#include"World.h"

World world;

int main()
{
    while (!world.stop)
    {
        world.bootUp();
    }

    return 0;
}
