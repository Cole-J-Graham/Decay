#include"World.h"

//Constructors and Destructors
World::World()
{
    //Core
    this->input = input;
    this->targetHpView = targetHpView;
    this->unicode = unicode;
    this->random = random;

    //Bool
    this->stop = false;
    this->keyPress = true;
    this->initialized = false;
    this->questone = false;
    this->questboard = false;
    this->combat = false;
    this->combatPlayer = false;
    this->combatTarget = false;
    this->playerturn = true;
    this->targetturn = true;

    //Player Stats
    this->level = 1;
    this->strike = 10;
    this->hp = 100;
    this->hpMax = 100;

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

    //create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Console Chat"/*, sf::Style::Fullscreen*/);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        std::cout << unicode;
        if (initialized == false) {
            while (window.pollEvent(event)) {
                //Main Bonfire Function For Options
                this->userInput();
                this->bonFire();
            }
        }
        else if (questboard == true) {
            while (window.pollEvent(event)) {
                this->userInput();
                this->questBoard();
            }
        }
        else if (statsmenu == true) {
            while (window.pollEvent(event)) {
                this->userInput();
                this->statsMenu();
            }
        }
        else if (questone == true) {
            while (window.pollEvent(event)) {
                this->userInput();
                this->questOne();
            }
        }
        else if (combat == true) {
            while (window.pollEvent(event)) {
                this->userInput();
                this->combatInit();
            }
        }
        else if (combatPlayer == true) {
            while (window.pollEvent(event)) {
                this->userInput();
                this->playerTurn();
            }
        }
        else if (combatTarget == true) {
            while (window.pollEvent(event)) {
                this->userInput();
                this->targetTurn();
            }
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

//Menu Functions
void World::bonFire()
{
    if (initialized == false) {
        text.setString("  BonFire Options\n 1:|Quest Board\n 2:|View Stats\n 3:|Hunt");
    }

    //Main Choices For Menu
    switch (unicode) {
    case 49:
        playerInput = "";
        this->initialized = true;
        this->questboard = true;
        this->questBoard();
        break;
    case 50:
        playerInput = "";
        this->initialized = true;
        this->questboard = false;
        this->statsmenu = true;
        this->statsMenu();
        break;
    case 51:
        playerInput = "";
        this->initialized = true;
        this->questboard = false;
        this->statsmenu = false;
        this->combat = true;
        this->combatInit();
        break;
    }
}

void World::questBoard()
{
    if (questboard == true) {
        text.setString("  Quests\n 0:|Return\n 2:|Quest One");
    }
    
    switch (unicode) {
    case 48:
        playerInput = "";
        this->initialized = false;
        this->questboard = false;
        this->bonFire();
        break;
    case 50:
        playerInput = "";
        this->questboard = false;
        this->questone = true;
        this->questOne();
        break;
    }
}

void World::statsMenu()
{
    if (statsmenu == true) {
        text.setString("  Statistics\n 0:|Return\n 1:|View Stats");
    }

    switch (unicode) {
    case 48:
        playerInput = "";
        this->initialized = false;
        this->statsmenu = false;
        this->bonFire();
        break;
    case 49:
        playerInput = "";
        text.setString("  ATTACK: 12\n DEF: 2...");
        break;
    }
}

//Combat Functions
void World::combatInit()
{
    if (combat == true) {
        text.setString("A combatant Ambushes you!\n 0:|Flee\n 1:|Strike");
        combatText.setString("Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
            + "\n Your HP ->" + std::to_string(hp) + "/" + std::to_string(hpMax));
    }
    

    switch (unicode) {
    case 48:
        playerInput = "";
        combatText.setString("");
        this->initialized = false;
        this->questboard = false;
        this->bonFire();
        break;
    case 49:
        playerInput = "";
        this->combat = false;
        this->combatPlayer = true;
        this->playerTurn();
        break;
    }
}

void World::playerTurn()
{
    if (combatPlayer == true && playerturn == true) {
        text.setString("You strike the combatant! Press '0' to continue...");
        soundCom.play();
        targetHp -= strike;
        combatText.setString("Target HP ->" + std::to_string(targetHp) + "/" + std::to_string(targetHpMax)
            + "\n Your HP ->" + std::to_string(hp) + "/" + std::to_string(hpMax));
        this->playerturn = false;
    }

    switch (unicode) {
    case 48:
        playerInput = "";
        this->combatPlayer = false;
        this->combatTarget = true;
        this->targetTurn();
        break;
    }
}

void World::targetTurn()
{
    //Deinitialize combat to continue combat loop
    if (combatTarget == true && targetturn == false) {
        this->playerturn = true;
        this->targetturn = true;
        this->combatInit();
    }

    text.setString("Target attacking! Press '1' to continue...");
    if (combatTarget == true && targetturn == true) {
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
                playerInput = "";
                text.setString("The target strikes you!");
                this->hp -= this->targetStrike;
                this->targetturn = false;
                
            }
            else {
                playerInput = "";
                text.setString("Target Missed!");
                this->targetturn = false;
            }
            break;
        }
    }
}

//Drawing Objects
void World::drawOutputBox()
{
    //Draw Output Text
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(sf::Color::White));
    text.setPosition(0, 825);

    //Draw Output Box
    outputRect.setSize(sf::Vector2f(1920, 125));
    outputRect.setFillColor(sf::Color(55, 55, 55));
    outputRect.setPosition(0, 825);
}

void World::drawTextBox()
{
    //Draw Input Box
    rectangle.setSize(sf::Vector2f(1920, 600));
    rectangle.setFillColor(sf::Color(50, 50, 50));
    rectangle.setPosition(0, 950);
}

void World::drawCombatText()
{
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    combatText.setFont(font);
    combatText.setCharacterSize(18);
    combatText.setFillColor(sf::Color(sf::Color::White));
    combatText.setPosition(500, 825);
}

void World::zinSprite()
{
    texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
    texture.update(window);
    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);
    sprite.setScale(1.5, 1.5);
    sprite.setPosition(sf::Vector2f(1700, 650)); // absolute position
}