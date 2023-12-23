#include"Animation.h"

Animation::Animation()
{
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

	//PLayer Movement Animations
	playerWalkDown.loadFromFile("Assets/SpriteSheets/playerWalkSpriteSheet.png");
	playerWalkLeft.loadFromFile("Assets/SpriteSheets/playerWalkLeftSpriteSheet.png");
	playerWalkRight.loadFromFile("Assets/SpriteSheets/playerWalkRightSpriteSheet.png");
	//playerWalkUp.loadFromFile(""); (SHEET REQUIRED)

	zinWalkDown.loadFromFile("Assets/SpriteSheets/zinWalkSpriteSheet.png");
	zinWalkLeft.loadFromFile("Assets/SpriteSheets/zinWalkLeftSpriteSheet.png");
	zinWalkRight.loadFromFile("Assets/SpriteSheets/zinWalkRightSpriteSheet.png");
	//zinWalkUp.loadFromFile(""); (SHEET REQUIRED)

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

	guard1.loadFromFile("Assets/Game_Resources/guard1.png");
	guard2.loadFromFile("Assets/Game_Resources/guard2.png");
	guard3.loadFromFile("Assets/Game_Resources/guard3.png");
	guard4.loadFromFile("Assets/Game_Resources/guard4.png");
	guard5.loadFromFile("Assets/Game_Resources/guard5.png");
	guardSprite.setScale(1.0f, 1.0f);

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
		animateSprite(hitSprite, 64);
		break;
	case 1:
		animateSprite(hitSprite, 64);
		break;
	case 2:
		animateSprite(guardSprite, 16);
		break;
	case 3:
		animateSprite(guardBrkSprite, 16);
		break;
	}
}

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

//Movement
void Animation::walkCycle()
{
	if (this->playerMoving) {
		this->animateTimer();
		switch (this->animationFrame) {
		case -1:
			sheetX = 0;
			sheetY = 0;
			break;
		case 0:
			sheetX = 16;
			sheetY = 0;
			break;
		case 1:
			sheetX = 32;
			sheetY = 0;
			break;
		case 2:
			sheetX = 48;
			sheetY = 0;
			break;
		}
	}
	playerPixelSprite.setPosition(x_pos, y_pos);
	playerPixelSprite.setScale(3, 3);
	playerPixelSprite.setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		playerPixelSprite.setPosition(x_pos, y_pos--);
		this->playerMoving = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerPixelSprite.setPosition(x_pos--, y_pos);
		playerPixelSprite.setTexture(playerWalkLeft);
		this->playerMoving = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		playerPixelSprite.setPosition(x_pos, y_pos++);
		playerPixelSprite.setTexture(playerWalkDown);
		this->playerMoving = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerPixelSprite.setPosition(x_pos++, y_pos);
		playerPixelSprite.setTexture(playerWalkRight);
		this->playerMoving = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->playerMoving = false;
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

void Animation::animateNote()
{
	decayWarn.setString(animateString);
	decayWarn.setFont(font);
	decayWarn.setCharacterSize(16);

	this->animateTimer();
	if (this->decayWarning) {
		switch (this->animationFrame) {
		case -1:
			decayWarn.setPosition(notePosX, notePosY);
			decayWarn.setFillColor(sf::Color(255, 255, 255));
			break;
		case 0:
			decayWarn.setPosition(notePosX, notePosY - 1);
			decayWarn.setFillColor(sf::Color(190, 190, 190));
			break;
		case 1:
			decayWarn.setPosition(notePosX, notePosY - 2);
			decayWarn.setFillColor(sf::Color(145, 145, 145));
			break;
		case 2:
			decayWarn.setPosition(notePosX, notePosY - 3);
			decayWarn.setFillColor(sf::Color(65, 65, 65));
			break;
		case 3:
			decayWarn.setPosition(10000, 10000);
			this->decayWarning = false;
			break;
		}
	}
}

void Animation::animateAnvil()
{
	anvilSprite.setTextureRect(sf::IntRect(sheetX, sheetY, 32, 32));
	anvilSprite.setPosition(1475, 675);
	this->animateTimer();
	switch (this->animationFrame) {
	case -1:
		sheetX = 0;
		sheetY = 0;
		break;
	case 0:
		sheetX = 32;
		sheetY = 0;
		break;
	case 1:
		sheetX = 64;
		sheetY = 0;
		break;
	case 2:
		sheetX = 86;
		sheetY = 0;
		break;
	}
}

void Animation::animateHeal()
{
	healSprite.setTextureRect(sf::IntRect(sheetX, sheetY, 32, 32));
	healSprite.setPosition(1475, 750);
	//Animate Heal Icon
	this->animateTimer();
	switch (this->animationFrame) {
	case -1:
		sheetX = 0;
		sheetY = 0;
		break;
	case 0:
		sheetX = 32;
		sheetY = 0;
		break;
	case 1:
		sheetX = 64;
		sheetY = 0;
		break;
	case 2:
		sheetX = 86;
		sheetY = 0;
		break;
	}
}

//Combat Animation Functions
void Animation::animateSprite(sf::Sprite& inSprite, float xOffset)
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

	//Animate Hit Animation
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
	this->animateAnvil();
	this->animateHeal();
}