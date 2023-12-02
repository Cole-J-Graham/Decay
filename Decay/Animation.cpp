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
	
	decayWarn.setPosition(10000, 10000);

	zin1.loadFromFile("Assets/Sprites/zinsprite.png");
	zin2.loadFromFile("Assets/Sprites/zinspriteannoyed.png");
	zinSprite.setPosition(50.0f, 345.0f);
	zinSprite.setScale(0.0504f, 0.0504f);

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
	anvilSprite.setScale(1.8f, 1.8f);

	hitBlank.loadFromFile("Assets/Game_Resources/hitanimateblank.png");
	hit1.loadFromFile("Assets/Game_Resources/hitanimation1.png");
	hit2.loadFromFile("Assets/Game_Resources/hitanimation2.png");
	hit3.loadFromFile("Assets/Game_Resources/hitanimation3.png");
	hit4.loadFromFile("Assets/Game_Resources/hitanimation4.png");
	hit5.loadFromFile("Assets/Game_Resources/hitanimation5.png");
	hit6.loadFromFile("Assets/Game_Resources/hitanimation6.png");
	hitSprite.setScale(0.24f, 0.24f);

	guard1.loadFromFile("Assets/Game_Resources/guard1.png");
	guard2.loadFromFile("Assets/Game_Resources/guard2.png");
	guard3.loadFromFile("Assets/Game_Resources/guard3.png");
	guard4.loadFromFile("Assets/Game_Resources/guard4.png");
	guard5.loadFromFile("Assets/Game_Resources/guard5.png");
	guardSprite.setScale(1.0f, 1.0f);

	guardBrk1.loadFromFile("Assets/Game_Resources/shield1.png");
	guardBrk2.loadFromFile("Assets/Game_Resources/shield2.png");
	guardBrk3.loadFromFile("Assets/Game_Resources/shield3.png");
	guardBrk4.loadFromFile("Assets/Game_Resources/shield4.png");
	guardBrk5.loadFromFile("Assets/Game_Resources/shield5.png");
	guardBrkSprite.setScale(1.0f, 1.0f);

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
void Animation::pickAnimation(Assets& assets)
{
	switch (this->animation) {
	case 0:
		animateSlash(assets);
		break;
	case 1:
		animateSmite(assets);
		break;
	case 2:
		animateGuard(assets);
		break;
	case 3:
		animateGuardBrk(assets);
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
	anvilSprite.setPosition(1475, 675);
	
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
	healSprite.setPosition(1475, 750);

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

//Combat Animation Functions
void Animation::animateSlash(Assets& assets)
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
		this->combatAnimationFrame = -1;
		break;
	}
}

void Animation::animateGuard(Assets& assets)
{
	//Set Animation Position
	switch (this->combatAnimationLocation) {
	case -1:
		guardSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		break;
	case 0:
		//Hostile Sprite Location
		guardSprite.setPosition(sf::Vector2f(1650.0f, 300.0f));
		break;
	case 1:
		//Player Sprite Location
		guardSprite.setPosition(sf::Vector2f(50.0f, 100.0f));
		break;
	case 2:
		//Zin Sprite Location
		guardSprite.setPosition(sf::Vector2f(50.0f, 300.0f));
		break;
	case 3:
		//Thom Sprite Location
		guardSprite.setPosition(sf::Vector2f(50.0f, 500.0f));
		break;
	}

	//Animate Hit Animation
	this->animateCombatTimer();
	switch (this->combatAnimationFrame) {
	case -1:
		guardSprite.setTexture(guard1);
		break;
	case 0:
		guardSprite.setTexture(guard2);
		break;
	case 1:
		guardSprite.setTexture(guard3);
		break;
	case 2:
		guardSprite.setTexture(guard4);
		break;
	case 3:
		guardSprite.setTexture(guard5);
		break;
	case 4:
		guardSprite.setTexture(hitBlank);
		guardSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		this->animEnd = true;
		this->combatAnimationFrame = -1;
		break;
	}
}

void Animation::animateGuardBrk(Assets& assets)
{
	//Set Animation Position
	switch (this->combatAnimationLocation) {
	case -1:
		guardBrkSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		break;
	case 0:
		//Hostile Sprite Location
		guardBrkSprite.setPosition(sf::Vector2f(1650.0f, 300.0f));
		break;
	case 1:
		//Player Sprite Location
		guardBrkSprite.setPosition(sf::Vector2f(50.0f, 100.0f));
		break;
	case 2:
		//Zin Sprite Location
		guardBrkSprite.setPosition(sf::Vector2f(50.0f, 300.0f));
		break;
	case 3:
		//Thom Sprite Location
		guardBrkSprite.setPosition(sf::Vector2f(50.0f, 500.0f));
		break;
	}

	//Animate Hit Animation
	this->animateCombatTimer();
	switch (this->combatAnimationFrame) {
	case -1:
		guardBrkSprite.setTexture(guardBrk1);
		break;
	case 0:
		guardBrkSprite.setTexture(guardBrk2);
		break;
	case 1:
		guardBrkSprite.setTexture(guardBrk3);
		break;
	case 2:
		guardBrkSprite.setTexture(guardBrk4);
		break;
	case 3:
		guardBrkSprite.setTexture(guardBrk5);
		break;
	case 4:
		guardBrkSprite.setTexture(hitBlank);
		guardBrkSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		this->animEnd = true;
		this->combatAnimationFrame = -1;
		break;
	}
}

void Animation::animateSmite(Assets& assets)
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
		hitSprite.setTexture(hitBlank);
		break;
	case 1:
		hitSprite.setTexture(hit1);
		break;
	case 2:
		hitSprite.setTexture(hit1);
		break;
	case 3:
		hitSprite.setTexture(hitBlank);
		break;
	case 4:
		hitSprite.setTexture(hitBlank);
		hitSprite.setPosition(sf::Vector2f(10000.0f, 10000.0f));
		this->animEnd = true;
		break;
	}
}

void Animation::animateMenu(Assets& assets)
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

//Draw Animation Functions
void Animation::drawAnimations(Assets& assets)
{
	if (assets.getBonfireAssets()) {
		this->animateAnvil(assets);
		this->animateHeal(assets);
	}
	else if (!assets.getBonfireAssets()) {
		anvilSprite.setPosition(10000, 10000);
		healSprite.setPosition(10000, 10000);
	}
}