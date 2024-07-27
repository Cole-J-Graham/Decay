#pragma once
#include"Rectangle.h"
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

	//Buttons Functions
	void updateButtons(const sf::Vector2f mousePos);

	//Maanager Functions
	void createInstance(const std::string& id);

private:

	class Interaction {
	public:
		//Constructions and Deconstructors
		Interaction() {
			this->buttons[this->id] = new Button(1370, 775, 200, 25, 0.5f, this->id,
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			this->rect = std::make_unique<Rectangle>(1400, 50, 400, 400, sf::Color::Transparent,
				sf::Color::White, 1.f, false);
			this->hidden = true;
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
				pair.second->setText(this->buttonName);
				this->buttonName = "INTERACT WITH " + this->id;
				std::cout << buttonName << "\n";
			}
		}

		void render(sf::RenderTarget* target) {
			for (auto& pair : this->buttons) {
				pair.second->render(target);
				this->rect->render(target);
			}
		}

		//File Functions

		//Getters
		std::string& getButtonId() { return this->buttonName; }
		std::map<std::string, Button*>& getButtons() { return this->buttons; };

		//Setters
		void setId(const std::string& id) { this->id = id; }

	private:
		
		bool hidden;
		std::unique_ptr<Rectangle> rect;
		std::string buttonName;
		std::string id;
		std::string dialogueFilePath;
		std::stack<std::string> dialogue;
		std::map<std::string, Button*> buttons;

	};

	bool hidden;

	std::map<std::string, Button*> buttons;
	std::unordered_map<std::string, std::unique_ptr<Interaction>> interactions;

};

