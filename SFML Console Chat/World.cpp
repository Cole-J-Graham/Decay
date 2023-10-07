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
void World::bootUp(Assets& assets, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate)
{
    //Load SFX
    assets.loadSFX();
    //create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Console Chat"/*, sf::Style::Fullscreen */ );
    window.setFramerateLimit(144);
    // run the program as long as the window is open
    while (window.isOpen()) {
        std::cout << clock.getElapsedTime().asMicroseconds() << "\n";
        clock.restart();
        clickTime.restart();
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            switch (event.type) { // Close Window on Closed Event
            case sf::Event::Closed:
                this->stop = true;
                window.close();
                break;
            case sf::Event::MouseMoved:
                { //Mouse Hover Actions
                    //Turn buttons grey on hover
                    this->greyOnHover(window, assets);
                    this->printToolTip(window, assets, notevent, combat, player);
                }
                break;
            case sf::Event::MouseButtonPressed:
                { //Get Mouse Click Input
                    this->travelButtons(window, assets, travel);
                    //If button in map is clicked, do something
                    if (!assets.getPlayerDeath() && assets.getInitMap()) {
                        this->mapButtons(window, assets, travel);
                    }
                    //Map Menu Bar Functionality
                    this->menuBarStats(window, combat, player, assets); //Must be loaded before menuBar(window); to withhold functionality
                    this->menuBar(window, assets);
                    //Dialogue Box Functionality
                    this->dialogueCombatBox(window, combat, assets, travel, notevent);
                    //Main Menu Functionality
                    this->mainMenuButtons(window, assets, travel, animate);
                    if (stop) { //Make quit button return to main function to stop program from running
                        return;
                    }
                    //Bonfire Functionality
                    if (assets.getBonfireAssets() == true) {
                        notevent.healCharacters(window, assets, combat);
                        notevent.smithingSharpenBlade(window, assets, player);
                        notevent.zinEvents(window, assets, animate);
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                {
                    assets.setMovableFalse();
                    assets.setMovableStatsBoxFalse();
                }
            case sf::Event::KeyPressed:
                {
                this->userInput(assets);
                }
                break;
            }
            //Run Main Function Loop...
            this->mainLoop(assets, notevent, combat, player, travel, animate);
        }
        //Draw Everything...
        this->Draw(window, assets, notevent, combat, player, travel, animate);
    }
}

void World::mainLoop(Assets& assets, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate)
{
    //Run Main Functions
    travel.travelCore(window, assets, notevent, combat, player, animate);
}

//User Input
void World::userInput(Assets& assets)
{
    //Get user input for keyboard inputs
    assets.font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    assets.playerText.setFont(assets.font);
    assets.playerText.setCharacterSize(18);
    assets.playerText.setFillColor(sf::Color::White);
    assets.playerText.setPosition(0, 950);
    
    playerInput += event.text.unicode;
    input = event.text.unicode;
    unicode = event.text.unicode;

    //Getting user input for settings
    if (unicode == 36) {
        assets.soundClick.play();
        //Make settings appear (Basically the main menu with some additions....)
        if (!assets.getSettingsShown()) {
            assets.getSettingsShown() = true;
        }
        else if (assets.getSettingsShown()){
            assets.getSettingsShown() = false;
        }
    }
}

void World::clearInput()
{
    //this->unicode = -1;
    //playerInput = "";
    //return;
}

//Display Functions
void World::Draw(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Initial Draw In
    if (assets.getInitialDrawIn() == false) {
        assets.windowIcon.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/shieldicon.jpeg");
        window.setIcon(assets.windowIcon.getSize().x, assets.windowIcon.getSize().y, assets.windowIcon.getPixelsPtr()); //set window icon
        assets.setInitialDrawInTrue();
    }
    // clear the window with black color
    window.clear(sf::Color::Black);

    // draw everything here...
    if (this->mainMenu == false && !assets.getPlayerDeath()) {
        assets.drawObjects();
        travel.travelCore(window, assets, notevent, combat, player, animate);

        window.draw(assets.rect);
        window.draw(assets.map);
        window.draw(assets.playerText);
        window.draw(assets.locationText);
        window.draw(assets.text);

        //Draw Entity Viewer
        window.draw(assets.entityBox);
        window.draw(assets.entitySprite);
        window.draw(assets.entityBoxHeader);
        window.draw(assets.entityBoxText);

        //Draw all sprite border rects and text
        for (int i = 0; i < assets.spriteRect.size(); i++) {
            window.draw(assets.spriteRect[i]);
            window.draw(assets.spriteText[i]);
        }

        for (int i = 0; i < assets.combatRect.size(); i++) {
            window.draw(assets.combatRect[i]);
            window.draw(assets.combatText[i]);
        }

        //Draw Bonfire Detection Rect
        if (travel.getBonfireInit() == true) {
            assets.bonfireHealDetectionText.setPosition(mousePos.x - 5, mousePos.y + 15);
            assets.bonfireSmithDetectionText.setPosition(mousePos.x - 5, mousePos.y + 15);
            //Healing
            window.draw(assets.bonfireHealDetectionRect);
            window.draw(assets.bonfireHealDetectionText);
            //Smithing
            window.draw(assets.bonfireSmithDetectionRect);
            window.draw(assets.bonfireSmithDetectionText);
        }

        //Draw all rectangle elements
        for (int i = 0; i < assets.rectElements.size(); i++) {
            window.draw(assets.rectElements[i]);
        }
        //Draw all text elements
        for (int i = 0; i < assets.textElements.size(); i++) {
            window.draw(assets.textElements[i]);
        }
        //Draw all sprite elements
        for (int i = 0; i < assets.spriteElements.size(); i++) {
            window.draw(assets.spriteElements[i]);
        }

        //Draw Tip Box
        window.draw(assets.tipBox);
        window.draw(assets.tipBoxText);

        //Draw Animations
        animate.drawAnimations();
        window.draw(animate.zinSprite);
        window.draw(animate.notSprite);

        if (assets.getInitMap() == true) {
            //Draw main map rect
            window.draw(assets.rectMap);
            //Choose which map is selected
            switch (assets.getMapCounter()) {
            case 0:
                this->drawForestMap(window, assets);
                break;
            case 1:
                this->drawCastleMap(window, assets);
                break;
            case 2:
                this->drawDecayMap(window, assets);
                break;
            }
            //Make Box Movable if clicked...
            this->movableBox(window, assets);
        }

        if (assets.getInitStats() == true) {
            window.draw(assets.rectStatsBox);
            if (assets.getPlayerStatsInit() == true) {
                this->printPlayerStats(window, assets, notevent, combat, player);
            }
            else if (assets.getZinStatsInit() == true) {
                this->printZinStats(window, assets, notevent, combat, player);
            }
            window.draw(assets.rectStatsSideMenu);
            window.draw(assets.playerStatsBoxButtonText);
            window.draw(assets.zinStatsBoxButtonText);
        }
        if (assets.getInitInventory() == true) {
            player.printInventory(assets);
            window.draw(assets.rectInventoryBox);
            window.draw(assets.inventoryText);
        }
    }
    else if (this->mainMenu == true) {
        assets.drawMainMenu();
        for (int i = 0; i < assets.menuScreenElements.size(); i++) {
            window.draw(assets.menuScreenElements[i]);
        }
        for (int i = 0; i < assets.menuScreenElementsText.size(); i++) {
            window.draw(assets.menuScreenElementsText[i]);
        }
    }
    else if (assets.getPlayerDeath()) {
        assets.drawDeathAssets();
        window.draw(assets.deathText);
        window.draw(assets.menuScreenElements[1]);
        window.draw(assets.menuScreenElements[2]);
        window.draw(assets.menuScreenElementsText[1]);
        window.draw(assets.menuScreenElementsText[2]);
    }

    //Draw User Input Rects
    for (int i = 0; i < assets.answerBox.size(); i++) {
        window.draw(assets.answerBox[i]);
        window.draw(assets.answerBoxText[i]);
    }

    //Draw Settings to screen
    if (assets.getSettingsShown()) {
        assets.drawMainMenu();
        for (int i = 0; i < assets.menuScreenElements.size(); i++) {
            window.draw(assets.menuScreenElements[i]);
        }
        for (int i = 0; i < assets.menuScreenElementsText.size(); i++) {
            window.draw(assets.menuScreenElementsText[i]);
        }
    }

    // end the current frame
    window.display();
}

void World::DrawMapSelectorButtons(sf::RenderWindow& window, Assets& assets)
{
    //Draw all rectangle elements for map button selectors
    for (int i = 0; i < assets.buttonViewMap.size(); i++) {
        window.draw(assets.buttonViewMap[i]);
    }
    //Draw all rectangle elements for map button selectors text
    for (int i = 0; i < assets.buttonViewMapText.size(); i++) {
        window.draw(assets.buttonViewMapText[i]);
    }
}

void World::greyOnHover(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Turn Rects Grey On Hover
    for (int i = 0; i < assets.rectElements.size(); i++) {
        if (assets.rectElements[i].getGlobalBounds().contains(mousePosF)) {
            assets.rectElements[i].setFillColor(sf::Color::Transparent);
            assets.textElements[i].setFillColor(sf::Color::White);
        }
        else {
            assets.rectElements[i].setFillColor(sf::Color::White);
            assets.textElements[i].setFillColor(sf::Color::Black);
        }
    }

    //Turn dialogue box grey on hover
    if (assets.rect.getGlobalBounds().contains(mousePosF) && assets.getShowAnsBoxesCounter() == -1) {
        assets.rect.setFillColor(sf::Color(10, 10, 10));
    }
    else {
        assets.rect.setFillColor(sf::Color::Black);
    }

    for (int i = 0; i < assets.answerBox.size(); i++) {
        if (assets.answerBox[i].getGlobalBounds().contains(mousePosF)) {
            assets.answerBox[i].setFillColor(sf::Color(25, 25, 25));
        }
        else {
            assets.answerBox[i].setFillColor(sf::Color::Black);
        }
    }

    //Main Menu Buttons Grey On Hover
    for (int i = 0; i < assets.menuScreenElements.size(); i++) {
        if (assets.menuScreenElements[i].getGlobalBounds().contains(mousePosF)) {
            assets.menuScreenElements[i].setFillColor(sf::Color::Transparent);
            assets.menuScreenElementsText[i].setFillColor(sf::Color::White);
        }
        else {
            assets.menuScreenElements[i].setFillColor(sf::Color::White);
            assets.menuScreenElementsText[i].setFillColor(sf::Color::Black);
        }
    }

    //Combat Rects Grey On Hover
    for (int i = 0; i < assets.combatRect.size(); i++) {
        if (assets.combatRect[i].getGlobalBounds().contains(mousePosF)) {
            assets.combatRect[i].setFillColor(sf::Color::Transparent);
            assets.combatText[i].setFillColor(sf::Color::White);
        }
        else {
            assets.combatRect[i].setFillColor(sf::Color::White);
            assets.combatText[i].setFillColor(sf::Color::Black);
        }
    }

    //Sprites Grey On Hover
    for (int i = 0; i < assets.spriteElements.size(); i++) {
        if (assets.spriteElements[i].getGlobalBounds().contains(mousePosF)) {
            assets.spriteElements[i].setColor(sf::Color(155, 155, 155));
        }
        else {
            assets.spriteElements[i].setColor(sf::Color(255, 255, 255));
        }
    }

    //Player Stats Grey On Hover
    for (int i = 0; i < assets.playerStatElements.size(); i++) {
        if (assets.playerStatElements[i].getGlobalBounds().contains(mousePosF)) {
            assets.playerStatElements[i].setFillColor(sf::Color::Black);
            assets.playerTextElements[i].setFillColor(sf::Color::White);
        }
        else {
            assets.playerStatElements[i].setFillColor(sf::Color::Black);
            assets.playerTextElements[i].setFillColor(sf::Color(5, 5, 5));
        }
    }

    //Zin Stats Grey On Hover
    for (int i = 0; i < assets.zinStatElements.size(); i++) {
        if (assets.zinStatElements[i].getGlobalBounds().contains(mousePosF)) {
            assets.zinStatElements[i].setFillColor(sf::Color::Transparent);
            assets.zinTextElements[i].setFillColor(sf::Color::White);
        }
        else {
            assets.zinStatElements[i].setFillColor(sf::Color::White);
            assets.zinTextElements[i].setFillColor(sf::Color::Black);
        }
    }

    //Map Selector Buttons Grey On Hover
    for (int i = 0; i < assets.buttonViewMap.size(); i++) {
        if (assets.buttonViewMap[i].getGlobalBounds().contains(mousePosF)) {
            assets.buttonViewMap[i].setFillColor(sf::Color::White);
            assets.buttonViewMapText[i].setFillColor(sf::Color::Black);
        }
        else {
            assets.buttonViewMap[i].setFillColor(sf::Color::Black);
            assets.buttonViewMapText[i].setFillColor(sf::Color::White);
        }
    }
    //Map Buttons Grey On Hover
    for (int i = 0; i < assets.mapCastleElements.size(); i++) {
        if (assets.mapCastleElements[i].getGlobalBounds().contains(mousePosF)) {
            assets.mapCastleElements[i].setColor(sf::Color(155, 155, 155));
        }
        else {
            assets.mapCastleElements[i].setColor(sf::Color(255, 255, 255));
        }
    }

    for (int i = 0; i < assets.mapForestElements.size(); i++) {
        if (assets.mapForestElements[i].getGlobalBounds().contains(mousePosF)) {
            assets.mapForestElements[i].setColor(sf::Color(155, 155, 155));
        }
        else {
            assets.mapForestElements[i].setColor(sf::Color(255, 255, 255));
        }
    }

    for (int i = 0; i < assets.mapDecayElements.size(); i++) {
        if (assets.mapDecayElements[i].getGlobalBounds().contains(mousePosF)) {
            assets.mapDecayElements[i].setColor(sf::Color(155, 155, 155));
        }
        else {
            assets.mapDecayElements[i].setColor(sf::Color(255, 255, 255));
        }
    }
}

void World::printPlayerStats(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    assets.playerTextElements[10].setString("HP: " + std::to_string(combat.getPlayerHp()) + "/" +
        std::to_string(combat.getPlayerHpMax()) + "\nDECAY: " + std::to_string(player.getDecay()) + "/" +
        std::to_string(player.getDecayMax()) + "\n\nSP: " + std::to_string(player.getSp()) +
        "\nEXP: " + std::to_string(player.getExp()) + "/" + std::to_string(player.getExpNext()));

    for (int i = 0; i < assets.playerStatElements.size(); i++) {
        window.draw(assets.playerStatElements[i]);
    }

    for (int i = 0; i < assets.playerTextElements.size(); i++) {
        window.draw(assets.playerTextElements[i]);
    }
}

void World::printZinStats(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    assets.zinTextElements[10].setString("HP: " + std::to_string(combat.getZinHp()) + "/" + std::to_string(combat.getZinHpMax()) + "\n\n\nSP: " + std::to_string(player.getZinSp()) +
        "\nEXP: " + std::to_string(player.getZinExp()) + "/" + std::to_string(player.getZinExpNext()));

    for (int i = 0; i < assets.zinStatElements.size(); i++) {
        window.draw(assets.playerStatElements[i]);
    }

    for (int i = 0; i < assets.zinTextElements.size(); i++) {
        window.draw(assets.zinTextElements[i]);
    }
}

void World::printToolTip(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Player Combat Buttons Functionality
    if (assets.getPlayerStatsInit()) {
        if (assets.playerStatElements[1].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("STRENGTH:\nMeasures the players raw power.\n\nIncreases all attack moves damage.");
        }
        else if (assets.playerStatElements[2].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("FORTITUDE:\nMeasures the players survivability against decay.\n\nHigher fortitude makes the player more \nresistant to the decay.");
        }
        else if (assets.playerStatElements[3].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("VITALITY:\nMeasures the players health.\n\nHigh vitality allows the player to take a beating\nin combat.");
        }
        else {
            assets.getTipBoxCounter() = -1;
        }
    }
    else if (assets.getZinStatsInit()) {
        if (assets.zinStatElements[1].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("RESOLVE:\nMeasures Zin's spells raw power.\n\nIncreases the damage of her lightning \nspells specifically.");
        }
        else if (assets.zinStatElements[2].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("PATIENCE:\nMeasures Zin's healing capabilities.\n\nHigh patience makes her heal \nsignificantly more.");
        }
        else if (assets.zinStatElements[3].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("RESILIENCE:\nMeasures Zin's health.\n\nHigh resilience allows Zin to take more \nhits and survive.");
        }
        else {
            assets.getTipBoxCounter() = -1;
        }
    }
    
    if (assets.getCombatAssets()) {
        if (assets.combatRect[0].getGlobalBounds().contains(mousePosF)) { //If attack button is clicked...
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("SLASH:\nThe players basic attack for inflicting damage...");
        }
        else if (assets.combatRect[1].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("GUARD:\nUses the players turn to protect Zin from \nALL damage...");
        }
        else if (assets.combatRect[2].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("DECAYED BLADE:\nThe player slashes his own skin open to use the \ndecay in his blood as a weapon...\n\nInflicts extra damage due to decayed blood...");
        }
        //Zin Combat Buttons Functionality
        else if (assets.combatRect[3].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("SMITE:\nZin's basic attack, inflicts damage on the \nopponent...");
        }
        else if (assets.combatRect[4].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("MEND:\nHeals the player and Zin...");
        }
        else if (assets.combatRect[5].getGlobalBounds().contains(mousePosF)) {
            assets.getTipBoxCounter() = 0;
            assets.tipBoxText.setString("VENGEANCE:\nUse Zin's rage and sorrow to turn the players\nblood into sharpened blades that hurdle\ntowards the enemy...\n\nInflicts damage equal to the players current \nlost health...");
        }
        else {
            assets.getTipBoxCounter() = -1;
        }
    }
}

//Display Element Functionality
void World::mainMenuButtons(sf::RenderWindow& window, Assets& assets, Travel& travel, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Shared Functionality between both main menu and settings menu
    if (assets.menuScreenElements[1].getGlobalBounds().contains(mousePosF)) {
        //Loading Game Button Funcionality (Not implemented yet...)
        std::cout << "Loading a save hypothetically speaking lmao...";
    }
    else if (assets.menuScreenElements[2].getGlobalBounds().contains(mousePosF)) {
        //Quit Game Button Functionality
        stop = true;
        return;
    }
    //Main menu specific functionality
    if (!assets.getIntroFinished()) {
        if (assets.menuScreenElements[0].getGlobalBounds().contains(mousePosF)) {
            //Continue to other buttons asking to skip intro or not (New Game Button)
            assets.setBootClickedTrue();
        }
        else if (assets.menuScreenElements[3].getGlobalBounds().contains(mousePosF)) {
            //Intro Button Functionality
            this->mainMenu = false;
            travel.getIntroCounterDialogue() = 0; //Allow the counter to load the main image specifically just for the intro to take place
        }
        else if (assets.menuScreenElements[4].getGlobalBounds().contains(mousePosF)) {
            //Skip Intro Button Functionality
            this->mainMenu = false;
            assets.getIntroFinished() = true;
            assets.setMapCounterZero(); //Skip intro and go straight to the forest
        }
    }//Settings specific functionality
    else if (assets.getIntroFinished()) {
        if (assets.menuScreenElements[5].getGlobalBounds().contains(mousePosF)) {
            //Saving Game Button Funcionality (Not implemented yet...)
            std::cout << "Saving game hypothetically speaking...";
        }
    }
   
}

void World::travelButtons(sf::RenderWindow& window, Assets& assets, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Main View Buttons Control
    if (assets.spriteElements[0].getGlobalBounds().contains(mousePosF))
    {
        travel.setFrameInc();
        travel.setFrameInitFalse();
        assets.blipsound.play();
    }
    else if (assets.spriteElements[1].getGlobalBounds().contains(mousePosF))
    {
        travel.setFrameDec();
        travel.setFrameInitFalse();
        assets.blipsound.play();
    }
}

void World::menuBar(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Map Menu Bar Functionaliy
    if (assets.multiArrow.getGlobalBounds().contains(mousePosF) && buttonClick == false) {
        //Click Multi Arrow to make map movable
        assets.setMovableTrue();
    }
    else if (assets.multiArrow.getGlobalBounds().contains(mousePosF) && buttonClick == false) {
        assets.setMovableStatsBoxTrue();
    }
    if (assets.rectElements[2].getGlobalBounds().contains(mousePosF) && assets.getInitMap() == false) {
        //Click to open map
        assets.setInitMapTrue();
        assets.blipmenu.play();
    }
    else if (assets.rectElements[2].getGlobalBounds().contains(mousePosF) && assets.getInitMap() == true) {
        //Click to close map
        assets.setInitMapFalse();
        assets.setRectMapXVal();
        assets.setRectMapYVal();
        this->resetMapPosition(window, assets);
        assets.blipmenu.play();
        assets.blipmenu.play();
    }
    this->buttonClick = false;
    //Stats Menu Bar Functionality
    if (assets.rectElements[0].getGlobalBounds().contains(mousePosF) && assets.getInitStats() == false) {
        assets.setInitStatsTrue();
        assets.setPlayerStatsInitTrue();
        assets.blipmenu.play();
    }
    else if (assets.rectElements[0].getGlobalBounds().contains(mousePosF) && assets.getInitStats() == true) {
        assets.setInitStatsFalse();
        assets.setPlayerStatsInitFalse();
        assets.setZinStatsInitFalse();
        assets.blipmenu.play();
    }
    //Inventory Menu Bar Functionality
    if (assets.rectElements[1].getGlobalBounds().contains(mousePosF) && assets.getInitInventory() == false) {
        assets.setInitInventoryTrue();
        assets.blipmenu.play();
    }
    else if (assets.rectElements[1].getGlobalBounds().contains(mousePosF) && assets.getInitInventory() == true) {
        assets.setInitInventoryFalse();
        assets.blipmenu.play();
    }
}

void World::menuBarStats(sf::RenderWindow& window, Combat& combat, Player& player, Assets& assets)
{
    //Add Text
    player.statsText(assets);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Menu Bar Stats Functionality (Switching between who's stats are visible)
    if (assets.playerStatElements[4].getGlobalBounds().contains(mousePosF) || assets.zinStatElements[4].getGlobalBounds().contains(mousePosF)) {
        if (assets.getPlayerStatsInit() == false) {
            assets.setPlayerStatsInitTrue();
            assets.setZinStatsInitFalse();
        }
    }
    if (assets.playerStatElements[5].getGlobalBounds().contains(mousePosF) || assets.zinStatElements[4].getGlobalBounds().contains(mousePosF)) {
        if (assets.getZinStatsInit() == false) {
            assets.setZinStatsInitTrue();
            assets.setPlayerStatsInitFalse();
        }
    }
    //Level Up Functionality
    if (assets.getInitStats() == true && assets.getPlayerStatsInit() == true) {
        if (assets.playerStatElements[0].getGlobalBounds().contains(mousePosF)) {
            if (player.getExp() >= player.getExpNext()) {
                player.setLevelInc();
                player.setSpInc();
                player.getExp() -= player.getExpNext();
                assets.playerTextElements[4].setString("LEVEL " + std::to_string(player.getLevel()));
                assets.text.setString("Level up achieved. Level " + std::to_string(player.getLevel()) + " reached. One SP point acquired...");
                combat.updateStats(assets, player);
            }
            else if (player.getExp() <= player.getExpNext()) {
                assets.text.setString("Required Exp not met...");
            }
            this->buttonClick = true;
        }
    }

    //Strength up functionality
    if (assets.getInitStats() == true && assets.getPlayerStatsInit() == true) {
        if (assets.playerStatElements[1].getGlobalBounds().contains(mousePosF)) {
            if (player.getSp() >= 1) {
                player.setStrengthInc();
                player.setSpDec();
                assets.playerTextElements[5].setString("STRENGTH " + std::to_string(player.getStrength()));
                assets.text.setString("Strength improved. Level " + std::to_string(player.getStrength()) + " in strength reached. One SP point spent...");
                combat.updateStats(assets, player);
            }
            else if (player.getSp() <= 0) {
                assets.text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
    //Fortitude up functionality
    if (assets.getInitStats() == true && assets.getPlayerStatsInit() == true) {
        if (assets.playerStatElements[2].getGlobalBounds().contains(mousePosF)) {
            if (player.getSp() >= 1) {
                player.setFortitudeInc();
                player.setSpDec();
                assets.playerTextElements[6].setString("FORTITUDE " + std::to_string(player.getFortitude()));
                assets.text.setString("Fortitude improved. Level " + std::to_string(player.getFortitude()) + " in fortitude reached. One SP point spent...");
                combat.updateStats(assets, player);
            }
            else if (player.getSp() <= 0) {
                assets.text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
    //Vitality up functionality
    if (assets.getInitStats() == true && assets.getPlayerStatsInit() == true) {
        if (assets.playerStatElements[3].getGlobalBounds().contains(mousePosF)) {
            if (player.getSp() >= 1) {
                player.setVitalityInc();
                player.setSpDec();
                combat.getPlayerHp() += player.getVitality();
                combat.getPlayerHpMax() = combat.getPlayerHp();
                assets.playerTextElements[7].setString("VITALITY " + std::to_string(player.getVitality()));
                assets.text.setString("Vitality improved. Level " + std::to_string(player.getVitality()) + " in vitality reached. One SP point spent...");
                combat.updateStats(assets, player);
            }
            else if (player.getSp() <= 0) {
                assets.text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Stats Level up Functionality
    if (assets.getInitStats() == true && assets.getZinStatsInit() == true) {
        if (assets.zinStatElements[0].getGlobalBounds().contains(mousePosF)) {
            if (player.getZinExp() >= player.getZinExpNext()) {
                player.setZinLevelInc();
                player.setZinSpInc();
                player.getZinExp() -= player.getZinExpNext();
                assets.zinTextElements[4].setString("LEVEL " + std::to_string(player.getZinLevel()));
                assets.text.setString("Level up achieved. Level " + std::to_string(player.getZinLevel()) + " reached for Zin. One SP point acquired...");
                combat.updateStatsZin(player);
            }
            else if (player.getZinExp() <= player.getZinExpNext()) {
                assets.text.setString("Zin's required Exp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Resolve up Functionality
    if (assets.getInitStats() == true && assets.getZinStatsInit() == true) {
        if (assets.zinStatElements[1].getGlobalBounds().contains(mousePosF)) {
            if (player.getZinSp() >= 1) {
                player.setZinResolveInc();
                player.setZinSpDec();
                assets.zinTextElements[5].setString("RESOLVE " + std::to_string(player.getZinResolve()));
                assets.text.setString("Zin's resolve increased. Level " + std::to_string(player.getZinResolve()) + " reached in resolve for Zin. One SP point spent...");
                combat.updateStatsZin(player);
            }
            else if (player.getZinExp() <= 0) {
                assets.text.setString("Zin's required Sp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Patience up Functionality
    if (assets.getInitStats() == true && assets.getZinStatsInit() == true) {
        if (assets.zinStatElements[2].getGlobalBounds().contains(mousePosF)) {
            if (player.getZinSp() >= 1) {
                player.setZinPatienceInc();
                player.setZinSpDec();
                assets.zinTextElements[6].setString("PATIENCE " + std::to_string(player.getZinPatience()));
                assets.text.setString("Zin's patience increased. Level " + std::to_string(player.getZinPatience()) + " reached in patience for Zin. One SP point spent...");
                combat.updateStatsZin(player);
            }
            else if (player.getZinExp() <= 0) {
                assets.text.setString("Zin's required Sp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Resilience up Functionality
    if (assets.getInitStats() == true && assets.getZinStatsInit() == true) {
        if (assets.zinStatElements[3].getGlobalBounds().contains(mousePosF)) {
            if (player.getZinSp() >= 1) {
                player.setZinResilienceInc();
                player.setZinSpDec();
                assets.zinTextElements[7].setString("RESILIENCE " + std::to_string(player.getZinResilience()));
                assets.text.setString("Zin's resilience increased. Level " + std::to_string(player.getZinResilience()) + " reached in resilience for Zin. One SP point spent...");
                combat.updateStatsZin(player);
            }
            else if (player.getZinExp() <= 0) {
                assets.text.setString("Zin's required Sp not met...");
            }
            this->buttonClick = true;
        }
    }
}

void World::dialogueCombatBox(sf::RenderWindow& window, Combat& combat, Assets& assets, Travel& travel, Event& notevent)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Player Combat Buttons Functionality
    if (assets.combatRect[0].getGlobalBounds().contains(mousePosF)) { //If attack button is clicked...
        if (combat.getTurnPlayer() == true) {
            combat.setAttackCounterInc();
            combat.getPlayerPickMove() = 0;
        }
    }
    if (assets.combatRect[1].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnPlayer() == true) {
            combat.setAttackCounterInc();
            combat.getPlayerPickMove() = 1;
        }
    }
    if (assets.combatRect[2].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnPlayer() == true) {
            combat.setAttackCounterInc();
            combat.getPlayerPickMove() = 2;
        }
    }
    //Zin Combat Buttons Functionality
    if (assets.combatRect[3].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnZin() == true) {
            combat.setZinAttackCounterInc();
            combat.getZinPickMove() = 0;
        }
    }
    if (assets.combatRect[4].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnZin() == true) {
            combat.setZinAttackCounterInc();
            combat.getZinPickMove() = 1;
        }
    }
    if (assets.combatRect[5].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnZin() == true) {
            combat.setZinAttackCounterInc();
            combat.getZinPickMove() = 2;
        }
    }
    else if (assets.rect.getGlobalBounds().contains(mousePosF) && assets.getShowAnsBoxesCounter() == -1) {
        //If dialogue box is clicked...
        assets.soundClick.play();
        assets.setDialogueCounterInc();
        travel.setFrameInitFalse(); //Allow images to be loaded again
        travel.setIntroCounterDialogueInc();
        notevent.setDialogueInc();
        if (combat.getAttackCounter() == 1) {
            combat.getAttackCounter() = 2;
        }
        if (combat.getZinAttackCounter() == 1) {
            combat.getZinAttackCounter() = 2;
        }
        if (combat.getTurnHostile() == true) {
            assets.setCombatCounterInc();
        }
        assets.setSpadeInitFalse();
    }
    else if (assets.getShowAnsBoxesCounter() == 0) {
        if (assets.answerBox[0].getGlobalBounds().contains(mousePosF)) {
            assets.getChoiceCounter() = 0;
            travel.setIntroCounterDialogueInc();
            notevent.setDialogueInc();
            assets.soundClick.play();
        }
        else if (assets.answerBox[1].getGlobalBounds().contains(mousePosF)) {
            assets.getChoiceCounter() = 1;
            travel.setIntroCounterDialogueInc();
            notevent.setDialogueInc();
            assets.soundClick.play();
        }
    }

}

void World::movableBox(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (assets.getMovable() == true) {
        assets.getRectMapX() = mousePos.x - 365;
        assets.getRectMapY() = mousePos.y - 23;
        this->resetMapPosition(window, assets);
    }
}

//Map Button Functionality
void World::mapButtons(sf::RenderWindow& window, Assets& assets, Travel& travel)
{
    this->selectMapView(window, assets, travel);
    //Map Button Functionality (Switching between whch button on the map is selected to change areas...)
    switch (assets.getMapCounter()) {
    case 0:
        this->mapButtonsForest(window, assets, travel);
        break;
    case 1:
        this->mapButtonsCastle(window, assets, travel);
        break;
    case 2:
        this->mapButtonsDecay(window, assets, travel);
        break;
    }
}

void World::mapButtonsForest(sf::RenderWindow& window, Assets& assets, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Forest Button Functionality
    if (assets.mapForestElements[0].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getForestCounter() = 0;
        travel.setFrameInitFalse();
        travel.getFrame() = 0; //Ensures whenever you move from area to area on map, player stays on 1st frame
        this->buttonClick = true;
    }
    else if (assets.mapForestElements[1].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getForestCounter() = 1;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (assets.mapForestElements[2].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getForestCounter() = 2;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (assets.mapForestElements[3].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getForestCounter() = 3;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (assets.mapForestElements[4].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getForestCounter() = 4;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
}

void World::mapButtonsCastle(sf::RenderWindow& window, Assets& assets, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Castle Button Functionality
    if (assets.mapCastleElements[0].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getCastleCounter() = 0;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (assets.mapCastleElements[1].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getCastleCounter() = 1;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (assets.mapCastleElements[2].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getCastleCounter() = 2;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (assets.mapCastleElements[3].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getCastleCounter() = 3;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (assets.mapCastleElements[4].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.getCastleCounter() = 4;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
}

void World::mapButtonsDecay(sf::RenderWindow& window, Assets& assets, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        //Decay Button Functionality
        if (assets.mapDecayElements[0].getGlobalBounds().contains(mousePosF)) {
            assets.soundWalk.play();
            travel.getDecayCounter() = 0;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
        else if (assets.mapDecayElements[1].getGlobalBounds().contains(mousePosF)) {
            assets.soundWalk.play();
            travel.getDecayCounter() = 1;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
        else if (assets.mapDecayElements[2].getGlobalBounds().contains(mousePosF)) {
            assets.soundWalk.play();
            travel.getDecayCounter() = 2;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
        else if (assets.mapDecayElements[3].getGlobalBounds().contains(mousePosF)) {
            assets.soundWalk.play();
            travel.getDecayCounter() = 3;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
        else if (assets.mapDecayElements[4].getGlobalBounds().contains(mousePosF)) {
            assets.soundWalk.play();
            travel.getDecayCounter() = 4;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
}


//Map Functions
void World::resetMapPosition(sf::RenderWindow& window, Assets& assets)
{
    //Forest
    assets.forestMapView.setPosition(assets.getRectMapX(), assets.getRectMapY());
    switch (assets.getForestAreaUnlocked()) {
    case 0:
        assets.mapForestElements[0].setPosition(assets.getRectMapX() + 145, assets.getRectMapY() + 25);
        break;
    case 1:
        assets.mapForestElements[0].setPosition(assets.getRectMapX() + 145, assets.getRectMapY() + 25);
        assets.mapForestElements[1].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + 20);
        break;
    case 2:
        assets.mapForestElements[0].setPosition(assets.getRectMapX() + 145, assets.getRectMapY() + 25);
        assets.mapForestElements[1].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + 20);
        assets.mapForestElements[2].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 240);
        break;
    case 3:
        assets.mapForestElements[0].setPosition(assets.getRectMapX() + 145, assets.getRectMapY() + 25);
        assets.mapForestElements[1].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + 20);
        assets.mapForestElements[2].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 240);
        assets.mapForestElements[3].setPosition(assets.getRectMapX() + 175, assets.getRectMapY() + 200);
        break;
    case 4:
        assets.mapForestElements[0].setPosition(assets.getRectMapX() + 145, assets.getRectMapY() + 25);
        assets.mapForestElements[1].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + 20);
        assets.mapForestElements[2].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 240);
        assets.mapForestElements[3].setPosition(assets.getRectMapX() + 175, assets.getRectMapY() + 200);
        assets.mapForestElements[4].setPosition(assets.getRectMapX() + 240, assets.getRectMapY() + 320);
        break;
    }
    assets.mapForestElementsText[0].setPosition(assets.getRectMapX() + 145, assets.getRectMapY() + 10);
    assets.mapForestElementsText[1].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + 5);
    assets.mapForestElementsText[2].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 225);
    assets.mapForestElementsText[3].setPosition(assets.getRectMapX() + 175, assets.getRectMapY() + 185);
    assets.mapForestElementsText[4].setPosition(assets.getRectMapX() + 240, assets.getRectMapY() + 305);
    //Castle
    assets.spriteMapView.setPosition(assets.getRectMapX(), assets.getRectMapY());
    switch (assets.getCastleAreaUnlocked()) {
    case 0:
        assets.mapCastleElements[0].setPosition(assets.getRectMapX() + 27, assets.getRectMapY() + 322);
        break;
    case 1:
        assets.mapCastleElements[0].setPosition(assets.getRectMapX() + 27, assets.getRectMapY() + 322);
        assets.mapCastleElements[1].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 240);
        break;
    case 2:
        assets.mapCastleElements[0].setPosition(assets.getRectMapX() + 27, assets.getRectMapY() + 322);
        assets.mapCastleElements[1].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 240);
        assets.mapCastleElements[2].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + 5);
        break;
    case 3:
        assets.mapCastleElements[0].setPosition(assets.getRectMapX() + 27, assets.getRectMapY() + 322);
        assets.mapCastleElements[1].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 240);
        assets.mapCastleElements[2].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + 5);
        assets.mapCastleElements[3].setPosition(assets.getRectMapX() + 200, assets.getRectMapY() + 20);
        break;
    case 4:
        assets.mapCastleElements[0].setPosition(assets.getRectMapX() + 27, assets.getRectMapY() + 322);
        assets.mapCastleElements[1].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 240);
        assets.mapCastleElements[2].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + 5);
        assets.mapCastleElements[3].setPosition(assets.getRectMapX() + 200, assets.getRectMapY() + 20);
        assets.mapCastleElements[4].setPosition(assets.getRectMapX() + 305, assets.getRectMapY() + 210);
        break;
    }
    assets.mapCastleElementsText[0].setPosition(assets.getRectMapX() + 27, assets.getRectMapY() + 307);
    assets.mapCastleElementsText[1].setPosition(assets.getRectMapX() + 75, assets.getRectMapY() + 225);
    assets.mapCastleElementsText[2].setPosition(assets.getRectMapX() + 34, assets.getRectMapY() + -10);
    assets.mapCastleElementsText[3].setPosition(assets.getRectMapX() + 200, assets.getRectMapY() + 5);
    assets.mapCastleElementsText[4].setPosition(assets.getRectMapX() + 305, assets.getRectMapY() + 195);
    //Decay
    assets.decayMapView.setPosition(assets.getRectMapX(), assets.getRectMapY());
    switch (assets.getDecayAreaUnlocked()) {
    case 0:
        assets.mapDecayElements[0].setPosition(assets.getRectMapX() + 220, assets.getRectMapY() + 215);
        break;
    case 1:
        assets.mapDecayElements[0].setPosition(assets.getRectMapX() + 220, assets.getRectMapY() + 215);
        assets.mapDecayElements[1].setPosition(assets.getRectMapX() + 245, assets.getRectMapY() + 110);
        break;
    case 2:
        assets.mapDecayElements[0].setPosition(assets.getRectMapX() + 220, assets.getRectMapY() + 215);
        assets.mapDecayElements[1].setPosition(assets.getRectMapX() + 245, assets.getRectMapY() + 110);
        assets.mapDecayElements[2].setPosition(assets.getRectMapX() + 200, assets.getRectMapY() + 60);
        break;
    case 3:
        assets.mapDecayElements[0].setPosition(assets.getRectMapX() + 220, assets.getRectMapY() + 215);
        assets.mapDecayElements[1].setPosition(assets.getRectMapX() + 245, assets.getRectMapY() + 110);
        assets.mapDecayElements[2].setPosition(assets.getRectMapX() + 200, assets.getRectMapY() + 60);
        assets.mapDecayElements[3].setPosition(assets.getRectMapX() + 150, assets.getRectMapY() + 40);
        break;
    case 4:
        assets.mapDecayElements[0].setPosition(assets.getRectMapX() + 220, assets.getRectMapY() + 215);
        assets.mapDecayElements[1].setPosition(assets.getRectMapX() + 245, assets.getRectMapY() + 110);
        assets.mapDecayElements[2].setPosition(assets.getRectMapX() + 200, assets.getRectMapY() + 60);
        assets.mapDecayElements[3].setPosition(assets.getRectMapX() + 150, assets.getRectMapY() + 40);
        assets.mapDecayElements[4].setPosition(assets.getRectMapX() + 25, assets.getRectMapY() + 50);
        break;
        
    }
    assets.mapDecayElementsText[0].setPosition(assets.getRectMapX() + 220, assets.getRectMapY() + 200);
    assets.mapDecayElementsText[1].setPosition(assets.getRectMapX() + 245, assets.getRectMapY() + 95);
    assets.mapDecayElementsText[2].setPosition(assets.getRectMapX() + 200, assets.getRectMapY() + 45);
    assets.mapDecayElementsText[3].setPosition(assets.getRectMapX() + 150, assets.getRectMapY() + 25);
    assets.mapDecayElementsText[4].setPosition(assets.getRectMapX() + 25, assets.getRectMapY() + 35);
}

void World::selectMapView(sf::RenderWindow& window, Assets& assets, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (assets.buttonViewMap[0].getGlobalBounds().contains(mousePosF)) {
        //Click to view forest from map selector buttons
        assets.setMapCounterZero();
        this->resetMapPosition(window, assets);

        travel.getFrame() = 0;
        assets.soundWalk.play();
        travel.getForestCounter() = 0;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (assets.buttonViewMap[1].getGlobalBounds().contains(mousePosF)) {
        //Click to view castle from map selector buttons
        assets.setMapCounterOne();
        this->resetMapPosition(window, assets);

        travel.getFrame() = 0;
        assets.soundWalk.play();
        travel.getCastleCounter() = 0;
        travel.setFrameInitFalse();
        this->buttonClick = true;
    }
    else if (assets.buttonViewMap[2].getGlobalBounds().contains(mousePosF)) {
        //Click to view decay from map selector buttons
        assets.setMapCounterTwo();
        this->resetMapPosition(window, assets);

        travel.getFrame() = 0;
        assets.soundWalk.play();
        travel.getDecayCounter() = 0;
        travel.setFrameInitFalse();
        this->buttonClick = true;
    }
}

void World::drawForestMap(sf::RenderWindow& window, Assets& assets)
{
    window.draw(assets.forestMapView);
    window.draw(assets.multiArrow);
    this->DrawMapSelectorButtons(window, assets);
    for (int i = 0; i < assets.mapForestElements.size(); i++) {
        window.draw(assets.mapForestElements[i]);
    }

    for (int i = 0; i < assets.mapForestElementsText.size(); i++) {
        window.draw(assets.mapForestElementsText[i]);
    }
}

void World::drawCastleMap(sf::RenderWindow& window, Assets& assets)
{
    //Draw Everything
    window.draw(assets.spriteMapView);
    window.draw(assets.multiArrow);
    this->DrawMapSelectorButtons(window, assets);
    for (int i = 0; i < assets.mapCastleElements.size(); i++) {
        window.draw(assets.mapCastleElements[i]);
    }

    for (int i = 0; i < assets.mapCastleElementsText.size(); i++) {
        window.draw(assets.mapCastleElementsText[i]);
    }
}

void World::drawDecayMap(sf::RenderWindow& window, Assets& assets)
{
    //Draw Everything
    window.draw(assets.decayMapView);
    window.draw(assets.multiArrow);
    this->DrawMapSelectorButtons(window, assets);
    for (int i = 0; i < assets.mapDecayElements.size(); i++) {
        window.draw(assets.mapDecayElements[i]);
    }

    for (int i = 0; i < assets.mapDecayElementsText.size(); i++) {
        window.draw(assets.mapDecayElementsText[i]);
    }
}