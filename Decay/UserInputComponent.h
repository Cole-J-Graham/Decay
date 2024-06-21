#pragma once
#include"Button.h"
#include"Rectangle.h"
#include"Text.h"
class UserInputComponent
{
public:
	
	//Constructors and Deconstructors
	UserInputComponent();
	~UserInputComponent();

	//Core Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Button Functions
	void initButtons();
	void updateButtons(sf::Vector2f mousePos);
	void renderButtons(sf::RenderTarget* target);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	//Getters
	const bool rightArrowClicked()& { return this->right_active; };
	const bool leftArrowClicked()& { return this->left_active; };
	const bool quitButtonClicked()& { return this->quit_active; };

	const bool topDialogueClicked()& { return this->top_dialogue_active; };
	const bool bottomDialogueClicked()& { return this->bottom_dialogue_active; };

	const bool getProcessingDialogue()& { return this->procressing_dialogue; };

	//Modifiers
	void setProcessingDialogueTrue() { this->procressing_dialogue = true; };
	void setProcessingDialogueFalse() { this->procressing_dialogue = false; };
	void setDialogueOptions(std::string& top, std::string& bottom);
	void showDialogueOptions();
	void hideDialogueOptions();
	void showMoveArrows();
	void hideMoveArrows();

private:
	//Assets
	std::map<std::string, Rectangle*> rectangles;
	std::map<std::string, Button*> buttons;
	sf::Font font;

	bool right_active;
	bool left_active;
	bool quit_active;

	bool procressing_dialogue;
	bool top_dialogue_active;
	bool bottom_dialogue_active;

};

