#include"World.h"

//Constructors and Destructors
World::World()
{
    this->keyPress = true;
    this->initialized = false;
    this->input = input;
    this->level = 1;
    this->unicode = 0;
}

World::~World() {

}

//Functions
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
        while (window.pollEvent(event)) {
            //Main Bonfire Function For Options
            this->bonFire();

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                this->stop = true;
                window.close();
            }
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

void World::bonFire()
{
    //Get User Input
    this->userInput();
    if (initialized == false) {
        this->initialized = true;
        text.setString("  BonFire Options\n 1:|Quest Board");
    }

    //Main Choices For Menu
    switch (event.text.unicode) {
    case '1':
        this->questBoard();
        break;
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
        playerText.setString(playerInput);
        sound.play();
        
        //Clearing string with backspace
        if (input == "\b") {
            //this->initialized = false; just work with initializer
            //playerInput.erase(playerInput.getSize() - 1, 1);
            //playerText.setString(playerInput);
            playerText.setString("");
            playerText.setCharacterSize(24);
            playerInput = "";
        }
    }
}

//Menu Functions
void World::questBoard()
{
    //unicode = event.text.unicode;
    //playerText.setString(""); ATTEMPT TO GET A DIFFERENT USER INPUT OF SOME KIND SETTING THE UNICODE VALUE  unicode = event.text.unicode;
    //text.setString(""); IDEA: CLEAR UNICODE VALUE AFTER EVERY INPUT?
    //playerInput.clear();
    if (this->level == 0) {
        text.setString("  Quests\n  None Currently Available...");
        return;
    }
    else if (this->level >= 1) {
        text.setString("  Quests\n 1:|Quest One");
        switch (event.text.unicode) {
        case '1':
            this->questOne();
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