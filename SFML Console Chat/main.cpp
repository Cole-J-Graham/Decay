#include"World.h"

World world;
Assets assets;
Combat combat;
Player player;
Event notevent;

int main()
{
    while (!world.getStop())
    {
        world.bootUp(assets, notevent, combat, player);
    }

    return 0;
}
