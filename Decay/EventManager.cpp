#include "EventManager.h"
//Constructors and Deconstructors
EventManager::EventManager()
{
    //Seed randomization
	srand(time(NULL));
}

EventManager::~EventManager()
{

}

//Core Functions
void EventManager::update()
{
    this->updateEvents();
}

void EventManager::render(sf::RenderTarget* target)
{

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

void EventManager::updateEvents()
{
    if (this->openFile("Assets/Wallpapers/test.txt")) {
        while (true) {
            if (!this->processNextLine()) {
                // End of file or error
                break;
            }
            this->processNextLine();
        }
        this->closeFile();
    }
}

//File Functions
bool EventManager::processNextLine() {
    if (!isFileOpen) {
        std::cerr << "File is not open!" << std::endl;
        return false;
    }

    std::string input;
    if (std::getline(ifs, input)) {
        // Process the input line
        if (input == "*SPEAK_CHARACTER") {
            std::cout << input << "\n";
            this->readLine(this->valExpression);
            this->readLine(this->valTalk);
        }
        else if (input == "*SPEAK_NPC") {
            std::cout << "BLAH BLAH BLAH BLAH BLAH BLAH BLAH BLAH" << "\n";
        }
        else {
            std::cout << "Unknown action: " << input << "\n";
        }
        return true;
    }
    else {
        // End of file reached or error
        return false;
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

    // Use getline to read an entire line and store it in extractedLine
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

    char* buffer = new char[numChars + 1]; // Create a buffer to hold the characters
    ifs.read(buffer, numChars); // Read the specified number of characters
    std::streamsize bytesRead = ifs.gcount(); // Get the actual number of characters read
    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    // Process the buffer
    std::cout << "Read characters: " << buffer << "\n";

    // Store the buffer content into the extractedString
    extractedString = std::string(buffer);

    delete[] buffer; // Clean up the buffer
}