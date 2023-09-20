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
public:
	Animation();
	~Animation();

	sf::Texture zin1;
	sf::Texture zin2;
	sf::Sprite zinSprite;

	sf::Clock timer;
	sf::Time elapsed;

	void animateZin();
	void animateTimer();
};


#endif
