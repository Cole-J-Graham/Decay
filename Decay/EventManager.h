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
	void updateEvents();

	//File Functions
	bool processNextLine();
	bool openFile(const std::string& file_input);
	void closeFile();
	void readLine(std::string& extractedLine);
	void readCharacters(size_t numChars, std::string& extractedString);

private:

	bool isFileOpen;
	
	std::string valExpression;
	std::string valTalk;

	std::string valResponseOne;
	std::string valResponseTwo;

	std::ifstream ifs;
	std::string line;

};

