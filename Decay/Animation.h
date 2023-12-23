#ifndef ANIMATION_H
#define ANIMATION_H
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Audio.hpp>
#include"Assets.h"

class Animation : virtual public Assets
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

	float x_pos;
	float y_pos;

	float sheetX;
	float sheetY;

	bool playerMoving;

	std::string animateString;

public:

	Animation();
	~Animation();

	//Character Sprite Animations
	sf::Sprite playerPixelSprite;
	sf::Texture playerWalkDown;
	sf::Texture playerWalkLeft;
	sf::Texture playerWalkRight;
	sf::Texture playerWalkUp;

	//Zin Walk Animations
	sf::Sprite zinPixelSprite;
	sf::Texture zinWalkDown;
	sf::Texture zinWalkLeft;
	sf::Texture zinWalkRight;
	sf::Texture zinWalkUp;

	//Other Animations
	sf::Font font;
	sf::Text decayWarn;

	sf::Texture zin1;
	sf::Texture zin2;

	sf::Texture healSpriteSheet;

	sf::Texture anvilSpriteSheet;

	sf::Texture hitBlank;
	sf::Texture hitSpriteSheet;

	sf::Texture guard1;
	sf::Texture guard2;
	sf::Texture guard3;
	sf::Texture guard4;
	sf::Texture guard5;

	sf::Texture guardBrkSpriteSheet;
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
	void pickAnimation();
	void animateTimer();
	void animateCombatTimer();
	void animateMenuTimer();

	//Movement
	void walkCycle();

	//Animation Functions
	void animateZin();
	void animateNote();
	void animateAnvil();
	void animateHeal();
	void animateMenu();

	//Combat Animation Functions
	void animateSprite(sf::Sprite& inSprite, float xOffset);
	void animateSlash();
	void animateGuard();
	void animateGuardBrk();
	void animateSmite();

	//Load Animations
	void bonfireAnimations();

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
