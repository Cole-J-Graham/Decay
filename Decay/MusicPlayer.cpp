#include "MusicPlayer.h"
//Constructors and Destructors
MusicPlayer::MusicPlayer() 
{
    this->fileRead = false;

	//Initialize
	this->initMusic();
}

MusicPlayer::~MusicPlayer()
{

}

//Core Functions
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

    if (!this->fileRead) {
        while (std::getline(file, line)) {
            this->music.push_back(line);
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

//Button Functions

//Rectangle Functions