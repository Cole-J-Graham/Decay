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
	int animation;
	int animationFrame;
	int combatAnimationFrame;
	int combatAnimationLocation;
	int menuAnimationFrame;

	bool decayWarning;
	bool menuCycleSlow;
	bool menuCycleFast;

	bool animEnd;

	float notePosX;
	float notePosY;

	std::string animateString;

public:

	Animation();
	~Animation();

	sf::Font font;
	sf::Text decayWarn;

	sf::Texture zin1;
	sf::Texture zin2;

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

	sf::Texture hitBlank;
	sf::Texture hit1;
	sf::Texture hit2;
	sf::Texture hit3;
	sf::Texture hit4;
	sf::Texture hit5;
	sf::Texture hit6;

	sf::Texture guard1;
	sf::Texture guard2;
	sf::Texture guard3;
	sf::Texture guard4;
	sf::Texture guard5;

	sf::Texture guardBrk1;
	sf::Texture guardBrk2;
	sf::Texture guardBrk3;
	sf::Texture guardBrk4;
	sf::Texture guardBrk5;

	sf::Texture menu1;
	sf::Texture menu2;
	sf::Texture menu3;
	sf::Texture menu4;
	sf::Texture menu5;
	sf::Texture menu6;

	sf::Sprite zinSprite;
	sf::Sprite healSprite;
	sf::Sprite anvilSprite;
	sf::Sprite hitSprite;
	sf::Sprite guardSprite;
	sf::Sprite guardBrkSprite;
	sf::Sprite menuSprite;

	sf::Clock timer;
	sf::Clock combatTimer;
	sf::Clock menuTimer;
	sf::Clock menuTimerFast;

	sf::Time elapsed;
	sf::Time combatElapsed;
	sf::Time menuElapsed;
	sf::Time menuElapsedFast;

	//Core Animation Functions
	void pickAnimation(Assets& assets);
	void animateTimer();
	void animateCombatTimer();
	void animateMenuTimer();

	//Animation Functions
	void animateZin();
	void animateNote();
	void animateAnvil(Assets& assets);
	void animateHeal(Assets& assets);
	void animateMenu(Assets& assets);

	//Combat Animation Functions
	void animateSlash(Assets& assets);
	void animateGuard(Assets& assets);
	void animateGuardBrk(Assets& assets);
	void animateSmite(Assets& assets);

	//Draw Animation Functions
	void drawAnimations(Assets& assets);

	//Getters
	int& getAnimation() { return this->animation; };
	int& getAnimationFrame() { return this->animationFrame; };
	int& getCombatAnimationFrame() { return this->combatAnimationFrame; };
	int& getCombatAnimationLocation() { return this->combatAnimationLocation;};

	float& getNotePosX() { return this->notePosX; };
	float& getNotePosY() { return this->notePosY; };
	std::string& getAnimateString() { return this->animateString; };

	bool& getDecayWarning() { return this->decayWarning; };
	bool& getAnimEnd() { return this->animEnd; };

	//Setters
	void setTimerRestart() { timer.restart(); };
};


#endif
