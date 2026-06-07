#include "Game.h"

#include "EnemyDatabase.h"
#include "EnemyMoveDatabase.h"
#include "CharacterMoveDatabase.h"
#include "EmotionDatabase.h"
#include "SettingsManager.h"
#include "Inventory.h"
#include "GameTriggers.h"
#include "MusicManager.h"

//Constructor and Destructors
Game::Game()
{
	GameTriggers::registerAll();
	AssetDatabase::getInstance().loadFromFile("Assets/Data/assets.db");
	SfxManager::getInstance().loadFromFile("Assets/Data/sfx.db");
	Inventory::getInstance().loadItemDefinitionsFromFile("Assets/Data/inventory.db");

	CharacterMoveDatabase::getInstance().loadFromFile("Assets/Data/character_moves.db");
	EnemyMoveDatabase::getInstance().loadFromFile("Assets/Data/enemy_moves.db");
	EnemyDatabase::getInstance().loadFromFile("Assets/Data/enemies.db");

	MusicManager::getInstance().loadFromFile("Assets/Data/songs.db");
	SettingsManager::getInstance().loadFromFile("Assets/Data/settings.db");

	this->initWindow();
	this->initStates();  // InitializeCharacters runs inside here

	// Must come after initStates so CharacterManager already has all characters registered
	EmotionDatabase::getInstance().loadFromFile("Assets/Data/emotions.db");
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}

//Initialization (Private Functions)
void Game::initWindow()
{
	std::string title = "None";
	sf::VideoMode window_bounds(1920, 1080);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->states.push(new MainMenuState(window, &states));
}

//Update
void Game::update()
{
	SfxManager::getInstance().update();

	this->updateSFMLEvents();

	if (!this->states.empty()) {
		this->states.top()->update();

		while (!this->states.empty() && this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else {
		this->endApplication();
		this->window->close();
	}
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed) {
			this->window->close();
		}
	}
}

//Render
void Game::render()
{
	this->window->clear();

	if (!this->states.empty()) {
		this->states.top()->render(this->window);
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}