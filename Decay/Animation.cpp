#include"Animation.h"

Animation::Animation()
{
	this->animationFrame = -1;
	this->combatAnimationFrame = -1;
	this->combatAnimationLocation = -1;

	this->zinTalkNot = true;
	this->decayWarning = false;

	this->animEnd = true;
	
	decayWarn.setPosition(10000, 10000);

	zin1.loadFromFile("Assets/Sprites/zinsprite.png");
	zin2.loadFromFile("Assets/Sprites/zinspriteannoyed.png");
	zinSprite.setPosition(50.0f, 345.0f);
	zinSprite.setScale(0.0504f, 0.0504f);

	not1.loadFromFile("Assets/Game_Resources/alert1.png");
	not2.loadFromFile("Assets/Game_Resources/alert2.png");
	not3.loadFromFile("Assets/Game_Resources/alert3.png");
	not4.loadFromFile("Assets/Game_Resources/alert4.png");
	notSprite.setScale(3.0f, 3.0f);

	heal1.loadFromFile("Assets/Game_Resources/heal1.png");
	heal2.loadFromFile("Assets/Game_Resources/heal2.png");
	heal3.loadFromFile("Assets/Game_Resources/heal3.png");
	heal4.loadFromFile("Assets/Game_Resources/heal4.png");
	heal5.loadFromFile("Assets/Game_Resources/heal5.png");
	healSprite.setScale(0.2f, 0.2f);

	anvil1.loadFromFile("Assets/Game_Resources/anvil1.png");
	anvil2.loadFromFile("Assets/Game_Resources/anvil2.png");
	anvil3.loadFromFile("Assets/Game_Resources/anvil3.png");
	anvil4.loadFromFile("Assets/Game_Resources/anvil4.png");
	anvil5.loadFromFile("Assets/Game_Resources/anvil5.png");
	anvilSprite.setScale(1.6f, 1.6f);

	hit1.loadFromFile("Assets/Game_Resources/hitanimation1.png");
	hit2.loadFromFile("Assets/Game_Resources/hitanimation2.png");
	hit3.loadFromFile("Assets/Game_Resources/hitanimation3.png");
	hit4.loadFromFile("Assets/Game_Resources/hitanimation4.png");
	hit5.loadFromFile("Assets/Game_Resources/hitanimation5.png");
	hit6.loadFromFile("Assets/Game_Resources/hitanimation6.png");
	hitSprite.setScale(0.24f, 0.24f);

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

void Animation::animateAnvil(Assets& assets)
{
	//Set Position Based Off Current Bonfire
	switch (assets.getMapCounter()) {
	case 0:
		anvilSprite.setPosition(975, 400);
		break;
	case 1:
		anvilSprite.setPosition(450, 705);
		break;
	case 2:
		anvilSprite.setPosition(1350, 150);
		break;
	}

	//Animate Anvil Icon
	this->animateTimer();
	switch (this->animationFrame) {
	case -1:
		anvilSprite.setTexture(anvil1);
		break;
	case 0:
		anvilSprite.setTexture(anvil2);
		break;
	case 1:
		anvilSprite.setTexture(anvil3);
		break;
	case 2:
		anvilSprite.setTexture(anvil4);
		break;
	case 3:
		anvilSprite.setTexture(anvil5);
		break;
	}
}

void Animation::animateHeal(Assets& assets)
{
	//Set Position Based Off Current Bonfire
	switch (assets.getMapCounter()) {
	case 0:
		healSprite.setPosition(650, 400);
		break;
	case 1:
		healSprite.setPosition(650, 450);
		break;
	case 2:
		healSprite.setPosition(700, 200);
		break;
	}

	//Animate Heal Icon
	this->animateTimer();
	switch (this->animationFrame) {
	case -1:
		healSprite.setTexture(heal1);
		break;
	case 0:
		healSprite.setTexture(heal2);
		break;
	case 1:
		healSprite.setTexture(heal3);
		break;
	case 2:
		healSprite.setTexture(heal4);
		break;
	case 3:
		healSprite.setTexture(heal5);
		break;
	}
}

void Animation::animateAttack(Assets& assets)
{
	//Set Animation Position
	switch (this->combatAnimationLocation) {
	case -1:
		hitSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		break;
	case 0:
		//Hostile Sprite Location
		hitSprite.setPosition(sf::Vector2f(1650.0f, 300.0f));
		break;
	case 1:
		//Player Sprite Location
		hitSprite.setPosition(sf::Vector2f(50.0f, 100.0f));
		break;
	case 2:
		//Zin Sprite Location
		hitSprite.setPosition(sf::Vector2f(50.0f, 300.0f));
		break;
	case 3:
		//Thom Sprite Location
		hitSprite.setPosition(sf::Vector2f(50.0f, 500.0f));
		break;
	}

	//Animate Hit Animation
	this->animateCombatTimer();
	switch (this->combatAnimationFrame) {
	case -1:
		hitSprite.setTexture(hit1);
		break;
	case 0:
		hitSprite.setTexture(hit2);
		break;
	case 1:
		hitSprite.setTexture(hit3);
		break;
	case 2:
		hitSprite.setTexture(hit4);
		break;
	case 3:
		hitSprite.setTexture(hit5);
		break;
	case 4:
		hitSprite.setTexture(hit6);
		hitSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		this->animEnd = true;
		break;
	}
}

//Draw Animation Functions
void Animation::drawAnimations(Assets& assets)
{
	if (this->zinTalkNot == true) {
		notSprite.setPosition(50.0f, 240.0f);
	}
	else if (this->zinTalkNot == false) {
		notSprite.setPosition(10000.0f, 10000.0f);
	}

	if (assets.getBonfireAssets()) {
		this->animateAnvil(assets);
		this->animateHeal(assets);
	}
	else if (!assets.getBonfireAssets()) {
		anvilSprite.setPosition(10000, 10000);
		healSprite.setPosition(10000, 10000);
	}
}