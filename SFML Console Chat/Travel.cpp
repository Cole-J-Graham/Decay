#include "Travel.h"

//Constructors & Destructors
Travel::Travel()
{
    this->traveling = false;
}

Travel::~Travel()
{

}

//Core
void Travel::userInput()
{
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    playerText.setFont(font);
    playerText.setCharacterSize(18);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(0, 950);

    //Getting user input
    if (eventTravel.type == sf::Event::TextEntered) {
        playerInput += eventTravel.text.unicode;
        input = eventTravel.text.unicode;
        unicode = eventTravel.text.unicode;
        unicode = static_cast<char>(eventTravel.text.unicode);
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

//Draw Main Window
void Travel::travelScreen()
{
    if (this->traveling == true) {

    }
}