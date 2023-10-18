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

    //Detection initialization (Controls whether or not the detection rect is drawn...)
    this->bonfireInit = false;

    //Sound Bools
    this->soundPlay = true;
}

Travel::~Travel()
{

}

//Core
void Travel::travelCore(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (sprites.getMapCounter()) {
    case -1:
        this->intro(window, sprites, notevent, combat, player);
        break;
    case 0:
        this->forestMap(window, sprites, notevent, combat, player, animate);
        break;
    case 1:
        this->castleMap(window, sprites, notevent, combat, player, animate);
        break;
    case 2:
        this->decayMap(window, sprites, notevent, combat, player, animate);
        break;
    }
}

void Travel::newArea(Sprites& sprites, Animation& animate)
{
    sprites.getSpriteViewerCounter() = 0;
    sprites.getEndFrame() = false; //Ensure that the forward arrow is allowed
    sprites.getStartFrame() = true; //Ensure that the back arrow is gone
    this->bonfireInit = false; //Uninit bonfire
    animate.getZinTalkNot() = false; //Unint bonfire zin notification
    sprites.soundCampfire.stop(); //Stop the ambience from playing
    this->soundPlay = true; //Reset bonfire sounds
    sprites.setBonfireAssetsFalse();
}

void Travel::enterBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent)
{
    //Draw healing detection rects
    notevent.healCharactersText(window, sprites);
    notevent.smithingText(window, sprites);
    //Make the entity viewer dissapear
    sprites.getSpriteViewerCounter() = -1;
    //Allow Zins sprite to be used again through the boolean
    sprites.setZinInitFalse();
    //Set correct frame for zins sprite to appear
    sprites.getZinCounter() = 0;
    //Draw detection rects for healing and smithing
    this->bonfireInit = true;
    sprites.setBonfireAssetsTrue();
    sprites.map.setTexture(sprites.mapTexture);
    sprites.map.setPosition(440.0f, -200.0f);
    if (this->soundPlay) {
        sprites.soundCampfire.play();
        this->soundPlay = false;
    }
}

//Draw Intro
void Travel::intro(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player)
{
    switch (this->introCounter) {
    case 0:
        this->introBeginning(window, sprites, notevent);
        break;
    }
}

void Travel::introBeginning(sf::RenderWindow& window, Sprites& sprites, Event& notevent)
{ //Frame init true or false fucking how
    switch (this->introCounterDialogue) {
    case 0:
        sprites.getEventAssets() = true;
        sprites.locationText.setString("");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro1.jpeg");
            this->frameInit = true;
        }
        sprites.text.setString("There once was a kingdom plentiful and prosperous. The citizens had very little to worry of and days were filled with joy. Though, not all good things last forever.");
        sprites.map.setTexture(sprites.mapTexture);
        sprites.map.setPosition(440.0f, -200.0f);
        break;
    case 1:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro2.jpeg");
            this->frameInit = true;
        }
        sprites.text.setString("A horrible blight began to grow deep from within the world. This sparked a dreadful plague those would later call 'Decay' which had sprung up from the Earth without warning.\nAnyone afflicted with the illness would watch as their skin would rot off of their very body. It caused the kingdom to be brought to its limits.");
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro3.jpeg");
            this->frameInit = true;
        }
        sprites.text.setString("You were a great knight of the kingdom. Raised with a blade and eventually working your way to the top of the ranks, you were the captain of the royal guard.\nThough, despite your prestiege, you were not safe from this terrible disease either.\nYou became afflicted with the decay throughout your help with the injured and it began to rot your flesh down to the bone.");
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro4.jpeg");
            this->frameInit = true;
        }
        sprites.text.setString("Some elven priests seemed to unexplainably have the power to resist the decay. \nMany believed they were granted the power by God himself as they possessed the power to burn the blight from the core of a human and restore them.\nThe king of the kingdom upon discovering this quickly rushed to find a priest to stop the disease from ravaging what is left of your body.");
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro5.jpeg");
            this->frameInit = true;
        }
        sprites.text.setString("A priestess came to your aid, saving most of your body from the decay and your life. However, much of your face had been melted off from the decay, only one of your eyes now usable.\nYou stayed as a knight of the kingdom after you were rescued, though it was by now on the brink of collapse.\n\nMuch of the world outside of the kingdom had shifted and changed. Many anomalies had taken place and much of the world and its creatures were no longer what you knew.\nChaos scratching at the kingdoms walls, you had a last stand with what was left of your royal guard leading them into battle.");
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro6.jpeg");
            this->frameInit = true;
        }
        sprites.text.setString("Despite your best efforts and hundreds of abominations slain under your sword, you had eventually fallen along with the kingdom. You had not lost your life, though nothing is left for you in these ruins.\nYou pick yourself up from the mud and begin to force yourself forwards into the lands unknown...");
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro7.jpeg");
            sprites.soundWalk.play();
            this->frameInit = true;
        }
        sprites.text.setString("You begin walking for what feels like days, time passage beginning to slip into a distant memory. You know something's wrong when you begin asking question like 'Who am I?', 'Where am I?'\n\nYou eventually pass out...");
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro8.jpeg");
            sprites.soundWalk.play();
            this->frameInit = true;
        }
        sprites.text.setString("When you awaken, you realize you're still in the woods, however you notice a small figure just beneath the foot of a tree. You look down at yourself and notice a lack of former injuries.\nShe must have healed you.");
        break;
    case 8:
        sprites.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'Are you a priest, kid?'");
        sprites.answerBoxText[1].setString("2. 'Did you save me?'");
        break;
    case 9:
        sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
        sprites.getShowAnsBoxesCounter() = -1;
        switch (notevent.getChoiceCounter()) {
        case 0:
            sprites.text.setString("'Uh... Yeah, I am. It doesn't mean I could help that though...\n\n*She points to your arm covered in decay, slowly rotting.\n\n*You roll your sleeve back up, hiding the wound, wondering how much time you have left...*'");
            break;
        case 1:
            sprites.text.setString("'I did the best I could, but your decay...'\n\n*She points to your arm covered in it, slowly rotting.\n\n*You roll your sleeve back up, hiding the wound, wondering how much time you have left...*");
            break;
        }
        break;
    case 10:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'Well, I appreciate you saving my life. I would be dead without your help.'");
        sprites.answerBoxText[1].setString("2. 'Did you come from the castle?'");
        break;
    case 11:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = -1;
        switch (notevent.getChoiceCounter()) {
        case 0:
            sprites.text.setString("*She refrains from speaking further, only looks away briefly from you.*");
            break;
        case 1:
            sprites.text.setString("'I did but... They burnt everything... It's all gone.'");
            break;
        }
        break;
    case 12:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'I should be off.' *Take your leave*");
        sprites.answerBoxText[1].setString("2. 'Do you know how to survive out here? In the woods I mean.'");
        break;
    case 13:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = -1;
        switch (notevent.getChoiceCounter()) {
        case 0:
            sprites.text.setString("*You stand up and begin to leave when the girl follows you and shouts.*\n\n'Wait! I need you to help me... If you leave me by myself... Could we just start a fire and talk instead? It's cold.'\n\n*You look down at your lack of fire starter...*");
            break;
        case 1:
            sprites.text.setString("'No, not really. We need to make a fire, don't we?'\n\n*You look down at your lack of fire starter...*");
            break;
        }
        break;
    case 14:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'Well, kid, you're the mage here. Can you cast fire?'");
        sprites.answerBoxText[1].setString("2. 'I'm out of firestarter, so it might take me a minute...'");
        break;
    case 15:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = -1;
        switch (notevent.getChoiceCounter()) {
        case 0:
            sprites.text.setString("'I can cast some lower level fire spells, but I would rather not use smite... It might attract creatures...'\n\n*You feel a bit confused by her words. Smite? That's a very high level lightning spell...*\n\n*She begins lighting a fire as you help stoke it, bringing the flame to life...*");
            break;
        case 1:
            sprites.text.setString("*The girl perks up in excitment briefly*\n\nI have firestarter! Or uh, well I can cast something that can get us going at least...\n\n*She begins lighting a fire as you help stoke it, bringing the flame to life...*");
            break;
        }
        break;
    case 16:
        notevent.getDialogue() = 0;//Reset dialogue counter to allow other events to take place
        sprites.setMapCounterZero();
        sprites.text.setString("");
        sprites.getIntroFinished() = true;
        sprites.getEventAssets() = false;
        break;
    }
}

//Draw Forest
void Travel::forestMap(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Pick which location is currently selected within the forest...
    switch (this->forestCounter) {
    case 0:
        this->forestBonfire(window, sprites, notevent, combat, player, animate);
        break;
    case 1:
        this->forestEntrance(sprites, notevent, combat, player, animate);
        break;
    case 2:
        this->forestDepths(sprites, notevent, combat, player, animate);
        break;
    case 3:
        this->forestAbyssal(sprites, notevent, combat, player, animate);
        break;
    case 4:
        this->forestAbyssalDepths(sprites, notevent, combat, player, animate);
        break;
    }
}

void Travel::forestBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    sprites.locationText.setString("Forest Bonfire");
    if (!this->frameInit) {
        sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestbonfire.jpeg");
        this->frameInit = true;
    }
    //Play notification animation if zin is willing to talk
    if (this->bonfireInit) {
        animate.animateNotification();
    }
    this->enterBonfire(window, sprites, notevent);
}

void Travel::forestEntrance(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Forest Entrance");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest1.jpeg");
            animate.getDecayWarning() = true;
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;//Allow back arrow to re appear
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest2.jpeg");
            this->frameInit = true;
        }
        combat.initDecayWalker(sprites);
        combat.combatLoop(sprites, player, animate);
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest7.jpeg");
            animate.getDecayWarning() = true;
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest11.jpeg");
            this->frameInit = true;
        }
        notevent.forestSiwardEncounter(sprites);
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forest15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::forestDepths(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Forest Depths");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        //Prep Encounter Dialogue
        //notevent.getReInitialize() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        //notevent.treeEncounter(assets, player);
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths6.jpeg");
            this->frameInit = true;
        }
        combat.initHostileTree(sprites);
        combat.combatLoop(sprites, player, animate);
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        notevent.getReInitialize() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        notevent.forestDepthsSpadeEncounter(sprites);
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false; //Ensure that the back arrow is gone
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true; //Ensure that the back arrow is gone
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestdepths15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::forestAbyssal(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Abyssal Forest");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        //Prep Encounter Dialogue
        //notevent.getReInitialize() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods5.jpeg");
            this->frameInit = true;
        }
        //notevent.obeliskEncounter(assets, player);
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        //Prep Encounter Dialogue
        notevent.getReInitialize() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        notevent.lostNunEncounter(sprites);
        if (notevent.getNunEncountered()) {
            combat.initLostNun(sprites);
            combat.combatLoop(sprites, player, animate);
        }
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::forestAbyssalDepths(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Abyssal Forest Depths");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths3.jpeg");
            this->frameInit = true;
        }
        combat.initDecapod(sprites);
        combat.combatLoop(sprites, player, animate);
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

//Draw Castle
void Travel::castleMap(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->castleCounter) {
    case 0:
        this->castleBonfire(window, sprites, notevent, combat, player, animate);
        break;
    case 1:
        this->castleHalls(sprites, notevent, combat, player, animate);
        break;
    case 2:
        this->castleDepths(sprites, notevent, combat, player, animate);
        break;
    case 3:
        this->castleChambers(sprites, notevent, combat, player, animate);
        break;
    case 4:
        this->castleLabyrinth(sprites, notevent, combat, player, animate);
        break;
    }
}

void Travel::castleBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    sprites.locationText.setString("Castle Bonfire");
    if (!this->frameInit) {
        sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleBonfire.jpeg");
        this->frameInit = true;
    }
    this->enterBonfire(window, sprites, notevent);
}

void Travel::castleHalls(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        this->newArea(sprites, animate);
        sprites.locationText.setString("Castle Entrance");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castle15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::castleDepths(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Castle Depths");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths1.jpeg");
            this->frameInit = true;
        }
        //Initialize Spade and Sprite
        notevent.spadeEncounter(sprites);
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleDepths15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::castleChambers(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Castle Chambers");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers13.jpeg");
            this->frameInit = true;
        }
        break;
        sprites.getEndFrame() = false;
    case 13:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlechambers15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::castleLabyrinth(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Castle Labyrinth");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

//Draw Decay
void Travel::decayMap(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->decayCounter) {
    case 0:
        this->decayBonfire(window, sprites, notevent, combat, player, animate);
        break;
    case 1:
        this->decayChasms(sprites, notevent, combat, player, animate);
        break;
    case 2:
        this->decayOcean(sprites, notevent, combat, player, animate);
        break;
    case 3:
        this->decayForest(sprites, notevent, combat, player, animate);
        break;
    case 4:
        this->decayGiants(sprites, notevent, combat, player, animate);
        break;
    }
}

void Travel::decayBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    sprites.locationText.setString("Decay Bonfire");
    if (!this->frameInit) {
        sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayBonfire.jpeg");
        this->frameInit = true;
    }
    this->enterBonfire(window, sprites, notevent);
}

void Travel::decayChasms(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Decay Chasms");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson4.jpeg");
            this->frameInit = true;
        }
        combat.initLimbSplitter(sprites);
        combat.combatLoop(sprites, player, animate);
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimson15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::decayOcean(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Decay Ocean");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayocean15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::decayForest(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Decay Ocean");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonforest15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}

void Travel::decayGiants(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Decay Ocean");
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants1.jpeg");
            this->frameInit = true;
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants2.jpeg");
            this->frameInit = true;
        }
        break;
    case 2:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants3.jpeg");
            this->frameInit = true;
        }
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants4.jpeg");
            this->frameInit = true;
        }
        break;
    case 4:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants5.jpeg");
            this->frameInit = true;
        }
        break;
    case 5:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants6.jpeg");
            this->frameInit = true;
        }
        break;
    case 6:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants7.jpeg");
            this->frameInit = true;
        }
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants8.jpeg");
            this->frameInit = true;
        }
        break;
    case 8:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants9.jpeg");
            this->frameInit = true;
        }
        break;
    case 9:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants10.jpeg");
            this->frameInit = true;
        }
        break;
    case 10:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants11.jpeg");
            this->frameInit = true;
        }
        break;
    case 11:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants12.jpeg");
            this->frameInit = true;
        }
        break;
    case 12:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants13.jpeg");
            this->frameInit = true;
        }
        break;
    case 13:
        sprites.getEndFrame() = false;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants14.jpeg");
            this->frameInit = true;
        }
        break;
    case 14:
        sprites.getEndFrame() = true;
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants15.jpeg");
            this->frameInit = true;
        }
        break;
    }
}