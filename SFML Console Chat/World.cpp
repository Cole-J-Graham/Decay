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

    //Menu Bool
    this->statsmenu = false;

    //Quest Bool
    this->buttonClick = false;

    //Player Stats
    this->level = 1;
    this->strike = 10;
    this->hp = 100;
    this->hpMax = 100;

    //Coordinate Plane
    this->xCord = 1920;
    this->yCord = 600;

    this->test = 0;
}

World::~World() 
{

}

//Core Functions
void World::bootUp()
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
                    this->greyOnHover(window);
                }
                break;
            case sf::Event::MouseButtonPressed:
                { //Get Mouse Click Input
                    this->travelButtons(window);
                    //If button in map is clicked, do something
                    this->mapButtons(window);
                    //Map Menu Bar Functionality
                    this->menuBarStats(window); //Must be loaded before menuBar(window); to withhold functionality
                    this->menuBar(window);
                    //Dialogue Box Functionality...
                    this->dialogueBox(window);
                }
                break;
            case sf::Event::MouseButtonReleased:
                {
                    assets.movable = false;
                    assets.movableStatsBox = false;
                }
            }
            //Run Main Function Loop...
            this->mainLoop();
        }
        //Draw Everything...
        this->Draw(window);
    }
}

void World::mainLoop()
{
    //Run Main Functions
    this->userInput();
    travel.travelCore(assets);
}

//User Input
void World::userInput()
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
void World::Draw(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // clear the window with black color
    window.clear(sf::Color::Black);

    // draw everything here...
    assets.drawObjects();
    travel.travelCore(assets);

    window.draw(assets.rect);
    window.draw(assets.map);
    window.draw(assets.buttonMap);
    window.draw(assets.button);
    window.draw(assets.buttonBack);
    window.draw(assets.playerText);
    window.draw(assets.locationText);
    window.draw(assets.text);
    window.draw(assets.combatText);
    window.draw(assets.rectSpriteBox);
    window.draw(assets.sprite);
    window.draw(assets.spriteText);
    window.draw(assets.menuText);
    window.draw(assets.rectStats);
    window.draw(assets.rectStatsText);
    //Draw Combat Stuff
    if (assets.playerTurnAssets == true) {
        window.draw(assets.rectAttack);
        window.draw(assets.rectFlee);
        window.draw(assets.attackText);
        window.draw(assets.fleeText);
    }
    window.draw(assets.playerSpriteBorder);
    window.draw(assets.playerNameText);
    window.draw(assets.zinSpriteBorder);
    window.draw(assets.zinText);
    window.draw(assets.hostileSpriteBorder);
    window.draw(assets.hostileNameText);
    window.draw(assets.zin);
    if (assets.initMap == true) {
        window.draw(assets.rectMap);
        window.draw(assets.spriteMapView);
        window.draw(assets.buttonCastleEntrance);
        window.draw(assets.buttonCastleDepths);
        window.draw(assets.castleEntranceText);
        window.draw(assets.castleDepthsText);
        if (assets.movable == true) {
            assets.rectMapX = mousePos.x - 190;
            assets.rectMapY = mousePos.y;
            assets.spriteMapView.setPosition(assets.rectMapX, assets.rectMapY);
            assets.buttonCastleEntrance.setPosition(assets.rectMapX + 34, assets.rectMapY + 20);
            assets.buttonCastleDepths.setPosition(assets.rectMapX + 75, assets.rectMapY + 240);
        }
    }
    if (assets.initStats == true) {
        window.draw(assets.rectStatsBox);
        window.draw(assets.statsText);
        window.draw(assets.rectStatsPointsBox);
        window.draw(assets.rectStrengthPointsBox);
        window.draw(assets.statsPointsText);
        window.draw(assets.statsPointsTextTitle);
        window.draw(assets.statsStrengthTextTitle);
        window.draw(assets.statsStrengthText);
        assets.statsText.setString("HP: " + std::to_string(combat.playerHp) + "/" + std::to_string(combat.playerHpMax) + "\nSP: " + std::to_string(player.sp));
        if (assets.movableStatsBox == true) {
            assets.rectStatsBoxX = mousePos.x - 100;
            assets.rectStatsBoxY = mousePos.y;
        }
    }

    // end the current frame
    window.display();
}

void World::greyOnHover(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (assets.button.getGlobalBounds().contains(mousePosF))
    {
        assets.button.setColor(sf::Color(155, 155, 155));
    }//Turn forward button grey on hover
    else {
        assets.button.setColor(sf::Color(255, 255, 255));
    }
    //Turn back button grey on hover
    if (assets.buttonBack.getGlobalBounds().contains(mousePosF)) {
        assets.buttonBack.setColor(sf::Color(155, 155, 155));
    }
    else {
        assets.buttonBack.setColor(sf::Color(255, 255, 255));
    }
    if (assets.buttonMap.getGlobalBounds().contains(mousePosF)) {
        assets.buttonMap.setFillColor(sf::Color::Transparent);
        assets.menuText.setFillColor(sf::Color::White);
    }
    else {
        assets.buttonMap.setFillColor(sf::Color::White);
        assets.menuText.setFillColor(sf::Color::Black);
    }

    //Turn rect button grey on hover
    if (assets.rectStats.getGlobalBounds().contains(mousePosF)) {
        assets.rectStats.setFillColor(sf::Color::Transparent);
        assets.rectStatsText.setFillColor(sf::Color::White);
    }
    else {
        assets.rectStats.setFillColor(sf::Color::White);
        assets.rectStatsText.setFillColor(sf::Color::Black);
    }
    //Turn map travel buttons grey on hover
    if (assets.initMap == true) {
        if (assets.buttonCastleEntrance.getGlobalBounds().contains(mousePosF)) {
            assets.buttonCastleEntrance.setColor(sf::Color(155, 155, 155));
        }
        else {
            assets.buttonCastleEntrance.setColor(sf::Color(255, 255, 255));
        }
    }
    if (assets.initMap == true) {
        if (assets.buttonCastleDepths.getGlobalBounds().contains(mousePosF)) {
            assets.buttonCastleDepths.setColor(sf::Color(155, 155, 155));
        }
        else {
            assets.buttonCastleDepths.setColor(sf::Color(255, 255, 255));
        }
    }
    //Turn Stats Points Button Grey
    if (assets.initStats == true) {
        if (assets.rectStatsPointsBox.getGlobalBounds().contains(mousePosF)) {
            assets.rectStatsPointsBox.setFillColor(sf::Color::Black);
            assets.statsPointsText.setFillColor(sf::Color(sf::Color::White));
        }
        else {
            assets.rectStatsPointsBox.setFillColor(sf::Color(255, 255, 255));
            assets.statsPointsText.setFillColor(sf::Color(sf::Color::Black));
        }
    }
    if (assets.initStats == true) {
        if (assets.rectStrengthPointsBox.getGlobalBounds().contains(mousePosF)) {
            assets.rectStrengthPointsBox.setFillColor(sf::Color::Black);
            assets.statsStrengthText.setFillColor(sf::Color(sf::Color::White));
        }
        else {
            assets.rectStrengthPointsBox.setFillColor(sf::Color(255, 255, 255));
            assets.statsStrengthText.setFillColor(sf::Color(sf::Color::Black));
        }
    }
 
    //Turn Combat Menu Buttons Grey On Hover
    if (assets.rectAttack.getGlobalBounds().contains(mousePosF)) {
        assets.rectAttack.setFillColor(sf::Color::Transparent);
        assets.attackText.setFillColor(sf::Color::White);
        assets.rectFlee.setFillColor(sf::Color::White);
        assets.fleeText.setFillColor(sf::Color::Black);
        assets.rect.setFillColor(sf::Color::Black);
    } else if (assets.rectFlee.getGlobalBounds().contains(mousePosF)) {
        assets.rectFlee.setFillColor(sf::Color::Transparent);
        assets.fleeText.setFillColor(sf::Color::White);
        assets.rectAttack.setFillColor(sf::Color::White);
        assets.attackText.setFillColor(sf::Color::Black);
        assets.rect.setFillColor(sf::Color::Black);
    }
    else if (assets.rect.getGlobalBounds().contains(mousePosF)) {
        assets.rect.setFillColor(sf::Color(10, 10, 10));
        assets.rectAttack.setFillColor(sf::Color::White);
        assets.attackText.setFillColor(sf::Color::Black);
        assets.rectFlee.setFillColor(sf::Color::White);
        assets.fleeText.setFillColor(sf::Color::Black);
    }
    else { //Turn dialogue box grey on hover
        assets.rectAttack.setFillColor(sf::Color::White);
        assets.attackText.setFillColor(sf::Color::Black);
        assets.rectFlee.setFillColor(sf::Color::White);
        assets.fleeText.setFillColor(sf::Color::Black);

        assets.rect.setFillColor(sf::Color::Black);
    }
}

//Display Element Functionality
void World::travelButtons(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Main View Buttons Control
    if (assets.button.getGlobalBounds().contains(mousePosF))
    {
        travel.frame++;
        travel.frameInit = false;
        assets.blipsound.play();
    }
    else if (assets.buttonBack.getGlobalBounds().contains(mousePosF))
    {
        travel.frame--;
        travel.frameInit = false;
        assets.blipsound.play();
    }
}

void World::mapButtons(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Castle Entrance Button Functionality
    if (assets.initMap == true) {
        if (assets.buttonCastleEntrance.getGlobalBounds().contains(mousePosF)) {
            assets.soundWalk.play();
            travel.castleEntranceInit = true;
            travel.castleDepthsInit = false;
            travel.frameInit = false;
            this->buttonClick = true;
        }
        else if (assets.buttonCastleDepths.getGlobalBounds().contains(mousePosF)){
            assets.soundWalk.play();
            travel.castleEntranceInit = false;
            travel.castleDepthsInit = true;
            travel.frameInit = false;
            this->buttonClick = true;
        }
    }
}

void World::menuBar(sf::RenderWindow& window)
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
    if (assets.buttonMap.getGlobalBounds().contains(mousePosF) && assets.initMap == false) {
        assets.mapCounter++;
        assets.initMap = true;
        assets.blipmenu.play();
    }
    else if (assets.buttonMap.getGlobalBounds().contains(mousePosF) && assets.initMap == true) {
        //Click to close map 
        assets.initMap = false;
        assets.rectMapX = 25;
        assets.rectMapY = 50;
        assets.spriteMapView.setPosition(assets.rectMapX, assets.rectMapY);
        assets.buttonCastleEntrance.setPosition(assets.rectMapX + 34, assets.rectMapY + 20);
        assets.buttonCastleDepths.setPosition(assets.rectMapX + 75, assets.rectMapY + 240);
        assets.castleDepthsText.setPosition(assets.rectMapX + 40, assets.rectMapY + 220);
        assets.castleEntranceText.setPosition(assets.rectMapX, assets.rectMapY + 5);
        assets.blipmenu.play();
    }
    this->buttonClick = false;
    //Stats Menu Bar Functionality
    if (assets.rectStats.getGlobalBounds().contains(mousePosF) && assets.initStats == false) {
        assets.initStats = true;
        assets.blipmenu.play();
    }
    else if (assets.rectStats.getGlobalBounds().contains(mousePosF) && assets.initStats == true) {
        assets.initStats = false;
        assets.blipmenu.play();
    }
}

void World::menuBarStats(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Level Up Functionality
    if (assets.initStats == false) {
        assets.statsPointsTextTitle.setString("LEVEL " + std::to_string(player.level));
    }
    if (assets.initStats == true) {
        if (assets.rectStatsPointsBox.getGlobalBounds().contains(mousePosF)) {
            if (player.exp >= player.expNext) {
                player.level++;
                player.sp++;
                player.exp -= player.expNext;
                assets.statsPointsTextTitle.setString("LEVEL " + std::to_string(player.level));
                assets.text.setString("Level up achieved. Level " + std::to_string(player.level) + " reached. One SP point acquired...");
            }
            else if (player.exp <= player.expNext) {
                assets.text.setString("Required Exp not met...");
            }
            this->buttonClick = true;
        }
    }
    //Strength up functionality
    if (assets.initStats == false) {
        assets.statsStrengthTextTitle.setString("STRENGTH " + std::to_string(player.strength));
    }
    if (assets.initStats == true) {
        if (assets.rectStrengthPointsBox.getGlobalBounds().contains(mousePosF)) {
            if (player.sp >= 1) {
                player.strength++;
                player.sp--;
                assets.statsStrengthTextTitle.setString("STRENGTH " + std::to_string(player.strength));
                assets.text.setString("Strength improved. Level " + std::to_string(player.strength) + " in strength reached. One SP point spent...");
            }
            else if (player.sp <= 0) {
                assets.text.setString("Required SP not met...");
            }
            this->buttonClick = true;
        }
    }
}

void World::dialogueBox(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (assets.rectAttack.getGlobalBounds().contains(mousePosF)) { //If attack button is clicked...
        std::cout << "\nAttack Button Clicked...";
        assets.attackCounter = 1;
    } 
    else if (assets.rectFlee.getGlobalBounds().contains(mousePosF)) { //If flee button is clicked...
        std::cout << "\nFlee Button Clicked...";
        assets.attackCounter = 2;
    } 
    else if (assets.rect.getGlobalBounds().contains(mousePosF)) { //If dialogue box is clicked...
        std::cout << "\nDialogue Box Clicked...";
        assets.dialogueCounter++;
        if (assets.combatAssets == true) {
            assets.combatCounter++;
        }
        assets.spadeInit = false;
    }
}