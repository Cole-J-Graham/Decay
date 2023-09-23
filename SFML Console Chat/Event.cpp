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
        assets.spriteText[1].setString("Zin            " + std::to_string(combat.getZinHp()) + "/" + std::to_string(combat.getZinHpMax()));
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
    case -1:
        animate.getZinTalkNot() = true;
        break;
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
    switch (this->dialogue) {
    case 0:
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'So, what was it you wanted to talk about?'");
        assets.answerBoxText[1].setString("2. 'What's your name, kid?'");
        animate.getZinTalkNot() = false;
        break;
    case 1:
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("'Well... Uhhh... Are you a monster like those others?'\n\n*You look down at your skin, slowly rotting.*");
            break;
        case 1:
            assets.text.setString("'I'm Zin... When did you get the decay?'\n\n*You look down at your skin, slowly rotting.*");
            break;
        }
        break;
    case 2:
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'The decay has been rotting away at me for the past year. I caught it during my time as a knight at the castle...'");
        assets.answerBoxText[1].setString("2. 'Look, I'm gonna be honest with you, I probably don't have a lot of time left, kid...'");
        break;
    case 3:
        assets.getShowAnsBoxesCounter() = -1;
        assets.text.setString("*Without another word, Zin reaches her hand out and places it on your shoulder, a bright light coming from her hand.\n\nIt burns quite badly, however you notice the decay slowly receding from your body...*");
        break;
    case 4:
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'You have the power to cleanse the decay?!'");
        assets.answerBoxText[1].setString("2. 'You CAN help the decay?!'");
        break;
    case 5:
        assets.getShowAnsBoxesCounter() = -1;
        assets.text.setString("'Sorry for lying to you earlier. My dad told me to never tell someone I can cleanse it unless I trust them.'");
        break;
    case 6:
        assets.text.setString("Your mind comes to a dire realization. Despite your armor and sword being lost, you must still carry out your duties as a knight.\n\nShe must be protected at all costs as she is one of the last bastions of preserving life in this horrible world...");
        break;
    case 7:
        assets.text.setString("");
        this->reInitialize = true;
        break;
    }
}

//Forest Events
void Event::siwardEncounter(Assets& assets)
{
    this->reInit(assets);
    switch (this->dialogue) {
    case 0:
        assets.getSiwardLoadOnce() = false; //Allow to be used again
        assets.getSiwardCounter() = 0; //Make Siwards Sprite Appear
        assets.getEventAssets() = true; //Hide map, inv, stat, forward && back buttons
        assets.text.setString("A knight suddenly appears from around a tree, practically ambushing your view. Though he seems to get startled from your presence as well...");
        break;
    case 1:
        assets.text.setString("'Pardon my intrusion! I did not believe I would be finding people this deep in the woods! You both must be strong!'");
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
