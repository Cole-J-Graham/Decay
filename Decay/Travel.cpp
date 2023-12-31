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
    this->reInMap = false;

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
    sprites.bonfire.stop(); //Stop the ambience from playing
    this->soundPlay = true; //Reset bonfire sounds
    sprites.setBonfireAssetsFalse();
    animate.getDecayWarning() = false;
    this->reInMap = false;
}

void Travel::enterBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent)
{
    //Draw healing detection rects
    notevent.healCharactersText(window, sprites);
    notevent.smithingText(window, sprites);
    //Make the entity viewer dissapear
    sprites.getSpriteViewerCounter() = -1;
    //Set correct frame for zins sprite to appear
    sprites.getZinCounter() = 0;
    //Set correct frame for Thom is he is unlocked
    if (sprites.getThomUnlocked()) {
        sprites.getThomCounter() = 0;
    }
    //Draw detection rects for healing and smithing
    this->bonfireInit = true;
    sprites.setBonfireAssetsTrue();
    sprites.map.setTexture(sprites.mapTexture);
    sprites.map.setPosition(440.0f, -200.0f);
    sprites.getTrackPlayed() = false;
    if (this->soundPlay) {
        sprites.bonfire.play();
        this->soundPlay = false;
    }
}

void Travel::nextArea(Sprites& sprites, std::string& inString)
{
    if (!this->frameInit) {
        sprites.mapTexture.loadFromFile(inString);
        frameInit = true;
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
            sprites.track2.play();
            sprites.track8.stop();
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
        sprites.text.setString("You were a great knight of the kingdom. Raised with a blade and eventually working your way to the top of the ranks, you were the captain of the royal guard.\nThough, despite your prestiege, you were not safe from this terrible disease either. You became afflicted with the decay throughout your help with the injured and it began to rot your flesh down to the bone.");
        break;
    case 3:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro4.jpeg");
            this->frameInit = true;
        }
        sprites.text.setString("Some elven priests seemed to unexplainably have the power to resist the decay. \n\nMany believed they were granted the power by God himself as they possessed the power to burn the blight from the core of a human and restore them.\n\nThe king of the kingdom upon discovering this quickly rushed to find a priest to stop the disease from ravaging what is left of your body.");
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
        sprites.text.setString("*You begin walking for what feels like days, time passage beginning to slip into a distant memory. You know something's wrong when you begin asking question like 'Who am I?', 'Where am I?'*\n\n*You eventually pass out...*");
        break;
    case 7:
        if (!this->frameInit) {
            sprites.mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro8.jpeg");
            sprites.soundWalk.play();
            this->frameInit = true;
        }
        sprites.text.setString("*When you awaken, you realize you're still in the woods and laying on the floor, however you notice a small figure just beneath the foot of a tree. You look down at yourself and notice a lack of former injuries.*\n\n*She must have healed you... And given by her ears she looks like an elf. You assume she must be a priestess.*");
        break;
    case 8:
        sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. *Try to stand*");
        sprites.answerBoxText[1].setString("2. 'Did you save me?'");
        break;
    case 9:
        sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
        sprites.getShowAnsBoxesCounter() = -1;
        switch (notevent.getChoiceCounter()) {
        case 0:
            sprites.text.setString("'Hey, be careful. I patched you up but uh... Well I can't do much about that long term...' *The girl states as she points to the decay festering in your arm.*\n\n*She seems to perk up slightly before speaking again...* 'Though, I am able to cleanse it for a time to keep you going.'");
            break;
        case 1:
            sprites.text.setString("'I did the best I could, but your decay...'\n\n*She points to your arm covered in it, slowly rotting. *You roll your sleeve back up, hiding the wound, wondering how much time you have left...*\n\n*She seems to perk up slightly before speaking again...* 'But I am able to cleanse it for a short time... to keep you going.'");
            break;
        }
        break;
    case 10:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'Thanks.'");
        sprites.answerBoxText[1].setString("2. 'I know how the decay works, kid.'");
        break;
    case 11:
        sprites.getShowAnsBoxesCounter() = -1;
        switch (notevent.getChoiceCounter()) {
        case 0:
            sprites.getZinCounter() = 1;
            sprites.text.setString("*The girl smiles from your simple thanks, taking the liberty to speak again.* 'My name is Zin, what's yours?'\n\n*Before you can answer, she suddenly seems to perk up once more.* 'Wait, I know you! You're that knight guy from the castle!'");
            break;
        case 1:
            sprites.getZinCounter() = 3;
            sprites.text.setString("*The girl looks slightly annoyed from your remark...* 'I just wanted to make sure you knew. A lot of people dealing with this stuff have no clue how bad it really is...' *She seems to almost be pouting...*\n\n*She continues to mutter before suddenly perking up...* 'My name is Zin by the wa- Hold on, I think I know you! You're that knight from the castle, aren't you?'");
            break;
        }
        break;
    case 12:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'How'd you know?'");
        sprites.answerBoxText[1].setString("2. 'Yeah, back when there was a castle...'");
        break;
    case 13:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = -1;
        sprites.text.setString("'I knew I thought I recognized you. Now it makes sense, you must have gotten infected while helping around the medical ward, huh?' *As she talks you notice her shivering...*");
        break;
    case 14:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. *Change subject* 'We need to get a fire going. Are you able to cast fire magic?'");
        sprites.answerBoxText[1].setString("2. 'Yeah, that is how I caught the decay unfortunately. But even with the decay, we still need to worry about the basic elements. Are you able to cast fire magic?'");
        break;
    case 15:
        sprites.getZinCounter() = 0;
        sprites.getShowAnsBoxesCounter() = -1;
        switch (notevent.getChoiceCounter()) {
        case 0:
            sprites.text.setString("'I can cast some lower level fire spells, but I would rather not use smite... It might attract creatures...'\n\n*You feel a bit confused by her words. Smite? That's a very high level lightning spell...*\n\n*She begins lighting a fire as you help stoke it, bringing the flame to life...*");
            break;
        case 1:
            sprites.text.setString("*The girl perks up briefly* 'I can cast something that can get it sparked at least...'\n\n*She begins lighting a fire as you help stoke it, bringing the flame to life...*");
            break;
        }
        break;
    case 16:
        notevent.getDialogue() = 0;//Reset dialogue counter to allow other events to take place
        sprites.setMapCounterZero();
        sprites.text.setString("");
        sprites.getIntroFinished() = true;
        sprites.getEventAssets() = false;
        sprites.track2.stop();
        sprites.getTrackPlayed() = false;
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
        this->forestEntrance(window, sprites, notevent, combat, player, animate);
        break;
    case 2:
        this->forestDepths(window, sprites, notevent, combat, player, animate);
        break;
    case 3:
        this->forestAbyssal(window, sprites, notevent, combat, player, animate);
        break;
    case 4:
        this->forestAbyssalDepths(window, sprites, notevent, combat, player, animate);
        break;
    }
}

void Travel::forestBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    sprites.locationText.setString("Forest Bonfire");
    if (!this->frameInit) {
        sprites.track6.stop();
        sprites.track7.stop();
        sprites.mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestbonfire.jpeg");
        this->frameInit = true;
    }
    this->enterBonfire(window, sprites, notevent);
}

void Travel::forestEntrance(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Forest Entrance");
        this->nextArea(sprites, sprites.forestEntrance1);
        sprites.playTrack(sprites.track1);
        sprites.playAmbience(sprites.forestAmbience);
        break;
    case 1:
        this->nextArea(sprites, sprites.forestEntrance2);
        sprites.getStartFrame() = false;//Allow back arrow to re appear
        combat.initDecayWalker(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track5, sprites.track1);
        break;
    case 2:
        this->nextArea(sprites, sprites.forestEntrance3);
        break;
    case 3:
        this->nextArea(sprites, sprites.forestEntrance4);
        break;
    case 4:
        this->nextArea(sprites, sprites.forestEntrance5);
        break;
    case 5:
        this->nextArea(sprites, sprites.forestEntrance6);
        break;
    case 6:
        this->nextArea(sprites, sprites.forestEntrance7);
        notevent.riEnc(sprites);
        break;
    case 7:
        this->nextArea(sprites, sprites.forestEntrance8);
        break;
    case 8:
        this->nextArea(sprites, sprites.forestEntrance9);
        break;
    case 9:
        this->nextArea(sprites, sprites.forestEntrance10);
        break;
    case 10:
        this->nextArea(sprites, sprites.forestEntrance11);
        notevent.forestSiwardEnc(sprites);
        break;
    case 11:
        this->nextArea(sprites, sprites.forestEntrance12);
        break;
    case 12:
        this->nextArea(sprites, sprites.forestEntrance13);
        break;
    case 13:
        this->nextArea(sprites, sprites.forestEntrance14);
        sprites.getEndFrame() = false;
        break;
    case 14:
        this->nextArea(sprites, sprites.forestEntrance15);
        sprites.getEndFrame() = true;
        sprites.getForestAreaUnlocked() = 2;
        this->reInitMap(sprites.getInitForestMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Forest Entrance explored. View map to move to a new area.");
        break;
    }
}

void Travel::forestDepths(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Forest Depths");
        this->nextArea(sprites, sprites.forestDepths1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.forestDepths2);
        break;
    case 2:
        this->nextArea(sprites, sprites.forestDepths3);
        combat.initWolf(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track5, sprites.track1);
        break;
    case 3:
        notevent.treeEnc(sprites, player);
        this->nextArea(sprites, sprites.forestDepths4);
        break;
    case 4:
        this->nextArea(sprites, sprites.forestDepths5);
        break;
    case 5:
        this->nextArea(sprites, sprites.forestDepths6);
        combat.initHostileTree(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track5, sprites.track1);
        break;
    case 6:
        this->nextArea(sprites, sprites.forestDepths7);
        notevent.thomEnc(sprites);
        break;
    case 7:
        this->nextArea(sprites, sprites.forestDepths8);
        break;
    case 8:
        this->nextArea(sprites, sprites.forestDepths9);
        break;
    case 9:
        this->nextArea(sprites, sprites.forestDepths10);
        combat.initDecayKnight(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track5, sprites.track1);
        break;
    case 10:
        notevent.forestDepthsSpadeEnc(sprites);
        this->nextArea(sprites, sprites.forestDepths11);
        break;
    case 11:
        this->nextArea(sprites, sprites.forestDepths12);
        notevent.forestDepthsSpadeEnc(sprites);
        break;
    case 12:
        this->nextArea(sprites, sprites.forestDepths13);
        break;
    case 13:
        sprites.getEndFrame() = false; //Ensure that the back arrow is gone
        this->nextArea(sprites, sprites.forestDepths14);
        break;
    case 14:
        sprites.getEndFrame() = true; //Ensure that the back arrow is gone
        this->nextArea(sprites, sprites.forestDepths15);
        sprites.getForestAreaUnlocked() = 3;
        this->reInitMap(sprites.getInitForestMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Forest Depths explored. View map to move to a new area.");
        break;
    }
}

void Travel::forestAbyssal(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Abyssal Forest");
        this->nextArea(sprites, sprites.forestAbyssal1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.forestAbyssal2);
        break;
    case 2:
        notevent.forestAbyssalSpadeEnc(sprites, player);
        this->nextArea(sprites, sprites.forestAbyssal3);
        break;
    case 3:
        this->nextArea(sprites, sprites.forestAbyssal4);
        break;
    case 4:
        notevent.obeliskEnc(sprites, player);
        this->nextArea(sprites, sprites.forestAbyssal5);
        break;
    case 5:
        this->nextArea(sprites, sprites.forestAbyssal6);
        break;
    case 6:
        this->nextArea(sprites, sprites.forestAbyssal7);
        break;
    case 7:
        this->nextArea(sprites, sprites.forestAbyssal8);
        break;
    case 8:
        this->nextArea(sprites, sprites.forestAbyssal9);
        break;
    case 9:
        this->nextArea(sprites, sprites.forestAbyssal10);
        break;
    case 10:
        this->nextArea(sprites, sprites.forestAbyssal11);
        break;
    case 11:
        notevent.lostNunEnc(sprites);
        if (notevent.getNunEnced()) {
            combat.initLostNun(sprites);
            combat.combatLoop(window, sprites, player, animate);
            combat.stopComTrack(sprites.track5, sprites.track1);
        }
        this->nextArea(sprites, sprites.forestAbyssal12);
        break;
    case 12:
        this->nextArea(sprites, sprites.forestAbyssal13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.forestAbyssal14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.forestAbyssal15);
        sprites.getForestAreaUnlocked() = 4;
        this->reInitMap(sprites.getInitForestMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Abyssal Forest explored. View map to move to a new area.");
        break;
    }
}

void Travel::forestAbyssalDepths(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Abyssal Forest Depths");
        this->nextArea(sprites, sprites.forestAbyssalDepth1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.forestAbyssalDepth2);
        notevent.forestAbyssalSpadeEnc(sprites, player);
        break;
    case 2:
        this->nextArea(sprites, sprites.forestAbyssalDepth3);
        combat.initDecapod(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track5, sprites.track1);
        break;
    case 3:
        this->nextArea(sprites, sprites.forestAbyssalDepth4);
        break;
    case 4:
        this->nextArea(sprites, sprites.forestAbyssalDepth5);
        break;
    case 5:
        this->nextArea(sprites, sprites.forestAbyssalDepth6);
        break;
    case 6:
        this->nextArea(sprites, sprites.forestAbyssalDepth7);
        break;
    case 7:
        this->nextArea(sprites, sprites.forestAbyssalDepth8);
        break;
    case 8:
        this->nextArea(sprites, sprites.forestAbyssalDepth9);
        break;
    case 9:
        this->nextArea(sprites, sprites.forestAbyssalDepth10);
        break;
    case 10:
        this->nextArea(sprites, sprites.forestAbyssalDepth11);
        break;
    case 11:
        this->nextArea(sprites, sprites.forestAbyssalDepth12);
        break;
    case 12:
        this->nextArea(sprites, sprites.forestAbyssalDepth13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.forestAbyssalDepth14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.forestAbyssalDepth15);
        sprites.getAreaUnlocked() = 1;
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Abyssal Depths explored. View map to move to a new area.");
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
        this->castleHalls(window, sprites, notevent, combat, player, animate);
        break;
    case 2:
        this->castleDepths(window, sprites, notevent, combat, player, animate);
        break;
    case 3:
        this->castleChambers(window, sprites, notevent, combat, player, animate);
        break;
    case 4:
        this->castleLabyrinth(window, sprites, notevent, combat, player, animate);
        break;
    }
}

void Travel::castleBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    sprites.locationText.setString("Castle Bonfire");
    if (!this->frameInit) {
        sprites.track1.stop();
        sprites.track7.stop();
        sprites.mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleBonfire.jpeg");
        this->frameInit = true;
    }
    this->enterBonfire(window, sprites, notevent);
}

void Travel::castleHalls(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        this->newArea(sprites, animate);
        sprites.playTrack(sprites.track6);
        sprites.locationText.setString("Castle Entrance");
        this->nextArea(sprites, sprites.castleHalls1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.castleHalls2);
        break;
    case 2:
        this->nextArea(sprites, sprites.castleHalls3);
        break;
    case 3:
        this->nextArea(sprites, sprites.castleHalls4);
        break;
    case 4:
        this->nextArea(sprites, sprites.castleHalls5);
        combat.initCourtJester(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track9, sprites.track6);
        break;
    case 5:
        this->nextArea(sprites, sprites.castleHalls6);
        break;
    case 6:
        this->nextArea(sprites, sprites.castleHalls7);
        break;
    case 7:
        this->nextArea(sprites, sprites.castleHalls8);
        break;
    case 8:
        this->nextArea(sprites, sprites.castleHalls9);
        break;
    case 9:
        this->nextArea(sprites, sprites.castleHalls10);
        break;
    case 10:
        this->nextArea(sprites, sprites.castleHalls11);
        break;
    case 11:
        this->nextArea(sprites, sprites.castleHalls12);
        break;
    case 12:
        this->nextArea(sprites, sprites.castleHalls13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.castleHalls14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.castleHalls15);
        sprites.getCastleAreaUnlocked() = 2;
        this->reInitMap(sprites.getInitCastleMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Castle Halls explored. View map to move to a new area.");
        break;
    }
}

void Travel::castleDepths(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Castle Depths");
        this->nextArea(sprites, sprites.castleDepths1);
        //Initialize Spade and Sprite
        if (notevent.getSpadePoison()) {
            notevent.castleSpadeEncPoison(sprites);
        }
        else {
            notevent.castleSpadeEnc(sprites);
        }
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.castleDepths2);
        break;
    case 2:
        this->nextArea(sprites, sprites.castleDepths3);
        break;
    case 3:
        this->nextArea(sprites, sprites.castleDepths4);
        combat.initWallMimic(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track9, sprites.track6);
        break;
    case 4:
        this->nextArea(sprites, sprites.castleDepths5);
        break;
    case 5:
        this->nextArea(sprites, sprites.castleDepths6);
        break;
    case 6:
        this->nextArea(sprites, sprites.castleDepths7);
        break;
    case 7:
        this->nextArea(sprites, sprites.castleDepths8);
        break;
    case 8:
        this->nextArea(sprites, sprites.castleDepths9);
        break;
    case 9:
        this->nextArea(sprites, sprites.castleDepths10);
        break;
    case 10:
        this->nextArea(sprites, sprites.castleDepths11);
        notevent.castleSiwardEnc(sprites);
        break;
    case 11:
        this->nextArea(sprites, sprites.castleDepths12);
        break;
    case 12:
        this->nextArea(sprites, sprites.castleDepths13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.castleDepths14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.castleDepths15);
        sprites.getCastleAreaUnlocked() = 3;
        this->reInitMap(sprites.getInitCastleMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Castle Depths explored. View map to move to a new area.");
        break;
    }
}

void Travel::castleChambers(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Castle Chambers");
        this->nextArea(sprites, sprites.castleChambers1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.castleChambers2);
        break;
    case 2:
        this->nextArea(sprites, sprites.castleChambers3);
        notevent.castleGrifEnc(sprites);
        break;
    case 3:
        this->nextArea(sprites, sprites.castleChambers4);
        break;
    case 4:
        this->nextArea(sprites, sprites.castleChambers5);
        combat.initLostKnight(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track9, sprites.track6);
        break;
    case 5:
        this->nextArea(sprites, sprites.castleChambers6);
        break;
    case 6:
        this->nextArea(sprites, sprites.castleChambers7);
        break;
    case 7:
        this->nextArea(sprites, sprites.castleChambers8);
        break;
    case 8:
        this->nextArea(sprites, sprites.castleChambers9);
        break;
    case 9:
        this->nextArea(sprites, sprites.castleChambers10);
        combat.initPhantom(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track9, sprites.track6);
        break;
    case 10:
        this->nextArea(sprites, sprites.castleChambers11);
        break;
    case 11:
        this->nextArea(sprites, sprites.castleChambers12);
        break;
    case 12:
        this->nextArea(sprites, sprites.castleChambers13);
        break;
        sprites.getEndFrame() = false;
    case 13:
        this->nextArea(sprites, sprites.castleChambers14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.castleChambers15);
        sprites.getCastleAreaUnlocked() = 4;
        this->reInitMap(sprites.getInitCastleMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Castle Chambers explored. View map to move to a new area.");
        break;
    }
}

void Travel::castleLabyrinth(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Castle Labyrinth");
        this->nextArea(sprites, sprites.castleLab1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.castleLab2);
        break;
    case 2:
        this->nextArea(sprites, sprites.castleLab3);
        break;
    case 3:
        this->nextArea(sprites, sprites.castleLab4);
        break;
    case 4:
        this->nextArea(sprites, sprites.castleLab5);
        combat.initSkinEater(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track9, sprites.track6);
        break;
    case 5:
        this->nextArea(sprites, sprites.castleLab6);
        break;
    case 6:
        this->nextArea(sprites, sprites.castleLab7);
        break;
    case 7:
        this->nextArea(sprites, sprites.castleLab8);
        break;
    case 8:
        this->nextArea(sprites, sprites.castleLab9);
        break;
    case 9:
        this->nextArea(sprites, sprites.castleLab10);
        break;
    case 10:
        this->nextArea(sprites, sprites.castleLab11);
        break;
    case 11:
        this->nextArea(sprites, sprites.castleLab12);
        break;
    case 12:
        this->nextArea(sprites, sprites.castleLab13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.castleLab14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.castleLab15);
        notevent.castleSiwardFinalEnc(sprites);
        if (notevent.getSiwardEncedFinal()) {
            sprites.spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            combat.initSiward(sprites);
            combat.combatLoop(window, sprites, player, animate);
        }
        sprites.getAreaUnlocked() = 2;
        if (combat.getCombatEnd() && notevent.getSiwardEncedFinal()) {
            sprites.getSiwardCounter() = -1;
            sprites.spriteText[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        }
        //Remove Text
        combat.getComTextRemoved() = false;
        combat.stopComTrack(sprites.track3, sprites.track6);
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
        this->decayChasms(window, sprites, notevent, combat, player, animate);
        break;
    case 2:
        this->decayOcean(window, sprites, notevent, combat, player, animate);
        break;
    case 3:
        this->decayForest(window, sprites, notevent, combat, player, animate);
        break;
    case 4:
        this->decayGiants(window, sprites, notevent, combat, player, animate);
        break;
    }
}

void Travel::decayBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    sprites.locationText.setString("Decay Bonfire");
    if (!this->frameInit) {
        sprites.track1.stop();
        sprites.track6.stop();
        sprites.mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayBonfire.jpeg");
        this->frameInit = true;
    }
    this->enterBonfire(window, sprites, notevent);
}

void Travel::decayChasms(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.playTrack(sprites.track7);
        sprites.locationText.setString("Decay Chasms");
        this->nextArea(sprites, sprites.decayChasms1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.decayChasms2);
        break;
    case 2:
        this->nextArea(sprites, sprites.decayChasms3);
        break;
    case 3:
        this->nextArea(sprites, sprites.decayChasms4);
        notevent.decayGrifEnc(sprites);
        break;
    case 4:
        this->nextArea(sprites, sprites.decayChasms5);
        combat.initLimbSplitter(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track10, sprites.track7);
        break;
    case 5:
        this->nextArea(sprites, sprites.decayChasms6);
        break;
    case 6:
        this->nextArea(sprites, sprites.decayChasms7);
        break;
    case 7:
        this->nextArea(sprites, sprites.decayChasms8);
        break;
    case 8:
        this->nextArea(sprites, sprites.decayChasms9);
        combat.initChatterMouth(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track10, sprites.track7);
        break;
    case 9:
        this->nextArea(sprites, sprites.decayChasms10);
        break;
    case 10:
        this->nextArea(sprites, sprites.decayChasms11);
        break;
    case 11:
        this->nextArea(sprites, sprites.decayChasms12);
        combat.initBurrower(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track10, sprites.track7);
        break;
    case 12:
        this->nextArea(sprites, sprites.decayChasms13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.decayChasms14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.decayChasms15);
        sprites.getDecayAreaUnlocked() = 2;
        this->reInitMap(sprites.getInitDecayMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Decay Chasms explored. View map to move to a new area.");
        break;
    }
}

void Travel::decayOcean(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Decay Ocean");
        this->nextArea(sprites, sprites.decayOcean1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.decayOcean2);
        break;
    case 2:
        this->nextArea(sprites, sprites.decayOcean3);
        break;
    case 3:
        this->nextArea(sprites, sprites.decayOcean4);
        break;
    case 4:
        this->nextArea(sprites, sprites.decayOcean5);
        break;
    case 5:
        this->nextArea(sprites, sprites.decayOcean6);
        break;
    case 6:
        this->nextArea(sprites, sprites.decayOcean7);
        break;
    case 7:
        this->nextArea(sprites, sprites.decayOcean8);
        combat.initTendrilAlpha(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track10, sprites.track7);
        break;
    case 8:
        this->nextArea(sprites, sprites.decayOcean9);
        break;
    case 9:
        this->nextArea(sprites, sprites.decayOcean10);
        break;
    case 10:
        this->nextArea(sprites, sprites.decayOcean11);
        break;
    case 11:
        this->nextArea(sprites, sprites.decayOcean12);
        break;
    case 12:
        this->nextArea(sprites, sprites.decayOcean13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.decayOcean14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.decayOcean15);
        sprites.getDecayAreaUnlocked() = 3;
        this->reInitMap(sprites.getInitDecayMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Decay Ocean explored. View map to move to a new area.");
        break;
    }
}

void Travel::decayForest(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Decay Ocean");
        this->nextArea(sprites, sprites.decayForest1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.decayForest2);
        break;
    case 2:
        this->nextArea(sprites, sprites.decayForest3);
        break;
    case 3:
        this->nextArea(sprites, sprites.decayForest4);
        break;
    case 4:
        this->nextArea(sprites, sprites.decayForest5);
        break;
    case 5:
        this->nextArea(sprites, sprites.decayForest6);
        break;
    case 6:
        this->nextArea(sprites, sprites.decayForest7);
        break;
    case 7:
        this->nextArea(sprites, sprites.decayForest8);
        break;
    case 8:
        this->nextArea(sprites, sprites.decayForest9);
        break;
    case 9:
        this->nextArea(sprites, sprites.decayForest10);
        break;
    case 10:
        this->nextArea(sprites, sprites.decayForest11);
        notevent.decaySpadeEncPoison(sprites);
        if (notevent.getSpadeEnced()) {
            sprites.spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            combat.initSpade(sprites);
            combat.combatLoop(window, sprites, player, animate);
            combat.stopComTrack(sprites.track4, sprites.track7);
        }
        if (combat.getCombatEnd() && notevent.getSpadeEnced()) {
            sprites.getSpadeCounter() = -1;
            sprites.spriteText[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        }
        break;
    case 11:
        this->nextArea(sprites, sprites.decayForest12);
        break;
    case 12:
        this->nextArea(sprites, sprites.decayForest13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.decayForest14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.decayForest15);
        sprites.getDecayAreaUnlocked() = 4;
        this->reInitMap(sprites.getInitDecayMapTexture());
        //Remove Text
        combat.getComTextRemoved() = false;
        sprites.text.setString("Decay Forest explored. View map to move to a new area.");
        break;
    }
}

void Travel::decayGiants(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(sprites, animate);
        sprites.locationText.setString("Decay Ocean");
        this->nextArea(sprites, sprites.decayGiants1);
        break;
    case 1:
        sprites.getStartFrame() = false;
        this->nextArea(sprites, sprites.decayGiants2);
        break;
    case 2:
        this->nextArea(sprites, sprites.decayGiants3);
        break;
    case 3:
        this->nextArea(sprites, sprites.decayGiants4);
        break;
    case 4:
        this->nextArea(sprites, sprites.decayGiants5);
        break;
    case 5:
        this->nextArea(sprites, sprites.decayGiants6);
        combat.initReclus(sprites);
        combat.combatLoop(window, sprites, player, animate);
        combat.stopComTrack(sprites.track10, sprites.track7);
        break;
    case 6:
        this->nextArea(sprites, sprites.decayGiants7);
        break;
    case 7:
        this->nextArea(sprites, sprites.decayGiants8);
        break;
    case 8:
        this->nextArea(sprites, sprites.decayGiants9);
        break;
    case 9:
        this->nextArea(sprites, sprites.decayGiants10);
        break;
    case 10:
        this->nextArea(sprites, sprites.decayGiants11);
        break;
    case 11:
        this->nextArea(sprites, sprites.decayGiants12);
        break;
    case 12:
        this->nextArea(sprites, sprites.decayGiants13);
        break;
    case 13:
        sprites.getEndFrame() = false;
        this->nextArea(sprites, sprites.decayGiants14);
        break;
    case 14:
        sprites.getEndFrame() = true;
        this->nextArea(sprites, sprites.decayGiants15);
        notevent.rotBeastEnc(sprites);
        if (notevent.getRotBeastEnced()) {
            combat.initRotBeast(sprites);
            combat.combatLoop(window, sprites, player, animate);
            if (!combat.getPlayerDead() && combat.getCombatEnd()) {
                notevent.rotBeastDeathEnding(sprites);
            }
            else if (combat.getPlayerDead()) {
                combat.getCombatEnd() = true;
                notevent.playerDeathEnding(sprites);
            }
        }
        break;
    }
}