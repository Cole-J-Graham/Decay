#pragma once
#include<unordered_map>
#include<stack>
#include <SFML/Graphics.hpp>
class InteractionManager
{
public:
	//Constructors and Deconstructors
	InteractionManager();
	~InteractionManager();

	//Core Functions
	void update();
	void render(sf::RenderTarget* target);

	//Maanager Functions
	void createInstance(std::string id);

private:

	class Interaction {
	public:
		//Constructions and Deconstructors
		Interaction(std::string p) : dialogueFilePath(p) {

		}

		~Interaction() {

		}

		//Core Functions

		//File Functions

	private:
		std::string dialogueFilePath;
		std::stack<std::string> dialogue;

	};

	std::unordered_map<std::string, std::unique_ptr<Interaction>> stats;

};

