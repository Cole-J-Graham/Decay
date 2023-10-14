#ifndef ANIMATION_H
#define ANIMATION_H
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Audio.hpp>
#include"Assets.h"

class Animation
{
private:
	int animationFrame;

	bool zinTalkNot;
	bool decayWarning;

public:
	Animation();
	~Animation();

	sf::Font font;
	sf::Text decayWarn;

	sf::Texture zin1;
	sf::Texture zin2;

	sf::Texture not1;
	sf::Texture not2;
	sf::Texture not3;
	sf::Texture not4;

	sf::Texture heal1;
	sf::Texture heal2;
	sf::Texture heal3;
	sf::Texture heal4;
	sf::Texture heal5;

	sf::Texture anvil1;
	sf::Texture anvil2;
	sf::Texture anvil3;
	sf::Texture anvil4;
	sf::Texture anvil5;

	sf::Sprite zinSprite;
	sf::Sprite notSprite;
	sf::Sprite healSprite;
	sf::Sprite anvilSprite;

	sf::Clock timer;
	sf::Time elapsed;

	//Core Animation Functions
	void animateTimer();

	//Animation Functions
	void animateZin();
	void animateNotification();
	void animateDecayWarn();
	void animateAnvil(Assets& assets);
	void animateHeal(Assets& assets);

	//Draw Animation Functions
	void drawAnimations(Assets& assets);

	//Getters
	int& getAnimationFrame() { return this->animationFrame; };

	bool& getZinTalkNot() { return this->zinTalkNot; };
	bool& getDecayWarning() { return this->decayWarning; };

	//Setters
	void setTimerRestart() { timer.restart(); };
};


#endif
