#include "MusicPlayer.h"
//Constructors and Destructors
MusicPlayer::MusicPlayer() 
{
    this->fileRead = false;
    this->currentSong = 0;
    this->songId = 0;
    this->buffer.loadFromFile(this->music[this->songId]);
    this->song.setBuffer(this->buffer);

	//Initialize
    this->initButtons();
	this->initMusic();
}

MusicPlayer::~MusicPlayer()
{

}

//Core Functions
void MusicPlayer::update(const sf::Vector2f mousePos)
{
    this->updateSongFunctions();
    this->updateButtons(mousePos);
}

void MusicPlayer::render(sf::RenderTarget* target)
{
    this->renderButtons(target);
}

void MusicPlayer::initMusic()
{
    
}

bool MusicPlayer::readFile(const std::string& input) {
    std::ifstream file(input);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << input << std::endl;
        return false;
    }

    std::string line;
    int key = this->music.size();  // Start key from the current size of the map

    if (!this->fileRead) {
        while (std::getline(file, line)) {
            this->music[this->songId] = line;
            ++this->songId;
            std::cout << "Total lines read: " << this->music.size() << "\n";
        }
    }

    if (file.eof()) {
        std::cout << "Reached end of file.\n";
        this->fileRead = true;
        file.close();
    }

    return true;
}

//Music Player Functions
void MusicPlayer::updateSongFunctions()
{
    this->nextSong();
}

void MusicPlayer::updateCurrentSong()
{
    this->currentSong = this->songId;
    this->buffer.loadFromFile(this->music[this->currentSong]);
    this->song.setBuffer(this->buffer);
    this->song.play();
    std::cout << "CURRENT SONG:" << this->music[this->currentSong] << "\n";
}

void MusicPlayer::nextSong()
{
    if (this->buttons["NEXT"]->isPressed()) {
        this->songId++;
        this->updateCurrentSong();
    }
    if (this->buttons["PREV"]->isPressed()) {
        this->songId--;
        this->buffer.loadFromFile(this->music[this->songId]);
        this->updateCurrentSong();
    }
}



//Button Functions
void MusicPlayer::initButtons() 
{
    this->buttons["NEXT"] = std::make_unique<Button>(100, 100, 150, 25, 0.5f, "PREV",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["PREV"] = std::make_unique<Button>(300, 100, 150, 25, 0.5f, "NEXT",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void MusicPlayer::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }
}

void MusicPlayer::renderButtons(sf::RenderTarget* target) {
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

//Rectangle Functions