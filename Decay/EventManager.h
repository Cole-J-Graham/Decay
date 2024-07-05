#pragma once
#include<filesystem>
#include<fstream>
#include<random>
#include<deque>
#include"CombatState.h"
#include"EventModule.h"

class EventManager {
public:
	//Constructors and Deconstructors
	EventManager(std::string& areaName);
	~EventManager();

	//Core Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Event Functions
	void initEvents();
	void updateEvents();
	void eventChance();

	//File Functions
	void updateInput();

	//Getters

	EventModule* eventModule;

	bool rightArrowClicked() { return this->eventModule->userInput->rightArrowClicked(); }
	bool leftArrowClicked() { return this->eventModule->userInput->leftArrowClicked(); }

	bool getEventActivated() { return this->eventActivated; }

private:

	bool isFileOpen;
	bool eventActivated;

	float eventOdds;
	float eventIncrease;
	float eventThresholdMax;
	float eventThresholdMin;

	int eventKey;

	std::ifstream ifs;
	std::string areaName;
	std::string inResponseOne, inResponseTwo, inExpression, inTalk;
	std::string currentLine;
	std::deque<std::string> eventsFilePaths;

	enum State {
		IDLE,
		PROCESSING_CHARACTER,
		PROCESSING_NPC,
		PROCESSING_DIALOGUE
	};

	State currentState = IDLE;

	//Private Event Functions
	void characterSpeak();
	void npcSpeak();

	//File Management Functions
	bool processNextLine();
	bool openFile(const std::string& file_input);
	void closeFile();
	void readLine(std::string& extractedLine);
	void readCharacters(size_t numChars, std::string& extractedString);
	std::deque<std::string> getFileNamesInDirectory(const std::string& directoryPath);
	void updateState(State newState);
};

