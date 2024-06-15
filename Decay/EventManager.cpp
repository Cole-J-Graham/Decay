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

void EventManager::loadEvent(std::string file_input)
{
    ifs.open(file_input);
    if (ifs.is_open()) {

        std::string input;
        while (getline(ifs, input)) {
            // Load texture from file
            std::cout << input << "\n";
            
        }
        ifs.close();
    }
    else {
        std::cerr << "Failed to open file: " << file_input << std::endl;
    }
}