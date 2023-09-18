#include"World.h"

World world;
Assets assets;
Combat combat;
Player player;
Event notevent;
Travel travel;

int main()
{
    while (!world.getStop())
    {
        world.bootUp(assets, notevent, combat, player, travel);
    }

    return 0;
}
