#include"World.h"

//Constructors and Destructors
World::World()
{
    //Core
    this->input = input;
    this->targetHpView = targetHpView;
    this->unicode = unicode;
    this->random = random;

    //Core Bool
    this->stop = false;
    this->keyPress = true;
    this->initialized = false;
    this->comInitialized = false;
    this->bonfire = true;
    this->mainMenu = true;

    this->mapDefinitionHasLoaded = false;

    //Menu Bool
    this->statsmenu = false;

    //Quest Bool
    this->buttonClick = false;

    //Coordinate Plane
    this->xCord = 1920;
    this->yCord = 600;

    this->test = 0;
}

World::~World() 
{

}

//Core Functions
void World::bootUp(Animation& animate)
{
    //Load SFX
    loadSFX();
    //create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Decay", sf::Style::Fullscreen  );
    window.setFramerateLimit(144);
    // run the program as long as the window is open
    while (window.isOpen()) {
        //std::cout << clock.getElapsedTime().asMicroseconds() << "\n";
        clock.restart();
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            switch (event.type) { // Close Window on Closed Event
            case sf::Event::Closed:
                this->stop = true;
                window.close();
                break;
            case sf::Event::MouseMoved:
                //Mouse Hover Actions
                this->printToolTip(window);
                break;
            case sf::Event::MouseButtonPressed:
                //Get Mouse Click Input
                this->travelButtons(window, animate);
                //If button in map is clicked, do something
                if (!getPlayerDeath() && getInitMap()) {
                    this->mapButtons(window);
                }
                //Map Menu Bar Functionality
                this->statsFunctionality(window); //Must be loaded before menuBar(window); to withhold functionality
                this->menuBar(window);
                //Dialogue Box Functionality
                this->dialogueCombatBox(window);
                //Main Menu Functionality
                this->mainMenuButtons(window, animate);
                if (stop) { //Make quit button return to main function to stop program from running
                    return;
                }
                //Bonfire Functionality
                if (getBonfireAssets() == true) {
                    healCharacters(window);
                    smithingSharpenBlade(window);
                }
                break;
            case sf::Event::MouseButtonReleased:
                setMovableFalse();
                setMovableStatsBoxFalse();
                break;
            case sf::Event::KeyPressed:
                this->userInput();
                break;
            }
            //Main Travel Loop
            travelCore(window, animate);
        }
        //Draw Everything...
        window.clear(sf::Color::Black);
        this->draw(window, animate);
        window.display();
    }
}

void World::userInput()
{
    //Get user input for keyboard inputs
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    playerText.setFont(font);
    playerText.setCharacterSize(18);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(0, 950);
    
    playerInput += event.text.unicode;
    input = event.text.unicode;
    unicode = event.text.unicode;

    //Getting user input for settings
    if (unicode == 36) {
        soundClick.play();
        //Make settings appear (Basically the main menu with some additions....)
        if (!getSettingsShown()) {
            getSettingsShown() = true;
        }
        else if (getSettingsShown()){
            getSettingsShown() = false;
        }
    }
}

void World::saveGame(Animation& animate)
{
    std::ofstream saveData;
    saveData.open("example.txt");
    if (saveData.is_open()) {
        saveData << getSpriteViewerCounter() << " " <<  getEntityViewerCounter() << " " <<  getSiwardCounter()
            << " " <<  getSpadeCounter() << " " <<  getRiCounter() << " " <<  getGrifCounter() << " " <<  getPlayerCounter()
            << " " <<  getZinCounter() << " " <<  getThomCounter() << " " <<  getHostileCounter() << " " <<  getCombatCounter()
            << " " <<  getDialogueCounter() << " " <<  getInitialDrawIn() << " " <<  getInitForestMapTexture()
            << " " <<  getInitCastleMapTexture() << " " <<  getInitDecayMapTexture() << " " <<  getInitMap()
            << " " <<  getInitStats() << " " <<  getInitInventory() << " " <<  getPlusboxes() << " " <<  getEndFrame()
            << " " <<  getStartFrame() << " " <<  getThomUnlocked() << " " <<  getPlayerStatsInit() << " " <<  getZinStatsInit()
            << " " <<  getBootClicked() << " " <<  getIntroFinished() << " " <<  getSettingsShown() << " " <<  getAreaUnlocked()
            << " " <<  getForestAreaUnlocked() << " " <<  getCastleAreaUnlocked() << " " <<  getDecayAreaUnlocked()
            << " " <<  getMapCounter() << " " <<  getShowAnsBoxesCounter() << " " <<  getTipBoxCounter()
            << " " <<  getMovable() << " " <<  getMovableStatsBox() << " " <<  getRectMapX() << " " <<  getRectMapY()
            << " " <<  getRectStatsBoxX() << " " <<  getRectStatsBoxY() << " " <<  getRectInventoryBoxX()
            << " " <<  getRectInventoryBoxY() << " " <<  getCombatAssets() << " " <<  getEventAssets()
            << " " <<  getBonfireAssets() << " " <<  getPlayerTurnAssets() << " " <<  getZinTurnAssets()
            << " " <<  getThomTurnAssets() << " " <<  getPlayerDeath() << " " <<  getCombatPlayerMoves()
            << " " <<  getCombatZinMoves() << " " <<  getCombatThomMoves() << " " <<  getReInitialize()
            << " " <<  getSfxUsed() << " " <<  getItemGained() << " " <<  getThomEnced() << " " <<  getSiwardEncedForest()
            << " " <<  getSiwardEncedCastle() << " " <<  getSiwardEncedFinal() << " " <<  getSpadeEncedForest()
            << " " <<  getSpadeEncedAbyssalForest() << " " <<  getSpadeEncedCastle() << " " <<  getSpadeEncedCastlePoison()
            << " " <<  getSpadeEncedDecay() << " " <<  getSpadeEncedDecayPoison() << " " <<  getSpadeEnced()
            << " " <<  getRiEncedForest() << " " <<  getRotBeastEnced() << " " <<  getGrifEncounteredCastle()
            << " " <<  getTreeEnced() << " " <<  getObeliskEnced() << " " <<  getNunEnced() << " " <<  getPlayerDeathEnced()
            << " " <<  getRotBeastDeathEnced() << " " <<  getRotBeastEnced() << " " <<  getChoiceCounter() << " " << getGrifEncounteredOcean()
            << " " <<  getDialogue() << " " <<  getSpadePoison() << " " <<  getValZero() << " " <<  getValOne()
            << " " <<  getValTwo() << " " <<  getValThree() << " " <<  getValFour() << " " <<  getValFive()
            << " " <<  getAttackCounter() << " " <<  getZinAttackCounter() << " " <<  getThomAttackCounter()
            << " " <<  getInitCombatOnce() << " " <<  getReInitCombatOnce() << " " <<  getCombatEnd()
            << " " <<  getTurnPlayer() << " " <<  getTurnZin() << " " <<  getTurnThom() << " " <<  getTurnHostile()
            << " " <<  getInitHostileWolf() << " " <<  getInitHostileWalker() << " " <<  getInitHostileKnight()
            << " " <<  getInitHostileTreeMimic() << " " <<  getInitHostileLostNun() << " " <<  getInitHostileDecapod()
            << " " <<  getInitHostileJester() << " " <<  getInitHostileWallMimic() << " " <<  getInitHostileLostKnight()
            << " " <<  getInitHostilePhantom() << " " <<  getInitHostileEater() << " " <<  getInitHostileSiward()
            << " " <<  getInitHostileLimbSplitter() << " " <<  getInitHostileBurrower() << " " <<  getInitHostileChatterMouth()
            << " " <<  getInitHostileReclus() << " " <<  getInitHostileTendrilAlpha() << " " <<  getInitHostileSpade()
            << " " <<  getPlayerAttack() << " " <<  getZinAttack() << " " <<  getThomAttack() << " " <<  getHostileAttack()
            << " " <<  getHostileAttackZin() << " " <<  getHostileAttackThom() << " " <<  getPlayerDead()
            << " " <<  getZinDead() << " " <<  getThomDead() << " " <<  getPlayerPickMove() << " " <<  getZinPickMove()
            << " " <<  getThomPickMove() << " " <<  getComTextRemoved() << " " <<  getDecay() << " " <<  getDecayMax()
            << " " <<  getLevel() << " " <<  getExp() << " " <<  getExpNext() << " " <<  getSp() << " " <<  getStrength()
            << " " <<  getFortitude() << " " <<  getVitality() << " " <<  getZinLevel() << " " <<  getZinSp()
            << " " <<  getZinExp() << " " <<  getZinExpNext() << " " <<  getZinResolve() << " " <<  getZinPatience()
            << " " <<  getZinResilience() << " " <<  getSwordPower() << " " <<  getGold() << " " <<  getSmithingStones()
            << " " <<  getIncease() << " " <<  getFrame() << " " <<  getTravel()
            << " " <<  getBonfireInit() << " " <<  getIntroCounterDialogue() << " " <<  getIntroCounter()
            << " " <<  getForestCounter() << " " <<  getCastleCounter() << " " <<  getDecayCounter()
            << " " <<  getFrameInit() << " " << this->unicode << " " << this->random << " " << this->test << " " << this->stop << " " << this->keyPress << " " << this->initialized
            << " " << this->comInitialized << " " << this->bonfire << " " << this->mainMenu << " " << this->statsmenu << " " << this->buttonClick << " " << this->xCord << " " << this->yCord;
        saveData.close();
    }
    

    animate.getNotePosX() = 215;
    animate.getNotePosY() = 145;
    animate.getAnimateString() = "Game Saved...";
    animate.getDecayWarning() = true;
}

void World::loadGame(Animation& animate)
{
    std::ifstream loadData;
    loadData.open("example.txt");

    if (loadData.is_open()) {
        std::cout << "File loading...";
        loadData >> getSpriteViewerCounter() >> getEntityViewerCounter() >> getSiwardCounter()
            >> getSpadeCounter() >> getRiCounter() >> getGrifCounter() >> getPlayerCounter()
            >> getZinCounter() >> getThomCounter() >> getHostileCounter() >> getCombatCounter()
            >> getDialogueCounter() >> getInitialDrawIn() >> getInitForestMapTexture()
            >> getInitCastleMapTexture() >> getInitDecayMapTexture() >> getInitMap()
            >> getInitStats() >> getInitInventory() >> getPlusboxes() >> getEndFrame()
            >> getStartFrame() >> getThomUnlocked() >> getPlayerStatsInit() >> getZinStatsInit()
            >> getBootClicked() >> getIntroFinished() >> getSettingsShown() >> getAreaUnlocked()
            >> getForestAreaUnlocked() >> getCastleAreaUnlocked() >> getDecayAreaUnlocked()
            >> getMapCounter() >> getShowAnsBoxesCounter() >> getTipBoxCounter()
            >> getMovable() >> getMovableStatsBox() >> getRectMapX() >> getRectMapY()
            >> getRectStatsBoxX() >> getRectStatsBoxY() >> getRectInventoryBoxX()
            >> getRectInventoryBoxY() >> getCombatAssets() >> getEventAssets()
            >> getBonfireAssets() >> getPlayerTurnAssets() >> getZinTurnAssets()
            >> getThomTurnAssets() >> getPlayerDeath() >> getCombatPlayerMoves()
            >> getCombatZinMoves() >> getCombatThomMoves() >> getReInitialize()
            >> getSfxUsed() >> getItemGained() >> getThomEnced() >> getSiwardEncedForest()
            >> getSiwardEncedCastle() >> getSiwardEncedFinal() >> getSpadeEncedForest()
            >> getSpadeEncedAbyssalForest() >> getSpadeEncedCastle() >> getSpadeEncedCastlePoison()
            >> getSpadeEncedDecay() >> getSpadeEncedDecayPoison() >> getSpadeEnced()
            >> getRiEncedForest() >> getRotBeastEnced() >> getGrifEncounteredCastle()
            >> getTreeEnced() >> getObeliskEnced() >> getNunEnced() >> getPlayerDeathEnced()
            >> getRotBeastDeathEnced() >> getRotBeastEnced() >> getChoiceCounter() >> getGrifEncounteredOcean()
            >> getDialogue() >> getSpadePoison() >> getValZero() >> getValOne()
            >> getValTwo() >> getValThree() >> getValFour() >> getValFive()
            >> getAttackCounter() >> getZinAttackCounter() >> getThomAttackCounter()
            >> getInitCombatOnce() >> getReInitCombatOnce() >> getCombatEnd()
            >> getTurnPlayer() >> getTurnZin() >> getTurnThom() >> getTurnHostile()
            >> getInitHostileWolf() >> getInitHostileWalker() >> getInitHostileKnight()
            >> getInitHostileTreeMimic() >> getInitHostileLostNun() >> getInitHostileDecapod()
            >> getInitHostileJester() >> getInitHostileWallMimic() >> getInitHostileLostKnight()
            >> getInitHostilePhantom() >> getInitHostileEater() >> getInitHostileSiward()
            >> getInitHostileLimbSplitter() >> getInitHostileBurrower() >> getInitHostileChatterMouth()
            >> getInitHostileReclus() >> getInitHostileTendrilAlpha() >> getInitHostileSpade()
            >> getPlayerAttack() >> getZinAttack() >> getThomAttack() >> getHostileAttack()
            >> getHostileAttackZin() >> getHostileAttackThom() >> getPlayerDead()
            >> getZinDead() >> getThomDead() >> getPlayerPickMove() >> getZinPickMove()
            >> getThomPickMove() >> getComTextRemoved() >> getDecay() >> getDecayMax()
            >> getLevel() >> getExp() >> getExpNext() >> getSp() >> getStrength()
            >> getFortitude() >> getVitality() >> getZinLevel() >> getZinSp()
            >> getZinExp() >> getZinExpNext() >> getZinResolve() >> getZinPatience()
            >> getZinResilience() >> getSwordPower() >> getGold() >> getSmithingStones()
            >> getIncease() >> getFrame() >> getTravel()
            >> getBonfireInit() >> getIntroCounterDialogue() >> getIntroCounter()
            >> getForestCounter() >> getCastleCounter() >> getDecayCounter()
            >> getFrameInit() >> this->unicode >> this->random >> this->test >> this->stop >> this->keyPress >> this->initialized
            >> this->comInitialized >> this->bonfire >> this->mainMenu >> this->statsmenu >> this->buttonClick >> this->xCord >> this->yCord;
        getFrameInit() = false;
        loadData.close();
    }
    

    animate.getNotePosX() = 215;
    animate.getNotePosY() = 145;
    animate.getAnimateString() = "Game Loaded...";
    animate.getDecayWarning() = true;
}

//Draw Functions
void World::draw(sf::RenderWindow& window, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Initial Draw In
    if (getInitialDrawIn() == false) {
        window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr()); //set window icon
        setInitialDrawInTrue();
    }
    // draw everything here...
    if (!this->mainMenu && !getPlayerDeath()) {
        combatTextElapsed = combatTextTime.getElapsedTime();//Reset stats text after 3 seconds
        if (combatTextElapsed.asSeconds() >= 3 && !getComTextRemoved()) {
            text.setString("");
            getComTextRemoved() = true;
        }

        //Allow all hoverables to work
        greyOnHover(window);
        //Draw all initial objects to screen
        drawObjects(window);
        //Allow traveling to work
        travelCore(window, animate);

        //Draw main window
        window.draw(rect);
        window.draw(map);
        window.draw(mapBorder);
        window.draw(playerText);
        window.draw(locationText);
        window.draw(text);

        //Draw Entity Viewer
        window.draw(entityBox);
        window.draw(entitySprite);
        window.draw(entityBoxHeader);
        window.draw(entityBoxText);

        //Draw all sprite border rects and text
        for (int i = 0; i < spriteRect.size(); i++) {
            window.draw(spriteRect[i]);
            window.draw(spriteText[i]);
        }
        //Draw combat elements
        for (int i = 0; i < combatRect.size(); i++) {
            window.draw(combatRect[i]);
            window.draw(combatText[i]);
        }

        //Draw Bonfire Detection Rect
        this->drawBonfire(window, animate);

        //Draw rectangle elements
        for (int i = 0; i < rectElements.size(); i++) {
            window.draw(rectElements[i]);
        }
        //Draw text elements
        for (int i = 0; i < textElements.size(); i++) {
            window.draw(textElements[i]);
        }
        //Draw sprite elements
        for (int i = 0; i < spriteElements.size(); i++) {
            window.draw(spriteElements[i]);
        }

        //Draw Tip Box
        window.draw(tipBox);
        window.draw(tipBoxText);

        //Draw Animations
        window.draw(animate.zinSprite);
        window.draw(animate.decayWarn);
        window.draw(animate.hitSprite);
        window.draw(animate.guardSprite);
        window.draw(animate.guardBrkSprite);

        //Draw Map
        this->drawMap(window);
        //Draw Stats Menu
        this->drawStatsMenu(window);

        if (getInitInventory()) {
            printInventory();
            window.draw(rectInventoryBox);
            window.draw(inventoryText);
        }
    }
    else if (this->mainMenu) {
        playTrack(track8);
        greyOnHover(window);
        animate.animateMenu();
        window.draw(animate.menuSprite);
        drawMainMenu();

        for (int i = 0; i < menuScreenElements.size(); i++) {
            window.draw(menuScreenElements[i]);
        }
        for (int i = 0; i < menuScreenElementsText.size(); i++) {
            window.draw(menuScreenElementsText[i]);
        }
        
        //buttonBoot.draw(window);
        
    }
    else if (getPlayerDeath()) {
        greyOnHover(window);
        drawDeathAssets();
        window.draw(deathText);
        window.draw(menuScreenElements[1]);
        window.draw(menuScreenElements[2]);
        window.draw(menuScreenElementsText[1]);
        window.draw(menuScreenElementsText[2]);
    }

    //Draw User Input Rects
    for (int i = 0; i < answerBox.size(); i++) {
        window.draw(answerBox[i]);
        window.draw(answerBoxText[i]);
    }

    //Draw Settings to screen
    if (getSettingsShown()) {
        drawMainMenu();
        for (int i = 0; i < menuScreenElements.size(); i++) {
            window.draw(menuScreenElements[i]);
        }
        for (int i = 0; i < menuScreenElementsText.size(); i++) {
            window.draw(menuScreenElementsText[i]);
        }
    }
}

void World::drawStatsMenu(sf::RenderWindow& window)
{
    if (getInitStats()) {
        textElapsed = textTime.getElapsedTime();//Reset stats text after 3 seconds
        if (textElapsed.asSeconds() >= 3) {
            text.setString("");
        }
        window.draw(rectStatsBox);
        if (getPlayerStatsInit()) {
            this->printPlayerStats(window);
        }
        else if (getZinStatsInit()) {
            this->printZinStats(window);
        }
        window.draw(rectStatsSideMenu);
        window.draw(playerStatsBoxButtonText);
        window.draw(zinStatsBoxButtonText);
    }
}

void World::drawMap(sf::RenderWindow& window)
{
    if (getInitMap()) {
        //Draw main map rect
        window.draw(rectMap);
        //Choose which map is selected
        switch (getMapCounter()) {
        case 0:
            this->drawForestMap(window);
            break;
        case 1:
            this->drawCastleMap(window);
            break;
        case 2:
            this->drawDecayMap(window);
            break;
        }
        //Make Box Movable if clicked...
        this->movableBox(window);
    }
}

void World::drawBonfire(sf::RenderWindow& window, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (getBonfireAssets()) {
        animate.bonfireAnimations();
        bonfireHealDetectionText.setPosition(mousePos.x - 5.0f, mousePos.y + 15.0f);
        bonfireSmithDetectionText.setPosition(mousePos.x - 5.0f, mousePos.y + 15.0f);
        //Animate Icons
        window.draw(animate.healSprite);
        window.draw(animate.anvilSprite);
        //Healing
        window.draw(bonfireHealDetectionRect);
        window.draw(bonfireHealBorder);
        //Smithing
        window.draw(bonfireSmithDetectionRect);
        window.draw(bonfireSmithBorder);
        //Text
        window.draw(bonfireHealDetectionText);
        window.draw(bonfireSmithDetectionText);
    }
}

//Display Functions
void World::drawMapSelectorButtons(sf::RenderWindow& window)
{
    //Draw all rectangle elements for map button selectors
    for (int i = 0; i < buttonViewMap.size(); i++) {
        window.draw(buttonViewMap[i]);
    }
    //Draw all rectangle elements for map button selectors text
    for (int i = 0; i < buttonViewMapText.size(); i++) {
        window.draw(buttonViewMapText[i]);
    }
}

void World::printPlayerStats(sf::RenderWindow& window)
{
    playerTextElements[4].setString("HP: " + std::to_string(getPlayerHp()) + "/" +
        std::to_string(getPlayerHpMax()) + "\nDECAY: " + std::to_string(getDecay()) + "/" +
        std::to_string(getDecayMax()) + "\n\nSP: " + std::to_string(getSp()) +
        "\nEXP: " + std::to_string(getExp()) + "/" + std::to_string(getExpNext()));

    for (int i = 0; i < playerStatElements.size(); i++) {
        window.draw(playerStatElements[i]);
    }

    for (int i = 0; i < playerTextPlus.size(); i++) {
        window.draw(playerTextPlus[i]);
    }

    for (int i = 0; i < playerTextElements.size(); i++) {
        window.draw(playerTextElements[i]);
    }
}

void World::printZinStats(sf::RenderWindow& window)
{
    zinTextElements[4].setString("HP: " + std::to_string(getZinHp()) + "/" + std::to_string(getZinHpMax()) + "\n\n\nSP: " + std::to_string(getZinSp()) +
        "\nEXP: " + std::to_string(getZinExp()) + "/" + std::to_string(getZinExpNext()));

    for (int i = 0; i < zinStatElements.size(); i++) {
        window.draw(playerStatElements[i]);
    }

    for (int i = 0; i < zinTextPlus.size(); i++) {
        window.draw(zinTextPlus[i]);
    }

    for (int i = 0; i < zinTextElements.size(); i++) {
        window.draw(zinTextElements[i]);
    }
}

void World::printToolTipFunc(sf::RenderWindow& window, sf::RectangleShape& inputRect, std::string& toolTip)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (inputRect.getGlobalBounds().contains(mousePosF)) {
        getTipBoxCounter() = 0;
        tipBoxText.setString(toolTip);
    }
}

void World::printToolTip(sf::RenderWindow& window)
{
    //Print Move Tool Tips
    if (getCombatAssets()) {
        this->printToolTipFunc(window, combatRect[0], getTipSlash());
        this->printToolTipFunc(window, combatRect[1], getTipGuard());
        this->printToolTipFunc(window, combatRect[2], getTipDecay());
        this->printToolTipFunc(window, combatRect[3], getTipHefty());
        this->printToolTipFunc(window, combatRect[4], getTipSynergy());
        this->printToolTipFunc(window, combatRect[5], getTipIronWall());

        this->printToolTipFunc(window, combatRect[6], getTipSmite());
        this->printToolTipFunc(window, combatRect[7], getTipMend());
        this->printToolTipFunc(window, combatRect[8], getTipVengeance());
        this->printToolTipFunc(window, combatRect[9], getTipBlaze());
        this->printToolTipFunc(window, combatRect[10], getTipHeal());
        this->printToolTipFunc(window, combatRect[11], getTipFlames());
    }

    //Print Zin Stat Tool Tips
    if (getZinStatsInit()) {
        this->printToolTipFunc(window, zinStatElements[1], getTipResolve());
        this->printToolTipFunc(window, zinStatElements[2], getTipPatience());
        this->printToolTipFunc(window, zinStatElements[3], getTipResilience());
    }

    //Print Player Stat Tool Tips
    if (getPlayerStatsInit()) {
        this->printToolTipFunc(window, playerStatElements[1], getTipStrength());
        this->printToolTipFunc(window, playerStatElements[2], getTipFortitude());
        this->printToolTipFunc(window, playerStatElements[3], getTipVitality());
    }
}

//Display Element Functionality
void World::mainMenuButtons(sf::RenderWindow& window, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Shared Functionality between both main menu and settings menu
    if (menuScreenElements[2].getGlobalBounds().contains(mousePosF)) {
        //Quit Game Button Functionality
        soundClick.play();
        stop = true;
        return;
    }
    //Main menu specific functionality
    if (!getIntroFinished()) {
        if (menuScreenElements[0].getGlobalBounds().contains(mousePosF)) {
            //Continue to other buttons asking to skip intro or not (New Game Button)
            soundClick.play();
            setBootClickedTrue();
        }
        else if (menuScreenElements[3].getGlobalBounds().contains(mousePosF)) {
            //Intro Button Functionality
            soundClick.play();
            this->mainMenu = false;
            getIntroCounterDialogue() = 0; //Allow the counter to load the main image specifically just for the intro to take place
        }
        else if (menuScreenElements[4].getGlobalBounds().contains(mousePosF)) {
            //Skip Intro Button Functionality
            track8.stop();
            soundClick.play();
            this->mainMenu = false;
            getIntroFinished() = true;
            setMapCounterZero(); //Skip intro and go straight to the forest
        }
    }//Settings specific functionality
    else if (getIntroFinished()) {
        if (menuScreenElements[1].getGlobalBounds().contains(mousePosF)) {
            //Loading Game Button Funcionality
            this->loadGame(animate);
            soundClick.play();
        } else if (menuScreenElements[5].getGlobalBounds().contains(mousePosF)) {
            //Saving Game Button Funcionality 
            this->saveGame(animate);
        }
    }
   
}

void World::travelButtons(sf::RenderWindow& window, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Main View Buttons Control
    if (spriteElements[0].getGlobalBounds().contains(mousePosF))
    {
        setFrameInc();
        setFrameInitFalse();
        blipsound.play();
        //Decay Increases Every Move
        getDecay()++;
        animate.getAnimateString() = "Decay +1";
        animate.getNotePosX() = 1500;
        animate.getNotePosY() = 43;
        animate.getDecayWarning() = true;
        animate.getAnimationFrame() = -1;
    }
    else if (spriteElements[1].getGlobalBounds().contains(mousePosF))
    {
        setFrameDec();
        setFrameInitFalse();
        blipsound.play();
        //Decay Increases Every Move
        getDecay()++;
        animate.getAnimateString() = "Decay +1";
        animate.getNotePosX() = 1500;
        animate.getNotePosY() = 43;
        animate.getDecayWarning() = true;
        animate.getAnimationFrame() = -1;
        //Sound && Music resetting
        getTrackPlayed() = false;
        getAmbTrackPlayed() = false;
    }
}

void World::menuBar(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Map Menu Bar Functionaliy
    if (multiArrow.getGlobalBounds().contains(mousePosF) && buttonClick == false) {
        //Click Multi Arrow to make map movable
        setMovableTrue();
    }
    else if (multiArrow.getGlobalBounds().contains(mousePosF) && buttonClick == false) {
        setMovableStatsBoxTrue();
    }
    if (rectElements[2].getGlobalBounds().contains(mousePosF) && getInitMap() == false) {
        //Click to open map
        setInitMapTrue();
        blipmenu.play();
    }
    else if (rectElements[2].getGlobalBounds().contains(mousePosF) && getInitMap() == true) {
        //Click to close map
        setInitMapFalse();
        setRectMapXVal();
        setRectMapYVal();
        this->resetMapPosition(window);
        blipmenu.play();
        blipmenu.play();
    }
    this->buttonClick = false;
    //Stats Menu Bar Functionality
    if (rectElements[0].getGlobalBounds().contains(mousePosF) && getInitStats() == false) {
        setInitStatsTrue();
        setPlayerStatsInitTrue();
        blipmenu.play();
    }
    else if (rectElements[0].getGlobalBounds().contains(mousePosF) && getInitStats() == true) {
        setInitStatsFalse();
        setPlayerStatsInitFalse();
        setZinStatsInitFalse();
        getTipBoxCounter() = -1;
        blipmenu.play();
    }
    //Inventory Menu Bar Functionality
    if (rectElements[1].getGlobalBounds().contains(mousePosF) && getInitInventory() == false) {
        setInitInventoryTrue();
        blipmenu.play();
    }
    else if (rectElements[1].getGlobalBounds().contains(mousePosF) && getInitInventory() == true) {
        setInitInventoryFalse();
        blipmenu.play();
    }
}

void World::dialogueCombatBox(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Player Combat Buttons Functionality
    pickMove(window);
    
    if (rect.getGlobalBounds().contains(mousePosF) && getShowAnsBoxesCounter() == -1) {
        //If dialogue box is clicked...
        soundClick.play();
        setDialogueCounterInc();
        setFrameInitFalse(); //Allow images to be loaded again
        setIntroCounterDialogueInc();
        setDialogueInc();
        //Increase combat counters with dialogue
        if (getTurnPlayer()) {
            getAttackCounter()++;
        }
        if (getTurnZin()) {
            getZinAttackCounter()++;
        }
        if (getTurnThom()) {
            getThomAttackCounter()++;
        }
        if (getTurnHostile()) {
            getCombatCounter()++;
        }
    }
    else if (getShowAnsBoxesCounter() == 0) {
        if (answerBox[0].getGlobalBounds().contains(mousePosF)) {
            getChoiceCounter() = 0;
            setIntroCounterDialogueInc();
            setDialogueInc();
            soundClick.play();
        }
        else if (answerBox[1].getGlobalBounds().contains(mousePosF)) {
            getChoiceCounter() = 1;
            setIntroCounterDialogueInc();
            setDialogueInc();
            soundClick.play();
        }
    }

}

void World::movableBox(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (getMovable() == true) {
        getRectMapX() = mousePos.x - 365.0f;
        getRectMapY() = mousePos.y - 23.0f;
        this->resetMapPosition(window);
    }
}

//Stat Functionality
void World::statsFunctionality(sf::RenderWindow& window)
{
    //Add Text
    statsText();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Menu Bar Stats Functionality (Switching between who's stats are visible)
    if (playerStatElements[4].getGlobalBounds().contains(mousePosF)) {
        if (getPlayerStatsInit() == false) {
            setPlayerStatsInitTrue();
            setZinStatsInitFalse();
            statSound.play();
        }
    }
    if (zinStatElements[5].getGlobalBounds().contains(mousePosF)) {
        if (getZinStatsInit() == false) {
            setZinStatsInitTrue();
            setPlayerStatsInitFalse();
            statSound.play();
        }
    }

    if (getPlayerStatsInit()) {
        //Call functions for player functionality
        this->levelUp(window, playerStatElements[0], getLevel(), getSp(), getExp(), getExpNext());
        this->statUp(window, playerStatElements[1], getStrength(), getSp(), getExp(), getExpNext());
        this->statUp(window, playerStatElements[2], getFortitude(), getSp(), getExp(), getExpNext());
        this->statUp(window, playerStatElements[3], getVitality(), getSp(), getExp(), getExpNext());
    }
    else if (getZinStatsInit()) {
        //Call functions for Zin functionality
        this->levelUp(window, zinStatElements[0], getZinLevel(), getZinSp(), getZinExp(), getZinExpNext());
        this->statUp(window, zinStatElements[1], getZinResolve(), getZinSp(), getZinExp(), getZinExpNext());
        this->statUp(window, zinStatElements[2], getZinPatience(), getZinSp(), getZinExp(), getZinExpNext());
        this->statUp(window, zinStatElements[3], getZinResilience(), getZinSp(), getZinExp(), getZinExpNext());
    }
}

void World::levelUp(sf::RenderWindow& window, sf::RectangleShape& inputRect, int& lvl, int& sp, int& exp, int& expNext)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (getInitStats()) {
        if (inputRect.getGlobalBounds().contains(mousePosF)) {
            textTime.restart();
            if (exp >= expNext) {
                lvl++;
                sp++;
                exp -= expNext;
                statsText();
                unlockMoves();
                playerTextElements[0].setString("LEVEL " + std::to_string(lvl));
                text.setString("Level up achieved. Level " + std::to_string(lvl) + " reached. One SP point acquired...");
                statSound.play();
            }
            else if (exp <= expNext) {
                text.setString("Required Exp not met...");
            }
            this->buttonClick = true;
        }
    }
}

void World::statUp(sf::RenderWindow& window, sf::RectangleShape& inputRect, int& stat, int& sp, int& exp, int& expNext)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (getInitStats()) {
        if (inputRect.getGlobalBounds().contains(mousePosF)) {
            textTime.restart();
            if (sp >= 1) {
                stat++;
                sp--;
                statsText();
                text.setString("Stat improved...");
                updateStats();
                statSound.play();
            }
            else if (sp <= 0) {
                text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
}

//Map Button Functionality
void World::mapButtons(sf::RenderWindow& window)
{
    this->selectMapView(window);
    //Map Button Functionality (Switching between whch button on the map is selected to change areas...)
    switch (getMapCounter()) {
    case 0:
        this->mapButtonsForest(window);
        break;
    case 1:
        this->mapButtonsCastle(window);
        break;
    case 2:
        this->mapButtonsDecay(window);
        break;
    }
}

void World::mapButtonsForest(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Forest Button Functionality
    if (mapForestElements[0].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getForestCounter() = 0;
        setFrameInitFalse();
        getFrame() = 0; //Ensures whenever you move from area to area on map, player stays on 1st frame
        this->buttonClick = true;
    }
    else if (mapForestElements[1].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getForestCounter() = 1;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
    else if (mapForestElements[2].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getForestCounter() = 2;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
    else if (mapForestElements[3].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getForestCounter() = 3;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
    else if (mapForestElements[4].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getForestCounter() = 4;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
}

void World::mapButtonsCastle(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Castle Button Functionality
    if (mapCastleElements[0].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getCastleCounter() = 0;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
    else if (mapCastleElements[1].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getCastleCounter() = 1;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
    else if (mapCastleElements[2].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getCastleCounter() = 2;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
    else if (mapCastleElements[3].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getCastleCounter() = 3;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
    else if (mapCastleElements[4].getGlobalBounds().contains(mousePosF)) {
        soundWalk.play();
        getCastleCounter() = 4;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
}

void World::mapButtonsDecay(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        //Decay Button Functionality
        if (mapDecayElements[0].getGlobalBounds().contains(mousePosF)) {
            soundWalk.play();
            getDecayCounter() = 0;
            setFrameInitFalse();
            getFrame() = 0;
            this->buttonClick = true;
        }
        else if (mapDecayElements[1].getGlobalBounds().contains(mousePosF)) {
            soundWalk.play();
            getDecayCounter() = 1;
            setFrameInitFalse();
            getFrame() = 0;
            this->buttonClick = true;
        }
        else if (mapDecayElements[2].getGlobalBounds().contains(mousePosF)) {
            soundWalk.play();
            getDecayCounter() = 2;
            setFrameInitFalse();
            getFrame() = 0;
            this->buttonClick = true;
        }
        else if (mapDecayElements[3].getGlobalBounds().contains(mousePosF)) {
            soundWalk.play();
            getDecayCounter() = 3;
            setFrameInitFalse();
            getFrame() = 0;
            this->buttonClick = true;
        }
        else if (mapDecayElements[4].getGlobalBounds().contains(mousePosF)) {
            soundWalk.play();
            getDecayCounter() = 4;
            setFrameInitFalse();
            getFrame() = 0;
            this->buttonClick = true;
        }
}

//Map Functions
void World::resetMapPosition(sf::RenderWindow& window)
{
    //Forest
    forestMapView.setPosition(getRectMapX(), getRectMapY());
    switch (getForestAreaUnlocked()) {
    case 0:
        mapForestElements[0].setPosition(getRectMapX() + 145, getRectMapY() + 25);
        break;
    case 1:
        mapForestElements[0].setPosition(getRectMapX() + 145, getRectMapY() + 25);
        mapForestElements[1].setPosition(getRectMapX() + 34, getRectMapY() + 20);
        break;
    case 2:
        mapForestElements[0].setPosition(getRectMapX() + 145, getRectMapY() + 25);
        mapForestElements[1].setPosition(getRectMapX() + 34, getRectMapY() + 20);
        mapForestElements[2].setPosition(getRectMapX() + 75, getRectMapY() + 240);
        break;
    case 3:
        mapForestElements[0].setPosition(getRectMapX() + 145, getRectMapY() + 25);
        mapForestElements[1].setPosition(getRectMapX() + 34, getRectMapY() + 20);
        mapForestElements[2].setPosition(getRectMapX() + 75, getRectMapY() + 240);
        mapForestElements[3].setPosition(getRectMapX() + 175, getRectMapY() + 200);
        break;
    case 4:
        mapForestElements[0].setPosition(getRectMapX() + 145, getRectMapY() + 25);
        mapForestElements[1].setPosition(getRectMapX() + 34, getRectMapY() + 20);
        mapForestElements[2].setPosition(getRectMapX() + 75, getRectMapY() + 240);
        mapForestElements[3].setPosition(getRectMapX() + 175, getRectMapY() + 200);
        mapForestElements[4].setPosition(getRectMapX() + 240, getRectMapY() + 320);
        break;
    }
    mapForestElementsText[0].setPosition(getRectMapX() + 145, getRectMapY() + 10);
    mapForestElementsText[1].setPosition(getRectMapX() + 34, getRectMapY() + 5);
    mapForestElementsText[2].setPosition(getRectMapX() + 75, getRectMapY() + 225);
    mapForestElementsText[3].setPosition(getRectMapX() + 175, getRectMapY() + 185);
    mapForestElementsText[4].setPosition(getRectMapX() + 240, getRectMapY() + 305);
    //Castle
    spriteMapView.setPosition(getRectMapX(), getRectMapY());
    switch (getCastleAreaUnlocked()) {
    case 0:
        mapCastleElements[0].setPosition(getRectMapX() + 27, getRectMapY() + 322);
        break;
    case 1:
        mapCastleElements[0].setPosition(getRectMapX() + 27, getRectMapY() + 322);
        mapCastleElements[1].setPosition(getRectMapX() + 75, getRectMapY() + 240);
        break;
    case 2:
        mapCastleElements[0].setPosition(getRectMapX() + 27, getRectMapY() + 322);
        mapCastleElements[1].setPosition(getRectMapX() + 75, getRectMapY() + 240);
        mapCastleElements[2].setPosition(getRectMapX() + 34, getRectMapY() + 5);
        break;
    case 3:
        mapCastleElements[0].setPosition(getRectMapX() + 27, getRectMapY() + 322);
        mapCastleElements[1].setPosition(getRectMapX() + 75, getRectMapY() + 240);
        mapCastleElements[2].setPosition(getRectMapX() + 34, getRectMapY() + 5);
        mapCastleElements[3].setPosition(getRectMapX() + 200, getRectMapY() + 20);
        break;
    case 4:
        mapCastleElements[0].setPosition(getRectMapX() + 27, getRectMapY() + 322);
        mapCastleElements[1].setPosition(getRectMapX() + 75, getRectMapY() + 240);
        mapCastleElements[2].setPosition(getRectMapX() + 34, getRectMapY() + 5);
        mapCastleElements[3].setPosition(getRectMapX() + 200, getRectMapY() + 20);
        mapCastleElements[4].setPosition(getRectMapX() + 305, getRectMapY() + 210);
        break;
    }
    mapCastleElementsText[0].setPosition(getRectMapX() + 27, getRectMapY() + 307);
    mapCastleElementsText[1].setPosition(getRectMapX() + 75, getRectMapY() + 225);
    mapCastleElementsText[2].setPosition(getRectMapX() + 34, getRectMapY() + -10);
    mapCastleElementsText[3].setPosition(getRectMapX() + 200, getRectMapY() + 5);
    mapCastleElementsText[4].setPosition(getRectMapX() + 305, getRectMapY() + 195);
    //Decay
    decayMapView.setPosition(getRectMapX(), getRectMapY());
    switch (getDecayAreaUnlocked()) {
    case 0:
        mapDecayElements[0].setPosition(getRectMapX() + 220, getRectMapY() + 215);
        break;
    case 1:
        mapDecayElements[0].setPosition(getRectMapX() + 220, getRectMapY() + 215);
        mapDecayElements[1].setPosition(getRectMapX() + 245, getRectMapY() + 110);
        break;
    case 2:
        mapDecayElements[0].setPosition(getRectMapX() + 220, getRectMapY() + 215);
        mapDecayElements[1].setPosition(getRectMapX() + 245, getRectMapY() + 110);
        mapDecayElements[2].setPosition(getRectMapX() + 200, getRectMapY() + 60);
        break;
    case 3:
        mapDecayElements[0].setPosition(getRectMapX() + 220, getRectMapY() + 215);
        mapDecayElements[1].setPosition(getRectMapX() + 245, getRectMapY() + 110);
        mapDecayElements[2].setPosition(getRectMapX() + 200, getRectMapY() + 60);
        mapDecayElements[3].setPosition(getRectMapX() + 150, getRectMapY() + 40);
        break;
    case 4:
        mapDecayElements[0].setPosition(getRectMapX() + 220, getRectMapY() + 215);
        mapDecayElements[1].setPosition(getRectMapX() + 245, getRectMapY() + 110);
        mapDecayElements[2].setPosition(getRectMapX() + 200, getRectMapY() + 60);
        mapDecayElements[3].setPosition(getRectMapX() + 150, getRectMapY() + 40);
        mapDecayElements[4].setPosition(getRectMapX() + 25, getRectMapY() + 50);
        break;
        
    }
    mapDecayElementsText[0].setPosition(getRectMapX() + 220, getRectMapY() + 200);
    mapDecayElementsText[1].setPosition(getRectMapX() + 245, getRectMapY() + 95);
    mapDecayElementsText[2].setPosition(getRectMapX() + 200, getRectMapY() + 45);
    mapDecayElementsText[3].setPosition(getRectMapX() + 150, getRectMapY() + 25);
    mapDecayElementsText[4].setPosition(getRectMapX() + 25, getRectMapY() + 35);
}

void World::selectMapView(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (buttonViewMap[0].getGlobalBounds().contains(mousePosF)) {
        //Click to view forest from map selector buttons
        setMapCounterZero();
        this->resetMapPosition(window);

        getFrame() = 0;
        soundWalk.play();
        getForestCounter() = 0;
        setFrameInitFalse();
        getFrame() = 0;
        this->buttonClick = true;
    }
    else if (buttonViewMap[1].getGlobalBounds().contains(mousePosF)) {
        //Click to view castle from map selector buttons
        setMapCounterOne();
        this->resetMapPosition(window);

        getFrame() = 0;
        soundWalk.play();
        getCastleCounter() = 0;
        setFrameInitFalse();
        this->buttonClick = true;
    }
    else if (buttonViewMap[2].getGlobalBounds().contains(mousePosF)) {
        //Click to view decay from map selector buttons
        setMapCounterTwo();
        this->resetMapPosition(window);

        getFrame() = 0;
        soundWalk.play();
        getDecayCounter() = 0;
        setFrameInitFalse();
        this->buttonClick = true;
    }
}

void World::drawForestMap(sf::RenderWindow& window)
{
    window.draw(forestMapView);
    window.draw(multiArrow);
    this->drawMapSelectorButtons(window);
    for (int i = 0; i < mapForestElements.size(); i++) {
        window.draw(mapForestElements[i]);
    }

    for (int i = 0; i < mapForestElementsText.size(); i++) {
        window.draw(mapForestElementsText[i]);
    }
}

void World::drawCastleMap(sf::RenderWindow& window)
{
    //Draw Everything
    window.draw(spriteMapView);
    window.draw(multiArrow);
    this->drawMapSelectorButtons(window);
    for (int i = 0; i < mapCastleElements.size(); i++) {
        window.draw(mapCastleElements[i]);
    }

    for (int i = 0; i < mapCastleElementsText.size(); i++) {
        window.draw(mapCastleElementsText[i]);
    }
}

void World::drawDecayMap(sf::RenderWindow& window)
{
    //Draw Everything
    window.draw(decayMapView);
    window.draw(multiArrow);
    this->drawMapSelectorButtons(window);
    for (int i = 0; i < mapDecayElements.size(); i++) {
        window.draw(mapDecayElements[i]);
    }

    for (int i = 0; i < mapDecayElementsText.size(); i++) {
        window.draw(mapDecayElementsText[i]);
    }
}