#ifndef WORLD_H
#define WORLD_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>
#include"Travel.h"
#include"Assets.h"
#include"Event.h"
#include"Combat.h"
#include"Animation.h"

class World
{
private:
	sf::RenderWindow window;
	sf::Image image;
	sf::Clock clock;
	sf::Clock textTime;
	sf::Time textElapsed;

	sf::String playerInput;

	sf::Event event;

	std::string stringtest;

	//Core
	std::string input;
	std::string targetHpView;
	int unicode;
	int random;
	int test;

	//Core Bool
	bool stop;
	bool keyPress;
	bool initialized;
	bool comInitialized;
	bool bonfire;
	bool mainMenu;

	//Menu Bool
	bool statsmenu;

	//Quest Bool
	bool buttonClick;

	//Coordinate Plane
	float xCord;
	float yCord;

public:
	//Constructors & Destructors
	World();
	~World();

	//Core Functions
	void BootUp(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate);
	void UserInput(Sprites& sprites);

	//Display Functions
	void Draw(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate);
	void DrawMapSelectorButtons(sf::RenderWindow& window, Sprites& sprites);
	void PrintPlayerStats(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player);
	void PrintZinStats(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player);
	void PrintToolTipFunc(sf::RenderWindow& window, Sprites& sprites, sf::RectangleShape& inputRect, bool& boolSet, std::string& toolTip);
	void PrintToolTip(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player);

	//Display Element Functionality
	void MainMenuButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel, Animation& animate);
	void TravelButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel, Animation& animate, Player& player);
	void MenuBar(sf::RenderWindow& window, Sprites& sprites);
	void DialogueCombatBox(sf::RenderWindow& window, Combat& combat, Sprites& sprites, Travel& travel, Event& notevent);
	void MovableBox(sf::RenderWindow& window, Sprites& sprites);

	//Stat Functionality
	void StatsFunctionality(sf::RenderWindow& window, Combat& combat, Player& player, Sprites& sprites);
	void LevelUp(sf::RenderWindow& window, Combat& combat, Player& player, Sprites& sprites, sf::RectangleShape& inputRect, int& lvl, int& sp, int& exp, int& expNext);
	void StatUp(sf::RenderWindow& window, Combat& combat, Player& player, Sprites& sprites, sf::RectangleShape& inputRect, int& stat, int& sp, int& exp, int& expNext);

	//Map Button Functionality
	void MapButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel);
	void MapButtonsForest(sf::RenderWindow& window, Sprites& sprites, Travel& travel);
	void MapButtonsCastle(sf::RenderWindow& window, Sprites& sprites, Travel& travel);
	void MapButtonsDecay(sf::RenderWindow& window, Sprites& sprites, Travel& travel);

	//Map Functions
	void ResetMapPosition(sf::RenderWindow& window, Sprites& sprites);
	void SelectMapView(sf::RenderWindow& window, Sprites& sprites, Travel& travel);
	void DrawForestMap(sf::RenderWindow& window, Sprites& sprites);
	void DrawCastleMap(sf::RenderWindow& window, Sprites& sprites);
	void DrawDecayMap(sf::RenderWindow& window, Sprites& sprites);

	//Getters and Setters
	bool& getStop() { return this->stop; };
};

#endif

