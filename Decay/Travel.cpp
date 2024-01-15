#include "Travel.h"

void Travel::render(sf::RenderTarget* target)
{

}

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
void Travel::travelCore(sf::RenderWindow& window, Animation& animate)
{
    switch (getMapCounter()) {
    case -1:
        this->intro(window);
        break;
    case 0:
        this->forestMap(window, animate);
        break;
    case 1:
        this->castleMap(window, animate);
        break;
    case 2:
        this->decayMap(window, animate);
        break;
    }
}

void Travel::newArea(Animation& animate)
{
    getSpriteViewerCounter() = 0;
    getEndFrame() = false; //Ensure that the forward arrow is allowed
    getStartFrame() = true; //Ensure that the back arrow is gone
    this->bonfireInit = false; //Uninit bonfire
    bonfire.stop(); //Stop the ambience from playing
    this->soundPlay = true; //Reset bonfire sounds
    getBonfireAssets() = false;
    animate.getDecayWarning() = false;
    this->reInMap = false;
    animate.anvilSprite.setPosition(10000, 10000);
    animate.healSprite.setPosition(10000, 10000);
}

void Travel::enterBonfire(sf::RenderWindow& window)
{
    //Draw healing detection rects
    healCharactersText(window);
    smithingText(window);
    //Make the entity viewer dissapear
    getSpriteViewerCounter() = -1;
    //Set correct frame for zins sprite to appear
    getZinCounter() = 0;
    //Set correct frame for Thom is he is unlocked
    if (getThomUnlocked()) {
        getThomCounter() = 0;
    }
    //Draw detection rects for healing and smithing
    this->bonfireInit = true;
    getBonfireAssets() = true;
    map.setTexture(mapTexture);
    map.setPosition(440.0f, -200.0f);
    getTrackPlayed() = false;
    if (this->soundPlay) {
        bonfire.play();
        this->soundPlay = false;
    }
}

void Travel::nextArea(std::string& inString)
{
    if (!this->frameInit) {
        mapTexture.loadFromFile(inString);
        frameInit = true;
    }
}

//Draw Intro
void Travel::intro(sf::RenderWindow& window)
{
    switch (this->introCounter) {
    case 0:
        this->introBeginning(window);
        break;
    }
}

void Travel::introBeginning(sf::RenderWindow& window)
{ //Frame init true or false fucking how
    switch (this->introCounterDialogue) {
    case 0:
        getEventAssets() = true;
        locationText.setString("");
        if (!this->frameInit) {
            mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro1.jpeg");
            track2.play();
            track8.stop();
            this->frameInit = true;
        }
        text.setString("There once was a kingdom plentiful and prosperous. The citizens had very little to worry of and days were filled with joy. Though, not all good things last forever.");
        map.setTexture(mapTexture);
        map.setPosition(440.0f, -200.0f);
        break;
    case 1:
        if (!this->frameInit) {
            mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro2.jpeg");
            this->frameInit = true;
        }
        text.setString("A horrible blight began to grow deep from within the world. This sparked a dreadful plague those would later call 'Decay' which had sprung up from the Earth without warning.\nAnyone afflicted with the illness would watch as their skin would rot off of their very body. It caused the kingdom to be brought to its limits.");
        break;
    case 2:
        if (!this->frameInit) {
            mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro3.jpeg");
            this->frameInit = true;
        }
        text.setString("You were a great knight of the kingdom. Raised with a blade and eventually working your way to the top of the ranks, you were the captain of the royal guard.\nThough, despite your prestiege, you were not safe from this terrible disease either. You became afflicted with the decay throughout your help with the injured and it began to rot your flesh down to the bone.");
        break;
    case 3:
        if (!this->frameInit) {
            mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro4.jpeg");
            this->frameInit = true;
        }
        text.setString("Some elven priests seemed to unexplainably have the power to resist the decay. \n\nMany believed they were granted the power by God himself as they possessed the power to burn the blight from the core of a human and restore them.\n\nThe king of the kingdom upon discovering this quickly rushed to find a priest to stop the disease from ravaging what is left of your body.");
        break;
    case 4:
        if (!this->frameInit) {
            mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro5.jpeg");
            this->frameInit = true;
        }
        text.setString("A priestess came to your aid, saving most of your body from the decay and your life. However, much of your face had been melted off from the decay, only one of your eyes now usable.\nYou stayed as a knight of the kingdom after you were rescued, though it was by now on the brink of collapse.\n\nMuch of the world outside of the kingdom had shifted and changed. Many anomalies had taken place and much of the world and its creatures were no longer what you knew.\nChaos scratching at the kingdoms walls, you had a last stand with what was left of your royal guard leading them into battle.");
        break;
    case 5:
        if (!this->frameInit) {
            mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro6.jpeg");
            this->frameInit = true;
        }
        text.setString("Despite your best efforts and hundreds of abominations slain under your sword, you had eventually fallen along with the kingdom. You had not lost your life, though nothing is left for you in these ruins.\nYou pick yourself up from the mud and begin to force yourself forwards into the lands unknown...");
        break;
    case 6:
        if (!this->frameInit) {
            mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro7.jpeg");
            soundWalk.play();
            this->frameInit = true;
        }
        text.setString("*You begin walking for what feels like days, time passage beginning to slip into a distant memory. You know something's wrong when you begin asking question like 'Who am I?', 'Where am I?'*\n\n*You eventually pass out...*");
        break;
    case 7:
        if (!this->frameInit) {
            mapTexture.loadFromFile("Assets/Wallpapers/Intro/intro8.jpeg");
            soundWalk.play();
            this->frameInit = true;
        }
        text.setString("*When you awaken, you realize you're still in the woods and laying on the floor, however you notice a small figure just beneath the foot of a tree. You look down at yourself and notice a lack of former injuries.*\n\n*She must have healed you... And given by her ears she looks like an elf. You assume she must be a priestess.*");
        break;
    case 8:
        getZinCounter() = 0; //Set correct frame for zins sprite to appear
        getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        answerBoxText[0].setString("1. *Try to stand*");
        answerBoxText[1].setString("2. 'Did you save me?'");
        break;
    case 9:
        getZinCounter() = 0; //Set correct frame for zins sprite to appear
        getShowAnsBoxesCounter() = -1;
        switch (getChoiceCounter()) {
        case 0:
            text.setString("'Hey, be careful. I patched you up but uh... Well I can't do much about that long term...' *The girl states as she points to the decay festering in your arm.*\n\n*She seems to perk up slightly before speaking again...* 'Though, I am able to cleanse it for a time to keep you going.'");
            break;
        case 1:
            text.setString("'I did the best I could, but your decay...'\n\n*She points to your arm covered in it, slowly rotting. *You roll your sleeve back up, hiding the wound, wondering how much time you have left...*\n\n*She seems to perk up slightly before speaking again...* 'But I am able to cleanse it for a short time... to keep you going.'");
            break;
        }
        break;
    case 10:
        getZinCounter() = 0;
        getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        answerBoxText[0].setString("1. 'Thanks.'");
        answerBoxText[1].setString("2. 'I know how the decay works, kid.'");
        break;
    case 11:
        getShowAnsBoxesCounter() = -1;
        switch (getChoiceCounter()) {
        case 0:
            getZinCounter() = 1;
            text.setString("*The girl smiles from your simple thanks, taking the liberty to speak again.* 'My name is Zin, what's yours?'\n\n*Before you can answer, she suddenly seems to perk up once more.* 'Wait, I know you! You're that knight guy from the castle!'");
            break;
        case 1:
            getZinCounter() = 3;
            text.setString("*The girl looks slightly annoyed from your remark...* 'I just wanted to make sure you knew. A lot of people dealing with this stuff have no clue how bad it really is...' *She seems to almost be pouting...*\n\n*She continues to mutter before suddenly perking up...* 'My name is Zin by the wa- Hold on, I think I know you! You're that knight from the castle, aren't you?'");
            break;
        }
        break;
    case 12:
        getZinCounter() = 0;
        getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        answerBoxText[0].setString("1. 'How'd you know?'");
        answerBoxText[1].setString("2. 'Yeah, back when there was a castle...'");
        break;
    case 13:
        getZinCounter() = 0;
        getShowAnsBoxesCounter() = -1;
        text.setString("'I knew I thought I recognized you. Now it makes sense, you must have gotten infected while helping around the medical ward, huh?' *As she talks you notice her shivering...*");
        break;
    case 14:
        getZinCounter() = 0;
        getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        answerBoxText[0].setString("1. *Change subject* 'We need to get a fire going. Are you able to cast fire magic?'");
        answerBoxText[1].setString("2. 'Yeah, that is how I caught the decay unfortunately. But even with the decay, we still need to worry about the basic elements. Are you able to cast fire magic?'");
        break;
    case 15:
        getZinCounter() = 0;
        getShowAnsBoxesCounter() = -1;
        switch (getChoiceCounter()) {
        case 0:
            text.setString("'I can cast some lower level fire spells, but I would rather not use smite... It might attract creatures...'\n\n*You feel a bit confused by her words. Smite? That's a very high level lightning spell...*\n\n*She begins lighting a fire as you help stoke it, bringing the flame to life...*");
            break;
        case 1:
            text.setString("*The girl perks up briefly* 'I can cast something that can get it sparked at least...'\n\n*She begins lighting a fire as you help stoke it, bringing the flame to life...*");
            break;
        }
        break;
    case 16:
        getDialogue() = 0;//Reset dialogue counter to allow other events to take place
        setMapCounterZero();
        text.setString("");
        getIntroFinished() = true;
        getEventAssets() = false;
        track2.stop();
        getTrackPlayed() = false;
        break;
    }
}

//Draw Forest
void Travel::forestMap(sf::RenderWindow& window, Animation& animate)
{
    //Pick which location is currently selected within the forest...
    switch (this->forestCounter) {
    case 0:
        this->forestBonfire(window);
        break;
    case 1:
        this->forestEntrance(window, animate);
        break;
    case 2:
        this->forestDepths(window, animate);
        break;
    case 3:
        this->forestAbyssal(window, animate);
        break;
    case 4:
        this->forestAbyssalDepths(window, animate);
        break;
    }
}

void Travel::forestBonfire(sf::RenderWindow& window)
{
    locationText.setString("Forest Bonfire");
    if (!this->frameInit) {
        track6.stop();
        track7.stop();
        mapTexture.loadFromFile("Assets/Wallpapers/Forest/forestbonfire.jpeg");
        this->frameInit = true;
    }
    this->enterBonfire(window);
}

void Travel::forestEntrance(sf::RenderWindow& window, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Forest Entrance");
        this->nextArea(forestEntrance1);
        playTrack(track1);
        playAmbience(forestAmbience);
        break;
    case 1:
        this->nextArea(forestEntrance2);
        getStartFrame() = false;//Allow back arrow to re appear
        initDecayWalker();
        combatLoop(window, animate);
        stopComTrack(track5, track1);
        break;
    case 2:
        this->nextArea(forestEntrance3);
        break;
    case 3:
        this->nextArea(forestEntrance4);
        break;
    case 4:
        this->nextArea(forestEntrance5);
        break;
    case 5:
        this->nextArea(forestEntrance6);
        break;
    case 6:
        this->nextArea(forestEntrance7);
        riEnc();
        break;
    case 7:
        this->nextArea(forestEntrance8);
        break;
    case 8:
        this->nextArea(forestEntrance9);
        break;
    case 9:
        this->nextArea(forestEntrance10);
        break;
    case 10:
        this->nextArea(forestEntrance11);
        forestSiwardEnc();
        break;
    case 11:
        this->nextArea(forestEntrance12);
        break;
    case 12:
        this->nextArea(forestEntrance13);
        break;
    case 13:
        this->nextArea(forestEntrance14);
        getEndFrame() = false;
        break;
    case 14:
        this->nextArea(forestEntrance15);
        getEndFrame() = true;
        getForestAreaUnlocked() = 2;
        this->reInitMap(getInitForestMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Forest Entrance explored. View map to move to a new area.");
        break;
    }
}

void Travel::forestDepths(sf::RenderWindow& window, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Forest Depths");
        this->nextArea(forestDepths1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(forestDepths2);
        break;
    case 2:
        this->nextArea(forestDepths3);
        initWolf();
        combatLoop(window, animate);
        stopComTrack(track5, track1);
        break;
    case 3:
        treeEnc();
        this->nextArea(forestDepths4);
        break;
    case 4:
        this->nextArea(forestDepths5);
        break;
    case 5:
        this->nextArea(forestDepths6);
        initHostileTree();
        combatLoop(window, animate);
        stopComTrack(track5, track1);
        break;
    case 6:
        this->nextArea(forestDepths7);
        thomEnc();
        break;
    case 7:
        this->nextArea(forestDepths8);
        break;
    case 8:
        this->nextArea(forestDepths9);
        break;
    case 9:
        this->nextArea(forestDepths10);
        initDecayKnight();
        combatLoop(window, animate);
        stopComTrack(track5, track1);
        break;
    case 10:
        forestDepthsSpadeEnc();
        this->nextArea(forestDepths11);
        break;
    case 11:
        this->nextArea(forestDepths12);
        forestDepthsSpadeEnc();
        break;
    case 12:
        this->nextArea(forestDepths13);
        break;
    case 13:
        getEndFrame() = false; //Ensure that the back arrow is gone
        this->nextArea(forestDepths14);
        break;
    case 14:
        getEndFrame() = true; //Ensure that the back arrow is gone
        this->nextArea(forestDepths15);
        getForestAreaUnlocked() = 3;
        this->reInitMap(getInitForestMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Forest Depths explored. View map to move to a new area.");
        break;
    }
}

void Travel::forestAbyssal(sf::RenderWindow& window, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Abyssal Forest");
        this->nextArea(forestAbyssal1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(forestAbyssal2);
        break;
    case 2:
        forestAbyssalSpadeEnc();
        this->nextArea(forestAbyssal3);
        break;
    case 3:
        this->nextArea(forestAbyssal4);
        break;
    case 4:
        obeliskEnc();
        this->nextArea(forestAbyssal5);
        break;
    case 5:
        this->nextArea(forestAbyssal6);
        break;
    case 6:
        this->nextArea(forestAbyssal7);
        break;
    case 7:
        this->nextArea(forestAbyssal8);
        break;
    case 8:
        this->nextArea(forestAbyssal9);
        break;
    case 9:
        this->nextArea(forestAbyssal10);
        break;
    case 10:
        this->nextArea(forestAbyssal11);
        break;
    case 11:
        lostNunEnc();
        if (getNunEnced()) {
            initLostNun();
            combatLoop(window, animate);
            stopComTrack(track5, track1);
        }
        this->nextArea(forestAbyssal12);
        break;
    case 12:
        this->nextArea(forestAbyssal13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(forestAbyssal14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(forestAbyssal15);
        getForestAreaUnlocked() = 4;
        this->reInitMap(getInitForestMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Abyssal Forest explored. View map to move to a new area.");
        break;
    }
}

void Travel::forestAbyssalDepths(sf::RenderWindow& window, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Abyssal Forest Depths");
        this->nextArea(forestAbyssalDepth1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(forestAbyssalDepth2);
        forestAbyssalSpadeEnc();
        break;
    case 2:
        this->nextArea(forestAbyssalDepth3);
        initDecapod();
        combatLoop(window, animate);
        stopComTrack(track5, track1);
        break;
    case 3:
        this->nextArea(forestAbyssalDepth4);
        break;
    case 4:
        this->nextArea(forestAbyssalDepth5);
        break;
    case 5:
        this->nextArea(forestAbyssalDepth6);
        break;
    case 6:
        this->nextArea(forestAbyssalDepth7);
        break;
    case 7:
        this->nextArea(forestAbyssalDepth8);
        break;
    case 8:
        this->nextArea(forestAbyssalDepth9);
        break;
    case 9:
        this->nextArea(forestAbyssalDepth10);
        break;
    case 10:
        this->nextArea(forestAbyssalDepth11);
        break;
    case 11:
        this->nextArea(forestAbyssalDepth12);
        break;
    case 12:
        this->nextArea(forestAbyssalDepth13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(forestAbyssalDepth14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(forestAbyssalDepth15);
        getAreaUnlocked() = 1;
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Abyssal Depths explored. View map to move to a new area.");
        break;
    }
}

//Draw Castle
void Travel::castleMap(sf::RenderWindow& window, Animation& animate)
{
    switch (this->castleCounter) {
    case 0:
        this->castleBonfire(window);
        break;
    case 1:
        this->castleHalls(window, animate);
        break;
    case 2:
        this->castleDepths(window, animate);
        break;
    case 3:
        this->castleChambers(window, animate);
        break;
    case 4:
        this->castleLabyrinth(window, animate);
        break;
    }
}

void Travel::castleBonfire(sf::RenderWindow& window)
{
    locationText.setString("Castle Bonfire");
    if (!this->frameInit) {
        track1.stop();
        track7.stop();
        mapTexture.loadFromFile("Assets/Wallpapers/Castle/castleBonfire.jpeg");
        this->frameInit = true;
    }
    this->enterBonfire(window);
}

void Travel::castleHalls(sf::RenderWindow& window, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        this->newArea(animate);
        playTrack(track6);
        locationText.setString("Castle Entrance");
        this->nextArea(castleHalls1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(castleHalls2);
        break;
    case 2:
        this->nextArea(castleHalls3);
        break;
    case 3:
        this->nextArea(castleHalls4);
        break;
    case 4:
        this->nextArea(castleHalls5);
        initCourtJester();
        combatLoop(window, animate);
        stopComTrack(track9, track6);
        break;
    case 5:
        this->nextArea(castleHalls6);
        break;
    case 6:
        this->nextArea(castleHalls7);
        break;
    case 7:
        this->nextArea(castleHalls8);
        break;
    case 8:
        this->nextArea(castleHalls9);
        break;
    case 9:
        this->nextArea(castleHalls10);
        break;
    case 10:
        this->nextArea(castleHalls11);
        break;
    case 11:
        this->nextArea(castleHalls12);
        break;
    case 12:
        this->nextArea(castleHalls13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(castleHalls14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(castleHalls15);
        getCastleAreaUnlocked() = 2;
        this->reInitMap(getInitCastleMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Castle Halls explored. View map to move to a new area.");
        break;
    }
}

void Travel::castleDepths(sf::RenderWindow& window, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Castle Depths");
        this->nextArea(castleDepths1);
        //Initialize Spade and Sprite
        if (getSpadePoison()) {
            castleSpadeEncPoison();
        }
        else {
            castleSpadeEnc();
        }
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(castleDepths2);
        break;
    case 2:
        this->nextArea(castleDepths3);
        break;
    case 3:
        this->nextArea(castleDepths4);
        initWallMimic();
        combatLoop(window, animate);
        stopComTrack(track9, track6);
        break;
    case 4:
        this->nextArea(castleDepths5);
        break;
    case 5:
        this->nextArea(castleDepths6);
        break;
    case 6:
        this->nextArea(castleDepths7);
        break;
    case 7:
        this->nextArea(castleDepths8);
        break;
    case 8:
        this->nextArea(castleDepths9);
        break;
    case 9:
        this->nextArea(castleDepths10);
        break;
    case 10:
        this->nextArea(castleDepths11);
        castleSiwardEnc();
        break;
    case 11:
        this->nextArea(castleDepths12);
        break;
    case 12:
        this->nextArea(castleDepths13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(castleDepths14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(castleDepths15);
        getCastleAreaUnlocked() = 3;
        this->reInitMap(getInitCastleMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Castle Depths explored. View map to move to a new area.");
        break;
    }
}

void Travel::castleChambers(sf::RenderWindow& window, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Castle Chambers");
        this->nextArea(castleChambers1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(castleChambers2);
        break;
    case 2:
        this->nextArea(castleChambers3);
        castleGrifEnc();
        break;
    case 3:
        this->nextArea(castleChambers4);
        break;
    case 4:
        this->nextArea(castleChambers5);
        initLostKnight();
        combatLoop(window, animate);
        stopComTrack(track9, track6);
        break;
    case 5:
        this->nextArea(castleChambers6);
        break;
    case 6:
        this->nextArea(castleChambers7);
        break;
    case 7:
        this->nextArea(castleChambers8);
        break;
    case 8:
        this->nextArea(castleChambers9);
        break;
    case 9:
        this->nextArea(castleChambers10);
        initPhantom();
        combatLoop(window, animate);
        stopComTrack(track9, track6);
        break;
    case 10:
        this->nextArea(castleChambers11);
        break;
    case 11:
        this->nextArea(castleChambers12);
        break;
    case 12:
        this->nextArea(castleChambers13);
        break;
        getEndFrame() = false;
    case 13:
        this->nextArea(castleChambers14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(castleChambers15);
        getCastleAreaUnlocked() = 4;
        this->reInitMap(getInitCastleMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Castle Chambers explored. View map to move to a new area.");
        break;
    }
}

void Travel::castleLabyrinth(sf::RenderWindow& window, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Castle Labyrinth");
        this->nextArea(castleLab1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(castleLab2);
        break;
    case 2:
        this->nextArea(castleLab3);
        break;
    case 3:
        this->nextArea(castleLab4);
        break;
    case 4:
        this->nextArea(castleLab5);
        initSkinEater();
        combatLoop(window, animate);
        stopComTrack(track9, track6);
        break;
    case 5:
        this->nextArea(castleLab6);
        break;
    case 6:
        this->nextArea(castleLab7);
        break;
    case 7:
        this->nextArea(castleLab8);
        break;
    case 8:
        this->nextArea(castleLab9);
        break;
    case 9:
        this->nextArea(castleLab10);
        break;
    case 10:
        this->nextArea(castleLab11);
        break;
    case 11:
        this->nextArea(castleLab12);
        break;
    case 12:
        this->nextArea(castleLab13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(castleLab14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(castleLab15);
        castleSiwardFinalEnc();
        if (getSiwardEncedFinal()) {
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            initSiward();
            combatLoop(window, animate);
        }
        getAreaUnlocked() = 2;
        if (getCombatEnd() && getSiwardEncedFinal()) {
            getSiwardCounter() = -1;
            spriteText[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        }
        //Remove Text
        getComTextRemoved() = false;
        stopComTrack(track3, track6);
        break;
    }
}

//Draw Decay
void Travel::decayMap(sf::RenderWindow& window, Animation& animate)
{
    switch (this->decayCounter) {
    case 0:
        this->decayBonfire(window);
        break;
    case 1:
        this->decayChasms(window, animate);
        break;
    case 2:
        this->decayOcean(window, animate);
        break;
    case 3:
        this->decayForest(window, animate);
        break;
    case 4:
        this->decayGiants(window, animate);
        break;
    }
}

void Travel::decayBonfire(sf::RenderWindow& window)
{
    locationText.setString("Decay Bonfire");
    if (!this->frameInit) {
        track1.stop();
        track6.stop();
        mapTexture.loadFromFile("Assets/Wallpapers/Decay/decayBonfire.jpeg");
        this->frameInit = true;
    }
    this->enterBonfire(window);
}

void Travel::decayChasms(sf::RenderWindow& window, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        playTrack(track7);
        locationText.setString("Decay Chasms");
        this->nextArea(decayChasms1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(decayChasms2);
        break;
    case 2:
        this->nextArea(decayChasms3);
        break;
    case 3:
        this->nextArea(decayChasms4);
        decayGrifEnc();
        break;
    case 4:
        this->nextArea(decayChasms5);
        initLimbSplitter();
        combatLoop(window, animate);
        stopComTrack(track10, track7);
        break;
    case 5:
        this->nextArea(decayChasms6);
        break;
    case 6:
        this->nextArea(decayChasms7);
        break;
    case 7:
        this->nextArea(decayChasms8);
        break;
    case 8:
        this->nextArea(decayChasms9);
        initChatterMouth();
        combatLoop(window, animate);
        stopComTrack(track10, track7);
        break;
    case 9:
        this->nextArea(decayChasms10);
        break;
    case 10:
        this->nextArea(decayChasms11);
        break;
    case 11:
        this->nextArea(decayChasms12);
        initBurrower();
        combatLoop(window, animate);
        stopComTrack(track10, track7);
        break;
    case 12:
        this->nextArea(decayChasms13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(decayChasms14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(decayChasms15);
        getDecayAreaUnlocked() = 2;
        this->reInitMap(getInitDecayMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Decay Chasms explored. View map to move to a new area.");
        break;
    }
}

void Travel::decayOcean(sf::RenderWindow& window, Animation& animate)
{
    //Uninitialize && Reinitialize castleDepth Event
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Decay Ocean");
        this->nextArea(decayOcean1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(decayOcean2);
        break;
    case 2:
        this->nextArea(decayOcean3);
        break;
    case 3:
        this->nextArea(decayOcean4);
        break;
    case 4:
        this->nextArea(decayOcean5);
        break;
    case 5:
        this->nextArea(decayOcean6);
        break;
    case 6:
        this->nextArea(decayOcean7);
        break;
    case 7:
        this->nextArea(decayOcean8);
        initTendrilAlpha();
        combatLoop(window, animate);
        stopComTrack(track10, track7);
        break;
    case 8:
        this->nextArea(decayOcean9);
        break;
    case 9:
        this->nextArea(decayOcean10);
        break;
    case 10:
        this->nextArea(decayOcean11);
        break;
    case 11:
        this->nextArea(decayOcean12);
        break;
    case 12:
        this->nextArea(decayOcean13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(decayOcean14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(decayOcean15);
        getDecayAreaUnlocked() = 3;
        this->reInitMap(getInitDecayMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Decay Ocean explored. View map to move to a new area.");
        break;
    }
}

void Travel::decayForest(sf::RenderWindow& window, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Decay Ocean");
        this->nextArea(decayForest1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(decayForest2);
        break;
    case 2:
        this->nextArea(decayForest3);
        break;
    case 3:
        this->nextArea(decayForest4);
        break;
    case 4:
        this->nextArea(decayForest5);
        break;
    case 5:
        this->nextArea(decayForest6);
        break;
    case 6:
        this->nextArea(decayForest7);
        break;
    case 7:
        this->nextArea(decayForest8);
        break;
    case 8:
        this->nextArea(decayForest9);
        break;
    case 9:
        this->nextArea(decayForest10);
        break;
    case 10:
        this->nextArea(decayForest11);
        decaySpadeEncPoison();
        if (getSpadeEnced()) {
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            initSpade();
            combatLoop(window, animate);
            stopComTrack(track4, track7);
        }
        if (getCombatEnd() && getSpadeEnced()) {
            getSpadeCounter() = -1;
            spriteText[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        }
        break;
    case 11:
        this->nextArea(decayForest12);
        break;
    case 12:
        this->nextArea(decayForest13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(decayForest14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(decayForest15);
        getDecayAreaUnlocked() = 4;
        this->reInitMap(getInitDecayMapTexture());
        //Remove Text
        getComTextRemoved() = false;
        text.setString("Decay Forest explored. View map to move to a new area.");
        break;
    }
}

void Travel::decayGiants(sf::RenderWindow& window, Animation& animate)
{
    switch (this->frame) {
    case 0:
        this->newArea(animate);
        locationText.setString("Decay Ocean");
        this->nextArea(decayGiants1);
        break;
    case 1:
        getStartFrame() = false;
        this->nextArea(decayGiants2);
        break;
    case 2:
        this->nextArea(decayGiants3);
        break;
    case 3:
        this->nextArea(decayGiants4);
        break;
    case 4:
        this->nextArea(decayGiants5);
        break;
    case 5:
        this->nextArea(decayGiants6);
        initReclus();
        combatLoop(window, animate);
        stopComTrack(track10, track7);
        break;
    case 6:
        this->nextArea(decayGiants7);
        break;
    case 7:
        this->nextArea(decayGiants8);
        break;
    case 8:
        this->nextArea(decayGiants9);
        break;
    case 9:
        this->nextArea(decayGiants10);
        break;
    case 10:
        this->nextArea(decayGiants11);
        break;
    case 11:
        this->nextArea(decayGiants12);
        break;
    case 12:
        this->nextArea(decayGiants13);
        break;
    case 13:
        getEndFrame() = false;
        this->nextArea(decayGiants14);
        break;
    case 14:
        getEndFrame() = true;
        this->nextArea(decayGiants15);
        rotBeastEnc();
        if (getRotBeastEnced()) {
            initRotBeast();
            combatLoop(window, animate);
            if (!getPlayerDead() && getCombatEnd()) {
                rotBeastDeathEnding();
            }
            else if (getPlayerDead()) {
                getCombatEnd() = true;
                playerDeathEnding();
            }
        }
        break;
    }
}