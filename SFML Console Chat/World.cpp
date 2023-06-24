#include"World.h"

//Constructors and Destructors
World::World()
{
    //Core
    this->input = input;
    this->unicode = unicode;

    //Bool
    this->stop = false;
    this->keyPress = true;
    this->initialized = false;
    this->questone = false;

    //Player Stats
    this->level = 1;
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
    music.play();
    // create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Console Chat"/*, sf::Style::Fullscreen*/);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        std::cout << unicode;
        while (window.pollEvent(event) && initialized == false) {
            //Main Bonfire Function For Options
            this->bonFire();
        }

        while (window.pollEvent(event) && questone == true) {
            this->questOne();
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
        window.draw(rectangle);
        window.draw(outputRect);
        window.draw(playerText);
        window.draw(text);
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
    //Get User Input
    this->userInput();
    if (initialized == false) {
        text.setString("  BonFire Options\n 1:|Quest Board");
    }

    //Main Choices For Menu
    switch (unicode) {
    case 49:
        text.setString("  Quests\n 2:|Quest One");
        break;
    case 50:
        this->questOne();
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