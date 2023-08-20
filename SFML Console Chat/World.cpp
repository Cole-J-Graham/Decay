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
void World::bootUp(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    //Load SFX
    assets.loadSFX();
    //create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Console Chat" /*, sf::Style::Fullscreen*/);
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
                }
                break;
            case sf::Event::MouseButtonPressed:
                { //Get Mouse Click Input
                    this->travelButtons(window, assets);
                    //If button in map is clicked, do something
                    this->mapButtons(window, assets);
                    //Map Menu Bar Functionality
                    this->menuBarStats(window, combat, player, assets); //Must be loaded before menuBar(window); to withhold functionality
                    this->menuBar(window, assets);
                    //Dialogue Box Functionality...
                    this->dialogueBox(window, combat, assets);
                    //Main Menu Functionality
                    this->mainMenuButtons(window, assets);
                    //Bonfire Functionality
                    notevent.healCharacters(window, assets, combat);
                    notevent.smithingSharpenBlade(window, assets, player);
                }
                break;
            case sf::Event::MouseButtonReleased:
                {
                    assets.movable = false;
                    assets.movableStatsBox = false;
                }
            }
            //Run Main Function Loop...
            this->mainLoop(assets, notevent, combat, player);
        }
        //Draw Everything...
        this->Draw(window, assets, notevent, combat, player);
    }
}

void World::mainLoop(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    //Run Main Functions
    this->userInput(assets);
    travel.travelCore(window, assets, notevent, combat, player);
}

//User Input
void World::userInput(Assets& assets)
{
    assets.font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    assets.playerText.setFont(assets.font);
    assets.playerText.setCharacterSize(18);
    assets.playerText.setFillColor(sf::Color::White);
    assets.playerText.setPosition(0, 950);

    //Getting user input
    if (event.type == sf::Event::TextEntered) {
        playerInput += event.text.unicode;
        input = event.text.unicode;
        unicode = event.text.unicode;
        unicode = static_cast<char>(event.text.unicode);
        assets.playerText.setString(playerInput);
        assets.sound.play();
        
        //Clearing string with backspace
        if (input == "\b") {
            assets.playerText.setString("");
            assets.playerText.setCharacterSize(24);
            playerInput = "";
        }
    }
}

void World::clearInput()
{
    this->unicode = -1;
    playerInput = "";
    return;
}

//Display Functions
void World::Draw(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Initial Draw In
    if (assets.initialDrawIn == false) {
        assets.windowIcon.loadFromFile("F:/Pfp's n Icons/Profile Pictures/pfp.jpg");
        window.setIcon(assets.windowIcon.getSize().x, assets.windowIcon.getSize().y, assets.windowIcon.getPixelsPtr()); //set window icon
        assets.initialDrawIn = true;
    }
    // clear the window with black color
    window.clear(sf::Color::Black);

    // draw everything here...
    if (this->mainMenu == false) {
        assets.drawObjects();
        travel.travelCore(window, assets, notevent, combat, player);

        window.draw(assets.rect);
        window.draw(assets.map);
        window.draw(assets.playerText);
        window.draw(assets.locationText);
        window.draw(assets.text);
        window.draw(assets.combatText);

        //Draw Bonfire Detection Rect
        if (travel.forestBonfireInit == true) {
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

        if (assets.initMap == true) {
            //Draw main map rect
            window.draw(assets.rectMap);
            //Choose which map is selected
            switch (assets.mapCounter) {
            case 0:
                this->drawForestMap(window, assets);
                break;
            case 1:
                this->drawCastleMap(window, assets);
                break;
            }
            //Make Box Movable if clicked...
            this->movableBox(window, assets);
        }
        if (assets.initStats == true) {
            window.draw(assets.rectStatsBox);
            if (assets.playerStatsInit == true) {
                this->printPlayerStats(window, assets, notevent, combat, player);
            }
            else if (assets.zinStatsInit = true) {
                this->printZinStats(window, assets, notevent, combat, player);
            }
            window.draw(assets.rectStatsSideMenu);
            window.draw(assets.playerStatsBoxButtonText);
            window.draw(assets.zinStatsBoxButtonText);
        }
        if (assets.initInventory == true) {
            this->printInventory(window, assets, notevent, combat, player);
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

    // end the current frame
    window.display();
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
    if (assets.rect.getGlobalBounds().contains(mousePosF)) {
        assets.rect.setFillColor(sf::Color(10, 10, 10));
    }
    else {
        assets.rect.setFillColor(sf::Color::Black);
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
            assets.playerStatElements[i].setFillColor(sf::Color::Transparent);
            assets.playerTextElements[i].setFillColor(sf::Color::White);
        }
        else {
            assets.playerStatElements[i].setFillColor(sf::Color::White);
            assets.playerTextElements[i].setFillColor(sf::Color::Black);
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
}

void World::printPlayerStats(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    assets.playerTextElements[10].setString("HP: " + std::to_string(combat.playerHp) + "/" + 
        std::to_string(combat.playerHpMax) + "\nDECAY: " + std::to_string(player.decay) + "/" +
        std::to_string(player.decayMax) + "\n\nSP: " + std::to_string(player.sp) +
        "\nEXP: " + std::to_string(player.exp) + "/" + std::to_string(player.expNext));

    for (int i = 0; i < assets.playerStatElements.size(); i++) {
        window.draw(assets.playerStatElements[i]);
    }

    for (int i = 0; i < assets.playerTextElements.size(); i++) {
        window.draw(assets.playerTextElements[i]);
    }
}

void World::printZinStats(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    assets.zinTextElements[10].setString("HP: " + std::to_string(combat.zinHp) + "/" + std::to_string(combat.zinHpMax) + "\n\n\nSP: " + std::to_string(player.zinSp) +
        "\nEXP: " + std::to_string(player.zinExp) + "/" + std::to_string(player.zinExpNext));

    for (int i = 0; i < assets.zinStatElements.size(); i++) {
        window.draw(assets.playerStatElements[i]);
    }

    for (int i = 0; i < assets.zinTextElements.size(); i++) {
        window.draw(assets.zinTextElements[i]);
    }
}

void World::printInventory(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    assets.inventoryText.setString("[GENERAL ITEMS]\nGold: x" + std::to_string(player.gold) + "\nSmithing Stones: x"
        + std::to_string(player.smithingStones) + "\n\n[EQUIPPED ITEMS]\n" + player.basicSword);
}

//Display Element Functionality
void World::mainMenuButtons(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (assets.menuScreenElements[0].getGlobalBounds().contains(mousePosF)) {
        //Continue to other buttons asking to skip intro or not (New Game Button)
        assets.bootClicked = true;
    }
    else if (assets.menuScreenElements[1].getGlobalBounds().contains(mousePosF)) {
        //Loading Game Button Funcionality (Not implemented yet...)
        std::cout << "Loading a save hypothetically speaking lmao...";
    }
    else if (assets.menuScreenElements[2].getGlobalBounds().contains(mousePosF)) {
        //Quit Game Button Functionality (ERROR Not working...)
        stop = true;
    }
    else if (assets.menuScreenElements[3].getGlobalBounds().contains(mousePosF)) {
        //Intro Button Functionality
        this->mainMenu = false;
        travel.introCounterDialogue = 0; //Allow the counter to load the main image specifically just for the intro to take place
    }
    else if (assets.menuScreenElements[4].getGlobalBounds().contains(mousePosF)) {
        //Skip Intro Button Functionality
        this->mainMenu = false;
        assets.mapCounter = 0; //Skip intro and go straight to the forest
    }
}

void World::travelButtons(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Main View Buttons Control
    if (assets.spriteElements[0].getGlobalBounds().contains(mousePosF))
    {
        travel.frame++;
        travel.frameInit = false;
        assets.blipsound.play();
    }
    else if (assets.spriteElements[1].getGlobalBounds().contains(mousePosF))
    {
        travel.frame--;
        travel.frameInit = false;
        assets.blipsound.play();
    }
}

void World::mapButtons(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Map Button Functionality (Switching between whch button on the map is selected to change areas...)
    //Forest Button Functionality
    if (assets.mapForestElements[0].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.forestCounter = 0;
        travel.frameInit = false;
        travel.frame = 0;
        this->buttonClick = true;
    }
    else if (assets.mapForestElements[1].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.forestCounter = 1;
        travel.frameInit = false;
        travel.frame = 0;
        this->buttonClick = true;
    }
    else if (assets.mapForestElements[2].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.forestCounter = 2;
        travel.frameInit = false;
        travel.frame = 0;
        this->buttonClick = true;
    }
    else if (assets.mapForestElements[3].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.forestCounter = 3;
        travel.frameInit = false;
        travel.frame = 0;
        this->buttonClick = true;
    }
    
    //Castle Button Functionality
    if (assets.mapCastleElements[0].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.castleCounter = 0;
        travel.frameInit = false;
        this->buttonClick = true;
    }
    else if (assets.mapCastleElements[1].getGlobalBounds().contains(mousePosF)) {
        assets.soundWalk.play();
        travel.castleCounter = 1;
        travel.frameInit = false;
        this->buttonClick = true;
    }
}

void World::menuBar(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Map Menu Bar Functionaliy
    if (assets.multiArrow.getGlobalBounds().contains(mousePosF) && buttonClick == false) {
        //Click Multi Arrow to make map movable
        assets.movable = true;
    }
    else if (assets.multiArrow.getGlobalBounds().contains(mousePosF) && buttonClick == false) {
        assets.movableStatsBox = true;
    }
    if (assets.rectElements[2].getGlobalBounds().contains(mousePosF) && assets.initMap == false) {
        //Click to open map
        assets.initMap = true;
        assets.blipmenu.play();
    }
    else if (assets.rectElements[2].getGlobalBounds().contains(mousePosF) && assets.initMap == true) {
        //Click to close map
        assets.initMap = false;
        assets.rectMapX = 25;
        assets.rectMapY = 50;
        this->resetMapPosition(window, assets);
        assets.blipmenu.play();
    }
    this->buttonClick = false;
    //Stats Menu Bar Functionality
    if (assets.rectElements[0].getGlobalBounds().contains(mousePosF) && assets.initStats == false) {
        assets.initStats = true;
        assets.playerStatsInit = true;
        assets.blipmenu.play();
    }
    else if (assets.rectElements[0].getGlobalBounds().contains(mousePosF) && assets.initStats == true) {
        assets.initStats = false;
        assets.blipmenu.play();
    }
    //Inventory Menu Bar Functionality
    if (assets.rectElements[1].getGlobalBounds().contains(mousePosF) && assets.initInventory == false) {
        assets.initInventory = true;
        assets.blipmenu.play();
    }
    else if (assets.rectElements[1].getGlobalBounds().contains(mousePosF) && assets.initInventory == true) {
        assets.initInventory = false;
        assets.blipmenu.play();
    }
}

void World::menuBarStats(sf::RenderWindow& window, Combat& combat, Player& player, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Menu Bar Stats Functionality (Switching between who's stats are visible)
    if (assets.playerStatElements[4].getGlobalBounds().contains(mousePosF) || assets.zinStatElements[4].getGlobalBounds().contains(mousePosF)) {
        if (assets.playerStatsInit == false) {
            assets.playerStatsInit = true;
            assets.zinStatsInit = false;
        }
    }
    if (assets.playerStatElements[5].getGlobalBounds().contains(mousePosF) || assets.zinStatElements[4].getGlobalBounds().contains(mousePosF)) {
        if (assets.zinStatsInit == false) {
            assets.zinStatsInit = true;
            assets.playerStatsInit = false;
        }
    }
    //Level Up Functionality
    if (assets.initStats == false && assets.playerStatsInit == true) {
        assets.playerTextElements[4].setString("LEVEL " + std::to_string(player.level));
    }
    if (assets.initStats == true && assets.playerStatsInit == true) {
        if (assets.playerStatElements[0].getGlobalBounds().contains(mousePosF)) {
            if (player.exp >= player.expNext) {
                player.level++;
                player.sp++;
                player.exp -= player.expNext;
                assets.playerTextElements[4].setString("LEVEL " + std::to_string(player.level));
                assets.text.setString("Level up achieved. Level " + std::to_string(player.level) + " reached. One SP point acquired...");
                combat.updateStats(player);
            }
            else if (player.exp <= player.expNext) {
                assets.text.setString("Required Exp not met...");
            }
            this->buttonClick = true;
        }
    }

    //Strength up functionality
    if (assets.initStats == false && assets.playerStatsInit == true) {
        assets.playerTextElements[5].setString("STRENGTH " + std::to_string(player.strength));
    }
    if (assets.initStats == true && assets.playerStatsInit == true) {
        if (assets.playerStatElements[1].getGlobalBounds().contains(mousePosF)) {
            if (player.sp >= 1) {
                player.strength++;
                player.sp--;
                assets.playerTextElements[5].setString("STRENGTH " + std::to_string(player.strength));
                assets.text.setString("Strength improved. Level " + std::to_string(player.strength) + " in strength reached. One SP point spent...");
                combat.updateStats(player);
            }
            else if (player.sp <= 0) {
                assets.text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
    //Fortitude up functionality
    if (assets.initStats == false && assets.playerStatsInit == true) {
        assets.playerTextElements[6].setString("FORTITUDE " + std::to_string(player.fortitude));
    }
    if (assets.initStats == true && assets.playerStatsInit == true) {
        if (assets.playerStatElements[2].getGlobalBounds().contains(mousePosF)) {
            if (player.sp >= 1) {
                player.fortitude++;
                player.sp--;
                assets.playerTextElements[6].setString("FORTITUDE " + std::to_string(player.fortitude));
                assets.text.setString("Fortitude improved. Level " + std::to_string(player.fortitude) + " in fortitude reached. One SP point spent...");
                combat.updateStats(player);
            }
            else if (player.sp <= 0) {
                assets.text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
    //Vitality up functionality
    if (assets.initStats == false && assets.playerStatsInit == true) {
        assets.playerTextElements[7].setString("VITALITY " + std::to_string(player.vitality));
    }
    if (assets.initStats == true && assets.playerStatsInit == true) {
        if (assets.playerStatElements[3].getGlobalBounds().contains(mousePosF)) {
            if (player.sp >= 1) {
                player.vitality++;
                player.sp--;
                combat.playerHp += player.vitality; 
                combat.playerHpMax = combat.playerHp;
                assets.playerTextElements[7].setString("VITALITY " + std::to_string(player.vitality));
                assets.text.setString("Vitality improved. Level " + std::to_string(player.vitality) + " in vitality reached. One SP point spent...");
                combat.updateStats(player);
            }
            else if (player.sp <= 0) {
                assets.text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Stats Level up Functionality
    if (assets.initStats == true && assets.zinStatsInit == true) {
        assets.zinTextElements[4].setString("LEVEL " + std::to_string(player.zinLevel));
    }
    if (assets.initStats == true && assets.zinStatsInit == true) {
        if (assets.zinStatElements[0].getGlobalBounds().contains(mousePosF)) {
            if (player.zinExp >= player.zinExpNext) {
                player.zinLevel++;
                player.zinSp++;
                player.zinExp -= player.zinExpNext;
                assets.zinTextElements[4].setString("LEVEL " + std::to_string(player.zinLevel));
                assets.text.setString("Level up achieved. Level " + std::to_string(player.zinLevel) + " reached for Zin. One SP point acquired...");
                combat.updateStatsZin(player);
            }
            else if (player.zinExp <= player.zinExpNext) {
                assets.text.setString("Zin's required Exp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Resolve up Functionality
    if (assets.initStats == true && assets.zinStatsInit == true) {
        assets.zinTextElements[5].setString("RESOLVE " + std::to_string(player.zinResolve));
    }
    if (assets.initStats == true && assets.zinStatsInit == true) {
        if (assets.zinStatElements[1].getGlobalBounds().contains(mousePosF)) {
            if (player.zinSp >= 1) {
                player.zinResolve++;
                player.zinSp--;
                assets.zinTextElements[5].setString("RESOLVE " + std::to_string(player.zinResolve));
                assets.text.setString("Zin's resolve increased. Level " + std::to_string(player.zinResolve) + " reached in resolve for Zin. One SP point spent...");
                combat.updateStatsZin(player);
            }
            else if (player.zinExp <= 0) {
                assets.text.setString("Zin's required Sp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Patience up Functionality
    if (assets.initStats == true && assets.zinStatsInit == true) {
        assets.zinTextElements[6].setString("PATIENCE " + std::to_string(player.zinPatience));
    }
    if (assets.initStats == true && assets.zinStatsInit == true) {
        if (assets.zinStatElements[2].getGlobalBounds().contains(mousePosF)) {
            if (player.zinSp >= 1) {
                player.zinPatience++;
                player.zinSp--;
                assets.zinTextElements[6].setString("PATIENCE " + std::to_string(player.zinPatience));
                assets.text.setString("Zin's patience increased. Level " + std::to_string(player.zinPatience) + " reached in patience for Zin. One SP point spent...");
                combat.updateStatsZin(player);
            }
            else if (player.zinExp <= 0) {
                assets.text.setString("Zin's required Sp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Resilience up Functionality
    if (assets.initStats == true && assets.zinStatsInit == true) {
        assets.zinTextElements[7].setString("RESILIENCE " + std::to_string(player.zinResilience));
    }
    if (assets.initStats == true && assets.zinStatsInit == true) {
        if (assets.zinStatElements[3].getGlobalBounds().contains(mousePosF)) {
            if (player.zinSp >= 1) {
                player.zinResilience++;
                player.zinSp--;
                assets.zinTextElements[7].setString("RESILIENCE " + std::to_string(player.zinResilience));
                assets.text.setString("Zin's resilience increased. Level " + std::to_string(player.zinResilience) + " reached in resilience for Zin. One SP point spent...");
                combat.updateStatsZin(player);
            }
            else if (player.zinExp <= 0) {
                assets.text.setString("Zin's required Sp not met...");
            }
            this->buttonClick = true;
        }
    }
}

void World::dialogueBox(sf::RenderWindow& window, Combat& combat, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (assets.rectElements[3].getGlobalBounds().contains(mousePosF)) { //If attack button is clicked...
        if (combat.turnPlayer == true) {
            combat.attackCounter++;
        }
    }
    if (assets.rectElements[4].getGlobalBounds().contains(mousePosF)) {
        if (combat.turnZin == true) {
            combat.zinAttackCounter++;
        }
    }
    else if (assets.rect.getGlobalBounds().contains(mousePosF)) { //If dialogue box is clicked...
        assets.dialogueCounter++;
        travel.frameInit = false; //Allow images to be loaded again
        travel.introCounterDialogue++;
        if (combat.attackCounter == 1) {
            combat.attackCounter = 2;
        }
        if (combat.zinAttackCounter == 1) {
            combat.zinAttackCounter = 2;
        }
        if (combat.turnHostile == true) {
            assets.combatCounter++;
        }
        assets.spadeInit = false;
    }
}

void World::movableBox(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (assets.movable == true) {
        assets.rectMapX = mousePos.x - 365;
        assets.rectMapY = mousePos.y - 23;
        this->resetMapPosition(window, assets);
    }
}

void World::resetMapPosition(sf::RenderWindow& window, Assets& assets)
{
    //Castle
    assets.spriteMapView.setPosition(assets.rectMapX, assets.rectMapY);
    assets.mapCastleElements[0].setPosition(assets.rectMapX + 34, assets.rectMapY + 20);
    assets.mapCastleElements[1].setPosition(assets.rectMapX + 75, assets.rectMapY + 240);
    //Forest
    assets.forestMapView.setPosition(assets.rectMapX, assets.rectMapY);
    assets.mapForestElements[0].setPosition(assets.rectMapX + 145, assets.rectMapY + 25);
    assets.mapForestElements[1].setPosition(assets.rectMapX + 34, assets.rectMapY + 20);
    assets.mapForestElements[2].setPosition(assets.rectMapX + 75, assets.rectMapY + 240);
    assets.mapForestElements[3].setPosition(assets.rectMapX + 175, assets.rectMapY + 200);
    assets.mapForestElementsText[0].setPosition(assets.rectMapX + 145, assets.rectMapY + 10);
    assets.mapForestElementsText[1].setPosition(assets.rectMapX + 34, assets.rectMapY + 5);
    assets.mapForestElementsText[2].setPosition(assets.rectMapX + 75, assets.rectMapY + 225);
    assets.mapForestElementsText[3].setPosition(assets.rectMapX + 175, assets.rectMapY + 185);
}

//Map Functions
void World::drawForestMap(sf::RenderWindow& window, Assets& assets)
{
    window.draw(assets.forestMapView);
    window.draw(assets.multiArrow);
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
    for (int i = 0; i < assets.mapCastleElements.size(); i++) {
        window.draw(assets.mapCastleElements[i]);
    }

    for (int i = 0; i < assets.mapCastleElementsText.size(); i++) {
        window.draw(assets.mapCastleElementsText[i]);
    }
}