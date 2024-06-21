#pragma once
#include<filesystem>
#include<fstream>
#include<random>
#include"CombatState.h"
#include"EventModule.h"

class EventManager {
public:
	//Constructors and Deconstructors
	EventManager();
	~EventManager();

	//Core Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Event Functions
	void initEvents();
	void updateEvents();

	//File Functions
	void updateInput();

private:
	EventModule* eventModule;

	bool isFileOpen;
	int eventRangeMin;
	int eventRangeMax;

	std::ifstream ifs;
	std::string inResponseOne, inResponseTwo, inExpression, inTalk;
	std::string currentLine;
	std::vector<std::string> eventsFilePaths;

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
	std::vector<std::string> getFileNamesInDirectory(const std::string& directoryPath);
	void updateState(State newState);
};

