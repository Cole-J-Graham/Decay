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
    this->questboard = false;

    //Combat Bool
    this->combat = false;
    this->combatPlayer = false;
    this->combatTarget = false;
    this->hostile1 = false;
    this->combatvictory = false;
    this->playerturn = true;
    this->targetturn = true;

    //Player Stats
    this->level = 1;
    this->strike = 10;
    this->hp = 100;
    this->hpMax = 100;

    //Coordinate Plane
    this->xCord = 1920;
    this->yCord = 600;

    //Enemy Stats
    this->targetHp = 50;
    this->targetHpMax = 50;
    this->targetStrike = 15;

    this->test = 0;
}

World::~World() 
{

}

//Core Functions
void World::bootUp()
{
    //Load Combat Sound Effects
    bufferCom.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/Boss hit 1.wav");
    soundCom.setBuffer(bufferCom);
    //Load Text Sfx
    buffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/Text 1.wav");
    sound.setBuffer(buffer);
    //Load Button Sfx
    blipbuffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/blipSelect.wav");
    blipsound.setBuffer(blipbuffer);
    blipmenubuffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/menuclick.wav");
    blipmenu.setBuffer(blipmenubuffer);
    //Load and stream music
    music.openFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Music/track1.wav");
    //music.play();

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
                    //Turn forward button grey on hover
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

                    if (assets.initMap == true) {
                        if (assets.buttonMapSprite.getGlobalBounds().contains(mousePosF)) {
                            assets.buttonMapSprite.setColor(sf::Color(155, 155, 155));
                        }
                        else {
                            assets.buttonMapSprite.setColor(sf::Color(255, 255, 255));
                        }
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                { //Get Mouse Click Input
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    //Main View Buttons Control
                    if (assets.button.getGlobalBounds().contains(mousePosF))
                    {
                        assets.testTexture++;
                        assets.init = false;
                        blipsound.play();
                        //travel.setTravelingTrue();
                    }
                    else if (assets.buttonBack.getGlobalBounds().contains(mousePosF))
                    {
                        assets.testTexture--;
                        assets.init = false;
                        blipsound.play();
                    }
                    //If button in map is clicked, do something
                    if (assets.initMap == true) {
                        if (assets.buttonMapSprite.getGlobalBounds().contains(mousePosF)) {
                            assets.castleEntrance = false;
                            assets.castleDepths = true;
                            assets.init = false;
                        }
                        else {

                        }
                    }
                    //Map Menu Bar Control
                    if (assets.rectMap.getGlobalBounds().contains(mousePosF) && clickTime.getElapsedTime().asSeconds() < 0.1) {
                        assets.movable = true;
                    }
                    if (assets.buttonMap.getGlobalBounds().contains(mousePosF) && assets.initMap == false) {
                        assets.testMap++;
                        assets.initMap = true;
                        blipmenu.play();
                    }
                    else if (assets.buttonMap.getGlobalBounds().contains(mousePosF) && assets.initMap == true) {
                        assets.initMap = false;
                        assets.rectMapX = 25;
                        assets.rectMapY = 50;
                        assets.spriteMapView.setPosition(assets.rectMapX, assets.rectMapY);
                        assets.buttonMapSprite.setPosition(assets.rectMapX + 20, assets.rectMapY + 20);
                        blipmenu.play();
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                {
                    assets.movable = false;
                }
            }
            //Run Main Function Loop
            this->mainLoop();
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        assets.drawObjects();

        window.draw(assets.rect);
        window.draw(assets.map);
        window.draw(assets.buttonMap);
        window.draw(assets.button);
        window.draw(assets.buttonBack);
        window.draw(assets.playerText);
        window.draw(assets.locationText);
        window.draw(assets.text);
        window.draw(assets.combatText);
        window.draw(assets.sprite);
        window.draw(assets.spriteText);
        window.draw(assets.menuText);
        if (assets.initMap == true) {
            window.draw(assets.rectMap);
            window.draw(assets.spriteMapView);
            window.draw(assets.buttonMapSprite);
            if (assets.movable == true) {
                assets.rectMapX = mousePos.x - 190;
                assets.rectMapY = mousePos.y;
                assets.spriteMapView.setPosition(assets.rectMapX, assets.rectMapY);
                assets.buttonMapSprite.setPosition(assets.rectMapX + 20, assets.rectMapY + 20);
            }
        }

        // end the current frame
        window.display();
    }
}

void World::mainLoop()
{
    //Run Main Functions
    this->userInput();
    this->bonFire();
    this->questBoard();
    this->statsMenu();
    this->combatInit();
    this->playerTurn();
    this->targetTurn();
    this->combatVictory();

    travel.travelScreen();
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
        sound.play();
        
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

//Menu Functions
void World::bonFire()
{
    if (initialized == false) {
        //Change Text
        assets.text.setString("  BonFire Options\n 1:|Quest Board\n 2:|View Stats\n 3:|Hunt");
        //Add Sprite
        assets.spriteZinNormal = true;

        //Main Choices For Menu
        switch (unicode) {
        case 49:
            this->clearInput();
            this->initialized = true;
            this->questboard = true;
            this->questBoard();
            break;
        case 50:
            this->clearInput();
            this->initialized = true;
            this->questboard = false;
            this->statsmenu = true;
            this->statsMenu();
            break;
        case 51:
            this->clearInput();
            this->initialized = true;
            this->questboard = false;
            this->statsmenu = false;
            this->combat = true;
            this->combatInit();
            break;
        }
    }
}

void World::questBoard()
{
    if (questboard == true) {
        assets.text.setString("  Quests\n 0:|Return\n 1:|Quest One");
    
        switch (unicode) {
        case 48:
            clearInput();
            this->initialized = false;
            this->questboard = false;
            this->bonFire();
            break;
        case 49:
            clearInput();
            this->questboard = false;
            break;
        }
    }
}

void World::statsMenu()
{
    if (statsmenu == true) {
        assets.text.setString("  Statistics\n 0:|Return\n 1:|View Stats");

        switch (unicode) {
        case 48:
            clearInput();
            assets.combatText.setString("");
            this->initialized = false;
            this->statsmenu = false;
            this->bonFire();
            break;
        case 49:
            clearInput();
            assets.combatText.setString("  ATTACK: 12\n DEF: 2...");
            break;
        }
    }
}

//Combat Functions
void World::combatInit()
{
    if (combat == true) {
        this->playerturn = true;
        this->targetturn = true;
        assets.text.setString("A combatant Ambushes you from the dark! \n1:|Strike");
        //Change Sprites
        assets.spriteZinNormal = false;
        assets.spriteZinSmug = true;

        switch (unicode) {
        case 49:
            this->clearInput();
            this->combat = false;
            this->combatPlayer = true;
            this->playerTurn();
            break;
        }
    }
}

void World::playerTurn()
{
    if (combatPlayer == true && playerturn == true) {
        assets.text.setString("You strike the combatant! Enemy revealed! \nPress '1' to continue...");
        soundCom.play();
        targetHp -= strike;
        if (targetHp <= 0) {
            this->clearInput();
            this->combatPlayer = false;
            this->playerturn = false;
            this->combatvictory = true;
            this->combatVictory();
        }
        assets.combatText.setString("Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
            + "\n Your HP ->" + std::to_string(hp) + "/" + std::to_string(hpMax));
        this->playerturn = false;
    }
    else if (combatPlayer == true) {
        switch (unicode) {
        case 49:
            this->clearInput();
            this->combatPlayer = false;
            this->combatTarget = true;
            this->targetTurn();
            break;
        }
    }
}

void World::targetTurn()
{
    if (combatTarget == true && targetturn == true) {
        assets.text.setString("Target attacking! Press '1' to continue...");
        assets.combatText.setString("Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
            + "\n Your HP ->" + std::to_string(hp) + "/" + std::to_string(hpMax));
        //Assign Random Chance
        srand((unsigned)time(NULL));
        this->random = 100 + (rand() % 20);

        switch (unicode) {
        case 49:
            //Targets Turn
            if (this->random < 110) {
                soundCom.play();
                this->clearInput();
                this->hp -= this->targetStrike;
                assets.combatText.setString("Target hit!\n Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
                    + "\n Your HP ->" + std::to_string(hp) + "/" + std::to_string(hpMax));
                this->combatTarget = false;
                this->targetturn = false;
                this->combat = true;
                this->combatInit();
            }
            else {
                this->clearInput();
                assets.combatText.setString("Target missed!\n Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
                    + "\n Your HP ->" + std::to_string(hp) + "/" + std::to_string(hpMax));
                this->combatTarget = false;
                this->targetturn = false;
                this->combat = true;
                this->combatInit();
            }
            break;
        }
    }
}

void World::combatVictory()
{
    if (this->combatvictory == true)
    {
        assets.text.setString("The abomination has fallen! Victory is yours! Press '0' to continue...");
        assets.combatText.setString("");

        switch (unicode) {
        case 48:
            this->clearInput();
            this->initialized = false;
            this->combatvictory = false;
            this->bonFire();
            break;
        }
    }
}