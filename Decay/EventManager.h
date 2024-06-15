#pragma once
#include"fstream"
#include<random>
#include"CombatState.h"
#include"EventModule.h"
class EventManager
{
public:
	//Constructors and Deconstructors
	EventManager();
	~EventManager();

	//Core Functions
	void update();
	void render(sf::RenderTarget* target);

	//Generation Functions
	void generateEvents();

	//Event Functions
	void initEvents();
	void loadEvent(std::string input);

private:

	std::ifstream ifs;
	std::string line;

};

