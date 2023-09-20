#include "Travel.h"

//Constructors & Destructors
Travel::Travel()
{
    //Core
    this->frame = 0;
    this->travel = 0;

    //Counters
    this->introCounterDialogue = -1;

    this->introCounter = 0;
    this->forestCounter = 0;
    this->castleCounter = 0;
    this->decayCounter = 0;

    //Core Bools
    this->frameInit = false;
    
    //Bonfire Bools Detection initialization (Controls whether or not the detection rect is drawn...)
    this->forestBonfireInit = false;
}

Travel::~Travel()
{

}

//Core
void Travel::travelCore(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (assets.getMapCounter()) {
    case -1:
        this->intro(window, assets, notevent, combat, player);
        break;
    case 0:
        this->forestMap(window, assets, notevent, combat, player, animate);
        break;
    case 1:
        this->castleMap(window, assets, notevent, combat, player, animate);
        break;
    case 2:
        this->decayMap(window, assets, notevent, combat, player, animate);
        break;
    }
}

//Draw Intro
void Travel::intro(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    switch (this->introCounter) {
    case 0:
        this->introBeginning(window, assets, notevent, combat, player);
        break;
    }
}

void Travel::introBeginning(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{ //Frame init true or false fucking how
    notevent.reInitialize(assets);
    switch (this->introCounterDialogue) {
    case 0:
        assets.locationText.setString("");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        
        assets.text.setString("There once was a kingdom plentiful and prosperous. The citizens had very little to worry of and days were filled with joy. Though, not all good things last forever.");
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("A horrible blight began to grow deep from within the world. This sparked a dreadful plague those would later call 'Decay' which had sprung up from the Earth without warning.\nAnyone afflicted with the illness would watch as their skin would rot off of their very body. It caused the kingdom to be brought to its limits.");
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("You were a great knight of the kingdom. Raised with a blade and eventually working your way to the top of the ranks, you were the captain of the royal guard.\nThough, despite your prestiege, you were not safe from this terrible disease either.\nYou became afflicted with the decay throughout your help with the injured and it began to rot your flesh down to the bone.");
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("Some elven priests seemed to unexplainably have the power to resist the decay. \nMany believed they were granted the power by God himself as they possessed the power to burn the blight from the core of a human and restore them.\nThe king of the kingdom upon discovering this quickly rushed to find a priest to stop the disease from ravaging what is left of your body.");
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("A priestess came to your aid, saving most of your body from the decay and your life. However, much of your face had been melted off from the decay, only one of your eyes now usable.\nYou stayed as a knight of the kingdom after you were rescued, though it was by now on the brink of collapse.\n\nMuch of the world outside of the kingdom had shifted and changed. Many anomalies had taken place and much of the world and its creatures were no longer what you knew.\nChaos scratching at the kingdoms walls, you had a last stand with what was left of your royal guard leading them into battle.");
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("Despite your best efforts and hundreds of abominations slain under your sword, you had eventually fallen along with the kingdom. You had not lost your life, though nothing is left for you in these ruins.\nYou pick yourself up from the mud and begin to force yourself forwards into the lands unknown...");
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro7.jpeg");
            assets.soundWalk.play();
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("You begin walking for what feels like days, time passage beginning to slip into a distant memory. You know something's wrong when you begin asking question like 'Who am I?', 'Where am I?'\n\nYou eventually pass out...");
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro8.jpeg");
            assets.soundWalk.play();
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("When you awaken, you realize you're still in the woods, however you notice a small figure just beneath the foot of a tree. You look down at yourself and notice a lack of former injuries.\nShe must have healed you.");
        break;
    case 8:
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'Are you a priest, kid?'");
        assets.answerBoxText[1].setString("2. 'Did you save me?'");
        break;
    case 9:
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("Uh... Yeah, I am.");
            break;
        case 1:
            assets.text.setString("I did.");
            break;
        }
        break;
    case 10:
        assets.setZinCounterZero();
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'Well, I appreciate you saving my life.'");
        assets.answerBoxText[1].setString("2. 'Did you come from the castle?'");
        break;
    case 11:
        assets.setZinCounterZero();
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("She refrains from speaking further, only looks away briefly from you.");
            break;
        case 1:
            assets.text.setString("I did. They burnt everything...");
            break;
        }
        break;
    case 12:
        assets.setZinCounterZero();
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. *Take your leave*");
        assets.answerBoxText[1].setString("2. 'Do you know how to survive out here? In the woods I mean.'");
        break;
    case 13:
        assets.setZinCounterZero();
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("*You stand up and begin to leave when the girl follows you.*\n\nWait! I need you to help me... If you leave me by myself... Could we just start a fire and talk instead? It's cold.\n\n*You look down at your lack of fire starter...*");
            break;
        case 1:
            assets.text.setString("No, not really. We need to make a fire, don't we?\n\n*You look down at your lack of fire starter...*");
            break;
        }
        break;
    case 14:
        assets.setZinCounterZero();
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'Well, kid, you're the mage here. Can you cast fire?'");
        assets.answerBoxText[1].setString("2. 'I'm out of firestarter, so it might take me a minute...'");
        break;
    case 15:
        assets.setZinCounterZero();
        assets.drawZinSpriteBox();
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("I have can cast some lower level fires, I would rather not use smite though... It might attract creatures...\n\n*She begins lighting a fire as you help stoke it, bringing the flame to life...");
            break;
        case 1:
            assets.text.setString("*The girl perks up in excitment briefly*\n\nI have firestarter! Or uh, well I can cast something that can get us going at least...\n\n*She begins lighting a fire as you help stoke it, bringing the flame to life...");
            break;
        }
        break;
    case 16:
        assets.setMapCounterZero();
        assets.text.setString("");
        break;
    }
}

//Draw Forest
void Travel::forestMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Pick which location is currently selected within the forest...
    switch (this->forestCounter) {
    case 0:
        this->forestBonfire(window, assets, notevent, combat, player, animate);
        break;
    case 1:
        this->forestEntrance(assets, notevent, combat, player, animate);
        break;
    case 2:
        this->forestDepths(assets, notevent, combat, player, animate);
        break;
    case 3:
        this->forestAbyssal(assets, notevent, combat, player, animate);
        break;
    case 4:
        this->forestAbyssalDepths(assets, notevent, combat, player, animate);
        break;
    }
}

void Travel::forestBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        assets.locationText.setString("Forest Bonfire");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestbonfire.jpeg");
            this->frameInit = true;
        }
        notevent.healCharactersText(window, assets);
        notevent.smithingText(window, assets);
        assets.setBonfireAssetsTrue();
        assets.setIntroAssetsFalse(); //Disable intro hiding assets for further in the game
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        this->forestBonfireInit = true; //Draw detection rects for healing and smithing
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::forestEntrance(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Uninit bonfire
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        combat.initDecayWalker(assets);
        combat.combatLoop(assets, player, animate);
        break;
    case 2:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 3:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 4:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 5:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 6:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 7:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 8:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 9:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 10:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 11:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 12:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 13:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 14:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::forestDepths(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Unint bonfire
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 2:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 3:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 4:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 5:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 6:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 7:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 8:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 9:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 10:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 11:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 12:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 13:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 14:
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::forestAbyssal(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Unint bonfire
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 2:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 3:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 4:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 5:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 6:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 7:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 8:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 9:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 10:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 11:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 12:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 13:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 14:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::forestAbyssalDepths(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Unint bonfire
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Abyssal Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssaldepths15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

//Draw Castle
void Travel::castleMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->castleCounter) {
    case 0:
        this->castleBonfire(window, assets, notevent, combat, player, animate);
        break;
    case 1:
        this->castleHalls(assets, notevent, combat, player, animate);
        break;
    case 2:
        this->castleDepths(assets, notevent, combat, player, animate);
        break;
    case 3:
        this->castleChambers(assets, notevent, combat, player, animate);
        break;
    case 4:
        this->castleLabyrinth(assets, notevent, combat, player, animate);
        break;
    }
}

void Travel::castleBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        assets.locationText.setString("Castle Bonfire");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleBonfire.jpeg");
            this->frameInit = true;
        }
        notevent.healCharactersText(window, assets);
        notevent.smithingText(window, assets);
        assets.setBonfireAssetsTrue();
        assets.setIntroAssetsFalse(); //Disable intro hiding assets for further in the game
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        this->forestBonfireInit = true; //Draw detection rects for healing and smithing
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::castleHalls(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        this->forestBonfireInit = false; //Uninit bonfire if switching via selector buttons
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Castle Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle1.jpeg");
            assets.map.setTexture(assets.mapTexture);
            assets.map.setPosition(440.0f, -200.0f); // absolute position
            this->frameInit = true;
        }
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        combat.combatLoop(assets, player, animate);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}

void Travel::castleDepths(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Uninit bonfire if switching via selector buttons
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Castle Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths1.jpeg");
            this->frameInit = true;
        }
        //Initialize Spade and Sprite
        notevent.spadeEncounter(assets);
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}

void Travel::castleChambers(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Uninit bonfire if switching via selector buttons
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Castle Chambers");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlechambers15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}

void Travel::castleLabyrinth(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Uninit bonfire if switching via selector buttons
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Castle Labyrinth");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castlelabyrinth15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}

//Draw Decay
void Travel::decayMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->decayCounter) {
    case 0:
        this->decayBonfire(window, assets, notevent, combat, player, animate);
        break;
    case 1:
        this->decayChasms(assets, notevent, combat, player, animate);
        break;
    case 2:
        this->decayOcean(assets, notevent, combat, player, animate);
        break;
    case 3:
        this->decayForest(assets, notevent, combat, player, animate);
        break;
    case 4:
        this->decayGiants(assets, notevent, combat, player, animate);
        break;
    }
}

void Travel::decayBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        assets.locationText.setString("Decay Bonfire");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayBonfire.jpeg");
            this->frameInit = true;
        }
        notevent.healCharactersText(window, assets);
        notevent.smithingText(window, assets);
        assets.setBonfireAssetsTrue();
        assets.setIntroAssetsFalse(); //Disable intro hiding assets for further in the game
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        this->forestBonfireInit = true; //Draw detection rects for healing and smithing
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::decayChasms(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        this->forestBonfireInit = false; //Uninit bonfire if switching via selector buttons
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Decay Chasms");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson1.jpeg");
            assets.map.setTexture(assets.mapTexture);
            assets.map.setPosition(440.0f, -200.0f); // absolute position
            this->frameInit = true;
        }
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimson15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}

void Travel::decayOcean(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        this->forestBonfireInit = false; //Uninit bonfire if switching via selector buttons
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Decay Ocean");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean1.jpeg");
            assets.map.setTexture(assets.mapTexture);
            assets.map.setPosition(440.0f, -200.0f); // absolute position
            this->frameInit = true;
        }
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayocean15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}

void Travel::decayForest(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        this->forestBonfireInit = false; //Uninit bonfire if switching via selector buttons
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Decay Ocean");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest1.jpeg");
            assets.map.setTexture(assets.mapTexture);
            assets.map.setPosition(440.0f, -200.0f); // absolute position
            this->frameInit = true;
        }
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonforest15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}

void Travel::decayGiants(Assets& assets, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        this->forestBonfireInit = false; //Uninit bonfire if switching via selector buttons
        assets.setBonfireAssetsFalse();
        assets.locationText.setString("Decay Ocean");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants1.jpeg");
            assets.map.setTexture(assets.mapTexture);
            assets.map.setPosition(440.0f, -200.0f); // absolute position
            this->frameInit = true;
        }
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 10:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 11:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 12:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants13.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 13:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants14.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 14:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/crimsonGiants15.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}