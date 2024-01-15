#include"Animation.h"

Animation::Animation()
{
	this->characterSelection = 1;
	this->animation = -1;
	this->animationFrame = -1;
	this->combatAnimationFrame = -1;
	this->combatAnimationLocation = -1;
	this->menuAnimationFrame = -1;

	this->menuCycleSlow = true;
	this->menuCycleFast = false;

	this->decayWarning = false;

	this->animEnd = true;

	this->sheetX;
	this->sheetY;
	
	this->notePosX = 0;
	this->notePosY = 0;

	this->animateString = "";
	
	decayWarn.setPosition(10000, 10000);

	zin1.loadFromFile("Assets/Sprites/zinsprite.png");
	zin2.loadFromFile("Assets/Sprites/zinspriteannoyed.png");
	zinSprite.setPosition(50.0f, 345.0f);
	zinSprite.setScale(0.0504f, 0.0504f);

	healSpriteSheet.loadFromFile("Assets/Game_Resources/healSpriteSheet.png");
	healSprite.setTexture(healSpriteSheet);
	healSprite.setScale(1.9f, 1.9f);

	anvilSpriteSheet.loadFromFile("Assets/Game_Resources/anvilSpriteSheet.png");
	anvilSprite.setTexture(anvilSpriteSheet);
	anvilSprite.setScale(1.9, 1.9f);

	hitBlank.loadFromFile("Assets/Game_Resources/hitanimateblank.png");
	hitSpriteSheet.loadFromFile("Assets/Game_Resources/hitAnimationSpriteSheet.png");
	hitSprite.setScale(2.4f, 2.4f);
	hitSprite.setTexture(hitSpriteSheet);
	hitSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));

	guardSpriteSheet.loadFromFile("Assets/Game_Resources/guardSpriteSheet.png");
	guardSprite.setScale(9.5f, 9.5f);
	guardSprite.setTexture(guardSpriteSheet);
	guardSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));

	guardBrkSpriteSheet.loadFromFile("Assets/Game_Resources/guardedSpriteSheet.png");
	guardBrkSprite.setScale(9.5f, 9.5f);
	guardBrkSprite.setTexture(guardBrkSpriteSheet);
	guardBrkSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));

	menu1.loadFromFile("Assets/Game_Resources/decay menu1.png");
	menu2.loadFromFile("Assets/Game_Resources/decay menu2.png");
	menu3.loadFromFile("Assets/Game_Resources/decay menu3.png");
	menu4.loadFromFile("Assets/Game_Resources/decay menu4.png");
	menu5.loadFromFile("Assets/Game_Resources/decay menu5.png");
	menu6.loadFromFile("Assets/Game_Resources/decay menu6.png");
	menuSprite.setPosition(620, 260);

	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
}

Animation::~Animation()
{

}

//Core Animation Functions
void Animation::pickAnimation()
{
	switch (this->animation) {
	case 0:
		animateSixFrames(hitSprite, 64);
		break;
	case 1:
		animateSixFrames(hitSprite, 64);
		break;
	case 2:
		animateSixFrames(guardSprite, 16);
		break;
	case 3:
		animateSixFrames(guardBrkSprite, 16);
		break;
	}
}

void Animation::animateSixFrames(sf::Sprite& inSprite, float xOffset)
{
	//Set Animation Position
	switch (this->combatAnimationLocation) {
	case -1:
		inSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		break;
	case 0:
		//Hostile Sprite Location
		inSprite.setPosition(sf::Vector2f(1650.0f, 300.0f));
		break;
	case 1:
		//Player Sprite Location
		inSprite.setPosition(sf::Vector2f(50.0f, 100.0f));
		break;
	case 2:
		//Zin Sprite Location
		inSprite.setPosition(sf::Vector2f(50.0f, 300.0f));
		break;
	case 3:
		//Thom Sprite Location
		inSprite.setPosition(sf::Vector2f(50.0f, 500.0f));
		break;
	}

	//Animate Sprite
	this->animateCombatTimer();
	switch (this->combatAnimationFrame) {
	case -1:
		inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
		sheetX = 0;
		sheetY = 0;
		break;
	case 0:
		inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
		sheetX = xOffset;
		sheetY = 0;
		break;
	case 1:
		inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
		sheetX = xOffset * 2;
		sheetY = 0;
		break;
	case 2:
		inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
		sheetX = xOffset * 3;
		sheetY = 0;
		break;
	case 3:
		inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
		sheetX = xOffset * 4;
		sheetY = 0;
		break;
	case 4:
		inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
		sheetX = xOffset * 5;
		sheetY = 0;
		inSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		this->animEnd = true;
		this->combatAnimationFrame = -1;
		break;
	}
}

void Animation::animateFourFrames(sf::Sprite& inSprite, float xOffset, float posX, float posY)
{
	inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
	inSprite.setPosition(posX, posY);
	this->animateTimer();
	switch (this->animationFrame) {
	case -1:
		sheetX = 0;
		sheetY = 0;
		break;
	case 0:
		sheetX = xOffset;
		sheetY = 0;
		break;
	case 1:
		sheetX = xOffset * 2;
		sheetY = 0;
		break;
	case 2:
		sheetX = xOffset * 3;
		sheetY = 0;
		break;
	}
}

//Animation Timers
void Animation::animateTimer()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 0.2f) {
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
			this->animationFrame = -1;
			timer.restart();
		}
	}
}

void Animation::animateCombatTimer()
{
	combatElapsed = combatTimer.getElapsedTime();
	if (combatElapsed.asSeconds() >= 0.1f) {
		if (this->combatAnimationFrame == -1) {
			this->combatAnimationFrame++;
			combatTimer.restart();
		}
		else if (this->combatAnimationFrame == 0) {
			this->combatAnimationFrame++;
			combatTimer.restart();
		}
		else if (this->combatAnimationFrame == 1) {
			this->combatAnimationFrame++;
			combatTimer.restart();
		}
		else if (this->combatAnimationFrame == 2) {
			this->combatAnimationFrame++;
			combatTimer.restart();
		}
		else if (this->combatAnimationFrame == 3) {
			this->combatAnimationFrame++;
			combatTimer.restart();
		}
		else if (this->combatAnimationFrame == 4) {
			this->combatAnimationFrame = -1;
			combatTimer.restart();
		}
	}
}

void Animation::animateMenuTimer()
{
	if (this->menuCycleSlow) {
		menuElapsed = menuTimer.getElapsedTime();
		if (menuElapsed.asSeconds() >= 1.5f) {
			if (this->menuAnimationFrame == -1) {
				this->menuAnimationFrame++;
				menuTimer.restart();
			}
			else if (this->menuAnimationFrame == 0) {
				this->menuAnimationFrame++;
				menuTimer.restart();
			}
			else if (this->menuAnimationFrame == 1) {
				this->menuAnimationFrame++;
				menuTimer.restart();
				this->menuCycleFast = true;
				this->menuCycleSlow = false;
			}
		}
	}
	else if (this->menuCycleFast) {
		menuElapsedFast = menuTimerFast.getElapsedTime();
		if (menuElapsedFast.asSeconds() >= 0.0001f) {
			if (this->menuAnimationFrame == 2) {
				this->menuAnimationFrame++;
				menuTimerFast.restart();
			}
			else if (this->menuAnimationFrame == 3) {
				this->menuAnimationFrame++;
				this->menuAnimationFrame = -1;
				menuTimerFast.restart();
				this->menuCycleSlow = true;
			}
			else if (this->menuAnimationFrame == 4) {
				this->menuAnimationFrame++;
				this->menuAnimationFrame = -1;
				menuTimerFast.restart();
				this->menuCycleSlow = true;
			}
		}
	}
}

//Animate Functions
void Animation::animateMenu()
{
	//Animate Hit Animation
	this->animateMenuTimer();
	switch (this->menuAnimationFrame) {
	case -1:
		menuSprite.setTexture(menu1);
		break;
	case 0:
		menuSprite.setTexture(menu2);
		break;
	case 1:
		menuSprite.setTexture(menu3);
		break;
	case 2:
		menuSprite.setTexture(menu4);
		break;
	case 3:
		menuSprite.setTexture(menu5);
		break;
	case 4:
		menuSprite.setTexture(menu6);
		break;
	}
}

//Load Animations
void Animation::bonfireAnimations()
{
	this->animateFourFrames(anvilSprite, 32, 1475, 675);
	this->animateFourFrames(healSprite, 32, 1475, 750);
}