#include "EventManager.h"

namespace
{
    constexpr float EVENT_PORTRAIT_X = 25.f;
    constexpr float EVENT_PORTRAIT_Y = 585.f;
}

//Constructors and Deconstructors
EventManager::EventManager(std::string& areaName)
{
    //Variable Initialization
    this->isFileOpen = false;
    this->eventActivated = false;
    this->eventOdds = 0;
    this->eventIncrease = 1;
    this->eventThresholdMax = 1000;
    this->eventThresholdMin = 0;
    this->eventKey = 0;
    this->areaName = areaName;
    this->inChar = "";
    this->skipLine = false;

    //Module Initialization
    this->dialogueInput = std::make_unique<DialogueInputComponent>();

    //Seed randomization
	srand(time(NULL));

    //Class Initialization
    this->initEvents();
}

EventManager::~EventManager()
{

}

//Core Functions
void EventManager::update(sf::Vector2f mousePos)
{
    this->dialogueInput->update(mousePos);
    this->updateEvents();
    this->updateInput();
}

void EventManager::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    this->dialogueInput->render(target);

    if (this->inChar.empty()) {
        return;
    }

    auto character = CharacterManager::getInstance().getCharacter(this->inChar);

    if (character == nullptr) {
        return;
    }

    character->renderPreview(target, EVENT_PORTRAIT_X, EVENT_PORTRAIT_Y);
}

//Event Functions
void EventManager::initEvents()
{
    this->getEventsInDirectory("Assets/Events/" + this->areaName);

    for (auto& event : events) {
        std::cout << "EVENT FILE LOADED: " << event.path
            << " | oneTime: " << event.oneTime
            << " | hasPlayed: " << event.hasPlayed << "\n";
    }
}

void EventManager::updateEvents()
{
    if (this->eventActivated) {

        if (!isFileOpen && !this->events.empty()) {
            std::vector<int> validEventIndexes;

            for (int i = 0; i < this->events.size(); i++) {
                if (this->eventCanPlay(this->events[i])) {
                    validEventIndexes.push_back(i);
                }
            }

            if (validEventIndexes.empty()) {
                this->eventActivated = false;
                std::cout << "No playable events remaining in area..." << "\n";
                return;
            }

            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::size_t> eventRange(0, validEventIndexes.size() - 1);

            this->activeEventIndex = validEventIndexes[eventRange(rng)];
            const std::string selectedFile = this->events[this->activeEventIndex].path;

            if (this->openFile(selectedFile)) {
                std::cout << "File " << selectedFile << " opened successfully." << std::endl;
            }
        }

        if (isFileOpen) {
            while (true) {
                if (currentState == IDLE && !this->processNextLine()) {
                    if (this->activeEventIndex >= 0 && this->activeEventIndex < this->events.size()) {
                        if (this->events[this->activeEventIndex].oneTime) {
                            this->events[this->activeEventIndex].hasPlayed = true;
                        }
                    }

                    this->activeEventIndex = -1;
                    this->eventActivated = false;
                    this->inChar = "";
                    this->closeFile();
                    break;
                }

                if (currentState != IDLE) {
                    break;
                }
            }
        }
    }
}

void EventManager::characterSpeak() {
    this->readLine(this->inResponseOne);
    this->readLine(this->inResponseTwo);
    this->dialogueInput->showDialogueOptions();
    this->dialogueInput->setDialogueOptions(this->inResponseOne, this->inResponseTwo);
    this->updateState(PROCESSING_DIALOGUE);
    std::cout << "Processing Dialogue: True (characterSpeak)" << std::endl; // Debug statement
}

void EventManager::npcSpeak() {
    std::string lineSkip;
    this->readLine(this->inChar);
    this->readLine(this->inExpression);
    if (this->skipLine) { this->readLine(lineSkip); this->skipLine = false; }
    this->readLine(this->inTalk);
    this->dialogueInput->setMainDialogueText(this->inTalk);
    this->dialogueInput->showMainDialogue();
    // Additional processing for NPC speak
    this->updateState(PROCESSING_DIALOGUE);
    std::cout << "Processing Dialogue: True (npcSpeak)" << std::endl; // Debug statement
}

bool EventManager::eventChance()
{
    if (this->eventActivated) {
        return true;
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> eventThreshold(this->eventThresholdMin, this->eventThresholdMax);

    if (this->eventOdds > eventThreshold(rng)) {
        std::cout << "Odds success..." << "\n";
        this->eventActivated = true;
        this->eventOdds = 0;
        this->eventIncrease = 1;
        return true;
    }

    std::cout << "Odds failed chances increased..." << "\n";
    this->eventOdds += this->eventIncrease;
    this->eventIncrease *= 2;
    return false;
}

void EventManager::forceEvent()
{
    this->eventActivated = true;
    this->eventOdds = 0;
    this->eventIncrease = 1;
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

std::deque<EventManager::EventDefinition> EventManager::getEventsInDirectory(const std::string& directoryPath)
{
    try {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                EventDefinition event;

                const std::string filename = entry.path().filename().string();

                event.path = entry.path().string();
                event.oneTime = filename.find(".once.") != std::string::npos;
                event.hasPlayed = false;

                this->events.push_back(event);
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return this->events;
}

void EventManager::updateState(State newState) {
    currentState = newState;
}

void EventManager::updateInput() {
    //Activate line skip boolean if bottom dialogue option is clicked
    if (this->dialogueInput->bottomDialogueClicked()) { std::cout << "LINE SKIP ACTIVATED" << "\n";  this->skipLine = true; }

    if (this->dialogueInput->topDialogueClicked() || this->dialogueInput->bottomDialogueClicked()) {
        this->dialogueInput->hideDialogueOptions();
        this->updateState(IDLE);
        std::cout << "Processing Dialogue: False (updateInput)" << std::endl; // Debug statement
    }

    if (this->dialogueInput->mainDialogueClicked()) {
        std::string test = "";
        this->dialogueInput->hideMainDialogue();
        this->dialogueInput->setMainDialogueText(test);
        this->updateState(IDLE);
        std::cout << "Processing Dialogue: False (updateInput)" << std::endl; // Debug statement
    }
}

//Helper
bool EventManager::eventCanPlay(const EventDefinition& event) const
{
    if (event.oneTime && event.hasPlayed) {
        return false;
    }

    return true;
}