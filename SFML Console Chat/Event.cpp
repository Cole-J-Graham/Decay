#include "Event.h"

//Constructors & Destructors
Event::Event()
{
    //Control Flow Bools
    this->reInitialize = true;

    this->encounterInit = true;
    this->encounterInitTwo = true;

    //Counters
    this->zinTalkCounter = -1;

    //Dialogue Counter
    this->dialogue = 0;
}

Event::~Event()
{

}

//Core Functions
void Event::reInit(Assets& assets)
{
    if (this->reInitialize) {
        this->dialogue = 0;
        this->reInitialize = false;
    }
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
        combat.getPlayerHp() = combat.getPlayerHpMax();
        combat.getZinHp() = combat.getZinHpMax();
        assets.text.setString("All party members Hp restored...");
        assets.textElements[7].setString("Zin            " + std::to_string(combat.getZinHp()) + "/" + std::to_string(combat.getZinHpMax()));
        assets.textElements[6].setString(assets.getPlayerName() + "     " + std::to_string(combat.getPlayerHp()) + "/" + std::to_string(combat.getPlayerHpMax()));
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
        if (player.getSmithingStones() >= 1) {
            player.setSmithingStonesDec();
            assets.text.setString("You use the smithing stone to improve your sword further...");
            player.setSwordPowerInc();
            switch (player.getSwordPower()) {
            case 0:
                player.getBasicSword() = "Basic Longsword";
                break;
            case 1:
                player.getBasicSword() = "Keen Longsword";
                break;
            case 2:
                player.getBasicSword() = "Honed Longsword";
                break;
            case 3:
                player.getBasicSword() = "Godsplitting Longsword";
                break;
            }
        }
        else if (player.getSmithingStones() <= 0) {
            assets.text.setString("You lack the required smithing stones to improve your sword...");
        }
    }
}

//Bonfire Text Events
void Event::zinEvents(sf::RenderWindow& window, Assets& assets, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Zin Conversations at Bonfire
    if (assets.spriteElements[3].getGlobalBounds().contains(mousePosF)) {
        this->zinTalkCounter = 0;
    }

    switch (this->zinTalkCounter) {
    case 0:
        this->zinInitialTalk(assets, animate);
        break;
    case 1:
        break;
    }
}

//Zin Events
void Event::zinInitialTalk(Assets& assets, Animation& animate)
{
    std::cout << this->dialogue;
    //this->reInit(assets);
    switch (this->dialogue) {
    case 0:
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.drawZinSpriteBox();
        assets.answerBoxText[0].setString("1. 'So, what was it you wanted to talk about?'");
        assets.answerBoxText[1].setString("2. 'What's your name, kid?'");
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        animate.getZinTalkNot() = false;
        break;
    case 1:
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("'Well... Uhhh... Are you a monster like those others?'");
            break;
        case 1:
            assets.text.setString("'I'm Zin...'");
            break;
        }
        break;
    }
}
//Castle Events
void Event::spadeEncounter(Assets& assets)
{
    //Initiate Dialogue
    switch (assets.getDialogueCounter()) {
    case 0:
        if (this->encounterInit == true) {
            assets.setSpriteInitTrue(); //Initialize Sprite Border
            assets.setSpadeCounterZero(); //Pick which Spade Sprite to use via switch statement
            assets.text.setString("Hey, what are you doing here...?"); //Set text for what's happening
            this->encounterInit = false; //Ensure this only runs once...
        }
        break;
    case 1:
        if (this->encounterInitTwo == true) {
            assets.setSpadeCounterOne();
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
