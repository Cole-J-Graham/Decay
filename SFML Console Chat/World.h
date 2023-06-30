#ifndef WORLD_H
#define WORLD_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>

class World
{
private:
	sf::Font font;
	sf::RenderWindow window;
	sf::RenderWindow combatWindow;
	sf::Texture texture;
	sf::Texture textureCombat;
	sf::Texture combatTexture;
	sf::Image image;
	sf::Sprite sprite;
	sf::Sprite spriteCombat;
	sf::RectangleShape rectangle;
	sf::RectangleShape outputRect;
	sf::String playerInput;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::SoundBuffer bufferCom;
	sf::Sound soundCom;
	sf::Music music;
	sf::Event event;
	sf::Text text;
	sf::Text playerText;
	sf::Text combatText;

	//Core
	std::string input;
	std::string targetHpView;
	int unicode;
	int random;
	float xCord;
	float yCord;

	//Bool
	bool stop;
	bool combatStop;
	bool keyPress;
	bool initialized;
	bool comInitialized;
	bool questone;
	bool statsmenu;
	bool questboard;
	bool combat;
	bool combatPlayer;
	bool combatTarget;
	bool playerturn;
	bool targetturn;
	bool hostile1;

	//Player Stats
	int level;
	int strike;
	int hp;
	int hpMax;

	//Enemy Stats
	int targetHp;
	int targetHpMax;
	int targetStrike;

public:
	//Constructors & Destructors
	World();
	~World();

	//CoreFunctions
	void bootUp();
	void userInput();
	void clearInput();

	//Menu Functions
	void bonFire();
	void statsMenu();
	void questBoard();

	//Combat Functions
	void combatInit();
	void playerTurn();
	void targetTurn();

	//Drawing Windows
	void combatScreen();

	//Drawing Objects
	void drawTextBox();
	void zinSprite();
	void drawOutputBox();
	void drawCombatText();
	void combatSprite();

	//Map Locations
	void questOne();

	//Getters and Setters
	bool& getStop() { return this->stop; };
};

#endif

