#pragma once
#include<filesystem>
#include<fstream>
#include<random>
#include<deque>
#include"CombatState.h"
#include "DialogueInputComponent.h"
#include <memory>

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
	bool eventChance();
	bool isEventActive() const { return this->eventActivated; }

	//File Functions
	void updateInput();

	//Getters
	bool getEventActivated() { return this->eventActivated; }

private:

	std::unique_ptr<DialogueInputComponent> dialogueInput;

	bool isFileOpen;
	bool eventActivated;
	bool skipLine;

	float eventOdds;
	float eventIncrease;
	float eventThresholdMax;
	float eventThresholdMin;

	int eventKey;

	std::ifstream ifs;
	std::string areaName;
	std::string inResponseOne, inResponseTwo, inExpression, inTalk, inChar;
	std::string currentLine;

	struct EventDefinition
	{
		std::string path;
		bool oneTime = false;
		bool hasPlayed = false;
	};

	std::deque<EventDefinition> events;
	int activeEventIndex = -1;

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
	std::deque<EventDefinition> getEventsInDirectory(const std::string& directoryPath);
	void updateState(State newState);

	//Helper
	bool eventCanPlay(const EventDefinition& event) const;
};

