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

    //Menu Bool
    this->statsmenu = false;

    //Quest Bool
    this->questone = false;
    this->questboard = false;

    //Combat Bool
    this->combat = false;
    this->combatPlayer = false;
    this->combatTarget = false;
    this->hostile1 = false;
    this->combatStop = false;
    this->combatvictory = false;
    this->playerturn = true;
    this->targetturn = true;

    //Sprite Bool
    this->sprite1 = false;
    this->sprite2 = false;

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
    //Load Text Sound Effects
    buffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/Text 1.wav");
    sound.setBuffer(buffer);
    //Load and stream music
    music.openFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Music/track1.wav");
    //music.play();

    World multi;
    sf::Thread thread(&World::combatScreen, &multi);
    //thread.launch();

    //create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Console Chat"/*, sf::Style::Fullscreen*/);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            //std::cout << this->unicode; //Debug Code

            //Get Mouse User Input
            if (sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if (sprite.getGlobalBounds().contains(mousePosF))
                {
                    std::cout << "Clicked, yay!" << std::endl;
                }
            }
            //Run Main Functions
            this->userInput();
            this->mouseInput();
            this->bonFire();
            this->questBoard();
            this->statsMenu();
            this->questOne();
            this->combatInit();
            this->playerTurn();
            this->targetTurn();
            this->combatVictory();
        }

        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            this->stop = true;
            window.close();
        }
    
        
        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        this->zinSprite();
        this->drawTextBox();
        this->drawOutputBox();
        this->drawCombatText();
        window.draw(rectangle);
        window.draw(outputRect);
        window.draw(playerText);
        window.draw(text);
        window.draw(combatText);
        window.draw(sprite);

        // end the current frame
        window.display();
    }
}

void World::userInput()
{
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    playerText.setFont(font);
    playerText.setCharacterSize(18);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(0, 950);

    //Getting user input
    if (event.type == sf::Event::TextEntered) {
        playerInput += event.text.unicode;
        input = event.text.unicode;
        unicode = event.text.unicode;
        unicode = static_cast<char>(event.text.unicode);
        playerText.setString(playerInput);
        sound.play();
        
        //Clearing string with backspace
        if (input == "\b") {
            playerText.setString("");
            playerText.setCharacterSize(24);
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

void World::mouseInput()
{

}

//Menu Functions
void World::bonFire()
{
    if (initialized == false) {
        //Change Text
        text.setString("  BonFire Options\n 1:|Quest Board\n 2:|View Stats\n 3:|Hunt");
        //Add Sprite
        this->sprite1 = true;

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
        text.setString("  Quests\n 0:|Return\n 1:|Quest One");
    
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
            this->questone = true;
            this->questOne();
            break;
        }
    }
}

void World::statsMenu()
{
    if (statsmenu == true) {
        text.setString("  Statistics\n 0:|Return\n 1:|View Stats");

        switch (unicode) {
        case 48:
            clearInput();
            combatText.setString("");
            this->initialized = false;
            this->statsmenu = false;
            this->bonFire();
            break;
        case 49:
            clearInput();
            combatText.setString("  ATTACK: 12\n DEF: 2...");
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
        text.setString("A combatant Ambushes you from the dark! \n1:|Strike");
        //Change Sprites
        this->sprite1 = false;
        this->sprite2 = true;


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
        text.setString("You strike the combatant! Enemy revealed! \nPress '1' to continue...");
        soundCom.play();
        targetHp -= strike;
        if (targetHp <= 0) {
            this->clearInput();
            this->combatPlayer = false;
            this->playerturn = false;
            this->combatvictory = true;
            this->combatVictory();
        }
        combatText.setString("Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
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
        text.setString("Target attacking! Press '1' to continue...");
        combatText.setString("Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
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
                combatText.setString("Target hit!\n Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
                    + "\n Your HP ->" + std::to_string(hp) + "/" + std::to_string(hpMax));
                this->combatTarget = false;
                this->targetturn = false;
                this->combat = true;
                this->combatInit();
            }
            else {
                this->clearInput();
                combatText.setString("Target missed!\n Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
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
        text.setString("The abomination has fallen! Victory is yours! Press '0' to continue...");
        combatText.setString("");

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

//Drawing Windows
void World::combatScreen()
{
    sf::RenderWindow windowCombat(sf::VideoMode(700, 450), "Threat Finder"/*, sf::Style::Fullscreen*/);
    while (windowCombat.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (windowCombat.pollEvent(event)) {
        }

        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            this->combatStop = true;
            windowCombat.close();
        }

        // clear the window with black color
        windowCombat.clear(sf::Color::Black);

        // draw everything here...
        this->combatSprite();
        windowCombat.draw(spriteCombat);

        //end the current frame
        windowCombat.display();
    }
}

//Drawing Objects
void World::drawOutputBox()
{
    //Draw Output Text
    font.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(sf::Color::White));
    text.setPosition(0.0f, 825.0f);

    //Draw Output Box
    outputRect.setSize(sf::Vector2f(1920.0f, 125.0f));
    outputRect.setFillColor(sf::Color(55, 55, 55));
    outputRect.setPosition(0.0f, 825.0f);
}

void World::drawTextBox()
{
    //Draw Input Box
    rectangle.setSize(sf::Vector2f(xCord, yCord));
    rectangle.setFillColor(sf::Color(50, 50, 50));
    rectangle.setPosition(0.0f, 950.0f);
}

void World::drawCombatText()
{
    font.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    combatText.setFont(font);
    combatText.setCharacterSize(18);
    combatText.setFillColor(sf::Color(sf::Color::White));
    combatText.setPosition(500.0f, 825.0f);
}

void World::zinSprite()
{
    if (sprite1 == true) {
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
    }
    else if (sprite2 == true) {
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite2.png");
    }
    texture.update(window);
    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(sf::Vector2f(50.0f, 650.0f)); // absolute position
}

void World::combatSprite()
{
    textureCombat.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/hostile.jpeg");
    textureCombat.update(combatWindow);
    textureCombat.setSmooth(true);
    textureCombat.setRepeated(false);
    spriteCombat.setTexture(textureCombat);
    spriteCombat.setScale(0.6f, 0.5f);
    spriteCombat.setPosition(sf::Vector2f(0.0f, 0.0f)); // absolute position
}