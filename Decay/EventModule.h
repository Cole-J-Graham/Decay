#pragma once
#include"UserInputComponent.h"
#include<fstream>
#include <sstream>
class EventModule
{
public:
	//Constructors and Destructors
	EventModule();
	~EventModule();

	//Core Functions
	void initEvent();
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	UserInputComponent* userInput;

private:
	class Event {
	public:
		//Constructors and Deconstructors
		Event() {

		}

		~Event() {

		}

		//Core Functions
		void loadEvent(std::string& input)
		{
			this->eventContainer.push_back(input);
		};

		std::vector<std::string>& getEventContainer() { return this->eventContainer; };

	private:
		std::vector<std::string> eventContainer;
	};
};

