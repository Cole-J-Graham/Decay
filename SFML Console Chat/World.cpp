#include"World.h"

//Constructors and Destructors
World::World()
{
    //Core
    this->input = input;
    this->targetHpView = targetHpView;
    this->unicode = unicode;
    this->random = random;
    this->map = 0;

    //Core Bool
    this->stop = false;
    this->keyPress = true;
    this->initialized = false;
    this->comInitialized = false;
    this->bonfire = true;

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
    travel.travelCore(assets, notevent, combat, player);
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
    assets.drawObjects();
    travel.travelCore(assets, notevent, combat, player);

    window.draw(assets.rect);
    window.draw(assets.map);
    window.draw(assets.playerText);
    window.draw(assets.locationText);
    window.draw(assets.text);
    window.draw(assets.combatText);

    if (assets.initMap == true) {
        //Draw main map rect
        window.draw(assets.rectMap);
        //Choose which map is selected
        switch (this->map) {
        case 0:
            this->drawCastleMap(window, assets);
            break;
        }
        if (assets.movable == true) {
            assets.rectMapX = mousePos.x - 190;
            assets.rectMapY = mousePos.y;
            assets.spriteMapView.setPosition(assets.rectMapX, assets.rectMapY);
            assets.mapCastleElements[0].setPosition(assets.rectMapX + 34, assets.rectMapY + 20);
            assets.mapCastleElements[1].setPosition(assets.rectMapX + 75, assets.rectMapY + 240);
        }
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
        if (assets.movableStatsBox == true) {
            assets.rectStatsBoxX = mousePos.x - 100;
            assets.rectStatsBoxY = mousePos.y;
        }
    }
    if (assets.initInventory == true) {
        this->printInventory(window, assets, notevent, combat, player);
        window.draw(assets.rectInventoryBox);
        window.draw(assets.inventoryText);
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
}

void World::printPlayerStats(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    assets.playerTextElements[10].setString("HP: " + std::to_string(combat.playerHp) + "/" + std::to_string(combat.playerHpMax) + "\nSP: " + std::to_string(player.sp) +
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
    assets.zinTextElements[10].setString("HP: " + std::to_string(combat.zinHp) + "/" + std::to_string(combat.zinHpMax) + "\nSP: " + std::to_string(combat.zinSp) +
        "\nEXP: " + std::to_string(combat.zinExp) + "/" + std::to_string(combat.zinExpNext));

    for (int i = 0; i < assets.zinStatElements.size(); i++) {
        window.draw(assets.playerStatElements[i]);
    }

    for (int i = 0; i < assets.zinTextElements.size(); i++) {
        window.draw(assets.zinTextElements[i]);
    }
}

void World::printInventory(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    assets.inventoryText.setString("x1 A Fucking Gun");
}

//Display Element Functionality
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
    //Castle Entrance Button Functionality
    if (assets.initMap == true) {
        if (assets.mapCastleElements[0].getGlobalBounds().contains(mousePosF)) {
            assets.soundWalk.play();
            travel.castleEntranceInit = true;
            travel.castleDepthsInit = false;
            travel.frameInit = false;
            this->buttonClick = true;
        }
        else if (assets.mapCastleElements[1].getGlobalBounds().contains(mousePosF)) {
            assets.soundWalk.play();
            travel.castleEntranceInit = false;
            travel.castleDepthsInit = true;
            travel.frameInit = false;
            this->buttonClick = true;
        }
    }
}

void World::menuBar(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Map Menu Bar Functionaliy
    if (assets.rectMap.getGlobalBounds().contains(mousePosF) && clickTime.getElapsedTime().asSeconds() < 0.3 && buttonClick == false) {
        assets.movable = true;
    }
    else if (assets.rectStatsBox.getGlobalBounds().contains(mousePosF) && clickTime.getElapsedTime().asSeconds() < 0.3 && buttonClick == false) {
        assets.movableStatsBox = true;
    }
    if (assets.rectElements[2].getGlobalBounds().contains(mousePosF) && assets.initMap == false) {
        //Click to open map
        assets.initMap = true;
        assets.mapCounter++;
        assets.blipmenu.play();
    }
    else if (assets.rectElements[2].getGlobalBounds().contains(mousePosF) && assets.initMap == true) {
        //Click to close map
        assets.initMap = false;
        assets.rectMapX = 25;
        assets.rectMapY = 50;
        assets.spriteMapView.setPosition(assets.rectMapX, assets.rectMapY);
        assets.mapCastleElements[0].setPosition(assets.rectMapX + 34, assets.rectMapY + 20);
        assets.mapCastleElements[1].setPosition(assets.rectMapX + 75, assets.rectMapY + 240);
        assets.mapCastleElementsText[0].setPosition(assets.rectMapX, assets.rectMapY + 5);
        assets.mapCastleElementsText[1].setPosition(assets.rectMapX + 40, assets.rectMapY + 220);
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
        assets.zinTextElements[4].setString("LEVEL " + std::to_string(combat.zinLevel));
    }
    if (assets.initStats == true && assets.zinStatsInit == true) {
        if (assets.zinStatElements[0].getGlobalBounds().contains(mousePosF)) {
            if (combat.zinExp >= combat.zinExpNext) {
                combat.zinLevel++;
                combat.zinSp++;
                combat.zinExp -= combat.zinExpNext;
                assets.zinTextElements[4].setString("LEVEL " + std::to_string(combat.zinLevel));
                assets.text.setString("Level up achieved. Level " + std::to_string(combat.zinLevel) + " reached for Zin. One SP point acquired...");
                combat.updateStatsZin();
            }
            else if (combat.zinExp <= combat.zinExpNext) {
                assets.text.setString("Zin's required Exp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Resolve up Functionality
    if (assets.initStats == true && assets.zinStatsInit == true) {
        assets.zinTextElements[5].setString("RESOLVE " + std::to_string(combat.zinResolve));
    }
    if (assets.initStats == true && assets.zinStatsInit == true) {
        if (assets.zinStatElements[1].getGlobalBounds().contains(mousePosF)) {
            if (combat.zinSp >= 1) {
                combat.zinResolve++;
                combat.zinSp--;
                assets.zinTextElements[5].setString("RESOLVE " + std::to_string(combat.zinResolve));
                assets.text.setString("Zin's resolve increased. Level " + std::to_string(combat.zinResolve) + " reached in resolve for Zin. One SP point spent...");
                combat.updateStatsZin();
            }
            else if (combat.zinExp <= 0) {
                assets.text.setString("Zin's required Sp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Patience up Functionality
    if (assets.initStats == true && assets.zinStatsInit == true) {
        assets.zinTextElements[6].setString("PATIENCE " + std::to_string(combat.zinPatience));
    }
    if (assets.initStats == true && assets.zinStatsInit == true) {
        if (assets.zinStatElements[2].getGlobalBounds().contains(mousePosF)) {
            if (combat.zinSp >= 1) {
                combat.zinPatience++;
                combat.zinSp--;
                assets.zinTextElements[6].setString("PATIENCE " + std::to_string(combat.zinPatience));
                assets.text.setString("Zin's patience increased. Level " + std::to_string(combat.zinPatience) + " reached in patience for Zin. One SP point spent...");
                combat.updateStatsZin();
            }
            else if (combat.zinExp <= 0) {
                assets.text.setString("Zin's required Sp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Zin Resilience up Functionality
    if (assets.initStats == true && assets.zinStatsInit == true) {
        assets.zinTextElements[7].setString("RESILIENCE " + std::to_string(combat.zinResilience));
    }
    if (assets.initStats == true && assets.zinStatsInit == true) {
        if (assets.zinStatElements[3].getGlobalBounds().contains(mousePosF)) {
            if (combat.zinSp >= 1) {
                combat.zinResilience++;
                combat.zinSp--;
                assets.zinTextElements[7].setString("RESILIENCE " + std::to_string(combat.zinResilience));
                assets.text.setString("Zin's resilience increased. Level " + std::to_string(combat.zinResilience) + " reached in resilience for Zin. One SP point spent...");
                combat.updateStatsZin();
            }
            else if (combat.zinExp <= 0) {
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

//Map Functions
void World::drawCastleMap(sf::RenderWindow& window, Assets& assets)
{
    //Draw Everything
    window.draw(assets.spriteMapView);
    for (int i = 0; i < assets.mapCastleElements.size(); i++) {
        window.draw(assets.mapCastleElements[i]);
    }

    for (int i = 0; i < assets.mapCastleElementsText.size(); i++) {
        window.draw(assets.mapCastleElementsText[i]);
    }
}