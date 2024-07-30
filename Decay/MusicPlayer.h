#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<fstream>
#include<vector>
#include<string>
class MusicPlayer
{
public:
	//Constructors and Destructors
	MusicPlayer();
	~MusicPlayer();

	//Core Functions
	void initMusic();
	bool readFile(const std::string& input);

	//Button Functions

	//Rectangle Functions

private:

	bool fileRead;
	std::vector<std::string> music;

	class Music {
	public:
		//Constructors and Destructors
		Music() {

		}

		~Music() {

		}

	private:



	};
};

