#pragma once
#include"fstream"
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

	//Generation Functions
	void generateEvents();

	//Event Functions
	void initEvents();
	void updateEvents();

	//File Functions
	void updateInput();

private:
	EventModule* eventModule;

	bool isFileOpen;

	std::ifstream ifs;
	std::string inResponseOne, inResponseTwo, inExpression, inTalk;
	std::string currentLine;

	enum State {
		IDLE,
		PROCESSING_CHARACTER,
		PROCESSING_NPC,
		PROCESSING_DIALOGUE
	};

	State currentState = IDLE;

	void characterSpeak();
	void npcSpeak();
	bool processNextLine();
	bool openFile(const std::string& file_input);
	void closeFile();
	void readLine(std::string& extractedLine);
	void readCharacters(size_t numChars, std::string& extractedString);
	void updateState(State newState);
};

