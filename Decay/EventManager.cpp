#include "EventManager.h"
//Constructors and Deconstructors
EventManager::EventManager()
{
    //Variable Initialization
    this->isFileOpen = false;

    //Module Initialization
    this->eventModule = new EventModule();

    //Seed randomization
	srand(time(NULL));
}

EventManager::~EventManager()
{
    delete this->eventModule;
}

//Core Functions
void EventManager::update(sf::Vector2f mousePos)
{
    this->eventModule->update(mousePos);
    this->updateEvents();
    this->updateInput();
}

void EventManager::render(sf::RenderTarget* target)
{
    this->eventModule->render(target);
}

//Generation Functions
void EventManager::generateEvents()
{
    //Insert random integers
    //std::random_device dev;
    //std::mt19937 rng(dev());
    //std::uniform_int_distribution<std::mt19937::result_type> enemyRange(this->enemyRangeMin, this->enemyRangeMax);
}

//Event Functions
void EventManager::initEvents()
{
    
}

void EventManager::updateEvents() {
    if (!isFileOpen && this->openFile("Assets/Wallpapers/test.txt")) {
        std::cout << "File opened successfully." << std::endl; // Debug statement
    }

    if (isFileOpen) {
        while (true) {
            if (currentState == IDLE && !this->processNextLine()) {
                break; // End of file or error
            }

            if (currentState != IDLE) {
                break; // Stop processing to wait for further input
            }
        }
    }
}

void EventManager::characterSpeak() {
    this->readLine(this->inResponseOne);
    this->readLine(this->inResponseTwo);
    this->eventModule->userInput->showDialogueOptions();
    this->eventModule->userInput->setDialogueOptions(this->inResponseOne, this->inResponseTwo);
    this->eventModule->userInput->setProcessingDialogueTrue();
    this->updateState(PROCESSING_DIALOGUE);
    std::cout << "Processing Dialogue: True (characterSpeak)" << std::endl; // Debug statement
}

void EventManager::npcSpeak() {
    this->readLine(this->inExpression);
    this->readLine(this->inTalk);
    this->eventModule->userInput->setMainDialogueText(this->inTalk);
    this->eventModule->userInput->showMainDialogue();
    // Additional processing for NPC speak
    this->updateState(PROCESSING_DIALOGUE);
    std::cout << "NPC Speak processed" << std::endl; // Debug statement
}

bool EventManager::processNextLine() {
    if (!isFileOpen) {
        std::cerr << "File is not open!" << std::endl;
        return false;
    }

    if (currentState == PROCESSING_DIALOGUE) {
        std::cout << "Currently processing dialogue, skipping file read" << std::endl; // Debug statement
        return true;
    }

    if (std::getline(ifs, currentLine)) {
        if (currentLine == "*SPEAK_CHARACTER") {
            this->characterSpeak();
            this->updateState(PROCESSING_CHARACTER);
        }
        else if (currentLine == "*SPEAK_NPC") {
            this->npcSpeak();
            this->updateState(PROCESSING_NPC);
        }
        else {
            std::cout << "Unknown action: " << currentLine << "\n";
        }
        return true;
    }
    else {
        return false; // End of file reached or error
    }
}

bool EventManager::openFile(const std::string& file_input) {
    ifs.open(file_input);
    isFileOpen = ifs.is_open();
    if (!isFileOpen) {
        std::cerr << "Failed to open file: " << file_input << std::endl;
    }
    return isFileOpen;
}

void EventManager::closeFile() {
    if (isFileOpen) {
        ifs.close();
        isFileOpen = false;
    }
}

void EventManager::readLine(std::string& extractedLine) {
    if (!isFileOpen) {
        std::cerr << "File is not open!" << std::endl;
        return;
    }

    if (std::getline(ifs, extractedLine)) {
        std::cout << "Read line: " << extractedLine << "\n";
    }
    else {
        std::cerr << "Failed to read line or end of file reached." << std::endl;
    }
}

void EventManager::readCharacters(size_t numChars, std::string& extractedString) {
    if (!isFileOpen) {
        std::cerr << "File is not open!" << std::endl;
        return;
    }

    char* buffer = new char[numChars + 1];
    ifs.read(buffer, numChars);
    std::streamsize bytesRead = ifs.gcount();
    buffer[bytesRead] = '\0';

    std::cout << "Read characters: " << buffer << "\n";
    extractedString = std::string(buffer);

    delete[] buffer;
}

void EventManager::updateState(State newState) {
    currentState = newState;
}

void EventManager::updateInput() {
    if (this->eventModule->userInput->topDialogueClicked() || this->eventModule->userInput->bottomDialogueClicked()) {
        this->eventModule->userInput->hideDialogueOptions();
        this->eventModule->userInput->setProcessingDialogueFalse();
        this->updateState(IDLE);
        std::cout << "Processing Dialogue: False (updateInput)" << std::endl; // Debug statement
    }

    if (this->eventModule->userInput->mainDialogueClicked()) {
        std::string test = "";
        this->eventModule->userInput->hideMainDialogue();
        this->eventModule->userInput->setMainDialogueText(test);
        this->updateState(IDLE);
        std::cout << "Processing Dialogue: False (updateInput)" << std::endl; // Debug statement
    }
}