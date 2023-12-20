#include"World.h"
World world;
Animation animate;

int main()
{
    while (!world.getStop())
    {
        world.bootUp(animate);
    }

    return 0;
}
