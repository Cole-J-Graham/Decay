#include "MusicPlayer.h"

// Constructors and Destructors
MusicPlayer::MusicPlayer(const std::string& music_list)
{
    this->x = 1370;
    this->y = 74;
    this->hidden = true;
    this->fileRead = false;
    this->bufferId = 0;
    this->currentBufferId = 0;
    this->musicList = music_list;
    this->border = std::make_unique<Rectangle>("Test", sf::Color::White, 16, this->x, this->y, 206, 200,
        sf::Color::Transparent, sf::Color::White, 1.f, false);

    // Initialize
    this->readFile(this->musicList);
    this->initButtons();
    this->initMusic();
}

MusicPlayer::~MusicPlayer()
{
    // Wait for all async tasks to complete before destruction
    for (auto& future : futures) {
        future.get();
    }
}

// Core Functions
void MusicPlayer::update(const sf::Vector2f mousePos)
{
    if (!this->hidden) {
        //Update if shown
        this->updateSongFunctions();
        this->updateButtons(mousePos);
        this->updateOpenButton(mousePos);
        this->border->update(mousePos);
    }
    else {
        //Update if hidden
        this->buttons["OPEN"]->update(mousePos);
        this->updateOpenButton(mousePos);
    }
    std::cout << this->currentBufferId << "\n";
}

void MusicPlayer::render(sf::RenderTarget* target)
{
    if (!this->hidden) { 
        //Render if shown
        this->renderButtons(target); 
        this->border->render(target);
    }
    else {
        //Render if hidden
        this->buttons["OPEN"]->render(target);
    }
}

void MusicPlayer::initMusic()
{
    // Initialize any necessary music components here
}

bool MusicPlayer::readFile(const std::string& input) {
    std::ifstream file(input);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << input << std::endl;
        return false;
    }

    std::string line;

    if (!this->fileRead) {
        while (std::getline(file, line)) {
            int id = this->bufferId.fetch_add(1); // Atomically increment bufferId and fetch its value
            this->songNames[id] = line;
            futures.push_back(std::async(std::launch::async, &MusicPlayer::loadSoundAsync, this, id, line));
            std::cout << "Total lines read: " << id << "\n";
        }
    }

    if (file.eof()) {
        std::cout << "Reached end of file.\n";
        this->fileRead = true;
        file.close();
    }

    return true;
}



void MusicPlayer::loadSoundAsync(int id, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filename)) {
        this->buffer[id] = buffer;
    }
    else {
        std::cerr << "Error loading sound with ID " << id << " from file " << filename << std::endl;
    }
}

// Music Player Functions
void MusicPlayer::updateSongFunctions()
{
    this->nextSong();
}

void MusicPlayer::nextSong() {
    if (this->buttons["NEXT"]->isPressed()) {
        if (this->currentBufferId + 1 < this->bufferId.load()) { // Ensure thread-safe read of bufferId
            this->currentBufferId++;
            this->border->setText(this->songNames[this->currentBufferId].substr(20));  // Adjust as needed
            this->song.setBuffer(this->buffer[this->currentBufferId]);
            this->song.play();
        }
    }
    else if (this->buttons["PREV"]->isPressed()) {
        if (this->currentBufferId > 0) {
            this->currentBufferId--;
            this->border->setText(this->songNames[this->currentBufferId].substr(20));  // Adjust as needed
            this->song.setBuffer(this->buffer[this->currentBufferId]);
            this->song.play();
        }
    }
}


// Button Functions
void MusicPlayer::initButtons()
{
    this->buttons["NEXT"] = std::make_unique<Button>(1475, 250, 100, 25, 0.5f, "NEXT",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["PREV"] = std::make_unique<Button>(1370, 250, 100, 25, 0.5f, "PREV",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["CLOSE"] = std::make_unique<Button>(1555, 74, 20, 25, 0.5f, " x ",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["OPEN"] = std::make_unique<Button>(1370, 10, 45, 25, 0.5f, "OPEN",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void MusicPlayer::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }

    //Close button functionality
    if (this->buttons["CLOSE"]->isPressed() && !this->hidden) {
        this->hidden = true;
    }
    else if (this->buttons["CLOSE"]->isPressed() && this->hidden) {
        this->hidden = false;
    }
}

void MusicPlayer::updateOpenButton(const sf::Vector2f mousePos)
{
    //Open button functionality
    if (this->buttons["OPEN"]->isPressed() && this->hidden) {
        this->hidden = false;
    } 
    else if (this->buttons["OPEN"]->isPressed() && !this->hidden) {
        this->hidden = true;
    }
}

void MusicPlayer::renderButtons(sf::RenderTarget* target) {
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}