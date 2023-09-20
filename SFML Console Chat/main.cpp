#include"World.h"

World world;
Assets assets;
Combat combat;
Player player;
Event notevent;
Travel travel;
Animation animate;

int main()
{
    while (!world.getStop())
    {
        world.bootUp(assets, notevent, combat, player, travel, animate);
    }

    return 0;
}
