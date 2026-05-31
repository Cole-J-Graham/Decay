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

    this->readFile(this->musicList);
    this->initUi();
    this->initMusic();
}

MusicPlayer::~MusicPlayer()
{
    this->song.stop();
}

// Core Functions
void MusicPlayer::update(const sf::Vector2f mousePos)
{
    this->ui.update(mousePos);
    this->updateUi(mousePos);

    if (!this->hidden) {
        this->updateSongFunctions();
    }
}

void MusicPlayer::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    this->ui.render(*target);
}

void MusicPlayer::initMusic()
{
    if (this->songNames.count(this->currentBufferId) > 0) {
        this->ui.rectangle("BORDER").setText(this->getDisplayName(this->songNames[this->currentBufferId]));
    }
}

bool MusicPlayer::readFile(const std::string& input)
{
    std::ifstream file(input);

    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << input << std::endl;
        return false;
    }

    if (this->fileRead) {
        return true;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        const int id = this->bufferId;

        // Lazy load: only store the file path here. Do NOT load the sound yet.
        this->songNames[id] = line;

        std::cout << "Song path registered: " << id << " -> " << line << "\n";

        this->bufferId++;
    }

    std::cout << "Reached end of file.\n";
    this->fileRead = true;

    return true;
}

bool MusicPlayer::loadSound(int id)
{
    if (this->buffer.count(id) > 0) {
        return true;
    }

    if (this->songNames.count(id) <= 0) {
        std::cerr << "Cannot load sound. No song path registered for ID " << id << std::endl;
        return false;
    }

    const std::string& filename = this->songNames[id];

    sf::SoundBuffer soundBuffer;

    if (!soundBuffer.loadFromFile(filename)) {
        std::cerr << "Error loading sound with ID " << id << " from file " << filename << std::endl;
        return false;
    }

    this->buffer[id] = soundBuffer;

    std::cout << "Loaded sound on demand: " << id << " -> " << filename << "\n";

    return true;
}

// Music Player Functions
void MusicPlayer::updateSongFunctions()
{
    this->nextSong();
}

void MusicPlayer::nextSong()
{
    if (this->ui.button("NEXT").isPressed()) {
        if (this->currentBufferId + 1 < this->bufferId) {
            this->currentBufferId++;
            this->playSong(this->currentBufferId);
        }
    }
    else if (this->ui.button("PREV").isPressed()) {
        if (this->currentBufferId > 0) {
            this->currentBufferId--;
            this->playSong(this->currentBufferId);
        }
    }
}

bool MusicPlayer::playSong(int id)
{
    if (id < 0 || id >= this->bufferId) {
        return false;
    }

    if (!this->loadSound(id)) {
        return false;
    }

    if (this->songNames.count(id) > 0) {
        this->ui.rectangle("BORDER").setText(this->getDisplayName(this->songNames[id]));
    }

    this->song.stop();
    this->song.setBuffer(this->buffer[id]);
    this->song.play();

    return true;
}

// UI Functions
void MusicPlayer::initUi()
{
    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(150, 150, 150, 255);
    const sf::Color active(20, 20, 20, 70);

    this->ui.addRectangle("BORDER", std::make_unique<Rectangle>("Test", sf::Color::White, 16, this->x, this->y, 206, 200, sf::Color::Transparent, sf::Color::White, 1.f, true));

    this->ui.addButton("NEXT", std::make_unique<Button>(1475, 250, 100, 25, 0.5f, "NEXT", idle, hover, active, true));
    this->ui.addButton("PREV", std::make_unique<Button>(1370, 250, 100, 25, 0.5f, "PREV", idle, hover, active, true));
    this->ui.addButton("CLOSE", std::make_unique<Button>(1555, 74, 20, 25, 0.5f, " x ", idle, hover, active, true));
    this->ui.addButton("OPEN", std::make_unique<Button>(1370, 10, 55, 25, 0.5f, "MUSIC", idle, hover, active, false));

    this->hidePanel();
}

void MusicPlayer::updateUi(const sf::Vector2f mousePos)
{
    if (this->hidden) {
        if (this->ui.button("OPEN").isPressed()) {
            this->showPanel();
        }

        return;
    }

    if (this->ui.button("OPEN").isPressed() || this->ui.button("CLOSE").isPressed()) {
        this->hidePanel();
    }
}

void MusicPlayer::showPanel()
{
    this->hidden = false;

    this->ui.rectangle("BORDER").show();

    this->ui.button("NEXT").show();
    this->ui.button("PREV").show();
    this->ui.button("CLOSE").show();
    this->ui.button("OPEN").show();
}

void MusicPlayer::hidePanel()
{
    this->hidden = true;

    this->ui.rectangle("BORDER").hide();

    this->ui.button("NEXT").hide();
    this->ui.button("PREV").hide();
    this->ui.button("CLOSE").hide();

    this->ui.button("OPEN").show();
}

// Setters
void MusicPlayer::setHidden()
{
    this->hidePanel();
}

void MusicPlayer::setShown()
{
    this->showPanel();
}

// Helpers
std::string MusicPlayer::getDisplayName(const std::string& filename) const
{
    const std::size_t slash = filename.find_last_of("/\\");

    if (slash == std::string::npos) {
        return filename;
    }

    return filename.substr(slash + 1);
}