#include"Animation.h"

Animation::Animation()
{
	this->animationFrame = -1;

	this->zinTalkNot = true;
	this->decayWarning = false;
	

	zin1.loadFromFile("Assets/Sprites/zinsprite.png");
	zin2.loadFromFile("Assets/Sprites/zinspriteannoyed.png");

	not1.loadFromFile("Assets/Game_Resources/alert1.png");
	not2.loadFromFile("Assets/Game_Resources/alert2.png");
	not3.loadFromFile("Assets/Game_Resources/alert3.png");
	not4.loadFromFile("Assets/Game_Resources/alert4.png");

	zinSprite.setPosition(50.0f, 345.0f);
	zinSprite.setScale(0.0504f, 0.0504f);

	notSprite.setScale(3.0f, 3.0f);

	decayWarn.setPosition(10000, 10000);

	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
}

Animation::~Animation()
{

}

//Core Animation Functions
void Animation::animateTimer()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 0.5f) {
		if (this->animationFrame == -1) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 0) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 1) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 2) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 3) {
			this->animationFrame = -1;
			timer.restart();
		}
	}
}

//Animation Functions
void Animation::animateZin()
{
	this->animateTimer();
	switch (this->animationFrame) {
	case 0:
		zinSprite.setTexture(zin1);
		break;
	case 1:
		zinSprite.setTexture(zin2);
		break;
	}
}

void Animation::animateNotification()
{
	this->animateTimer();
	switch (this->animationFrame) {
	case 0:
		notSprite.setTexture(not1);
		break;
	case 1:
		notSprite.setTexture(not2);
		break;
	case 2:
		notSprite.setTexture(not3);
		break;
	case 3:
		notSprite.setTexture(not4);
		break;
	}
}

void Animation::animateDecayWarn()
{
	decayWarn.setString("+1 Decay...");
	decayWarn.setFont(font);
	decayWarn.setCharacterSize(16);

	this->animateTimer();
	if (this->decayWarning) {
		switch (this->animationFrame) {
		case -1:
			decayWarn.setPosition(1500, 43);
			decayWarn.setFillColor(sf::Color(255, 255, 255));
			break;
		case 0:
			decayWarn.setPosition(1500, 42);
			decayWarn.setFillColor(sf::Color(190, 190, 190));
			break;
		case 1:
			decayWarn.setPosition(1500, 41);
			decayWarn.setFillColor(sf::Color(145, 145, 145));
			break;
		case 2:
			decayWarn.setPosition(1500, 40);
			decayWarn.setFillColor(sf::Color(65, 65, 65));
			break;
		case 3:
			decayWarn.setPosition(10000, 10000);
			this->decayWarning = false;
			break;
		}
	}
}

//Draw Animation Functions
void Animation::drawAnimations()
{
	if (this->zinTalkNot == true) {
		notSprite.setPosition(50.0f, 240.0f);
	}
	else if (this->zinTalkNot == false) {
		notSprite.setPosition(10000.0f, 10000.0f);
	}
}