#include "Event.h"

//Constructors & Destructors
Event::Event()
{
    this->encounterInit = true;
    this->encounterInitTwo = true;
}

Event::~Event()
{

}

//Core Functions
void Event::reInitialize(Assets& assets)
{
   // assets.spadeCounter = -1;//Reset Spade sprite switch case counter
   // assets.spriteInit = false; //Uninitialize sprite border
    //assets.dialogueCounter = 0; //Reset dialogue counter
    //assets.spadeInit = false; //Allow zins sprite to be loaded again...
    //assets.text.setString(""); //Reset dialogue box

    //this->encounterInit = true; //Reset Local Control Flow Bools
    //this->encounterInitTwo = true;
}

//Bonfire Events
void Event::healCharactersText(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (assets.bonfireHealDetectionRect.getGlobalBounds().contains(mousePosF)) {
        assets.bonfireHealDetectionText.setString("Rest to restore health...?");
    }
    else {
        assets.bonfireHealDetectionText.setString("");
    }
}

void Event::healCharacters(sf::RenderWindow& window, Assets& assets, Combat& combat)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (assets.bonfireHealDetectionRect.getGlobalBounds().contains(mousePosF)) {
        combat.playerHp = combat.playerHpMax;
        combat.zinHp = combat.zinHpMax;
        assets.text.setString("All party members Hp restored...");
    }
}

void Event::smithingText(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (assets.bonfireSmithDetectionRect.getGlobalBounds().contains(mousePosF)) {
        assets.bonfireSmithDetectionText.setString("Smith Weapons...?");
    }
    else {
        assets.bonfireSmithDetectionText.setString("");
    }
}

void Event::smithingSharpenBlade(sf::RenderWindow& window, Assets& assets, Player& player)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (assets.bonfireSmithDetectionRect.getGlobalBounds().contains(mousePosF)) {
        if (player.smithingStones >= 1) {
            player.smithingStones--;
            assets.text.setString("You use the smithing stone to improve your sword further...");
            player.swordPower++;
            switch (player.swordPower) {
            case 0:
                player.basicSword = "Basic Longsword";
                break;
            case 1:
                player.basicSword = "Keen Longsword";
                break;
            case 2:
                player.basicSword = "Honed Longsword";
                break;
            case 3:
                player.basicSword = "Godsplitting Longsword";
                break;
            }
        }
        else if (player.smithingStones <= 0) {
            assets.text.setString("You lack the required smithing stones to improve your sword...");
        }
    }
}

//Castle Events
void Event::spadeEncounter(Assets& assets)
{
    //Initiate Dialogue
    switch (assets.dialogueCounter) {
    case 0:
        if (this->encounterInit == true) {
            assets.spriteInit = true; //Initialize Sprite Border
            assets.spadeCounter = 0; //Pick which Spade Sprite to use via switch statement
            assets.text.setString("Hey, what are you doing here...?"); //Set text for what's happening
            this->encounterInit = false; //Ensure this only runs once...
        }
        break;
    case 1:
        if (this->encounterInitTwo == true) {
            assets.spadeCounter = 1;
            assets.text.setString("Get OUT!");
            assets.soundAngry.play();
            this->encounterInitTwo = false;
        }
        break;
    case 2:
        std::cout << "Success";
        break;
    }
}
