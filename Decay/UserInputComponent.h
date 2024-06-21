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
	void updateRects(sf::Vector2f mousePos);
	void renderRects(sf::RenderTarget* target);

	//Getters
	const bool rightArrowClicked()& { return this->right_active; };
	const bool leftArrowClicked()& { return this->left_active; };
	const bool quitButtonClicked()& { return this->quit_active; };

	const bool topDialogueClicked()& { return this->top_dialogue_active; };
	const bool bottomDialogueClicked()& { return this->bottom_dialogue_active; };
	const bool mainDialogueClicked()& { return this->main_dialogue_active; };

	//Modifiers
	void setMainDialogueText(std::string& text) { this->buttons["DIALOGUEBOXCENTER"]->setText(text); };
	void setDialogueOptions(std::string& top, std::string& bottom);
	void showDialogueOptions();
	void showMainDialogue() { this->buttons["DIALOGUEBOXCENTER"]->show(); };

	void hideDialogueOptions();
	void hideMainDialogue() { this->buttons["DIALOGUEBOXCENTER"]->hide(); };
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

	bool top_dialogue_active;
	bool bottom_dialogue_active;
	bool main_dialogue_active;

};

