#include "Sprites.h"

//Contructors and Destructors
Sprites::Sprites()
{
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
    //Player Sprites
    playerTexture.loadFromFile("Assets/Sprites/player.png");
    playerTextureRage.loadFromFile("Assets/Sprites/playerRage.png");

    //Zin Sprites
    zinTexture.loadFromFile("Assets/Sprites/zinSprite.png");
    zinTextureHappy.loadFromFile("Assets/Sprites/zinHappy.png");
    zinTextureConcerned.loadFromFile("Assets/Sprites/zinConcerned.png");
    zinTextureAnnoyed.loadFromFile("Assets/Sprites/zinSpriteAnnoyed.png");
    zinTextureSad.loadFromFile("Assets/Sprites/zinSad.png");

    //Thom Sprites
    thomTexture.loadFromFile("Assets/Sprites/thomNormal.png");
    thomEnragedTexture.loadFromFile("Assets/Sprites/thomRage.png");

    //Siward Sprites
    siwardTexture.loadFromFile("Assets/Sprites/siward.png");
    siwardTextureDecaying.loadFromFile("Assets/Sprites/siwardDecaying.png");
    siwardTextureDecayed.loadFromFile("Assets/Sprites/siwardDecayed.png");

    //Spade Sprites
    spadeTexture.loadFromFile("Assets/Sprites/spadeNormal.png");
    spadeTextureAngry.loadFromFile("Assets/Sprites/spadeAngry.png");
    spadeTextureHappy.loadFromFile("Assets/Sprites/spadeSmug.png");
    spadeTextureSmug.loadFromFile("Assets/Sprites/spadeHappy.png");
    spadeTextureConfused.loadFromFile("Assets/Sprites/spadeConfused.png");
    spadeTextureStare.loadFromFile("Assets/Sprites/spadeStare.png");
    spadeTextureStareExtra.loadFromFile("Assets/Sprites/spadeStareExtra.png");

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
    siwardEntityCastleTexture.loadFromFile("Assets/Entities/siwardCastle.jpeg");
    siwardEntityDuelTexture.loadFromFile("Assets/Entities/siwardCastleDuel.jpeg");
    spadeEntityForest.loadFromFile("Assets/Entities/spadeEntityForest.png");
    spadeEntityAbyssalForest.loadFromFile("Assets/Entities/spadeForestAbyssalEntity.jpeg");
    spadeEntityCastle.loadFromFile("Assets/Entities/spadeEntityCastle.jpg");
    spadeEntityCrimson.loadFromFile("Assets/Entities/spadeEntityCrimson.jpeg");
    spadeEntityCrimsonPoison.loadFromFile("Assets/Entities/spadeEntityCrimsonPoison.jpeg");
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
    case 23:
        entitySprite.setTexture(siwardEntityCastleTexture);
        break;
    case 24:
        entitySprite.setTexture(siwardEntityDuelTexture);
        break;
    case 25:
        entitySprite.setTexture(spadeEntityAbyssalForest);
        break;
    case 26:
        entitySprite.setTexture(spadeEntityCrimson);
        break;
    case 27:
        entitySprite.setTexture(spadeEntityCrimsonPoison);
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
    //Pick Hostile Sprite
    switch (assets.getHostileCounter()) {
    case -1:
        spriteElements[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteText[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteElements[5].setScale(0.15f, 0.15f);
        break;
    case 0:
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        break;
    case 1:
        //Wolf Sprite
        hostileTextureWolf.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureWolf);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 2:
        //Decay Walker Sprite
        hostileTextureWalker.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureWalker);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 3:
        //Decay knight Sprite
        hostileTextureKnight.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureKnight);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 4:
        //Hostile Tree Mimic
        hostileTextureTree.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureTree);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 5:
        //Hostile Nun
        hostileTextureNun.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureNun);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 6:
        //Hostile Decapod
        hostileTextureDecapod.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureDecapod);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 7:
        //Hostile Haze Demon
        hostileTextureHaze.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureHaze);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 8:
        //Hostile Jester
        hostileTextureJester.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureJester);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 9:
        //Hostile Wall Mimic
        hostileTextureWallMimic.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureWallMimic);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 10:
        //Hostile Lost Knight
        hostileTextureLostKnight.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureLostKnight);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 11:
        //Hostile Phantom
        hostileTexturePhantom.setRepeated(false);
        spriteElements[5].setTexture(hostileTexturePhantom);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 12:
        //Hostile Skin Eater
        hostileTextureEater.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureEater);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 13:
        //Hostile Limb Splitter
        hostileTextureLimbSplitter.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureLimbSplitter);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 14:
        //Hostile Burrower
        hostileTextureBurrower.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureBurrower);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 15:
        //Hostile ChatterMouth
        hostileTextureChatterMouth.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureChatterMouth);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 16:
        //Hostile Reclus
        hostileTextureReclus.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureReclus);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    case 17:
        //Hostile Tendril Alpha
        hostileTextureAlphaEntity.setRepeated(false);
        spriteElements[5].setTexture(hostileTextureAlphaEntity);
        spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
        break;
    }
}

void Sprites::playerSprite(Assets& assets)
{
    //Pick Player Sprite Emotion
    switch (assets.getPlayerCounter()) {
    case -1:
        spriteElements[4].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[0].setPosition(10000.0f, 10000.0f);
        spriteText[0].setPosition(10000.0f, 10000.0f);
        break;
    case 0:
        //PLayer Normal
        spriteElements[4].setTexture(playerTexture);
        spriteElements[4].setPosition(sf::Vector2f(50.0f, 100.0f));
        spriteRect[0].setPosition(50.0f, 100.0f);
        spriteText[0].setPosition(50.0f, 253.0f);
        break;
    case 1:
        //Player Rage
        spriteElements[4].setTexture(playerTextureRage);
        spriteElements[4].setPosition(sf::Vector2f(50.0f, 100.0f));
        spriteRect[0].setPosition(50.0f, 100.0f);
        spriteText[0].setPosition(50.0f, 253.0f);
        break;
    }

    //Sprite Options, ect
    playerTexture.setSmooth(true);
    playerTexture.setRepeated(false);
    spriteElements[4].setScale(0.244f, 0.244f);
}

void Sprites::zinSprite(Assets& assets)
{
    //Pick Zin Sprite Emotion
    switch (assets.getZinCounter()) {
    case -1:
        //Hide Zin Sprite
        spriteElements[3].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[1].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteText[1].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        //Normal Zin
        spriteElements[3].setTexture(zinTexture);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 1:
        //Zin Happy
        spriteElements[3].setTexture(zinTextureHappy);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 2:
        //Zin Concerned
        spriteElements[3].setTexture(zinTextureConcerned);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 3:
        //Zin Annoyed
        spriteElements[3].setTexture(zinTextureAnnoyed);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 4:
        //Zin Sad
        spriteElements[3].setTexture(zinTextureSad);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 5:
        //Zin Scared
        spriteElements[3].setTexture(zinTextureScared);
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
        //Hide Thom
        spriteElements[7].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteText[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        //Normal Thom
        spriteElements[7].setTexture(thomTexture);
        spriteElements[7].setPosition(sf::Vector2f(50.0f, 500.0f));
        spriteRect[5].setPosition(sf::Vector2f(50.0f, 500.0f));
        spriteText[5].setPosition(sf::Vector2f(50.0f, 653.0f));
        break;
    case 1:
        //Enraged Thom
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
    //Pick Siward Sprite Decay State
    switch (this->siwardCounter) {
    case -1:
        //Hide Siward
        spriteElements[6].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[4].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        //Regular Siward
        spriteElements[6].setTexture(siwardTexture);
        spriteElements[6].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[4].setPosition(sf::Vector2f(1650.0f, 300.0f));
        break;
    case 1:
        //Decaying Siward
        spriteElements[6].setTexture(siwardTextureDecaying);
        spriteElements[6].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[4].setPosition(sf::Vector2f(1650.0f, 300.0f));
        break;
    case 2:
        //Decayed Siward
        spriteElements[6].setTexture(siwardTextureDecayed);
        spriteElements[6].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[4].setPosition(sf::Vector2f(1650.0f, 300.0f));
        break;
    }

    //Sprite Options, ect
    siwardTexture.setRepeated(false);
    spriteElements[6].setScale(0.24f, 0.24f);
}

void Sprites::spadeSprite()
{
    //Pick Spade Sprite Emotion
    switch (this->spadeCounter) {
    case -1:
        spriteElements[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[3].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        //Normal Spade
        spriteElements[2].setTexture(spadeTexture);
        spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteElements[2].setScale(0.050f, 0.050f);
        break;
    case 1:
        //Angry Spade
        spriteElements[2].setTexture(spadeTextureAngry);
        spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteElements[2].setScale(0.050f, 0.050f);
        break;
    case 2:
        //Happy Spade
        spriteElements[2].setTexture(spadeTextureHappy);
        spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteElements[2].setScale(0.050f, 0.050f);
        break;
    case 3:
        //Smug Spade
        spriteElements[2].setTexture(spadeTextureSmug);
        spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteElements[2].setScale(0.050f, 0.050f);
        break;
    case 4:
        //Confused Spade
        spriteElements[2].setTexture(spadeTextureConfused);
        spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteElements[2].setScale(0.150f, 0.150f);
        break;
    case 5:
        //Staring Spade
        spriteElements[2].setTexture(spadeTextureStare);
        spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteElements[2].setScale(0.150f, 0.150f);
        break;
    case 6:
        //Extra Staring Spade
        spriteElements[2].setTexture(spadeTextureStareExtra);
        spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
        spriteElements[2].setScale(0.150f, 0.150f);
        break;
    }

    //Sprite Options, ect
    spadeTexture.setSmooth(true);
    spadeTexture.setRepeated(false);
}

//Display Functions
void Sprites::greyOnHover(sf::RenderWindow& window)
{
    this->greyOnHoverRect(window, rectElements, textElements);
    this->greyOnHoverRect(window, menuScreenElements, menuScreenElementsText);
    this->greyOnHoverRect(window, combatRect, combatText);
    this->greyOnHoverRect(window, playerStatElements, playerTextPlus);
    this->greyOnHoverRect(window, zinStatElements, zinTextPlus);
    this->greyOnHoverRect(window, buttonViewMap, buttonViewMapText);

    this->highlightOnHover(window, answerBox);

    this->greyOnHoverSprite(window, spriteElements);
    this->greyOnHoverSprite(window, mapCastleElements);
    this->greyOnHoverSprite(window, mapForestElements);
    this->greyOnHoverSprite(window, mapDecayElements);
}

void Sprites::greyOnHoverRect(sf::RenderWindow& window, std::vector<sf::RectangleShape>& inputRect, std::vector<sf::Text>& inputText)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    for (int i = 0; i < inputRect.size(); i++) {
        if (inputRect[i].getGlobalBounds().contains(mousePosF)) {
            inputRect[i].setFillColor(sf::Color::Black);
            inputText[i].setFillColor(sf::Color::White);
        }
        else {
            inputRect[i].setFillColor(sf::Color::White);
            inputText[i].setFillColor(sf::Color::Black);
        }
    }

    //Turn dialogue box grey on hover
    if (rect.getGlobalBounds().contains(mousePosF) && getShowAnsBoxesCounter() == -1) {
        rect.setFillColor(sf::Color(10, 10, 10));
    }
    else {
        rect.setFillColor(sf::Color::Black);
    }
}

void Sprites::highlightOnHover(sf::RenderWindow& window, std::vector<sf::RectangleShape>& inputRect)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    for (int i = 0; i < inputRect.size(); i++) {
        if (inputRect[i].getGlobalBounds().contains(mousePosF)) {
            inputRect[i].setFillColor(sf::Color(25, 25, 25));
        }
        else {
            inputRect[i].setFillColor(sf::Color::Black);
        }
    }
}

void Sprites::greyOnHoverSprite(sf::RenderWindow& window, std::vector<sf::Sprite>& inputSprite)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    for (int i = 0; i < inputSprite.size(); i++) {
        if (inputSprite[i].getGlobalBounds().contains(mousePosF)) {
            inputSprite[i].setColor(sf::Color(155, 155, 155));
        }
        else {
            inputSprite[i].setColor(sf::Color(255, 255, 255));
        }
    }
}