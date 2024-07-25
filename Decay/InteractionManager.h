#pragma once
#include"Button.h"
#include<unordered_map>
#include<stack>
class InteractionManager
{
public:
	//Constructors and Deconstructors
	InteractionManager();
	~InteractionManager();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);	

	//Maanager Functions
	void createInstance(std::string id);

private:

	class Interaction {
	public:
		//Constructions and Deconstructors
		Interaction() {
			this->buttons["INTERACT"] = new Button(1370, 775, 100, 25, 0.5f, this->id,
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
		};

		~Interaction() {
			auto ib = this->buttons.begin();
			for (ib = this->buttons.begin(); ib != this->buttons.end(); ++ib) {
				delete ib->second;
			}
		}

		//Core Functions
		void update(const sf::Vector2f mousePos) {
			for (auto& pair : this->buttons) {
				pair.second->update(mousePos);
			}
		}

		void render(sf::RenderTarget* target) {
			for (auto& pair : this->buttons) {
				pair.second->render(target);
			}
		}

		//File Functions

		//Getters
		std::string& getButtonId() { return this->buttonId; }
		std::map<std::string, Button*>& getButtons() { return this->buttons; };

		//Setters
		void setId(std::string& id) { this->id = id; }

	private:

		std::string buttonId;
		std::string id;
		std::string dialogueFilePath;
		std::stack<std::string> dialogue;
		std::map<std::string, Button*> buttons;

	};

	bool hidden;

	std::map<std::string, Button*> buttons;
	std::unordered_map<std::string, std::unique_ptr<Interaction>> stats;

};

