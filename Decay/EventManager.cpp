#include "EventManager.h"
//Constructors and Deconstructors
EventManager::EventManager(std::string& areaName)
{
    //Variable Initialization
    this->isFileOpen = false;
    this->eventActivated = false;
    this->eventRangeMin = 0;
    this->eventOdds = 0;
    this->eventIncrease = 1;
    this->eventThresholdMax = 1000;
    this->eventThresholdMin = 0;
    this->areaName = areaName;

    //Module Initialization
    this->eventModule = new EventModule();

    //Seed randomization
	srand(time(NULL));

    //Class Initialization
    this->initEvents();
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

//Event Functions
void EventManager::initEvents()
{
    this->getFileNamesInDirectory("Assets/Events/" + this->areaName);
    for (int i = 0; i < eventsFilePaths.size(); i++) {
        this->eventsFilePaths[i] = "Assets/Events/" + this->areaName + "/" + this->eventsFilePaths[i];
        std::cout << "EVENT FILE LOADED:" << eventsFilePaths[i] << "\n";
    }
    this->eventRangeMax = this->eventsFilePaths.size() - 1;
}

void EventManager::updateEvents() {
    if (this->eventActivated) {
        this->eventModule->userInput->hideMoveArrows();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> eventRange(this->eventRangeMin, this->eventRangeMax);

        if (!isFileOpen && this->openFile(this->eventsFilePaths[eventRange(rng)])) {
            std::cout << "File" << this->eventsFilePaths[eventRange(rng)] << " opened successfully." << std::endl; // Debug statement
        }

        if (isFileOpen) {
            while (true) {
                if (currentState == IDLE && !this->processNextLine()) {
                    this->eventActivated = false;
                    this->eventModule->userInput->showMoveArrows();
                    break; // End of file or error
                }

                if (currentState != IDLE) {
                    break; // Stop processing to wait for further input
                }
            }
        }
    }
}

void EventManager::characterSpeak() {
    this->readLine(this->inResponseOne);
    this->readLine(this->inResponseTwo);
    this->eventModule->userInput->showDialogueOptions();
    this->eventModule->userInput->setDialogueOptions(this->inResponseOne, this->inResponseTwo);
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
    std::cout << "Processing Dialogue: True (npcSpeak)" << std::endl; // Debug statement
}

void EventManager::eventChance()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> eventThreshold(this->eventThresholdMin, this->eventThresholdMax);

    if (this->eventOdds > eventThreshold(rng)) {
        //Activate event if eventodds are above the eventthreshold
        std::cout << "Odds success..." << "\n";
        this->eventActivated = true;
        this->eventOdds = 0;
        this->eventIncrease = 1;
    }
    else {
        //Increase chance of odd happening if failed
        std::cout << "Odds failed chances increased..." << "\n";
        this->eventOdds += this->eventIncrease;
        this->eventIncrease * 2;
    }
}

//File Management Functions
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

std::vector<std::string> EventManager::getFileNamesInDirectory(const std::string& directoryPath) {

    try {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) { // Ensure it is a file (not a directory or symlink)
                this->eventsFilePaths.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return this->eventsFilePaths;
}

void EventManager::updateState(State newState) {
    currentState = newState;
}

void EventManager::updateInput() {
    if (this->eventModule->userInput->topDialogueClicked() || this->eventModule->userInput->bottomDialogueClicked()) {
        this->eventModule->userInput->hideDialogueOptions();
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