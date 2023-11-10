#include"World.h"

World world;
Assets assets;
Sprites sprites;
Combat combat;
Player player;
Event notevent;
Travel travel;
Animation animate;

int main()
{
    while (!world.getStop())
    {
        world.BootUp(sprites, notevent, combat, player, travel, animate);
    }

    return 0;
}
