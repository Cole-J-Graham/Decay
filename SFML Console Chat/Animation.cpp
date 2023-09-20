#include"Animation.h"

Animation::Animation()
{
	this->animationFrame = 0;

	zin1.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
	zin2.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinspriteannoyed.png");

	zinSprite.setPosition(50.0f, 345.0f);
	zinSprite.setScale(0.0504f, 0.0504f);
}

Animation::~Animation()
{

}

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

void Animation::animateTimer()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 1.0f) {
		if (this->animationFrame == 0) {
			this->animationFrame++;
		}
		else if (this->animationFrame == 1) {
			this->animationFrame--;
		}
		std::cout << animationFrame;
		timer.restart();
	}
}