#include "Sprites.h"

//Contructors and Destructors
Sprites::Sprites()
{
    this->hostileLoadOnce = true;
    this->zinInit = false;
    this->spadeInit = false;
    this->hostileInit = false;

    //Sprite Control Flow
    this->siwardLoadOnce = true;
    this->playerLoadOnce = true;
    this->zinLoadOnce = true;
    this->spadeLoadOnce = true;

    //Sprite Border Control Flow
    this->spriteInit = false;
    this->playerInit = false;

    //Sprite Integer Selection
    this->spriteViewerCounter = -1;
    this->entityViewerCounter = -1;
    this->siwardCounter = -1;
    this->spadeCounter = -1;

    //Load Objects
    this->loadSprites();
    this->loadEntities();
}

Sprites::~Sprites()
{

}

//Core Functions
void Sprites::drawObjects(Assets& assets)
{
    this->drawMainWindow();
    this->drawText();
    this->drawMap();
    this->drawStats();
    this->drawInventory();
    this->drawZinStats();
    this->drawTipBox();
    //Sprite Boxes
    this->drawSpriteBoxes();
    //Combat Asset Functions
    this->initCombatAssets();
    //Detection
    this->bonfireHealDetection();
    this->bonfireSmithDetection();
    //User Input
    this->drawAnswerBoxes();
    //Sprite Assets
    this->playerSprite(assets);
    this->zinSprite(assets);
    this->thomSprite(assets);
    this->hostileSprite(assets);
    this->siwardSprite();
    this->spadeSprite();
    this->drawEntityViewer();
}

//Loading Functions
void Sprites::loadSprites()
{
    //Zin Sprites
    zinTexture.loadFromFile("Assets/Sprites/zinSprite.png");
    zinTextureHappy.loadFromFile("Assets/Sprites/zinHappy.png");
    zinTextureConcerned.loadFromFile("Assets/Sprites/zinConcerned.png");
    zinTextureAnnoyed.loadFromFile("Assets/Sprites/zinSpriteAnnoyed.png");
    zinTextureSad.loadFromFile("Assets/Sprites/zinSad.png");

    //Thom Sprites
    thomTexture.loadFromFile("Assets/Sprites/thomNormal.png");
    thomEnragedTexture.loadFromFile("Assets/Sprites/thomRage.png");

    //Load Hostile Sprites
    hostileTextureWalker.loadFromFile("Assets/HostileSprites/decaywalkersprite.jpeg");
    hostileTextureWolf.loadFromFile("Assets/HostileSprites/wolfsprite.png");
    hostileTextureKnight.loadFromFile("Assets/HostileSprites/decayknight.png");
    hostileTextureTree.loadFromFile("Assets/HostileSprites/hostileTreeSprite.png");
    hostileTextureNun.loadFromFile("Assets/HostileSprites/lostNunSprite.jpeg");
    hostileTextureDecapod.loadFromFile("Assets/HostileSprites/abyssalDecapodSprite.jpeg");
    hostileTextureHaze.loadFromFile("Assets/HostileSprites/hazedemonSprite.jpeg");
    hostileTextureJester.loadFromFile("Assets/HostileSprites/courtJesterSprite.jpeg");
    hostileTextureWallMimic.loadFromFile("Assets/HostileSprites/wallMimicSprite.jpeg");
    hostileTextureLostKnight.loadFromFile("Assets/HostileSprites/lostKnightSprite.jpeg");
    hostileTexturePhantom.loadFromFile("Assets/HostileSprites/phantomSprite.jpeg");
    hostileTextureEater.loadFromFile("Assets/HostileSprites/skinEaterSprite.jpeg");
    hostileTextureLimbSplitter.loadFromFile("Assets/HostileSprites/limbSplitterSprite.png");
    hostileTextureBurrower.loadFromFile("Assets/HostileSprites/burrowerSprite.png");
    hostileTextureChatterMouth.loadFromFile("Assets/HostileSprites/chatterMouthSprite.png");
    hostileTextureReclus.loadFromFile("Assets/HostileSprites/reclusSprite.png");
    hostileTextureAlphaEntity.loadFromFile("Assets/HostileSprites/tendrilAlphaSprite.png");
}

void Sprites::loadEntities()
{
    //Load Entity Viewer Files Main
    blankEntity.loadFromFile("Assets/Entities/entityBlank.png");
    thomEntity.loadFromFile("Assets/Entities/thomEntity.jpeg");
    siwardEntityTexture.loadFromFile("Assets/Entities/siwardEntity.jpeg");
    spadeEntityForest.loadFromFile("Assets/Entities/spadeEntityForest.png");
    spadeEntityCastle.loadFromFile("Assets/Entities/spadeEntityCastle.jpg");
    //Load Entity Viewer Files Random Events
    treeEntity.loadFromFile("Assets/Entities/entityTree.jpeg");
    obeliskEntity.loadFromFile("Assets/Entities/obeliskEntity.jpeg");
    strangeCreature.loadFromFile("Assets/Entities/strangeCreatureEntity.jpeg");
    //Load Entity Viewer Files Hostile Entities
    decayEntity.loadFromFile("Assets/Entities/decayEntity.jpeg");
    hostileTreeEntity.loadFromFile("Assets/Entities/hostileTreeSpriteEntity.jpeg");
    lostNunEntity.loadFromFile("Assets/Entities/lostNunEntity.jpeg");
    decapodEntity.loadFromFile("Assets/Entities/abyssalDecapodEntity.jpeg");
    wolfEntity.loadFromFile("Assets/Entities/wolfEntity.jpeg");
    knightEntity.loadFromFile("Assets/Entities/knightEntity.jpeg");
    hazeEntity.loadFromFile("Assets/Entities/hazeDemonEntity.jpeg");
    jesterEntity.loadFromFile("Assets/Entities/courtJesterEntity.jpeg");
    wallMimicEntity.loadFromFile("Assets/Entities/wallMimicEntity.jpeg");
    lostKnightEntity.loadFromFile("Assets/Entities/lostKnightEntity.jpeg");
    phantomEntity.loadFromFile("Assets/Entities/phantomEntity.jpeg");
    eaterEntity.loadFromFile("Assets/Entities/skinEaterEntity.jpeg");
    limbSplitterEntity.loadFromFile("Assets/Entities/limbSplitterEntity.jpeg");
    burrowerEntity.loadFromFile("Assets/Entities/burrowerEntity.jpeg");
    chatterMouthEntity.loadFromFile("Assets/Entities/chatterMouthEntity.jpeg");
    reclusEntity.loadFromFile("Assets/Entities/reclusEntity.jpeg");
    tendrilAlphaEntity.loadFromFile("Assets/Entities/tendrilAlphaEntity.jpeg");
}

//Entity Functions
void Sprites::drawEntityViewer()
{
    entityBoxText.setFont(font);
    entityBoxText.setCharacterSize(14);
    entityBoxText.setString("Close Vision Viewer");
    entityBoxText.setPosition(1500, 75);

    entityBoxHeader.setFillColor(sf::Color::Black);
    entityBoxHeader.setSize(sf::Vector2f(250.0f, 25.0f));
    entityBoxHeader.setOutlineColor(sf::Color::White);
    entityBoxHeader.setOutlineThickness(1.0f);
    entityBoxHeader.setPosition(1500, 75);

    entityBox.setFillColor(sf::Color::Black);
    entityBox.setSize(sf::Vector2f(250.0f, 250.0f));
    entityBox.setOutlineColor(sf::Color::White);
    entityBox.setOutlineThickness(1.0f);
    //Select which sprite to use in the entity viewer
    switch (this->entityViewerCounter) {
    case -1:
        entitySprite.setTexture(blankEntity);
        break;
    case 0:
        entitySprite.setTexture(siwardEntityTexture);
        break;
    case 1:
        entitySprite.setTexture(decayEntity);
        break;
    case 2:
        entitySprite.setTexture(treeEntity);
        break;
    case 3:
        entitySprite.setTexture(spadeEntityForest);
        break;
    case 4:
        entitySprite.setTexture(spadeEntityCastle);
        break;
    case 5:
        entitySprite.setTexture(hostileTreeEntity);
        break;
    case 6:
        entitySprite.setTexture(obeliskEntity);
        break;
    case 7:
        entitySprite.setTexture(lostNunEntity);
        break;
    case 8:
        entitySprite.setTexture(decapodEntity);
        break;
    case 9:
        entitySprite.setTexture(wolfEntity);
        break;
    case 10:
        entitySprite.setTexture(knightEntity);
        break;
    case 11:
        entitySprite.setTexture(hazeEntity);
        break;
    case 12:
        entitySprite.setTexture(jesterEntity);
        break;
    case 13:
        entitySprite.setTexture(wallMimicEntity);
        break;
    case 14:
        entitySprite.setTexture(lostKnightEntity);
        break;
    case 15:
        entitySprite.setTexture(phantomEntity);
        break;
    case 16:
        entitySprite.setTexture(eaterEntity);
        break;
    case 17:
        entitySprite.setTexture(limbSplitterEntity);
        break;
    case 18:
        entitySprite.setTexture(burrowerEntity);
        break;
    case 19:
        entitySprite.setTexture(chatterMouthEntity);
        break;
    case 20:
        entitySprite.setTexture(reclusEntity);
        break;
    case 21:
        entitySprite.setTexture(tendrilAlphaEntity);
        break;
    case 22:
        entitySprite.setTexture(thomEntity);
        break;
    }
    //Select whether or not the sprite is visible
    switch (this->spriteViewerCounter) {
    case -1:
        entityBox.setPosition(10000, 10000);
        entitySprite.setPosition(10000, 10000);
        entityBoxText.setPosition(10000, 10000);
        entityBoxHeader.setPosition(10000, 10000);
        break;
    case 0:
        entityBox.setPosition(1500, 100);
        entitySprite.setPosition(1500, 100);
        entityBoxText.setPosition(1500, 75);
        entityBoxHeader.setPosition(1500, 75);
        break;
    }

    entitySprite.setScale(0.244f, 0.244f);
}

//Sprite Functions
void Sprites::hostileSprite(Assets& assets)
{
    if (this->hostileLoadOnce) {
        spriteElements[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteElements[5].setScale(0.15f, 0.15f);
        spriteRect[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteText[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        this->hostileLoadOnce = false;
    }
    //Pick Hostile Sprite
    switch (assets.getHostileCounter()) {
    case -1:
        spriteElements[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        if (this->hostileInit == false) {
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            this->hostileInit = true;
        }
        break;
    case 1:
        //Wolf Sprite
        if (this->hostileInit == false) {
            hostileTextureWolf.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureWolf);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 2:
        //Decay Walker Sprite
        if (this->hostileInit == false) {
            hostileTextureWalker.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureWalker);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            spriteElements[5].setScale(0.235f, 0.235f);
            this->hostileInit = true;
        }
        break;
    case 3:
        //Decay knight Sprite
        if (this->hostileInit == false) {
            hostileTextureKnight.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureKnight);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            spriteElements[5].setScale(0.235f, 0.235f);
            this->hostileInit = true;
        }
        break;
    case 4:
        //Hostile Tree Mimic
        if (this->hostileInit == false) {
            hostileTextureTree.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureTree);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 5:
        //Hostile Nun
        if (this->hostileInit == false) {
            hostileTextureNun.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureNun);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 6:
        //Hostile Decapod
        if (this->hostileInit == false) {
            hostileTextureDecapod.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureDecapod);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 7:
        //Hostile Haze Demon
        if (this->hostileInit == false) {
            hostileTextureHaze.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureHaze);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 8:
        //Hostile Jester
        if (this->hostileInit == false) {
            hostileTextureJester.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureJester);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 9:
        //Hostile Wall Mimic
        if (this->hostileInit == false) {
            hostileTextureWallMimic.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureWallMimic);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 10:
        //Hostile Lost Knight
        if (this->hostileInit == false) {
            hostileTextureLostKnight.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureLostKnight);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 11:
        //Hostile Phantom
        if (this->hostileInit == false) {
            hostileTexturePhantom.setRepeated(false);
            spriteElements[5].setTexture(hostileTexturePhantom);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 12:
        //Hostile Skin Eater
        if (this->hostileInit == false) {
            hostileTextureEater.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureEater);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 13:
        //Hostile Limb Splitter
        if (this->hostileInit == false) {
            hostileTextureLimbSplitter.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureLimbSplitter);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 14:
        //Hostile Burrower
        if (this->hostileInit == false) {
            hostileTextureBurrower.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureBurrower);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 15:
        //Hostile ChatterMouth
        if (this->hostileInit == false) {
            hostileTextureChatterMouth.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureChatterMouth);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 16:
        //Hostile Reclus
        if (this->hostileInit == false) {
            hostileTextureReclus.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureReclus);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    case 17:
        //Hostile Tendril Alpha
        if (this->hostileInit == false) {
            hostileTextureAlphaEntity.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureAlphaEntity);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            this->hostileInit = true;
        }
        break;
    }
}

void Sprites::playerSprite(Assets& assets)
{
    //Initialize Player Sprite
    if (this->playerLoadOnce == true) {
        playerTexture.loadFromFile("Assets/Sprites/player.png");
        spriteElements[4].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        this->playerLoadOnce = false;
    }
    //Pick Player Sprite Emotion
    switch (assets.getPlayerCounter()) {
    case -1:
        spriteElements[4].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[0].setPosition(10000.0f, 10000.0f);
        spriteText[0].setPosition(10000.0f, 10000.0f);
        break;
    case 0:
        if (this->playerInit == false) {
            playerTexture.loadFromFile("Assets/Sprites/player.png");
            spriteElements[4].setPosition(sf::Vector2f(50.0f, 100.0f));
            spriteRect[0].setPosition(50.0f, 100.0f);
            spriteText[0].setPosition(50.0f, 253.0f);
            this->playerInit = true;
        }
        break;
    }

    //Sprite Options, ect
    playerTexture.setSmooth(true);
    playerTexture.setRepeated(false);
    spriteElements[4].setTexture(playerTexture);
    spriteElements[4].setScale(0.244f, 0.244f);
}

void Sprites::zinSprite(Assets& assets)
{
    //Pick Zin Sprite Emotion
    switch (assets.getZinCounter()) {
    case -1:
        spriteElements[3].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[1].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteText[1].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        spriteElements[3].setTexture(zinTexture);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 1:
        spriteElements[3].setTexture(zinTextureHappy);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 2:
        spriteElements[3].setTexture(zinTextureConcerned);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 3:
        spriteElements[3].setTexture(zinTextureAnnoyed);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 4:
        spriteElements[3].setTexture(zinTextureSad);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    }

    //Sprite Options, ect
    zinTexture.setRepeated(false);
    spriteElements[3].setScale(0.0504f, 0.0504f);
}

void Sprites::thomSprite(Assets& assets)
{
    //Pick Thom Emotion
    switch (assets.getThomCounter()) {
    case -1:
        spriteElements[7].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteText[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        spriteElements[7].setTexture(thomTexture);
        spriteElements[7].setPosition(sf::Vector2f(50.0f, 500.0f));
        spriteRect[5].setPosition(sf::Vector2f(50.0f, 500.0f));
        spriteText[5].setPosition(sf::Vector2f(50.0f, 653.0f));
        break;
    case 1:
        spriteElements[7].setTexture(thomEnragedTexture);
        spriteElements[7].setPosition(sf::Vector2f(50.0f, 500.0f));
        spriteRect[5].setPosition(sf::Vector2f(50.0f, 500.0f));
        spriteText[5].setPosition(sf::Vector2f(50.0f, 653.0f));
        break;
    }

    //Sprite Options, ect
    thomTexture.setRepeated(false);
    spriteElements[7].setScale(0.48f, 0.48f);
}

void Sprites::siwardSprite()
{
    //Initialize Siward Sprite
    if (this->siwardLoadOnce == true) {
        siwardTexture.loadFromFile("Assets/Sprites/siward.png");
        spriteElements[6].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        this->siwardLoadOnce = false;
    }
    //Pick Siward Sprite Emotion
    switch (this->siwardCounter) {
    case -1:
        spriteElements[6].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[4].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        if (this->siwardLoadOnce == false) {
            spriteElements[6].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[4].setPosition(sf::Vector2f(1650.0f, 300.0f));
            this->siwardLoadOnce = true;
        }
        break;
    }

    //Sprite Options, ect
    siwardTexture.setRepeated(false);
    spriteElements[6].setTexture(siwardTexture);
    spriteElements[6].setScale(0.24f, 0.24f);
}

void Sprites::spadeSprite()
{
    //Initialize Spade Sprite
    if (this->spadeLoadOnce == true) {
        spadeTexture.loadFromFile("Assets/Sprites/spadePixel.png");
        spriteElements[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        this->spadeLoadOnce = false;
    }
    //Pick Spade Sprite Emotion
    switch (this->spadeCounter) {
    case -1:
        spriteElements[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[3].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        if (this->spadeInit == false) {
            spadeTexture.loadFromFile("Assets/Sprites/spadePixel.png");
            spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
            this->spadeInit = true;
        }
        break;
    case 1:
        if (this->spadeInit == false) {
            spadeTexture.loadFromFile("Assets/Sprites/spadePixelAngry.png");
            this->spadeInit = true;
        }
        break;
    }

    //Sprite Options, ect
    spadeTexture.setSmooth(true);
    spadeTexture.setRepeated(false);
    spriteElements[2].setTexture(spadeTexture);
    spriteElements[2].setScale(0.050f, 0.050f);
}