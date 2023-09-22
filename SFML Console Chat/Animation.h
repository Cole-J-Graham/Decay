#ifndef ANIMATION_H
#define ANIMATION_H
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Audio.hpp>

class Animation
{
private:
	int animationFrame;

	bool zinTalkNot;

public:
	Animation();
	~Animation();

	sf::Texture zin1;
	sf::Texture zin2;

	sf::Texture not1;
	sf::Texture not2;
	sf::Texture not3;
	sf::Texture not4;

	sf::Sprite zinSprite;
	sf::Sprite notSprite;

	sf::Clock timer;
	sf::Time elapsed;

	//Core Animation Functions
	void animateTimer();

	//Animation Functions
	void animateZin();
	void animateNotification();

	//Draw Animation Functions
	void drawAnimations();

	//Getters
	bool& getZinTalkNot() { return this->zinTalkNot; };
};


#endif
