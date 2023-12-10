#include "Assets.h"

//Constructors & Destructors
Assets::Assets()
{
    this->thomUnlocked = false;
    this->dialogueCounter = 0;
    this->combatCounter = 0;
    this->playerCounter = -1;
    this->zinCounter = -1;
    this->thomCounter = -1;
    this->hostileCounter = -1;
    this->mapCounter = -1;
    this->tipBoxCounter = -1;
    this->showAnsBoxesCounter = -1;

    //Sprite Bool
    this->initialDrawIn = false;
    this->initCastleMapTexture = false;
    this->initForestMapTexture = false;
    this->initDecayMapTexture = false;
    this->initMap = false;
    this->initStats = false;
    this->initInventory = false;
    this->plusboxes = false;

    //Menu Control Flow
    this->playerStatsInit = false;
    this->zinStatsInit = false;
    this->bootClicked = false;
    this->introFinished = false;
    this->settingsShown = false;

    //Map Button Control Flow
    this->areaUnlocked = 0;
    this->forestAreaUnlocked = 1;
    this->castleAreaUnlocked = 1;
    this->decayAreaUnlocked = 1;

    this->startFrame = true;
    this->endFrame = false;

    //Movable
    this->movable = false;
    this->movableStatsBox = false;

    //Rect Coordinates
    this->rectMapX = 25;
    this->rectMapY = 50;
    this->rectStatsBoxX = 1470;
    this->rectStatsBoxY = 10;
    this->rectInventoryBoxX = 1700;
    this->rectInventoryBoxY = 10;
        
    //Initialize Combat Assets
    this->combatAssets = false;
    this->eventAssets = false;
    this->bonfireAssets = false;
    this->playerTurnAssets = false;
    this->zinTurnAssets = false;
    this->thomTurnAssets = false;

    //Combat Move Unlocks
    this->combatPlayerMoves = 0;
    this->combatZinMoves = 0;
    this->combatThomMoves = 1;

    //Music
    this->trackPlayed = false;
    this->ambPlayed = false;

    //Strings
    this->playerName = "player";

    //ToolTip Strings
    this->tipStrength = "STRENGTH:\nMeasures the players raw power.\n\nIncreases all attack moves damage.";
    this->tipFortitude = "FORTITUDE:\nMeasures the players survivability against decay.\n\nHigher fortitude makes the player more \nresistant to the decay.";
    this->tipVitality = "VITALITY:\nMeasures the players health.\n\nHigh vitality allows the player to take a beating\nin combat.";

    this->tipResolve = "RESOLVE:\nMeasures Zin's spells raw power.\n\nIncreases the damage of her lightning \nspells specifically.";
    this->tipPatience = "PATIENCE:\nMeasures Zin's healing capabilities.\n\nHigh patience makes her heal \nsignificantly more.";
    this->tipResilience = "RESILIENCE:\nMeasures Zin's health.\n\nHigh resilience allows Zin to take more \nhits and survive.";

    this->tipSlash = "SLASH:\nThe players basic attack for inflicting damage...";
    this->tipGuard = "GUARD:\nUses the players turn to protect Zin from \nALL damage...";
    this->tipDecay = "DECAYED BLADE:\nThe player slashes his own skin open to use the \ndecay in his blood as a weapon...\n\nInflicts extra damage due to decayed blood...";
    this->tipHefty = "HEFTY BLOW:\nThe player utilizes his weapon to cause as much\ndamage as physically possible to the\nhostile...\n\nRequires a one turn cooldown after use.";
    this->tipSynergy = "DECAYING SYNERGY:\nThe player turns his decay into a physical\nmaterial, using it to shield Zin\nand inflict damage on the enemy...\n\nGives Zin defense and attacks for decay DMG.";
    this->tipIronWall = "IRON WALL:\nThe player uses all of his strength to defend the\nfellow members of his party.\n\nEntire party gains a specific amount of BLK.";

    this->tipSmite = "SMITE:\nZin's basic attack, inflicts damage on the \nopponent...";
    this->tipMend = "MEND:\nHeals the player and Zin...";
    this->tipVengeance = "VENGEANCE:\nUse Zin's rage and sorrow to turn the players\nblood into sharpened blades that hurdle\ntowards the enemy...\n\nInflicts damage equal to the players current \nlost health...";
    this->tipBlaze = "HELLISH BLAZE:\nZin casts a horrifying blaze of fire,\nengulfing the enemy in a pit of flames...\n\nRequires two turns to cooldown after use.";
    this->tipHeal = "FOCUSED HEAL:\nZin concentrates a healing spell around\nyou, mending you greatly.";
    this->tipFlames = "CRIMSON FLAMES:\nZin absorbs both of your rage and uses\nit to engulf you both in flames...\n\nGreatly increases attack DMG for\nthe rest of combat.";

    this->tipBarrier = "BARRIER:\nThom casts a barrier made of Decay,\nblocking some of the players damage.";
    this->tipEnrage = "ENRAGE:\nThom enters a state of pure rage.\nThis lasts for three turns, boosting\nall party damage.\n\nThom is unable to use any other moves during\nhis state of rage.";

    //Load game assets
    this->loadSprites();
    this->loadSounds();
    this->loadMapImages(); //(DEBUG)
}

Assets::~Assets()
{

}

//Load Functions
void Assets::loadSprites()
{
    //Game Resource Textures
    windowIcon.loadFromFile("Assets/Game_Resources/shieldicon.jpeg");
    buttonTexture.loadFromFile("Assets/Game_Resources/buttonsolid.png");
    arrowTextureRight.loadFromFile("Assets/Game_Resources/arrowright.png");
    arrowTextureLeft.loadFromFile("Assets/Game_Resources/arrowleft.png");
}

void Assets::loadSounds()
{
    //Load Sfx
    bufferClick.loadFromFile("Assets/Sounds/click.wav");
    bonfire.openFromFile("Assets/Sounds/campfire.wav");
    forestAmbience.openFromFile("Assets/Sounds/forestAmbience.wav");
    bufferDecay.loadFromFile("Assets/Sounds/decayblade.wav");
    bufferVengeance.loadFromFile("Assets/Sounds/vengeance.wav");
    bufferSlash.loadFromFile("Assets/Sounds/slash.wav");
    bufferSmite.loadFromFile("Assets/Sounds/smite.wav");
    bufferMend.loadFromFile("Assets/Sounds/mend.wav");
    bufferGuarded.loadFromFile("Assets/Sounds/guarded.wav");
    bufferGuard.loadFromFile("Assets/Sounds/guard.wav");
    bufferSoundHover.loadFromFile("Assets/Sounds/hoversound.wav");
    bufferWalk.loadFromFile("Assets/Sounds/moveRoom.wav");
    bufferCom.loadFromFile("Assets/Sounds/Boss hit 1.wav");
    buffer.loadFromFile("Assets/Sounds/Text 1.wav");
    blipbuffer.loadFromFile("Assets/Sounds/blipSelect.wav");
    statBuffer.loadFromFile("Assets/Sounds/statsup.wav");
    blipmenubuffer.loadFromFile("Assets/Sounds/menuclick.wav");
    bufferAngry.loadFromFile("Assets/Sounds/angry.wav");
    bufferCombatStart.loadFromFile("Assets/Sounds/combatstart.wav");
    bufferPlayerGuarded.loadFromFile("Assets/Sounds/playerguarded.wav");
    bufferThomGuard.loadFromFile("Assets/Sounds/thomatkguard.wav");
    bufferEnraged.loadFromFile("Assets/Sounds/enraged.wav");
    bufferHefty.loadFromFile("Assets/Sounds/heftyBlow.wav");
    bufferSynergy.loadFromFile("Assets/Sounds/decaySynergy.wav");
    bufferBlaze.loadFromFile("Assets/Sounds/hellBlaze.wav");
    bufferFlames.loadFromFile("Assets/Sounds/crimsonFlames.wav");
    bufferIronWall.loadFromFile("Assets/Sounds/ironWall.wav");

    //Load Music
    track1.openFromFile("Assets/Music/track2.wav");
    track2.openFromFile("Assets/Music/ANocturneForAll.wav");
    track3.openFromFile("Assets/Music/Communication.wav");
    track4.openFromFile("Assets/Music/Helplessness.wav");
    track5.openFromFile("Assets/Music/incision.wav");
    track6.openFromFile("Assets/Music/grandRiver.wav");
    track7.openFromFile("Assets/Music/Tugrul.wav");
    track8.openFromFile("Assets/Music/StoneBeacon.wav");
    track9.openFromFile("Assets/Music/incarnadine.wav");
    track10.openFromFile("Assets/Music/Accolade.wav");
}

void Assets::loadMapImages()
{
    //Forest Wallpapers
    forestEntrance1.loadFromFile("Assets/Wallpapers/Forest/forest1.jpeg");
    forestEntrance2.loadFromFile("Assets/Wallpapers/Forest/forest2.jpeg");
    forestEntrance3.loadFromFile("Assets/Wallpapers/Forest/forest3.jpeg");
    forestEntrance4.loadFromFile("Assets/Wallpapers/Forest/forest4.jpeg");
    forestEntrance5.loadFromFile("Assets/Wallpapers/Forest/forest5.jpeg");
    forestEntrance6.loadFromFile("Assets/Wallpapers/Forest/forest6.jpeg");
    forestEntrance7.loadFromFile("Assets/Wallpapers/Forest/forest7.jpeg");
    forestEntrance8.loadFromFile("Assets/Wallpapers/Forest/forest8.jpeg");
    forestEntrance9.loadFromFile("Assets/Wallpapers/Forest/forest9.jpeg");
    forestEntrance10.loadFromFile("Assets/Wallpapers/Forest/forest10.jpeg");
    forestEntrance11.loadFromFile("Assets/Wallpapers/Forest/forest11.jpeg");
    forestEntrance12.loadFromFile("Assets/Wallpapers/Forest/forest12.jpeg");
    forestEntrance13.loadFromFile("Assets/Wallpapers/Forest/forest13.jpeg");
    forestEntrance14.loadFromFile("Assets/Wallpapers/Forest/forest14.jpeg");
    forestEntrance15.loadFromFile("Assets/Wallpapers/Forest/forest15.jpeg");

    forestDepths1.loadFromFile("Assets/Wallpapers/Forest/forestdepths1.jpeg");
    forestDepths2.loadFromFile("Assets/Wallpapers/Forest/forestdepths2.jpeg");
    forestDepths3.loadFromFile("Assets/Wallpapers/Forest/forestdepths3.jpeg");
    forestDepths4.loadFromFile("Assets/Wallpapers/Forest/forestdepths4.jpeg");
    forestDepths5.loadFromFile("Assets/Wallpapers/Forest/forestdepths5.jpeg");
    forestDepths6.loadFromFile("Assets/Wallpapers/Forest/forestdepths6.jpeg");
    forestDepths7.loadFromFile("Assets/Wallpapers/Forest/forestdepths7.jpeg");
    forestDepths8.loadFromFile("Assets/Wallpapers/Forest/forestdepths8.jpeg");
    forestDepths9.loadFromFile("Assets/Wallpapers/Forest/forestdepths9.jpeg");
    forestDepths10.loadFromFile("Assets/Wallpapers/Forest/forestdepths10.jpeg");
    forestDepths11.loadFromFile("Assets/Wallpapers/Forest/forestdepths11.jpeg");
    forestDepths12.loadFromFile("Assets/Wallpapers/Forest/forestdepths12.jpeg");
    forestDepths13.loadFromFile("Assets/Wallpapers/Forest/forestdepths13.jpeg");
    forestDepths14.loadFromFile("Assets/Wallpapers/Forest/forestdepths14.jpeg");
    forestDepths15.loadFromFile("Assets/Wallpapers/Forest/forestdepths15.jpeg");

    forestAbyssal1.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods1.jpeg");
    forestAbyssal2.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods2.jpeg");
    forestAbyssal3.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods3.jpeg");
    forestAbyssal4.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods4.jpeg");
    forestAbyssal5.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods5.jpeg");
    forestAbyssal6.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods6.jpeg");
    forestAbyssal7.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods7.jpeg");
    forestAbyssal8.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods8.jpeg");
    forestAbyssal9.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods9.jpeg");
    forestAbyssal10.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods10.jpeg");
    forestAbyssal11.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods11.jpeg");
    forestAbyssal12.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods12.jpeg");
    forestAbyssal13.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods13.jpeg");
    forestAbyssal14.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods14.jpeg");
    forestAbyssal15.loadFromFile("Assets/Wallpapers/Forest/abyssalwoods15.jpeg");

    forestAbyssalDepth1.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths1.jpeg");
    forestAbyssalDepth2.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths2.jpeg");
    forestAbyssalDepth3.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths3.jpeg");
    forestAbyssalDepth4.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths4.jpeg");
    forestAbyssalDepth5.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths5.jpeg");
    forestAbyssalDepth6.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths6.jpeg");
    forestAbyssalDepth7.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths7.jpeg");
    forestAbyssalDepth8.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths8.jpeg");
    forestAbyssalDepth9.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths9.jpeg");
    forestAbyssalDepth10.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths10.jpeg");
    forestAbyssalDepth11.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths11.jpeg");
    forestAbyssalDepth12.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths12.jpeg");
    forestAbyssalDepth13.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths13.jpeg");
    forestAbyssalDepth14.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths14.jpeg");
    forestAbyssalDepth15.loadFromFile("Assets/Wallpapers/Forest/abyssaldepths15.jpeg");

    //Castle Wallpapers
    castleHalls1.loadFromFile("Assets/Wallpapers/Castle/castle1.jpeg");
    castleHalls2.loadFromFile("Assets/Wallpapers/Castle/castle2.jpeg");
    castleHalls3.loadFromFile("Assets/Wallpapers/Castle/castle3.jpeg");
    castleHalls4.loadFromFile("Assets/Wallpapers/Castle/castle4.jpeg");
    castleHalls5.loadFromFile("Assets/Wallpapers/Castle/castle5.jpeg");
    castleHalls6.loadFromFile("Assets/Wallpapers/Castle/castle6.jpeg");
    castleHalls7.loadFromFile("Assets/Wallpapers/Castle/castle7.jpeg");
    castleHalls8.loadFromFile("Assets/Wallpapers/Castle/castle8.jpeg");
    castleHalls9.loadFromFile("Assets/Wallpapers/Castle/castle9.jpeg");
    castleHalls10.loadFromFile("Assets/Wallpapers/Castle/castle10.jpeg");
    castleHalls11.loadFromFile("Assets/Wallpapers/Castle/castle11.jpeg");
    castleHalls12.loadFromFile("Assets/Wallpapers/Castle/castle12.jpeg");
    castleHalls13.loadFromFile("Assets/Wallpapers/Castle/castle13.jpeg");
    castleHalls14.loadFromFile("Assets/Wallpapers/Castle/castle14.jpeg");
    castleHalls15.loadFromFile("Assets/Wallpapers/Castle/castle15.jpeg");

    castleDepths1.loadFromFile("Assets/Wallpapers/Castle/castleDepths1.jpeg");
    castleDepths2.loadFromFile("Assets/Wallpapers/Castle/castleDepths2.jpeg");
    castleDepths3.loadFromFile("Assets/Wallpapers/Castle/castleDepths3.jpeg");
    castleDepths4.loadFromFile("Assets/Wallpapers/Castle/castleDepths4.jpeg");
    castleDepths5.loadFromFile("Assets/Wallpapers/Castle/castleDepths5.jpeg");
    castleDepths6.loadFromFile("Assets/Wallpapers/Castle/castleDepths6.jpeg");
    castleDepths7.loadFromFile("Assets/Wallpapers/Castle/castleDepths7.jpeg");
    castleDepths8.loadFromFile("Assets/Wallpapers/Castle/castleDepths8.jpeg");
    castleDepths9.loadFromFile("Assets/Wallpapers/Castle/castleDepths9.jpeg");
    castleDepths10.loadFromFile("Assets/Wallpapers/Castle/castleDepths10.jpeg");
    castleDepths11.loadFromFile("Assets/Wallpapers/Castle/castleDepths11.jpeg");
    castleDepths12.loadFromFile("Assets/Wallpapers/Castle/castleDepths12.jpeg");
    castleDepths13.loadFromFile("Assets/Wallpapers/Castle/castleDepths13.jpeg");
    castleDepths14.loadFromFile("Assets/Wallpapers/Castle/castleDepths14.jpeg");
    castleDepths15.loadFromFile("Assets/Wallpapers/Castle/castleDepths15.jpeg");

    castleChambers1.loadFromFile("Assets/Wallpapers/Castle/castlechambers1.jpeg");
    castleChambers2.loadFromFile("Assets/Wallpapers/Castle/castlechambers2.jpeg");
    castleChambers3.loadFromFile("Assets/Wallpapers/Castle/castlechambers3.jpeg");
    castleChambers4.loadFromFile("Assets/Wallpapers/Castle/castlechambers4.jpeg");
    castleChambers5.loadFromFile("Assets/Wallpapers/Castle/castlechambers5.jpeg");
    castleChambers6.loadFromFile("Assets/Wallpapers/Castle/castlechambers6.jpeg");
    castleChambers7.loadFromFile("Assets/Wallpapers/Castle/castlechambers7.jpeg");
    castleChambers8.loadFromFile("Assets/Wallpapers/Castle/castlechambers8.jpeg");
    castleChambers9.loadFromFile("Assets/Wallpapers/Castle/castlechambers9.jpeg");
    castleChambers10.loadFromFile("Assets/Wallpapers/Castle/castlechambers10.jpeg");
    castleChambers11.loadFromFile("Assets/Wallpapers/Castle/castlechambers11.jpeg");
    castleChambers12.loadFromFile("Assets/Wallpapers/Castle/castlechambers12.jpeg");
    castleChambers13.loadFromFile("Assets/Wallpapers/Castle/castlechambers13.jpeg");
    castleChambers14.loadFromFile("Assets/Wallpapers/Castle/castlechambers14.jpeg");
    castleChambers15.loadFromFile("Assets/Wallpapers/Castle/castlechambers15.jpeg");

    castleLab1.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth1.jpeg");
    castleLab2.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth2.jpeg");
    castleLab3.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth3.jpeg");
    castleLab4.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth4.jpeg");
    castleLab5.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth5.jpeg");
    castleLab6.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth6.jpeg");
    castleLab7.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth7.jpeg");
    castleLab8.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth8.jpeg");
    castleLab9.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth9.jpeg");
    castleLab10.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth10.jpeg");
    castleLab11.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth11.jpeg");
    castleLab12.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth12.jpeg");
    castleLab13.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth13.jpeg");
    castleLab14.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth14.jpeg");
    castleLab15.loadFromFile("Assets/Wallpapers/Castle/castlelabyrinth15.jpeg");

    //Decay Wallpapers
    decayChasms1.loadFromFile("Assets/Wallpapers/Decay/crimson1.jpeg");
    decayChasms2.loadFromFile("Assets/Wallpapers/Decay/crimson2.jpeg");
    decayChasms3.loadFromFile("Assets/Wallpapers/Decay/crimson3.jpeg");
    decayChasms4.loadFromFile("Assets/Wallpapers/Decay/crimson4.jpeg");
    decayChasms5.loadFromFile("Assets/Wallpapers/Decay/crimson5.jpeg");
    decayChasms6.loadFromFile("Assets/Wallpapers/Decay/crimson6.jpeg");
    decayChasms7.loadFromFile("Assets/Wallpapers/Decay/crimson7.jpeg");
    decayChasms8.loadFromFile("Assets/Wallpapers/Decay/crimson8.jpeg");
    decayChasms9.loadFromFile("Assets/Wallpapers/Decay/crimson9.jpeg");
    decayChasms10.loadFromFile("Assets/Wallpapers/Decay/crimson10.jpeg");
    decayChasms11.loadFromFile("Assets/Wallpapers/Decay/crimson11.jpeg");
    decayChasms12.loadFromFile("Assets/Wallpapers/Decay/crimson12.jpeg");
    decayChasms13.loadFromFile("Assets/Wallpapers/Decay/crimson13.jpeg");
    decayChasms14.loadFromFile("Assets/Wallpapers/Decay/crimson14.jpeg");
    decayChasms15.loadFromFile("Assets/Wallpapers/Decay/crimson15.jpeg");

    decayOcean1.loadFromFile("Assets/Wallpapers/Decay/decayocean1.jpeg");
    decayOcean2.loadFromFile("Assets/Wallpapers/Decay/decayocean2.jpeg");
    decayOcean3.loadFromFile("Assets/Wallpapers/Decay/decayocean3.jpeg");
    decayOcean4.loadFromFile("Assets/Wallpapers/Decay/decayocean4.jpeg");
    decayOcean5.loadFromFile("Assets/Wallpapers/Decay/decayocean5.jpeg");
    decayOcean6.loadFromFile("Assets/Wallpapers/Decay/decayocean6.jpeg");
    decayOcean7.loadFromFile("Assets/Wallpapers/Decay/decayocean7.jpeg");
    decayOcean8.loadFromFile("Assets/Wallpapers/Decay/decayocean8.jpeg");
    decayOcean9.loadFromFile("Assets/Wallpapers/Decay/decayocean9.jpeg");
    decayOcean10.loadFromFile("Assets/Wallpapers/Decay/decayocean10.jpeg");
    decayOcean11.loadFromFile("Assets/Wallpapers/Decay/decayocean11.jpeg");
    decayOcean12.loadFromFile("Assets/Wallpapers/Decay/decayocean12.jpeg");
    decayOcean13.loadFromFile("Assets/Wallpapers/Decay/decayocean13.jpeg");
    decayOcean14.loadFromFile("Assets/Wallpapers/Decay/decayocean14.jpeg");
    decayOcean15.loadFromFile("Assets/Wallpapers/Decay/decayocean15.jpeg");

    decayForest1.loadFromFile("Assets/Wallpapers/Decay/crimsonforest1.jpeg");
    decayForest2.loadFromFile("Assets/Wallpapers/Decay/crimsonforest2.jpeg");
    decayForest3.loadFromFile("Assets/Wallpapers/Decay/crimsonforest3.jpeg");
    decayForest4.loadFromFile("Assets/Wallpapers/Decay/crimsonforest4.jpeg");
    decayForest5.loadFromFile("Assets/Wallpapers/Decay/crimsonforest5.jpeg");
    decayForest6.loadFromFile("Assets/Wallpapers/Decay/crimsonforest6.jpeg");
    decayForest7.loadFromFile("Assets/Wallpapers/Decay/crimsonforest7.jpeg");
    decayForest8.loadFromFile("Assets/Wallpapers/Decay/crimsonforest8.jpeg");
    decayForest9.loadFromFile("Assets/Wallpapers/Decay/crimsonforest9.jpeg");
    decayForest10.loadFromFile("Assets/Wallpapers/Decay/crimsonforest10.jpeg");
    decayForest11.loadFromFile("Assets/Wallpapers/Decay/crimsonforest11.jpeg");
    decayForest12.loadFromFile("Assets/Wallpapers/Decay/crimsonforest12.jpeg");
    decayForest13.loadFromFile("Assets/Wallpapers/Decay/crimsonforest13.jpeg");
    decayForest14.loadFromFile("Assets/Wallpapers/Decay/crimsonforest14.jpeg");
    decayForest15.loadFromFile("Assets/Wallpapers/Decay/crimsonforest15.jpeg");

    decayGiants1.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants1.jpeg");
    decayGiants2.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants2.jpeg");
    decayGiants3.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants3.jpeg");
    decayGiants4.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants4.jpeg");
    decayGiants5.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants5.jpeg");
    decayGiants6.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants6.jpeg");
    decayGiants7.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants7.jpeg");
    decayGiants8.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants8.jpeg");
    decayGiants9.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants9.jpeg");
    decayGiants10.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants10.jpeg");
    decayGiants11.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants11.jpeg");
    decayGiants12.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants12.jpeg");
    decayGiants13.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants13.jpeg");
    decayGiants14.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants14.jpeg");
    decayGiants15.loadFromFile("Assets/Wallpapers/Decay/crimsonGiants15.jpeg");
}

//Draw Fuctions
void Assets::drawMainWindow()
{
    //Draw Menu Box
    rect.setPosition(0.0f, 825.0f);
    rect.setSize(sf::Vector2f(1920.0f, 825.0f));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1.0f);
    mapBorder.setPosition(440.0f, -200.0f);
    mapBorder.setSize(sf::Vector2f(1024.0f, 1024.0f));
    mapBorder.setOutlineColor(sf::Color::White);
    mapBorder.setOutlineThickness(1.0f);
    mapBorder.setFillColor(sf::Color::Transparent);
    if (combatAssets == false && bonfireAssets == false) {
        //Draw Rect Element Similiarities
        for (int i = 0; i < rectElements.size(); i++) {
            rectElements[i].setSize(sf::Vector2f(100.0f, 25.0f));
            rectElements[i].setOutlineColor(sf::Color::White);
            rectElements[i].setOutlineThickness(1.0f);
        }
        //Draw Map Button position
        rectElements[2].setPosition(1.0f, 795.0f);
        //Draw Stats Button position
        rectElements[0].setPosition(105.0f, 795.0f);
        //Draw Inventory Button position
        rectElements[1].setPosition(209.0f, 795.0f);
        //Draw Button
        if (this->endFrame) {
            spriteElements[0].setPosition(10000.0f, 10000.0f);
        }
        else {
            spriteElements[0].setPosition(1400.0f, 765.0f);
        }
        spriteElements[0].setTexture(arrowTextureRight);
        spriteElements[0].setScale(0.04f, 0.04f);
        //Draw Back Button
        if (this->startFrame == true) {
            spriteElements[1].setPosition(10000.0f, 10000.0f);
        }
        else {
            spriteElements[1].setPosition(445.0f, 765.0f);
        }
        buttonBackTexture.loadFromFile("Assets/Game_Resources/buttonsolid.png");
        spriteElements[1].setTexture(arrowTextureLeft);
        spriteElements[1].setScale(0.04f, 0.04f);
        if (eventAssets == true) {
            //Make assets hidden during Events
            rectElements[2].setPosition(1.0f, 10000.0f);
            rectElements[1].setPosition(209.0f, 10000.0f);
            rectElements[0].setPosition(105.0f, 10000.0f);
            spriteElements[0].setPosition(1400.0f, 10000.0f);
            spriteElements[1].setPosition(445.0f, 10000.0f);
        }
    }
    else if (combatAssets == true) {
        //Make assets hidden during combat
        rectElements[2].setPosition(1.0f, 10000.0f);
        rectElements[1].setPosition(209.0f, 10000.0f);
        rectElements[0].setPosition(105.0f, 10000.0f);
        spriteElements[0].setPosition(1400.0f, 10000.0f);
        spriteElements[1].setPosition(445.0f, 10000.0f);
    }
    else if (bonfireAssets == true) {
        for (int i = 0; i < rectElements.size(); i++) {
            rectElements[i].setSize(sf::Vector2f(100.0f, 25.0f));
            rectElements[i].setOutlineColor(sf::Color::White);
            rectElements[i].setOutlineThickness(1.0f);
        }
        //Draw Map Button
        rectElements[2].setPosition(1.0f, 795.0f);
        //Draw Stats Button
        rectElements[0].setPosition(105.0f, 795.0f);
        //Draw Inventory Button
        rectElements[1].setPosition(209.0f, 795.0f);
        //Hide Back and Forward Buttons
        spriteElements[0].setPosition(1400.0f, 10000.0f);
        spriteElements[1].setPosition(445.0f, 10000.0f);
    }
}

void Assets::drawText()
{
    //Draw Font
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    //Draw Font and Output Text
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color(sf::Color::White));
    text.setPosition(0.0f, 825.0f);
    //Draw Input Text
    playerText.setFont(font);
    playerText.setFillColor(sf::Color(sf::Color::White));
    playerText.setPosition(0.0f, 970.0f);
    //Draw Location Text
    locationText.setFont(font);
    locationText.setCharacterSize(18);
    locationText.setFillColor(sf::Color(sf::Color::White));
    locationText.setPosition(275.0f, 10.0f);
    //Menu Bar Text
    for (int i = 0; i < textElements.size(); i++) {
        textElements[i].setFont(font);
        textElements[i].setCharacterSize(16);
    }
    textElements[2].setPosition(1.0f, 797.0f);
    textElements[2].setString("Map");
    textElements[0].setPosition(105.0f, 797.0f);
    textElements[0].setString("Stats");
    textElements[1].setPosition(210.0f, 797.0f);
    textElements[1].setString("Inventory");
}

void Assets::drawMainMenu()
{
    //Set all screen elements attributes
    for (int i = 0; i < menuScreenElements.size(); i++) {
        menuScreenElementsText[i].setFont(font);
        menuScreenElementsText[i].setCharacterSize(18);
        menuScreenElements[i].setSize(sf::Vector2f(150.0f, 25.0f));
        menuScreenElements[i].setOutlineColor(sf::Color::White);
        menuScreenElements[i].setOutlineThickness(1.0f);
    }

    //Set Text Elements Names
    menuScreenElementsText[0].setString("Boot");
    menuScreenElementsText[1].setString("Load");
    menuScreenElementsText[2].setString("Quit");
    menuScreenElementsText[3].setString("Play Intro");
    menuScreenElementsText[4].setString("Skip Intro");

    menuScreenElementsText[5].setString("Save Game");

    if (!this->introFinished) {
        font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
        //Draw Main Menu
        menuScreen.setSize(sf::Vector2f(1920.0f, 1080.0f));
        menuScreen.setFillColor(sf::Color::Black);

        //Choose which elements are currently visible on the screen for choosing whether to skip intro or not
        if (this->bootClicked == false) {
            menuScreenElements[1].setPosition(10000.0f, 10000.0f);
            menuScreenElements[3].setPosition(10000.0f, 10000.0f);
            menuScreenElements[4].setPosition(10000.0f, 10000.0f);
            menuScreenElements[5].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[1].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[3].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[4].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[5].setPosition(10000.0f, 10000.0f);

            menuScreenElements[0].setPosition(10.0f, 100.0f);
            menuScreenElements[2].setPosition(10.0f, 125.0f);
            menuScreenElementsText[0].setPosition(10.0f, 100.0f);
            menuScreenElementsText[2].setPosition(10.0f, 125.0f);
        }
        else if (this->bootClicked == true) {
            //Hide menu buttons
            menuScreenElements[0].setPosition(10.0f, 10000.0f);
            menuScreenElements[1].setPosition(10.0f, 10000.0f);
            menuScreenElements[2].setPosition(10.0f, 10000.0f);
            menuScreenElementsText[0].setPosition(10.0f, 10000.0f);
            menuScreenElementsText[1].setPosition(10.0f, 10000.0f);
            menuScreenElementsText[2].setPosition(10.0f, 10000.0f);
            //Show skip or no skip intro
            menuScreenElements[3].setPosition(10.0f, 100.0f);
            menuScreenElements[4].setPosition(10.0f, 125.0f);
            menuScreenElementsText[3].setPosition(10.0f, 100.0f);
            menuScreenElementsText[4].setPosition(10.0f, 125.0f);
        }
    }
    else if (this->introFinished) {
        if (this->settingsShown) {
            //Hide intro options
            menuScreenElements[3].setPosition(10000.0f, 10000.0f);
            menuScreenElements[4].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[3].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[4].setPosition(10000.0f, 10000.0f);
            //Show setting options
            menuScreenElements[1].setPosition(10.0f, 125.0f);
            menuScreenElements[2].setPosition(10.0f, 150.0f);
            menuScreenElements[5].setPosition(10.0f, 175.0f);
            menuScreenElementsText[1].setPosition(10.0f, 125.0f);
            menuScreenElementsText[2].setPosition(10.0f, 150.0f);
            menuScreenElementsText[5].setPosition(10.0f, 175.0f);
        }
        else if (!this->settingsShown) {
            //Hide all elements
            menuScreenElements[1].setPosition(10000.0f, 10000.0f);
            menuScreenElements[2].setPosition(10000.0f, 10000.0f);
            menuScreenElements[5].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[1].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[2].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[5].setPosition(10000.0f, 10000.0f);
        }
    }
}

void Assets::drawDeathAssets()
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");

    //Draw Load and Quit Buttons
    menuScreenElements[1].setPosition(10.0f, 125.0f);
    menuScreenElements[2].setPosition(10.0f, 150.0f);

    menuScreenElements[1].setSize(sf::Vector2f(100.0f, 25.0f));
    menuScreenElements[1].setOutlineColor(sf::Color::White);
    menuScreenElements[1].setOutlineThickness(1.0f);
    menuScreenElements[2].setSize(sf::Vector2f(100.0f, 25.0f));
    menuScreenElements[2].setOutlineColor(sf::Color::White);
    menuScreenElements[2].setOutlineThickness(1.0f);
    //Draw Load and Quit Text
    deathText.setFont(font);
    deathText.setCharacterSize(48);
    deathText.setString("Perished...");
    deathText.setPosition(25.0f, 25.0f);

    menuScreenElementsText[1].setFont(font);
    menuScreenElementsText[1].setCharacterSize(18);
    menuScreenElementsText[1].setString("Load");
    menuScreenElementsText[2].setFont(font);
    menuScreenElementsText[2].setCharacterSize(18);
    menuScreenElementsText[2].setString("Quit");
    menuScreenElementsText[1].setPosition(10.0f, 125.0f);
    menuScreenElementsText[2].setPosition(10.0f, 150.0f);
}

void Assets::drawAnswerBoxes()
{
    switch (this->showAnsBoxesCounter) {
    case -1:
        for (int i = 0; i < answerBox.size(); i++) {
            answerBox[i].setPosition(10000, 10000);
            answerBoxText[i].setPosition(10000, 10000);
        }
        break;
    case 0:
        for (int i = 0; i < answerBox.size(); i++) {
            answerBox[i].setSize(sf::Vector2f(1920.0f,127.5f));
            answerBox[i].setOutlineColor(sf::Color::White);
            answerBox[i].setOutlineThickness(1.0f);
            answerBoxText[i].setFont(font);
            answerBoxText[i].setCharacterSize(16);
        }
        answerBox[0].setPosition(0.0f, 825.0f);
        answerBox[1].setPosition(0.0f, 952.5f);

        answerBoxText[0].setPosition(0.0f, 825.0f);
        answerBoxText[1].setPosition(0.0f, 952.0f);
        break;
    }
}

void Assets::drawTipBox()
{
    tipBox.setFillColor(sf::Color::Black);
    tipBox.setSize(sf::Vector2f(380.0f, 150.0f));
    tipBox.setOutlineColor(sf::Color::White);
    tipBox.setOutlineThickness(1.0f);

    tipBoxText.setFont(font);
    tipBoxText.setCharacterSize(14);

    switch (this->tipBoxCounter) {
    case -1:
        tipBox.setPosition(10000, 10000);
        tipBoxText.setPosition(10000, 10000);
        break;
    case 0:
        tipBox.setPosition(1500, 650);
        tipBoxText.setPosition(1500, 650);
        break;
    }
}

//Stat && Inventory Functions
void Assets::drawStats()
{
    //Main Rect
    rectStatsBox.setFillColor(sf::Color::Black);
    rectStatsBox.setPosition(rectStatsBoxX, rectStatsBoxY);
    rectStatsBox.setSize(sf::Vector2f(200.0f, 600.0f));
    rectStatsBox.setOutlineColor(sf::Color::White);
    rectStatsBox.setOutlineThickness(1.0f);

    //Player Stat Elements Loop
    for (int i = 0; i < playerStatElements.size(); i++) {
        playerStatElements[i].setOutlineColor(sf::Color::White);
        playerStatElements[i].setOutlineThickness(1.0f);
    }
    //Level up plus Box
    playerStatElements[0].setPosition(rectStatsBoxX, rectStatsBoxY + 100);
    playerStatElements[0].setSize(sf::Vector2f(20.0f, 20.0f));
    //Strength plus box
    playerStatElements[1].setPosition(rectStatsBoxX, rectStatsBoxY + 180);
    playerStatElements[1].setSize(sf::Vector2f(20.0f, 20.0f));
    //Fortitude plus box
    playerStatElements[2].setPosition(rectStatsBoxX, rectStatsBoxY + 160);
    playerStatElements[2].setSize(sf::Vector2f(20.0f, 20.0f));
    //Vitality plus box
    playerStatElements[3].setPosition(rectStatsBoxX, rectStatsBoxY + 140);
    playerStatElements[3].setSize(sf::Vector2f(20.0f, 20.0f));
    //Side Menu Player Stats Menu Rect
    playerStatElements[4].setPosition(rectStatsBoxX + 200, rectStatsBoxY);
    playerStatElements[4].setSize(sf::Vector2f(20.0f, 120.0f));
    //Side Menu Zin Stats Menu Rect
    playerStatElements[5].setPosition(rectStatsBoxX + 200, rectStatsBoxY + 120);
    playerStatElements[5].setSize(sf::Vector2f(20.0f, 100.0f));

    //Plus sign text for level up
    for (int i = 0; i < playerTextPlus.size(); i++) {
        playerTextPlus[i].setFont(font);
    }
    playerTextPlus[0].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 94);
    playerTextPlus[0].setString("+");
    playerTextPlus[0].setCharacterSize(24);
    //plus sign text for strength
    playerTextPlus[1].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 174);
    playerTextPlus[1].setString("+");
    playerTextPlus[1].setCharacterSize(24);
    //plus sign text for fortitude
    playerTextPlus[2].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 154);
    playerTextPlus[2].setString("+");
    playerTextPlus[2].setCharacterSize(24);
    //plus sign text for vitality
    playerTextPlus[3].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 133);
    playerTextPlus[3].setString("+");
    playerTextPlus[3].setCharacterSize(24);
    //Side Menu Player Stats Menu Rect Text
    playerTextPlus[4].setCharacterSize(16);
    playerTextPlus[4].setPosition(rectStatsBoxX + 205, rectStatsBoxY);
    playerTextPlus[4].setString("P\nL\nA\nY\nE\nR");
    //Side Menu Zin Stats Menu Rect Text
    playerTextPlus[5].setCharacterSize(16);
    playerTextPlus[5].setPosition(rectStatsBoxX + 205, rectStatsBoxY + 120);
    playerTextPlus[5].setString("\nZ\nI\nN");

    //Player Text Elements Loop
    for (int i = 0; i < playerTextElements.size(); i++) {
        playerTextElements[i].setFont(font);
        playerTextElements[i].setFillColor(sf::Color::White);
    }
    //Title next to level box
    playerTextElements[0].setCharacterSize(14);
    playerTextElements[0].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 100);
    //Title next to strength box
    playerTextElements[1].setFont(font);
    playerTextElements[1].setCharacterSize(14);
    playerTextElements[1].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 180);
    //Title next to fortitude box
    playerTextElements[2].setFont(font);
    playerTextElements[2].setCharacterSize(14);
    playerTextElements[2].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 160);
    //Title next to vitality box
    playerTextElements[3].setFont(font);
    playerTextElements[3].setCharacterSize(14);
    playerTextElements[3].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 140);
    //Hp text
    playerTextElements[4].setCharacterSize(16);
    playerTextElements[4].setPosition(rectStatsBoxX, rectStatsBoxY);
}

void Assets::drawZinStats()
{
    //Zin Stat Elements Loop
    for (int i = 0; i < zinStatElements.size(); i++) {
        zinStatElements[i].setOutlineColor(sf::Color::White);
        zinStatElements[i].setOutlineThickness(1.0f);
    }
    //Level up plus Box
    zinStatElements[0].setPosition(rectStatsBoxX, rectStatsBoxY + 100);
    zinStatElements[0].setSize(sf::Vector2f(20.0f, 20.0f));
    //Strength plus box
    zinStatElements[1].setPosition(rectStatsBoxX, rectStatsBoxY + 180);
    zinStatElements[1].setSize(sf::Vector2f(20.0f, 20.0f));
    //Fortitude plus box
    zinStatElements[2].setPosition(rectStatsBoxX, rectStatsBoxY + 160);
    zinStatElements[2].setSize(sf::Vector2f(20.0f, 20.0f));
    //Vitality plus box
    zinStatElements[3].setPosition(rectStatsBoxX, rectStatsBoxY + 140);
    zinStatElements[3].setSize(sf::Vector2f(20.0f, 20.0f));
    //Side Menu Zin Stats Menu Rect
    zinStatElements[4].setPosition(rectStatsBoxX + 200, rectStatsBoxY);
    zinStatElements[4].setSize(sf::Vector2f(20.0f, 120.0f));
    //Side Menu Zin Stats Menu Rect
    zinStatElements[5].setPosition(rectStatsBoxX + 200, rectStatsBoxY + 120);
    zinStatElements[5].setSize(sf::Vector2f(20.0f, 100.0f));

    //Plus sign text for level up
    for (int i = 0; i < zinTextPlus.size(); i++) {
        zinTextPlus[i].setFont(font);
    }
    zinTextPlus[0].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 94);
    zinTextPlus[0].setString("+");
    zinTextPlus[0].setCharacterSize(24);
    //plus sign text for resolve
    zinTextPlus[1].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 174);
    zinTextPlus[1].setString("+");
    zinTextPlus[1].setCharacterSize(24);
    //plus sign text for patience
    zinTextPlus[2].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 154);
    zinTextPlus[2].setString("+");
    zinTextPlus[2].setCharacterSize(24);
    //plus sign text for resilience
    zinTextPlus[3].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 133);
    zinTextPlus[3].setString("+");
    zinTextPlus[3].setCharacterSize(24);
    //Side Menu Zin Stats Menu Rect Text
    zinTextPlus[4].setCharacterSize(16);
    zinTextPlus[4].setPosition(rectStatsBoxX + 205, rectStatsBoxY);
    zinTextPlus[4].setString("P\nL\nA\nY\nE\nR");
    //Side Menu Zin Stats Menu Rect Text
    zinTextPlus[5].setCharacterSize(16);
    zinTextPlus[5].setPosition(rectStatsBoxX + 205, rectStatsBoxY + 120);
    zinTextPlus[5].setString("\nZ\nI\nN");

    //Zin Text Elements Loop
    for (int i = 0; i < zinTextElements.size(); i++) {
        zinTextElements[i].setFont(font);
        zinTextElements[i].setFillColor(sf::Color::White);
    }
    //Title next to level box
    zinTextElements[0].setCharacterSize(14);
    zinTextElements[0].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 100);
    //Title next to resolve box
    zinTextElements[1].setFont(font);
    zinTextElements[1].setCharacterSize(14);
    zinTextElements[1].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 180);
    //Title next to patience box
    zinTextElements[2].setFont(font);
    zinTextElements[2].setCharacterSize(14);
    zinTextElements[2].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 160);
    //Title next to resilience box
    zinTextElements[3].setFont(font);
    zinTextElements[3].setCharacterSize(14);
    zinTextElements[3].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 140);
    //Hp text
    zinTextElements[4].setCharacterSize(16);
    zinTextElements[4].setPosition(rectStatsBoxX, rectStatsBoxY);
}

void Assets::drawInventory()
{
    //Main Rect
    rectInventoryBox.setFillColor(sf::Color::Black);
    rectInventoryBox.setPosition(rectInventoryBoxX, rectInventoryBoxY);
    rectInventoryBox.setSize(sf::Vector2f(200.0f, 600.0f));
    rectInventoryBox.setOutlineColor(sf::Color::White);
    rectInventoryBox.setOutlineThickness(1.0f);
    //Inventory Text
    inventoryText.setFont(font);
    inventoryText.setCharacterSize(16);
    inventoryText.setFillColor(sf::Color(sf::Color::White));
    inventoryText.setPosition(rectInventoryBoxX, rectInventoryBoxY);
}

//Drawing Map Segments
void Assets::drawMap()
{
    rectMap.setFillColor(sf::Color::Black);
    rectMap.setPosition(rectMapX, rectMapY);
    rectMap.setSize(sf::Vector2f(400.0f, 400.0f));
    rectMap.setOutlineColor(sf::Color::White);
    rectMap.setOutlineThickness(1.0f);

    //Switch map areas via map selectors
    switch (this->areaUnlocked) {
    case 0:
        //Load no buttons
        break;
    case 1:
        for (int i = 0; i < buttonViewMap.size(); i++) {
            buttonViewMap[i].setSize(sf::Vector2f(200.0f, 25.0f));
            buttonViewMap[i].setOutlineColor(sf::Color::White);
            buttonViewMap[i].setOutlineThickness(1.0f);
        }
        //Set button map selector positions
        buttonViewMap[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMap[1].setPosition(rectMapX + 200, rectMapY - 25);
        buttonViewMap[2].setPosition(rectMapX + 20000, rectMapY - 25);
        for (int i = 0; i < buttonViewMapText.size(); i++) {
            buttonViewMapText[i].setFont(font);
            buttonViewMapText[i].setCharacterSize(12);
        }
        //Castle Map Button Selector Text
        buttonViewMapText[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMapText[0].setString("Forest Plane");

        buttonViewMapText[1].setPosition(rectMapX + 200, rectMapY - 25);
        buttonViewMapText[1].setString("Castle Plane");
        break;
    case 2:
        for (int i = 0; i < buttonViewMap.size(); i++) {
            buttonViewMap[i].setSize(sf::Vector2f(133.3f, 25.0f));
            buttonViewMap[i].setOutlineColor(sf::Color::White);
            buttonViewMap[i].setOutlineThickness(1.0f);
        }
        //Set button map selector positions
        buttonViewMap[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMap[1].setPosition(rectMapX + 133.0f, rectMapY - 25.0f);
        buttonViewMap[2].setPosition(rectMapX + 266.0f, rectMapY - 25.0f);
        for (int i = 0; i < buttonViewMapText.size(); i++) {
            buttonViewMapText[i].setFont(font);
            buttonViewMapText[i].setCharacterSize(14);
        }
        //Castle Map Button Selector Text
        buttonViewMapText[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMapText[0].setString("Forest Plane");

        buttonViewMapText[1].setPosition(rectMapX + 133.0f, rectMapY - 25.0f);
        buttonViewMapText[1].setString("Castle Plane");

        buttonViewMapText[2].setPosition(rectMapX + 266.0f, rectMapY - 25.0f);
        buttonViewMapText[2].setString("Decay Plane");
        break;
    }

    multiArrow.setPosition(rectMapX + 340, rectMapY + 10);
    multiArrow.setScale(0.06f, 0.06f);
    switch (mapCounter) {
    case 0:
        this->drawForestMapButtons();
        break;
    case 1:
        this->drawCastleMapButtons();
        break;
    case 2:
        this->drawDecayMapButtons();
        break;
    }
}

void Assets::drawForestMapButtons()
{
    if (this->initForestMapTexture == false) {
        //Hide Castle Textures
        spriteMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapCastleElements.size(); i++) {
            mapCastleElements[i].setPosition(10000, 10000);
            mapCastleElementsText[i].setPosition(10000, 10000);
        }
        //Hide Decay Textures
        decayMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapDecayElements.size(); i++) {
            mapDecayElements[i].setPosition(10000, 10000);
            mapDecayElementsText[i].setPosition(10000, 10000);
        }

        //Load Movable Arrow
        multiArrowTexture.loadFromFile("Assets/Game_Resources/multiarrow.png");
        multiArrow.setTexture(multiArrowTexture);

        //Load Map View
        forestMapTexture.loadFromFile("Assets/Wallpapers/Forest/forestmap.jpeg");
        forestMapView.setTexture(forestMapTexture);
        forestMapView.setPosition(rectMapX, rectMapY);
        forestMapView.setScale(0.39f, 0.39f);

        //Load Buttons
        for (int i = 0; i < mapForestElements.size(); i++) {
            mapForestElements[i].setTexture(buttonTexture);
            mapForestElements[i].setScale(0.5f, 0.5f);
            mapForestElementsText[i].setFont(font);
            mapForestElementsText[i].setFillColor(sf::Color::White);
            mapForestElementsText[i].setCharacterSize(12);
        }

        //Forest areas unlocked
        switch (this->forestAreaUnlocked) {
        case 0:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            //Hidden
            mapForestElements[1].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[2].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[3].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[4].setPosition(rectMapX + 10000, rectMapY + 10000);
            break;
        case 1:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            mapForestElements[1].setPosition(rectMapX + 34, rectMapY + 20);
            mapForestElementsText[1].setPosition(rectMapX + 34, rectMapY + 5);
            mapForestElementsText[1].setString("Forest Entrance");
            //Hidden
            mapForestElements[2].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[3].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[4].setPosition(rectMapX + 10000, rectMapY + 10000);
            break;
        case 2:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            mapForestElements[1].setPosition(rectMapX + 34, rectMapY + 20);
            mapForestElementsText[1].setPosition(rectMapX + 34, rectMapY + 5);
            mapForestElementsText[1].setString("Forest Entrance");
            mapForestElements[2].setPosition(rectMapX + 75, rectMapY + 240);
            mapForestElementsText[2].setPosition(rectMapX + 75, rectMapY + 225);
            mapForestElementsText[2].setString("Forest Depths");
            //Hidden
            mapForestElements[3].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[4].setPosition(rectMapX + 10000, rectMapY + 10000);
            break;
        case 3:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            mapForestElements[1].setPosition(rectMapX + 34, rectMapY + 20);
            mapForestElementsText[1].setPosition(rectMapX + 34, rectMapY + 5);
            mapForestElementsText[1].setString("Forest Entrance");
            mapForestElements[2].setPosition(rectMapX + 75, rectMapY + 240);
            mapForestElementsText[2].setPosition(rectMapX + 75, rectMapY + 225);
            mapForestElementsText[2].setString("Forest Depths");
            mapForestElements[3].setPosition(rectMapX + 175, rectMapY + 200);
            mapForestElementsText[3].setPosition(rectMapX + 175, rectMapY + 185);
            mapForestElementsText[3].setString("Abyssal Forest");
            //Hidden
            mapForestElements[4].setPosition(rectMapX + 10000, rectMapY + 10000);
            break;
        case 4:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            mapForestElements[1].setPosition(rectMapX + 34, rectMapY + 20);
            mapForestElementsText[1].setPosition(rectMapX + 34, rectMapY + 5);
            mapForestElementsText[1].setString("Forest Entrance");
            mapForestElements[2].setPosition(rectMapX + 75, rectMapY + 240);
            mapForestElementsText[2].setPosition(rectMapX + 75, rectMapY + 225);
            mapForestElementsText[2].setString("Forest Depths");
            mapForestElements[3].setPosition(rectMapX + 175, rectMapY + 200);
            mapForestElementsText[3].setPosition(rectMapX + 175, rectMapY + 185);
            mapForestElementsText[3].setString("Abyssal Forest");
            mapForestElements[4].setPosition(rectMapX + 240, rectMapY + 320);
            mapForestElementsText[4].setPosition(rectMapX + 240, rectMapY + 305);
            mapForestElementsText[4].setString("Abyssal Depths");
            break;
        }
        this->initForestMapTexture = true;
    }
}

void Assets::drawCastleMapButtons()
{
    if (this->initCastleMapTexture == false) {
        //Load Movable Arrow
        multiArrowTexture.loadFromFile("Assets/Game_Resources/multiarrow.png");
        multiArrow.setTexture(multiArrowTexture);

        //Hide Forest Textures
        forestMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapForestElements.size(); i++) {
            mapForestElements[i].setPosition(10000, 10000);
            mapForestElementsText[i].setPosition(10000, 10000);
        }
        //Hide Decay Textures
        decayMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapDecayElements.size(); i++) {
            mapDecayElements[i].setPosition(10000, 10000);
            mapDecayElementsText[i].setPosition(10000, 10000);
        }

        //Load Map View
        textureMapView.loadFromFile("Assets/Wallpapers/Castle/castleMap.jpeg");
        spriteMapView.setTexture(textureMapView);
        spriteMapView.setPosition(rectMapX, rectMapY);
        spriteMapView.setScale(0.38f, 0.38f);

        //Load Castle Buttons
        for (int i = 0; i < mapCastleElements.size(); i++) {
            mapCastleElements[i].setTexture(buttonTexture);
            mapCastleElements[i].setScale(0.5f, 0.5f);
            mapCastleElementsText[i].setFont(font);
            mapCastleElementsText[i].setCharacterSize(12);
            mapCastleElementsText[i].setFillColor(sf::Color::White);
        }

        switch (this->castleAreaUnlocked) {
        case 0:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            break;
        case 1:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElementsText[1].setPosition(rectMapX + 75, rectMapY + 225);
            mapCastleElementsText[1].setString("Halls");
            break;
        case 2:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElementsText[1].setPosition(rectMapX + 75, rectMapY + 225);
            mapCastleElementsText[1].setString("Halls");
            mapCastleElements[2].setPosition(rectMapX + 34, rectMapY + 20);
            mapCastleElementsText[2].setPosition(rectMapX + 34, rectMapY + 5);
            mapCastleElementsText[2].setString("Depths");
            break;
        case 3:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElementsText[1].setPosition(rectMapX + 75, rectMapY + 225);
            mapCastleElementsText[1].setString("Halls");
            mapCastleElements[2].setPosition(rectMapX + 34, rectMapY + 20);
            mapCastleElementsText[2].setPosition(rectMapX + 34, rectMapY + 5);
            mapCastleElementsText[2].setString("Depths");
            mapCastleElements[3].setPosition(rectMapX + 200, rectMapY + 20);
            mapCastleElementsText[3].setPosition(rectMapX + 200, rectMapY + 5);
            mapCastleElementsText[3].setString("Chambers");
            break;
        case 4:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElementsText[1].setPosition(rectMapX + 75, rectMapY + 225);
            mapCastleElementsText[1].setString("Halls");
            mapCastleElements[2].setPosition(rectMapX + 34, rectMapY + 20);
            mapCastleElementsText[2].setPosition(rectMapX + 34, rectMapY + 5);
            mapCastleElementsText[2].setString("Depths");
            mapCastleElements[3].setPosition(rectMapX + 200, rectMapY + 20);
            mapCastleElementsText[3].setPosition(rectMapX + 200, rectMapY + 5);
            mapCastleElementsText[3].setString("Chambers");
            mapCastleElements[4].setPosition(rectMapX + 305, rectMapY + 210);
            mapCastleElementsText[4].setPosition(rectMapX + 305, rectMapY + 195);
            mapCastleElementsText[4].setString("Labyrinth");
            break;
        }
        this->initCastleMapTexture = true;
    }
}

void Assets::drawDecayMapButtons()
{
    if (this->initDecayMapTexture == false) {
        //Load Movable Arrow
        multiArrowTexture.loadFromFile("Assets/Game_Resources/multiarrow.png");
        multiArrow.setTexture(multiArrowTexture);

        //Hide Forest Textures
        forestMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapForestElements.size(); i++) {
            mapForestElements[i].setPosition(10000, 10000);
            mapForestElementsText[i].setPosition(10000, 10000);
        }
        //Hide Castle Textures
        spriteMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapCastleElements.size(); i++) {
            mapCastleElements[i].setPosition(10000, 10000);
            mapCastleElementsText[i].setPosition(10000, 10000);
        }

        //Load Map View
        decayTexture.loadFromFile("Assets/Wallpapers/Decay/decayMap.jpeg");
        decayMapView.setTexture(decayTexture);
        decayMapView.setPosition(rectMapX, rectMapY);
        decayMapView.setScale(0.39f, 0.39f);

        //Load Decay buttons
        for (int i = 0; i < mapDecayElements.size(); i++) {
            mapDecayElements[i].setTexture(buttonTexture);
            mapDecayElements[i].setScale(0.5f, 0.5f);
            mapDecayElementsText[i].setFont(font);
            mapDecayElementsText[i].setCharacterSize(12);
            mapDecayElementsText[i].setFillColor(sf::Color::White);
        }

        switch (this->decayAreaUnlocked) {
        case 0:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            break;
        case 1:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            mapDecayElements[1].setPosition(rectMapX + 245, rectMapY + 110);
            mapDecayElementsText[1].setPosition(rectMapX + 245, rectMapY + 95);
            mapDecayElementsText[1].setString("Crimson Chasms");
            break;
        case 2:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            mapDecayElements[1].setPosition(rectMapX + 245, rectMapY + 110);
            mapDecayElementsText[1].setPosition(rectMapX + 245, rectMapY + 95);
            mapDecayElementsText[1].setString("Crimson Chasms");
            mapDecayElements[2].setPosition(rectMapX + 200, rectMapY + 60);
            mapDecayElementsText[2].setPosition(rectMapX + 200, rectMapY + 45);
            mapDecayElementsText[2].setString("Decay Ocean");
            break;
        case 3:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            mapDecayElements[1].setPosition(rectMapX + 245, rectMapY + 110);
            mapDecayElementsText[1].setPosition(rectMapX + 245, rectMapY + 95);
            mapDecayElementsText[1].setString("Crimson Chasms");
            mapDecayElements[2].setPosition(rectMapX + 200, rectMapY + 60);
            mapDecayElementsText[2].setPosition(rectMapX + 200, rectMapY + 45);
            mapDecayElementsText[2].setString("Decay Ocean");
            mapDecayElements[3].setPosition(rectMapX + 150, rectMapY + 40);
            mapDecayElementsText[3].setPosition(rectMapX + 150, rectMapY + 25);
            mapDecayElementsText[3].setString("Decay Forest");
            break;
        case 4:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            mapDecayElements[1].setPosition(rectMapX + 245, rectMapY + 110);
            mapDecayElementsText[1].setPosition(rectMapX + 245, rectMapY + 95);
            mapDecayElementsText[1].setString("Crimson Chasms");
            mapDecayElements[2].setPosition(rectMapX + 200, rectMapY + 60);
            mapDecayElementsText[2].setPosition(rectMapX + 200, rectMapY + 45);
            mapDecayElementsText[2].setString("Decay Ocean");
            mapDecayElements[3].setPosition(rectMapX + 150, rectMapY + 40);
            mapDecayElementsText[3].setPosition(rectMapX + 150, rectMapY + 25);
            mapDecayElementsText[3].setString("Decay Forest");
            mapDecayElements[4].setPosition(rectMapX + 25, rectMapY + 50);
            mapDecayElementsText[4].setPosition(rectMapX + 25, rectMapY + 35);
            mapDecayElementsText[4].setString("Giants Plateau");
            break;
        } 
        this->initDecayMapTexture = true;
    }
}

//Detection Functions
void Assets::bonfireHealDetection()
{
    //Forest Bonfire Heal Detection
    bonfireHealDetectionRect.setFillColor(sf::Color::Transparent);
    bonfireHealDetectionRect.setSize(sf::Vector2f(58, 58));
    bonfireHealDetectionRect.setPosition(1475, 750);

    bonfireHealBorder.setSize(sf::Vector2f(60, 65));
    bonfireHealBorder.setPosition(1475, 750);
    bonfireHealBorder.setFillColor(sf::Color::Transparent);
    bonfireHealBorder.setOutlineColor(sf::Color::White);
    bonfireHealBorder.setOutlineThickness(1.0f);

    bonfireHealDetectionText.setFont(font);
    bonfireHealDetectionText.setCharacterSize(18);
    bonfireHealDetectionText.setFillColor(sf::Color::White);
}

void Assets::bonfireSmithDetection()
{
    //Forest Bonfire Smith Detection
    bonfireSmithDetectionRect.setFillColor(sf::Color::Transparent);
    bonfireSmithDetectionRect.setSize(sf::Vector2f(58, 58));
    bonfireSmithDetectionRect.setPosition(1475, 675);

    bonfireSmithBorder.setSize(sf::Vector2f(58, 58));
    bonfireSmithBorder.setPosition(1475, 675);
    bonfireSmithBorder.setFillColor(sf::Color::Transparent);
    bonfireSmithBorder.setOutlineColor(sf::Color::White);
    bonfireSmithBorder.setOutlineThickness(1.0f);

    bonfireSmithDetectionText.setFont(font);
    bonfireSmithDetectionText.setCharacterSize(18);
    bonfireSmithDetectionText.setFillColor(sf::Color::White);
}

//Draw Sprite Boxes
void Assets::drawSpriteBoxes()
{
    for (int i = 0; i < spriteRect.size(); i++) {
        spriteRect[i].setFillColor(sf::Color::Black);
        spriteRect[i].setSize(sf::Vector2f(153.0f, 153.0f));
        spriteRect[i].setOutlineColor(sf::Color::White);
        spriteRect[i].setOutlineThickness(2.0f);
        spriteText[i].setFont(font);
        spriteText[i].setCharacterSize(18);
        spriteText[i].setFillColor(sf::Color::White);
    }

    //Set Text Rect Names
    textPlayer.setString(playerName);
    textZin.setString("Zin");
    textSpade.setString("Spade");
    textSiward.setString("Siward");
    textThom.setString("Thom");
}

//Combat Asset Functions
void Assets::initCombatAssets()
{
    if (combatAssets == true) {
        //Set All Objects
        for (int i = 0; i < combatRect.size(); i++) {
            combatRect[i].setSize(sf::Vector2f(100.0f, 25.0f));
            combatRect[i].setOutlineColor(sf::Color::White);
            combatRect[i].setOutlineThickness(1.0f);
            combatRect[i].setPosition(10000, 10000);
            combatText[i].setFont(font);
            combatText[i].setCharacterSize(18);
            combatText[i].setPosition(10000, 10000);
        }
        this->playerCombatAssets();
        this->zinCombatAssets();
        this->thomCombatAssets();
    }
    else if (!combatAssets && !bonfireAssets && !eventAssets) {
        //Hide all combat assets
        for (int i = 0; i < spriteRect.size(); i++) {
            spriteRect[i].setPosition(10000, 10000);
            spriteText[i].setPosition(10000, 10000);
        }
        for (int i = 0; i < combatRect.size(); i++) {
            combatRect[i].setPosition(10000, 10000);
            combatText[i].setPosition(10000, 10000);
        }
        playerCounter = -1;
        zinCounter = -1;
        hostileCounter = -1;
        thomCounter = -1;
    }
}

void Assets::playerCombatAssets()
{
    if (this->playerTurnAssets) {
        switch (this->combatPlayerMoves) {
        case 0:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            break;
        case 1:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            //Draw Player Guard Button
            combatRect[1].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[1].setPosition(335.0f, 765.0f);
            combatText[1].setString("Guard");
            break;
        case 2:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            //Draw Player Guard Button
            combatRect[1].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[1].setPosition(335.0f, 765.0f);
            combatText[1].setString("Guard");
            //Draw Player Decay Button
            combatRect[2].setPosition(335.0f, 735.0f);
            //Draw Player Decay Text
            combatText[2].setPosition(335.0f, 735.0f);
            combatText[2].setString("Decay");
            break;
        case 3:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            //Draw Player Guard Button
            combatRect[1].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[1].setPosition(335.0f, 765.0f);
            combatText[1].setString("Guard");
            //Draw Player Decay Button
            combatRect[2].setPosition(335.0f, 735.0f);
            //Draw Player Decay Text
            combatText[2].setPosition(335.0f, 735.0f);
            combatText[2].setString("Decay");
            //Draw Player Hefty Button
            combatRect[3].setPosition(335.0f, 705.0f);
            //Draw Player Hefty Text
            combatText[3].setPosition(335.0f, 705.0f);
            combatText[3].setString("Hefty Blow");
            break;
        case 4:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            //Draw Player Guard Button
            combatRect[1].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[1].setPosition(335.0f, 765.0f);
            combatText[1].setString("Guard");
            //Draw Player Decay Button
            combatRect[2].setPosition(335.0f, 735.0f);
            //Draw Player Decay Text
            combatText[2].setPosition(335.0f, 735.0f);
            combatText[2].setString("Decay");
            //Draw Player Hefty Button
            combatRect[3].setPosition(335.0f, 705.0f);
            //Draw Player Hefty Text
            combatText[3].setPosition(335.0f, 705.0f);
            combatText[3].setString("Hefty Blow");
            //Draw Player Synergy Button
            combatRect[4].setPosition(335.0f, 675.0f);
            //Draw Player Synergy Text
            combatText[4].setPosition(335.0f, 675.0f);
            combatText[4].setString("Synergy");
            break;
        case 5:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            //Draw Player Guard Button
            combatRect[1].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[1].setPosition(335.0f, 765.0f);
            combatText[1].setString("Guard");
            //Draw Player Decay Button
            combatRect[2].setPosition(335.0f, 735.0f);
            //Draw Player Decay Text
            combatText[2].setPosition(335.0f, 735.0f);
            combatText[2].setString("Decay");
            //Draw Player Hefty Button
            combatRect[3].setPosition(335.0f, 705.0f);
            //Draw Player Hefty Text
            combatText[3].setPosition(335.0f, 705.0f);
            combatText[3].setString("Hefty Blow");
            //Draw Player Synergy Button
            combatRect[4].setPosition(335.0f, 675.0f);
            //Draw Player Synergy Text
            combatText[4].setPosition(335.0f, 675.0f);
            combatText[4].setString("Synergy");
            //Draw Player Iron Wall Button
            combatRect[5].setPosition(335.0f, 645.0f);
            //Draw Player Iron Wall Text
            combatText[5].setPosition(335.0f, 645.0f);
            combatText[5].setString("Iron wall");
            break;
        }
    }
    else if (!this->playerTurnAssets) {
        combatRect[0].setPosition(10000.0f, 10000.0f);
        combatRect[1].setPosition(10000.0f, 10000.0f);
        combatRect[2].setPosition(10000.0f, 10000.0f);
        combatRect[3].setPosition(10000.0f, 10000.0f);
        combatRect[4].setPosition(10000.0f, 10000.0f);
        combatRect[5].setPosition(10000.0f, 10000.0f);
    }
}

void Assets::zinCombatAssets()
{
    if (this->zinTurnAssets) {
        switch (this->combatZinMoves) {
        case 0:
            combatRect[6].setPosition(335.0f, 795.0f);
            combatText[6].setPosition(335.0f, 795.0f);
            combatText[6].setString("Smite");
            break;
        case 1:
            combatRect[6].setPosition(335.0f, 795.0f);
            combatText[6].setPosition(335.0f, 795.0f);
            combatText[6].setString("Smite");
            combatRect[7].setPosition(335.0f, 765.0f);
            combatText[7].setPosition(335.0f, 765.0f);
            combatText[7].setString("Mend");
            break;
        case 2:
            combatRect[6].setPosition(335.0f, 795.0f);
            combatText[6].setPosition(335.0f, 795.0f);
            combatText[6].setString("Smite");
            combatRect[7].setPosition(335.0f, 765.0f);
            combatText[7].setPosition(335.0f, 765.0f);
            combatText[7].setString("Mend");
            combatRect[8].setPosition(335.0f, 735.0f);
            combatText[8].setPosition(335.0f, 735.0f);
            combatText[8].setString("Vengeance");
            break;
        case 3:
            combatRect[6].setPosition(335.0f, 795.0f);
            combatText[6].setPosition(335.0f, 795.0f);
            combatText[6].setString("Smite");
            combatRect[7].setPosition(335.0f, 765.0f);
            combatText[7].setPosition(335.0f, 765.0f);
            combatText[7].setString("Mend");
            combatRect[8].setPosition(335.0f, 735.0f);
            combatText[8].setPosition(335.0f, 735.0f);
            combatText[8].setString("Vengeance");
            combatRect[9].setPosition(335.0f, 705.0f);
            combatText[9].setPosition(335.0f, 705.0f);
            combatText[9].setString("Hell Blaze");
            break;
        case 4:
            combatRect[6].setPosition(335.0f, 795.0f);
            combatText[6].setPosition(335.0f, 795.0f);
            combatText[6].setString("Smite");
            combatRect[7].setPosition(335.0f, 765.0f);
            combatText[7].setPosition(335.0f, 765.0f);
            combatText[7].setString("Mend");
            combatRect[8].setPosition(335.0f, 735.0f);
            combatText[8].setPosition(335.0f, 735.0f);
            combatText[8].setString("Vengeance");
            combatRect[9].setPosition(335.0f, 705.0f);
            combatText[9].setPosition(335.0f, 705.0f);
            combatText[9].setString("Hell Blaze");
            combatRect[10].setPosition(335.0f, 675.0f);
            combatText[10].setPosition(335.0f, 675.0f);
            combatText[10].setString("Focus");
            break;
        case 5:
            combatRect[6].setPosition(335.0f, 795.0f);
            combatText[6].setPosition(335.0f, 795.0f);
            combatText[6].setString("Smite");
            combatRect[7].setPosition(335.0f, 765.0f);
            combatText[7].setPosition(335.0f, 765.0f);
            combatText[7].setString("Mend");
            combatRect[8].setPosition(335.0f, 735.0f);
            combatText[8].setPosition(335.0f, 735.0f);
            combatText[8].setString("Vengeance");
            combatRect[9].setPosition(335.0f, 705.0f);
            combatText[9].setPosition(335.0f, 705.0f);
            combatText[9].setString("Hell Blaze");
            combatRect[10].setPosition(335.0f, 675.0f);
            combatText[10].setPosition(335.0f, 675.0f);
            combatText[10].setString("Focus");
            combatRect[11].setPosition(335.0f, 645.0f);
            combatText[11].setPosition(335.0f, 645.0f);
            combatText[11].setString("Flames");
            break;
        }
    }
    else if (!this->zinTurnAssets) {
        combatRect[6].setPosition(10000.0f, 10000.0f);
        combatRect[7].setPosition(10000.0f, 10000.0f);
        combatRect[8].setPosition(10000.0f, 10000.0f);
        combatRect[9].setPosition(10000.0f, 10000.0f);
        combatRect[10].setPosition(10000.0f, 10000.0f);
        combatRect[11].setPosition(10000.0f, 10000.0f);
        combatText[6].setPosition(10000.0f, 10000.0f);
        combatText[7].setPosition(10000.0f, 10000.0f);
        combatText[8].setPosition(10000.0f, 10000.0f);
        combatText[9].setPosition(10000.0f, 10000.0f);
        combatText[10].setPosition(10000.0f, 10000.0f);
        combatText[11].setPosition(10000.0f, 10000.0f);
    }
}

void Assets::thomCombatAssets()
{
    if (this->thomTurnAssets) {
        switch (this->combatThomMoves) {
        case 0:
            //Draw Thom Barrier Button
            combatRect[12].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[12].setPosition(335.0f, 795.0f);
            combatText[12].setString("Barrier");
            break;
        case 1:
            //Draw Thom Barrier Button
            combatRect[12].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[12].setPosition(335.0f, 795.0f);
            combatText[12].setString("Barrier");
            //Draw Thom Barrier Button
            combatRect[13].setPosition(335.0f, 765.0f);
            //Draw Player Slash Text
            combatText[13].setPosition(335.0f, 765.0f);
            combatText[13].setString("Enrage");
            break;
        }
    }
    else if (!this->thomTurnAssets) {
        combatRect[12].setPosition(10000.0f, 10000.0f);
        combatText[12].setPosition(10000.0f, 10000.0f);
        combatRect[13].setPosition(10000.0f, 10000.0f);
        combatText[13].setPosition(10000.0f, 10000.0f);
    }
}

//Sound Functions
void Assets::loadSFX()
{
    //Click Sound
    soundClick.setBuffer(bufferClick);
    //Load Campfire Sound
    soundCampfire.setBuffer(bufferCampfire);

    //Load Hover Sound
    soundHover.setBuffer(bufferSoundHover);
    //Load Walk Sound
    soundWalk.setBuffer(bufferWalk);
    //Load Text Sfx
    sound.setBuffer(buffer);
    //Load Button Sfx
    blipsound.setBuffer(blipbuffer);
    blipmenu.setBuffer(blipmenubuffer);
    //Load Stats Sfx
    statSound.setBuffer(statBuffer);

    //Load Combat Sound Effects
    soundCom.setBuffer(bufferCom);
    //Load Decay Blade Sound
    soundDecay.setBuffer(bufferDecay);
    //Load Vengeance Sound
    soundVengeance.setBuffer(bufferVengeance);
    //Load Slash Sound
    soundSlash.setBuffer(bufferSlash);
    //Load Smite Sound
    soundSmite.setBuffer(bufferSmite);
    //Load Mend Sound
    soundMend.setBuffer(bufferMend);
    //Load Guarded Sound
    soundGuarded.setBuffer(bufferGuarded);
    //Load Guard Sound
    soundGuard.setBuffer(bufferGuard);
    //Load Anger Sfx
    soundAngry.setBuffer(bufferAngry);
    //Load Combat Start Sfx
    soundCombatStart.setBuffer(bufferCombatStart);
    //Load Thom Guarding Player Sfx
    soundPlayerGuarded.setBuffer(bufferPlayerGuarded);
    //Load Thom's Barrier Shattering Sfx
    soundThomGuard.setBuffer(bufferThomGuard);
    //Load Enraged Sfx
    soundEnraged.setBuffer(bufferEnraged);
    //Load Hefty Blow Sfx
    soundHefty.setBuffer(bufferHefty);
    //Load Synergy Sfx
    soundSynergy.setBuffer(bufferSynergy);
    //Sound Blaze Sfx
    soundBlaze.setBuffer(bufferBlaze);
    //Sound Flames Sfx
    soundFlames.setBuffer(bufferFlames);
    //Sound Iron Wall Sfx
    soundIronWall.setBuffer(bufferIronWall);
   
    //Set Volume Levels
    blipmenu.setVolume(60);
}

void Assets::playTrack(sf::Music& track)
{
    if (!this->trackPlayed) {
        track.play();
        this->trackPlayed = true;
    }
}

void Assets::playAmbience(sf::Music& track)
{
    if (!this->ambPlayed) {
        track.play();
        this->ambPlayed = true;
    }
}
