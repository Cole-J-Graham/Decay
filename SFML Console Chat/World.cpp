#include"World.h"

//Constructors and Destructors
World::World()
{
    //Core
    this->input = input;
    this->targetHpView = targetHpView;
    this->unicode = unicode;

    //Bool
    this->stop = false;
    this->keyPress = true;
    this->initialized = false;
    this->questone = false;
    this->questboard = false;
    this->combat = false;

    //Player Stats
    this->level = 1;

    //Enemy Stats
    this->targetHp = 50;
    this->targetHpMax = 50;
}

World::~World() 
{

}

//Core Functions
void World::bootUp()
{
    buffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/Text 1.wav");
    sound.setBuffer(buffer);
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
        text.setString("A combatant Ambushes you!");
        combatText.setString("HP ->" + std::to_string(targetHpMax));
    }

    switch (unicode) {
    case 48:
        playerInput = "";
        this->initialized = false;
        this->questboard = false;
        this->bonFire();
        break;
    case 49:
        playerInput = "";
        break;
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
    combatText.setPosition(325, 825);
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