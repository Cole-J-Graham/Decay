#pragma once
//States
#include"State.h"
//Componenets
#include"MapComponent.h"
//Managers
#include"CharacterManager.h"
//States
#include"CombatState.h"
#include"MusicPlayer.h"
class TravelState : public State
{
public:
	//Constructors and Destructors
	TravelState(sf::RenderWindow* window, std::stack<State*>* states);
	~TravelState();

	//Core Functions
	void update();
	void render(sf::RenderTarget* target = nullptr);

	//Travel Functions
	void updateEventsFromMovement();

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	void checkFPS(sf::Clock& clock, sf::Clock& fpsClock, int& frameCount) {
		// Measure the elapsed time since the last frame
		sf::Time elapsed = clock.restart();

		// Increment the frame count
		frameCount++;

		// Check if one second has passed
		if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
			// Calculate FPS
			float fps = frameCount / fpsClock.restart().asSeconds();
			std::cout << "FPS: " << fps << std::endl;
			frameCount = 0;
		}
	}
	sf::Clock clock;
	sf::Clock fpsClock;
	int frameCount = 0;

private:
	int combatChanceMin;
	int combatChanceMax;
	float combatOdds;

	std::unique_ptr<UserInputComponent> userInput;
	std::vector<sf::Texture> mapData;
	std::map<std::string, Rectangle*> rectangles;

	CombatState* combat;
	MapComponent* map;

	std::unique_ptr<MusicPlayer> music;
	
};