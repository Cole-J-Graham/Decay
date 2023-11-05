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
void World::bootUp(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate)
{
    //Load SFX
    sprites.loadSFX();
    //create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Console Chat", sf::Style::Fullscreen  );
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
                this->printToolTip(window, sprites, notevent, combat, player);
                break;
            case sf::Event::MouseButtonPressed:
                //Get Mouse Click Input
                this->travelButtons(window, sprites, travel, animate, player);
                //If button in map is clicked, do something
                if (!sprites.getPlayerDeath() && sprites.getInitMap()) {
                    this->mapButtons(window, sprites, travel);
                }
                //Map Menu Bar Functionality
                this->statsFunctionality(window, combat, player, sprites); //Must be loaded before menuBar(window); to withhold functionality
                this->menuBar(window, sprites);
                //Dialogue Box Functionality
                this->dialogueCombatBox(window, combat, sprites, travel, notevent);
                //Main Menu Functionality
                this->mainMenuButtons(window, sprites, travel, animate);
                if (stop) { //Make quit button return to main function to stop program from running
                    return;
                }
                //Bonfire Functionality
                if (sprites.getBonfireAssets() == true) {
                    notevent.healCharacters(window, sprites, combat);
                    notevent.smithingSharpenBlade(window, sprites, player);
                    notevent.zinEvents(window, sprites, animate);
                }
                break;
            case sf::Event::MouseButtonReleased:
                sprites.setMovableFalse();
                sprites.setMovableStatsBoxFalse();
                break;
            case sf::Event::KeyPressed:
                this->userInput(sprites);
                break;
            }
            //Main Travel Loop
            travel.travelCore(window, sprites, notevent, combat, player, animate);
        }
        //Draw Everything...
        this->Draw(window, sprites, notevent, combat, player, travel, animate);
    }
}

//User Input
void World::userInput(Sprites& sprites)
{
    //Get user input for keyboard inputs
    sprites.font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    sprites.playerText.setFont(sprites.font);
    sprites.playerText.setCharacterSize(18);
    sprites.playerText.setFillColor(sf::Color::White);
    sprites.playerText.setPosition(0, 950);
    
    playerInput += event.text.unicode;
    input = event.text.unicode;
    unicode = event.text.unicode;

    //Getting user input for settings
    if (unicode == 36) {
        sprites.soundClick.play();
        //Make settings appear (Basically the main menu with some additions....)
        if (!sprites.getSettingsShown()) {
            sprites.getSettingsShown() = true;
        }
        else if (sprites.getSettingsShown()){
            sprites.getSettingsShown() = false;
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
void World::Draw(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Initial Draw In
    if (sprites.getInitialDrawIn() == false) {
        window.setIcon(sprites.windowIcon.getSize().x, sprites.windowIcon.getSize().y, sprites.windowIcon.getPixelsPtr()); //set window icon
        sprites.setInitialDrawInTrue();
    }
    // clear the window with black color
    window.clear(sf::Color::Black);

    // draw everything here...
    if (this->mainMenu == false && !sprites.getPlayerDeath()) {
        combat.combatTextElapsed = combat.combatTextTime.getElapsedTime();//Reset stats text after 3 seconds
        if (combat.combatTextElapsed.asSeconds() >= 3 && !combat.getComTextRemoved()) {
            sprites.text.setString("");
            combat.getComTextRemoved() = true;
        }
        sprites.greyOnHover(window);
        sprites.drawObjects(sprites);
        travel.travelCore(window, sprites, notevent, combat, player, animate);

        window.draw(sprites.rect);
        window.draw(sprites.map);
        window.draw(sprites.mapBorder);
        window.draw(sprites.playerText);
        window.draw(sprites.locationText);
        window.draw(sprites.text);

        //Draw Entity Viewer
        window.draw(sprites.entityBox);
        window.draw(sprites.entitySprite);
        window.draw(sprites.entityBoxHeader);
        window.draw(sprites.entityBoxText);

        //Draw all sprite border rects and text
        for (int i = 0; i < sprites.spriteRect.size(); i++) {
            window.draw(sprites.spriteRect[i]);
            window.draw(sprites.spriteText[i]);
        }
        //Draw combat elements
        for (int i = 0; i < sprites.combatRect.size(); i++) {
            window.draw(sprites.combatRect[i]);
            window.draw(sprites.combatText[i]);
        }

        //Draw Bonfire Detection Rect
        if (travel.getBonfireInit() == true) {
            sprites.bonfireHealDetectionText.setPosition(mousePos.x - 5.0f, mousePos.y + 15.0f);
            sprites.bonfireSmithDetectionText.setPosition(mousePos.x - 5.0f, mousePos.y + 15.0f);
            //Healing
            window.draw(sprites.bonfireHealDetectionRect);
            window.draw(sprites.bonfireHealDetectionText);
            //Smithing
            window.draw(sprites.bonfireSmithDetectionRect);
            window.draw(sprites.bonfireSmithDetectionText);
        }

        //Draw rectangle elements
        for (int i = 0; i < sprites.rectElements.size(); i++) {
            window.draw(sprites.rectElements[i]);
        }
        //Draw text elements
        for (int i = 0; i < sprites.textElements.size(); i++) {
            window.draw(sprites.textElements[i]);
        }
        //Draw sprite elements
        for (int i = 0; i < sprites.spriteElements.size(); i++) {
            window.draw(sprites.spriteElements[i]);
        }

        //Draw Tip Box
        window.draw(sprites.tipBox);
        window.draw(sprites.tipBoxText);

        //Draw Animations
        animate.drawAnimations(sprites);
        animate.animateDecayWarn();
        window.draw(animate.zinSprite);
        window.draw(animate.notSprite);
        window.draw(animate.decayWarn);
        window.draw(animate.healSprite);
        window.draw(animate.anvilSprite);
        window.draw(animate.hitSprite);
        

        if (sprites.getInitMap() == true) {
            //Draw main map rect
            window.draw(sprites.rectMap);
            //Choose which map is selected
            switch (sprites.getMapCounter()) {
            case 0:
                this->drawForestMap(window, sprites);
                break;
            case 1:
                this->drawCastleMap(window, sprites);
                break;
            case 2:
                this->drawDecayMap(window, sprites);
                break;
            }
            //Make Box Movable if clicked...
            this->movableBox(window, sprites);
        }

        if (sprites.getInitStats() == true) {
            textElapsed = textTime.getElapsedTime();//Reset stats text after 3 seconds
            if (textElapsed.asSeconds() >= 3) {
                sprites.text.setString("");
            }
            window.draw(sprites.rectStatsBox);
            if (sprites.getPlayerStatsInit() == true) {
                this->printPlayerStats(window, sprites, notevent, combat, player);
            }
            else if (sprites.getZinStatsInit() == true) {
                this->printZinStats(window, sprites, notevent, combat, player);
            }
            window.draw(sprites.rectStatsSideMenu);
            window.draw(sprites.playerStatsBoxButtonText);
            window.draw(sprites.zinStatsBoxButtonText);
        }
        if (sprites.getInitInventory() == true) {
            player.printInventory(sprites);
            window.draw(sprites.rectInventoryBox);
            window.draw(sprites.inventoryText);
        }
    }
    else if (this->mainMenu == true) {
        sprites.greyOnHover(window);
        animate.animateMenu(sprites);
        window.draw(animate.menuSprite);
        sprites.drawMainMenu();
        for (int i = 0; i < sprites.menuScreenElements.size(); i++) {
            window.draw(sprites.menuScreenElements[i]);
        }
        for (int i = 0; i < sprites.menuScreenElementsText.size(); i++) {
            window.draw(sprites.menuScreenElementsText[i]);
        }
    }
    else if (sprites.getPlayerDeath()) {
        sprites.drawDeathAssets();
        window.draw(sprites.deathText);
        window.draw(sprites.menuScreenElements[1]);
        window.draw(sprites.menuScreenElements[2]);
        window.draw(sprites.menuScreenElementsText[1]);
        window.draw(sprites.menuScreenElementsText[2]);
    }

    //Draw User Input Rects
    for (int i = 0; i < sprites.answerBox.size(); i++) {
        window.draw(sprites.answerBox[i]);
        window.draw(sprites.answerBoxText[i]);
    }

    //Draw Settings to screen
    if (sprites.getSettingsShown()) {
        sprites.drawMainMenu();
        for (int i = 0; i < sprites.menuScreenElements.size(); i++) {
            window.draw(sprites.menuScreenElements[i]);
        }
        for (int i = 0; i < sprites.menuScreenElementsText.size(); i++) {
            window.draw(sprites.menuScreenElementsText[i]);
        }
    }

    // end the current frame
    window.display();
}

void World::DrawMapSelectorButtons(sf::RenderWindow& window, Sprites& sprites)
{
    //Draw all rectangle elements for map button selectors
    for (int i = 0; i < sprites.buttonViewMap.size(); i++) {
        window.draw(sprites.buttonViewMap[i]);
    }
    //Draw all rectangle elements for map button selectors text
    for (int i = 0; i < sprites.buttonViewMapText.size(); i++) {
        window.draw(sprites.buttonViewMapText[i]);
    }
}

void World::printPlayerStats(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player)
{
    sprites.playerTextElements[4].setString("HP: " + std::to_string(combat.getPlayerHp()) + "/" +
        std::to_string(combat.getPlayerHpMax()) + "\nDECAY: " + std::to_string(player.getDecay()) + "/" +
        std::to_string(player.getDecayMax()) + "\n\nSP: " + std::to_string(player.getSp()) +
        "\nEXP: " + std::to_string(player.getExp()) + "/" + std::to_string(player.getExpNext()));

    for (int i = 0; i < sprites.playerStatElements.size(); i++) {
        window.draw(sprites.playerStatElements[i]);
    }

    for (int i = 0; i < sprites.playerTextPlus.size(); i++) {
        window.draw(sprites.playerTextPlus[i]);
    }

    for (int i = 0; i < sprites.playerTextElements.size(); i++) {
        window.draw(sprites.playerTextElements[i]);
    }
}

void World::printZinStats(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player)
{
    sprites.zinTextElements[4].setString("HP: " + std::to_string(combat.getZinHp()) + "/" + std::to_string(combat.getZinHpMax()) + "\n\n\nSP: " + std::to_string(player.getZinSp()) +
        "\nEXP: " + std::to_string(player.getZinExp()) + "/" + std::to_string(player.getZinExpNext()));

    for (int i = 0; i < sprites.zinStatElements.size(); i++) {
        window.draw(sprites.playerStatElements[i]);
    }

    for (int i = 0; i < sprites.zinTextPlus.size(); i++) {
        window.draw(sprites.zinTextPlus[i]);
    }

    for (int i = 0; i < sprites.zinTextElements.size(); i++) {
        window.draw(sprites.zinTextElements[i]);
    }
}

void World::printToolTip(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Player Combat Buttons Functionality
    if (sprites.getPlayerStatsInit()) {
        if (sprites.playerStatElements[1].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("STRENGTH:\nMeasures the players raw power.\n\nIncreases all attack moves damage.");
        }
        else if (sprites.playerStatElements[2].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("FORTITUDE:\nMeasures the players survivability against decay.\n\nHigher fortitude makes the player more \nresistant to the decay.");
        }
        else if (sprites.playerStatElements[3].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("VITALITY:\nMeasures the players health.\n\nHigh vitality allows the player to take a beating\nin combat.");
        }
        else {
            sprites.getTipBoxCounter() = -1;
        }
    }
    else if (sprites.getZinStatsInit()) {
        if (sprites.zinStatElements[1].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("RESOLVE:\nMeasures Zin's spells raw power.\n\nIncreases the damage of her lightning \nspells specifically.");
        }
        else if (sprites.zinStatElements[2].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("PATIENCE:\nMeasures Zin's healing capabilities.\n\nHigh patience makes her heal \nsignificantly more.");
        }
        else if (sprites.zinStatElements[3].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("RESILIENCE:\nMeasures Zin's health.\n\nHigh resilience allows Zin to take more \nhits and survive.");
        }
        else {
            sprites.getTipBoxCounter() = -1;
        }
    }
    
    if (sprites.getCombatAssets()) {
        if (sprites.combatRect[0].getGlobalBounds().contains(mousePosF)) { //If attack button is clicked...
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("SLASH:\nThe players basic attack for inflicting damage...");
        }
        else if (sprites.combatRect[1].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("GUARD:\nUses the players turn to protect Zin from \nALL damage...");
        }
        else if (sprites.combatRect[2].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("DECAYED BLADE:\nThe player slashes his own skin open to use the \ndecay in his blood as a weapon...\n\nInflicts extra damage due to decayed blood...");
        }
        //Zin Combat Buttons Functionality
        else if (sprites.combatRect[3].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("SMITE:\nZin's basic attack, inflicts damage on the \nopponent...");
        }
        else if (sprites.combatRect[4].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("MEND:\nHeals the player and Zin...");
        }
        else if (sprites.combatRect[5].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("VENGEANCE:\nUse Zin's rage and sorrow to turn the players\nblood into sharpened blades that hurdle\ntowards the enemy...\n\nInflicts damage equal to the players current \nlost health...");
        }
        else if (sprites.combatRect[6].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("BARRIER:\nThom casts a barrier made of Decay,\nblocking some of the players damage.");
        }
        else if (sprites.combatRect[7].getGlobalBounds().contains(mousePosF)) {
            sprites.getTipBoxCounter() = 0;
            sprites.tipBoxText.setString("ENRAGE:\nThom enters a state of pure rage.\nThis lasts for three turns, boosting\nall party damage.\n\nThom is unable to use any other moves during\nhis state of rage.");
        }
        else {
            sprites.getTipBoxCounter() = -1;
        }
    }
}

//Display Element Functionality
void World::mainMenuButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Shared Functionality between both main menu and settings menu
    if (sprites.menuScreenElements[1].getGlobalBounds().contains(mousePosF)) {
        //Loading Game Button Funcionality (Not implemented yet...)
        sprites.soundClick.play();
        std::cout << "Loading a save hypothetically speaking lmao...";
    }
    else if (sprites.menuScreenElements[2].getGlobalBounds().contains(mousePosF)) {
        //Quit Game Button Functionality
        sprites.soundClick.play();
        stop = true;
        return;
    }
    //Main menu specific functionality
    if (!sprites.getIntroFinished()) {
        if (sprites.menuScreenElements[0].getGlobalBounds().contains(mousePosF)) {
            //Continue to other buttons asking to skip intro or not (New Game Button)
            sprites.soundClick.play();
            sprites.setBootClickedTrue();
        }
        else if (sprites.menuScreenElements[3].getGlobalBounds().contains(mousePosF)) {
            //Intro Button Functionality
            sprites.soundClick.play();
            this->mainMenu = false;
            travel.getIntroCounterDialogue() = 0; //Allow the counter to load the main image specifically just for the intro to take place
        }
        else if (sprites.menuScreenElements[4].getGlobalBounds().contains(mousePosF)) {
            //Skip Intro Button Functionality
            sprites.soundClick.play();
            this->mainMenu = false;
            sprites.getIntroFinished() = true;
            sprites.setMapCounterZero(); //Skip intro and go straight to the forest
        }
    }//Settings specific functionality
    else if (sprites.getIntroFinished()) {
        if (sprites.menuScreenElements[5].getGlobalBounds().contains(mousePosF)) {
            //Saving Game Button Funcionality (Not implemented yet...)
            std::cout << "Saving game hypothetically speaking...";
        }
    }
   
}

void World::travelButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel, Animation& animate, Player& player)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Main View Buttons Control
    if (sprites.spriteElements[0].getGlobalBounds().contains(mousePosF))
    {
        travel.setFrameInc();
        travel.setFrameInitFalse();
        sprites.blipsound.play();
        //Decay Increases Every Move
        player.getDecay()++;
        animate.getDecayWarning() = true;
        animate.getAnimationFrame() = -1;
    }
    else if (sprites.spriteElements[1].getGlobalBounds().contains(mousePosF))
    {
        travel.setFrameDec();
        travel.setFrameInitFalse();
        sprites.blipsound.play();
        //Decay Increases Every Move
        player.getDecay()++;
        animate.getDecayWarning() = true;
        animate.getAnimationFrame() = -1;
    }
}

void World::menuBar(sf::RenderWindow& window, Sprites& sprites)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Map Menu Bar Functionaliy
    if (sprites.multiArrow.getGlobalBounds().contains(mousePosF) && buttonClick == false) {
        //Click Multi Arrow to make map movable
        sprites.setMovableTrue();
    }
    else if (sprites.multiArrow.getGlobalBounds().contains(mousePosF) && buttonClick == false) {
        sprites.setMovableStatsBoxTrue();
    }
    if (sprites.rectElements[2].getGlobalBounds().contains(mousePosF) && sprites.getInitMap() == false) {
        //Click to open map
        sprites.setInitMapTrue();
        sprites.blipmenu.play();
    }
    else if (sprites.rectElements[2].getGlobalBounds().contains(mousePosF) && sprites.getInitMap() == true) {
        //Click to close map
        sprites.setInitMapFalse();
        sprites.setRectMapXVal();
        sprites.setRectMapYVal();
        this->resetMapPosition(window, sprites);
        sprites.blipmenu.play();
        sprites.blipmenu.play();
    }
    this->buttonClick = false;
    //Stats Menu Bar Functionality
    if (sprites.rectElements[0].getGlobalBounds().contains(mousePosF) && sprites.getInitStats() == false) {
        sprites.setInitStatsTrue();
        sprites.setPlayerStatsInitTrue();
        sprites.blipmenu.play();
    }
    else if (sprites.rectElements[0].getGlobalBounds().contains(mousePosF) && sprites.getInitStats() == true) {
        sprites.setInitStatsFalse();
        sprites.setPlayerStatsInitFalse();
        sprites.setZinStatsInitFalse();
        sprites.blipmenu.play();
    }
    //Inventory Menu Bar Functionality
    if (sprites.rectElements[1].getGlobalBounds().contains(mousePosF) && sprites.getInitInventory() == false) {
        sprites.setInitInventoryTrue();
        sprites.blipmenu.play();
    }
    else if (sprites.rectElements[1].getGlobalBounds().contains(mousePosF) && sprites.getInitInventory() == true) {
        sprites.setInitInventoryFalse();
        sprites.blipmenu.play();
    }
}

void World::dialogueCombatBox(sf::RenderWindow& window, Combat& combat, Sprites& sprites, Travel& travel, Event& notevent)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Player Combat Buttons Functionality
    if (sprites.combatRect[0].getGlobalBounds().contains(mousePosF)) { //If attack button is clicked...
        if (combat.getTurnPlayer() == true) {
            combat.setAttackCounterInc();
            combat.getPlayerPickMove() = 0;
        }
    }
    if (sprites.combatRect[1].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnPlayer() == true) {
            combat.setAttackCounterInc();
            combat.getPlayerPickMove() = 1;
        }
    }
    if (sprites.combatRect[2].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnPlayer() == true) {
            combat.setAttackCounterInc();
            combat.getPlayerPickMove() = 2;
        }
    }
    //Zin Combat Buttons Functionality
    if (sprites.combatRect[3].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnZin() == true) {
            combat.setZinAttackCounterInc();
            combat.getZinPickMove() = 0;
        }
    }
    if (sprites.combatRect[4].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnZin() == true) {
            combat.setZinAttackCounterInc();
            combat.getZinPickMove() = 1;
        }
    }
    if (sprites.combatRect[5].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnZin() == true) {
            combat.setZinAttackCounterInc();
            combat.getZinPickMove() = 2;
        }
    }
    //Thom Combat Buttons Functionality
    if (sprites.combatRect[6].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnThom() == true) {
            combat.getThomAttackCounter()++;
            combat.getThomPickMove() = 0;
        }
    }
    if (sprites.combatRect[7].getGlobalBounds().contains(mousePosF)) {
        if (combat.getTurnThom() == true) {
            combat.getThomAttackCounter()++;
            combat.getThomPickMove() = 1;
        }
    }
    else if (sprites.rect.getGlobalBounds().contains(mousePosF) && sprites.getShowAnsBoxesCounter() == -1) {
        //If dialogue box is clicked...
        sprites.soundClick.play();
        sprites.setDialogueCounterInc();
        travel.setFrameInitFalse(); //Allow images to be loaded again
        travel.setIntroCounterDialogueInc();
        notevent.setDialogueInc();
        if (combat.getAttackCounter() == 1) {
            combat.getAttackCounter() = 2;
        }
        if (combat.getZinAttackCounter() == 1) {
            combat.getZinAttackCounter() = 2;
        }
        if (sprites.getThomUnlocked() && combat.getThomAttackCounter() == 1) {
            combat.getThomAttackCounter() = 2;
        }
        if (combat.getTurnHostile() == true) {
            sprites.getCombatCounter()++;
        }
    }
    else if (sprites.getShowAnsBoxesCounter() == 0) {
        if (sprites.answerBox[0].getGlobalBounds().contains(mousePosF)) {
            notevent.getChoiceCounter() = 0;
            travel.setIntroCounterDialogueInc();
            notevent.setDialogueInc();
            sprites.soundClick.play();
        }
        else if (sprites.answerBox[1].getGlobalBounds().contains(mousePosF)) {
            notevent.getChoiceCounter() = 1;
            travel.setIntroCounterDialogueInc();
            notevent.setDialogueInc();
            sprites.soundClick.play();
        }
    }

}

void World::movableBox(sf::RenderWindow& window, Sprites& sprites)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (sprites.getMovable() == true) {
        sprites.getRectMapX() = mousePos.x - 365.0f;
        sprites.getRectMapY() = mousePos.y - 23.0f;
        this->resetMapPosition(window, sprites);
    }
}

//Stat Functionality
void World::statsFunctionality(sf::RenderWindow& window, Combat& combat, Player& player, Sprites& sprites)
{
    //Add Text
    player.statsText(sprites);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Menu Bar Stats Functionality (Switching between who's stats are visible)
    if (sprites.playerStatElements[4].getGlobalBounds().contains(mousePosF)) {
        if (sprites.getPlayerStatsInit() == false) {
            sprites.setPlayerStatsInitTrue();
            sprites.setZinStatsInitFalse();
            sprites.statSound.play();
        }
    }
    if (sprites.zinStatElements[5].getGlobalBounds().contains(mousePosF)) {
        if (sprites.getZinStatsInit() == false) {
            sprites.setZinStatsInitTrue();
            sprites.setPlayerStatsInitFalse();
            sprites.statSound.play();
        }
    }

    if (sprites.getPlayerStatsInit()) {
        //Call functions for player functionality
        this->levelUp(window, combat, player, sprites, sprites.playerStatElements[0], player.getLevel(), player.getSp(), player.getExp(), player.getExpNext());
        this->statUp(window, combat, player, sprites, sprites.playerStatElements[1], player.getStrength(), player.getSp(), player.getExp(), player.getExpNext());
        this->statUp(window, combat, player, sprites, sprites.playerStatElements[2], player.getFortitude(), player.getSp(), player.getExp(), player.getExpNext());
        this->statUp(window, combat, player, sprites, sprites.playerStatElements[3], player.getVitality(), player.getSp(), player.getExp(), player.getExpNext());
    }
    else if (sprites.getZinStatsInit()) {
        //Call functions for Zin functionality
        this->levelUp(window, combat, player, sprites, sprites.zinStatElements[0], player.getZinLevel(), player.getZinSp(), player.getZinExp(), player.getZinExpNext());
        this->statUp(window, combat, player, sprites, sprites.zinStatElements[1], player.getZinResolve(), player.getZinSp(), player.getZinExp(), player.getZinExpNext());
        this->statUp(window, combat, player, sprites, sprites.zinStatElements[2], player.getZinPatience(), player.getZinSp(), player.getZinExp(), player.getZinExpNext());
        this->statUp(window, combat, player, sprites, sprites.zinStatElements[3], player.getZinResilience(), player.getZinSp(), player.getZinExp(), player.getZinExpNext());
    }
}

void World::levelUp(sf::RenderWindow& window, Combat& combat, Player& player, Sprites& sprites, sf::RectangleShape& inputRect, int& lvl, int& sp, int& exp, int& expNext)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (sprites.getInitStats()) {
        if (inputRect.getGlobalBounds().contains(mousePosF)) {
            textTime.restart();
            if (exp >= expNext) {
                lvl++;
                sp++;
                exp -= expNext;
                player.statsText(sprites);
                sprites.playerTextElements[0].setString("LEVEL " + std::to_string(lvl));
                sprites.text.setString("Level up achieved. Level " + std::to_string(lvl) + " reached. One SP point acquired...");
                sprites.statSound.play();
            }
            else if (exp <= expNext) {
                sprites.text.setString("Required Exp not met...");
            }
            this->buttonClick = true;
        }
    }
}

void World::statUp(sf::RenderWindow& window, Combat& combat, Player& player, Sprites& sprites, sf::RectangleShape& inputRect, int& stat, int& sp, int& exp, int& expNext)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (sprites.getInitStats()) {
        if (inputRect.getGlobalBounds().contains(mousePosF)) {
            textTime.restart();
            if (sp >= 1) {
                stat++;
                sp--;
                player.statsText(sprites);
                sprites.text.setString("Stat improved...");
                combat.updateStats(sprites, player);
                sprites.statSound.play();
            }
            else if (sp <= 0) {
                sprites.text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
}

//Map Button Functionality
void World::mapButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel)
{
    this->selectMapView(window, sprites, travel);
    //Map Button Functionality (Switching between whch button on the map is selected to change areas...)
    switch (sprites.getMapCounter()) {
    case 0:
        this->mapButtonsForest(window, sprites, travel);
        break;
    case 1:
        this->mapButtonsCastle(window, sprites, travel);
        break;
    case 2:
        this->mapButtonsDecay(window, sprites, travel);
        break;
    }
}

void World::mapButtonsForest(sf::RenderWindow& window, Sprites& sprites, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Forest Button Functionality
    if (sprites.mapForestElements[0].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getForestCounter() = 0;
        travel.setFrameInitFalse();
        travel.getFrame() = 0; //Ensures whenever you move from area to area on map, player stays on 1st frame
        this->buttonClick = true;
    }
    else if (sprites.mapForestElements[1].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getForestCounter() = 1;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (sprites.mapForestElements[2].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getForestCounter() = 2;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (sprites.mapForestElements[3].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getForestCounter() = 3;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (sprites.mapForestElements[4].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getForestCounter() = 4;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
}

void World::mapButtonsCastle(sf::RenderWindow& window, Sprites& sprites, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Castle Button Functionality
    if (sprites.mapCastleElements[0].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getCastleCounter() = 0;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (sprites.mapCastleElements[1].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getCastleCounter() = 1;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (sprites.mapCastleElements[2].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getCastleCounter() = 2;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (sprites.mapCastleElements[3].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getCastleCounter() = 3;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (sprites.mapCastleElements[4].getGlobalBounds().contains(mousePosF)) {
        sprites.soundWalk.play();
        travel.getCastleCounter() = 4;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
}

void World::mapButtonsDecay(sf::RenderWindow& window, Sprites& sprites, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        //Decay Button Functionality
        if (sprites.mapDecayElements[0].getGlobalBounds().contains(mousePosF)) {
            sprites.soundWalk.play();
            travel.getDecayCounter() = 0;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
        else if (sprites.mapDecayElements[1].getGlobalBounds().contains(mousePosF)) {
            sprites.soundWalk.play();
            travel.getDecayCounter() = 1;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
        else if (sprites.mapDecayElements[2].getGlobalBounds().contains(mousePosF)) {
            sprites.soundWalk.play();
            travel.getDecayCounter() = 2;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
        else if (sprites.mapDecayElements[3].getGlobalBounds().contains(mousePosF)) {
            sprites.soundWalk.play();
            travel.getDecayCounter() = 3;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
        else if (sprites.mapDecayElements[4].getGlobalBounds().contains(mousePosF)) {
            sprites.soundWalk.play();
            travel.getDecayCounter() = 4;
            travel.setFrameInitFalse();
            travel.getFrame() = 0;
            this->buttonClick = true;
        }
}

//Map Functions
void World::resetMapPosition(sf::RenderWindow& window, Sprites& sprites)
{
    //Forest
    sprites.forestMapView.setPosition(sprites.getRectMapX(), sprites.getRectMapY());
    switch (sprites.getForestAreaUnlocked()) {
    case 0:
        sprites.mapForestElements[0].setPosition(sprites.getRectMapX() + 145, sprites.getRectMapY() + 25);
        break;
    case 1:
        sprites.mapForestElements[0].setPosition(sprites.getRectMapX() + 145, sprites.getRectMapY() + 25);
        sprites.mapForestElements[1].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + 20);
        break;
    case 2:
        sprites.mapForestElements[0].setPosition(sprites.getRectMapX() + 145, sprites.getRectMapY() + 25);
        sprites.mapForestElements[1].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + 20);
        sprites.mapForestElements[2].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 240);
        break;
    case 3:
        sprites.mapForestElements[0].setPosition(sprites.getRectMapX() + 145, sprites.getRectMapY() + 25);
        sprites.mapForestElements[1].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + 20);
        sprites.mapForestElements[2].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 240);
        sprites.mapForestElements[3].setPosition(sprites.getRectMapX() + 175, sprites.getRectMapY() + 200);
        break;
    case 4:
        sprites.mapForestElements[0].setPosition(sprites.getRectMapX() + 145, sprites.getRectMapY() + 25);
        sprites.mapForestElements[1].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + 20);
        sprites.mapForestElements[2].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 240);
        sprites.mapForestElements[3].setPosition(sprites.getRectMapX() + 175, sprites.getRectMapY() + 200);
        sprites.mapForestElements[4].setPosition(sprites.getRectMapX() + 240, sprites.getRectMapY() + 320);
        break;
    }
    sprites.mapForestElementsText[0].setPosition(sprites.getRectMapX() + 145, sprites.getRectMapY() + 10);
    sprites.mapForestElementsText[1].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + 5);
    sprites.mapForestElementsText[2].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 225);
    sprites.mapForestElementsText[3].setPosition(sprites.getRectMapX() + 175, sprites.getRectMapY() + 185);
    sprites.mapForestElementsText[4].setPosition(sprites.getRectMapX() + 240, sprites.getRectMapY() + 305);
    //Castle
    sprites.spriteMapView.setPosition(sprites.getRectMapX(), sprites.getRectMapY());
    switch (sprites.getCastleAreaUnlocked()) {
    case 0:
        sprites.mapCastleElements[0].setPosition(sprites.getRectMapX() + 27, sprites.getRectMapY() + 322);
        break;
    case 1:
        sprites.mapCastleElements[0].setPosition(sprites.getRectMapX() + 27, sprites.getRectMapY() + 322);
        sprites.mapCastleElements[1].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 240);
        break;
    case 2:
        sprites.mapCastleElements[0].setPosition(sprites.getRectMapX() + 27, sprites.getRectMapY() + 322);
        sprites.mapCastleElements[1].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 240);
        sprites.mapCastleElements[2].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + 5);
        break;
    case 3:
        sprites.mapCastleElements[0].setPosition(sprites.getRectMapX() + 27, sprites.getRectMapY() + 322);
        sprites.mapCastleElements[1].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 240);
        sprites.mapCastleElements[2].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + 5);
        sprites.mapCastleElements[3].setPosition(sprites.getRectMapX() + 200, sprites.getRectMapY() + 20);
        break;
    case 4:
        sprites.mapCastleElements[0].setPosition(sprites.getRectMapX() + 27, sprites.getRectMapY() + 322);
        sprites.mapCastleElements[1].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 240);
        sprites.mapCastleElements[2].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + 5);
        sprites.mapCastleElements[3].setPosition(sprites.getRectMapX() + 200, sprites.getRectMapY() + 20);
        sprites.mapCastleElements[4].setPosition(sprites.getRectMapX() + 305, sprites.getRectMapY() + 210);
        break;
    }
    sprites.mapCastleElementsText[0].setPosition(sprites.getRectMapX() + 27, sprites.getRectMapY() + 307);
    sprites.mapCastleElementsText[1].setPosition(sprites.getRectMapX() + 75, sprites.getRectMapY() + 225);
    sprites.mapCastleElementsText[2].setPosition(sprites.getRectMapX() + 34, sprites.getRectMapY() + -10);
    sprites.mapCastleElementsText[3].setPosition(sprites.getRectMapX() + 200, sprites.getRectMapY() + 5);
    sprites.mapCastleElementsText[4].setPosition(sprites.getRectMapX() + 305, sprites.getRectMapY() + 195);
    //Decay
    sprites.decayMapView.setPosition(sprites.getRectMapX(), sprites.getRectMapY());
    switch (sprites.getDecayAreaUnlocked()) {
    case 0:
        sprites.mapDecayElements[0].setPosition(sprites.getRectMapX() + 220, sprites.getRectMapY() + 215);
        break;
    case 1:
        sprites.mapDecayElements[0].setPosition(sprites.getRectMapX() + 220, sprites.getRectMapY() + 215);
        sprites.mapDecayElements[1].setPosition(sprites.getRectMapX() + 245, sprites.getRectMapY() + 110);
        break;
    case 2:
        sprites.mapDecayElements[0].setPosition(sprites.getRectMapX() + 220, sprites.getRectMapY() + 215);
        sprites.mapDecayElements[1].setPosition(sprites.getRectMapX() + 245, sprites.getRectMapY() + 110);
        sprites.mapDecayElements[2].setPosition(sprites.getRectMapX() + 200, sprites.getRectMapY() + 60);
        break;
    case 3:
        sprites.mapDecayElements[0].setPosition(sprites.getRectMapX() + 220, sprites.getRectMapY() + 215);
        sprites.mapDecayElements[1].setPosition(sprites.getRectMapX() + 245, sprites.getRectMapY() + 110);
        sprites.mapDecayElements[2].setPosition(sprites.getRectMapX() + 200, sprites.getRectMapY() + 60);
        sprites.mapDecayElements[3].setPosition(sprites.getRectMapX() + 150, sprites.getRectMapY() + 40);
        break;
    case 4:
        sprites.mapDecayElements[0].setPosition(sprites.getRectMapX() + 220, sprites.getRectMapY() + 215);
        sprites.mapDecayElements[1].setPosition(sprites.getRectMapX() + 245, sprites.getRectMapY() + 110);
        sprites.mapDecayElements[2].setPosition(sprites.getRectMapX() + 200, sprites.getRectMapY() + 60);
        sprites.mapDecayElements[3].setPosition(sprites.getRectMapX() + 150, sprites.getRectMapY() + 40);
        sprites.mapDecayElements[4].setPosition(sprites.getRectMapX() + 25, sprites.getRectMapY() + 50);
        break;
        
    }
    sprites.mapDecayElementsText[0].setPosition(sprites.getRectMapX() + 220, sprites.getRectMapY() + 200);
    sprites.mapDecayElementsText[1].setPosition(sprites.getRectMapX() + 245, sprites.getRectMapY() + 95);
    sprites.mapDecayElementsText[2].setPosition(sprites.getRectMapX() + 200, sprites.getRectMapY() + 45);
    sprites.mapDecayElementsText[3].setPosition(sprites.getRectMapX() + 150, sprites.getRectMapY() + 25);
    sprites.mapDecayElementsText[4].setPosition(sprites.getRectMapX() + 25, sprites.getRectMapY() + 35);
}

void World::selectMapView(sf::RenderWindow& window, Sprites& sprites, Travel& travel)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (sprites.buttonViewMap[0].getGlobalBounds().contains(mousePosF)) {
        //Click to view forest from map selector buttons
        sprites.setMapCounterZero();
        this->resetMapPosition(window, sprites);

        travel.getFrame() = 0;
        sprites.soundWalk.play();
        travel.getForestCounter() = 0;
        travel.setFrameInitFalse();
        travel.getFrame() = 0;
        this->buttonClick = true;
    }
    else if (sprites.buttonViewMap[1].getGlobalBounds().contains(mousePosF)) {
        //Click to view castle from map selector buttons
        sprites.setMapCounterOne();
        this->resetMapPosition(window, sprites);

        travel.getFrame() = 0;
        sprites.soundWalk.play();
        travel.getCastleCounter() = 0;
        travel.setFrameInitFalse();
        this->buttonClick = true;
    }
    else if (sprites.buttonViewMap[2].getGlobalBounds().contains(mousePosF)) {
        //Click to view decay from map selector buttons
        sprites.setMapCounterTwo();
        this->resetMapPosition(window, sprites);

        travel.getFrame() = 0;
        sprites.soundWalk.play();
        travel.getDecayCounter() = 0;
        travel.setFrameInitFalse();
        this->buttonClick = true;
    }
}

void World::drawForestMap(sf::RenderWindow& window, Sprites& sprites)
{
    window.draw(sprites.forestMapView);
    window.draw(sprites.multiArrow);
    this->DrawMapSelectorButtons(window, sprites);
    for (int i = 0; i < sprites.mapForestElements.size(); i++) {
        window.draw(sprites.mapForestElements[i]);
    }

    for (int i = 0; i < sprites.mapForestElementsText.size(); i++) {
        window.draw(sprites.mapForestElementsText[i]);
    }
}

void World::drawCastleMap(sf::RenderWindow& window, Sprites& sprites)
{
    //Draw Everything
    window.draw(sprites.spriteMapView);
    window.draw(sprites.multiArrow);
    this->DrawMapSelectorButtons(window, sprites);
    for (int i = 0; i < sprites.mapCastleElements.size(); i++) {
        window.draw(sprites.mapCastleElements[i]);
    }

    for (int i = 0; i < sprites.mapCastleElementsText.size(); i++) {
        window.draw(sprites.mapCastleElementsText[i]);
    }
}

void World::drawDecayMap(sf::RenderWindow& window, Sprites& sprites)
{
    //Draw Everything
    window.draw(sprites.decayMapView);
    window.draw(sprites.multiArrow);
    this->DrawMapSelectorButtons(window, sprites);
    for (int i = 0; i < sprites.mapDecayElements.size(); i++) {
        window.draw(sprites.mapDecayElements[i]);
    }

    for (int i = 0; i < sprites.mapDecayElementsText.size(); i++) {
        window.draw(sprites.mapDecayElementsText[i]);
    }
}