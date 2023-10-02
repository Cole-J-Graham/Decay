#include "Event.h"

//Constructors & Destructors
Event::Event()
{
    //Control Flow Bools
    this->reInitialize = true;
    this->sfxUsed = false;

    this->encounterInit = true;
    this->encounterInitTwo = true;

    //Counters
    this->zinTalkCounter = -1;

    //Dialogue Counter
    this->dialogue = 0;
}

Event::~Event()
{

}

//Core Functions
void Event::reInit(Assets& assets)
{
    if (this->reInitialize) {
        this->dialogue = 0;
        this->reInitialize = false;
    }
}

//Bonfire Events
void Event::healCharactersText(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (assets.bonfireHealDetectionRect.getGlobalBounds().contains(mousePosF)) {
        assets.bonfireHealDetectionText.setString("Rest to restore health...?");
    }
    else {
        assets.bonfireHealDetectionText.setString("");
    }
}

void Event::healCharacters(sf::RenderWindow& window, Assets& assets, Combat& combat)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (assets.bonfireHealDetectionRect.getGlobalBounds().contains(mousePosF)) {
        combat.getPlayerHp() = combat.getPlayerHpMax();
        combat.getZinHp() = combat.getZinHpMax();
        assets.text.setString("All party members Hp restored...");
        assets.spriteText[1].setString("Zin            " + std::to_string(combat.getZinHp()) + "/" + std::to_string(combat.getZinHpMax()));
    }
}

void Event::smithingText(sf::RenderWindow& window, Assets& assets)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (assets.bonfireSmithDetectionRect.getGlobalBounds().contains(mousePosF)) {
        assets.bonfireSmithDetectionText.setString("Smith Weapons...?");
    }
    else {
        assets.bonfireSmithDetectionText.setString("");
    }
}

void Event::smithingSharpenBlade(sf::RenderWindow& window, Assets& assets, Player& player)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (assets.bonfireSmithDetectionRect.getGlobalBounds().contains(mousePosF)) {
        if (player.getSmithingStones() >= 1) {
            player.setSmithingStonesDec();
            assets.text.setString("You use the smithing stone to improve your sword further...");
            player.setSwordPowerInc();
            switch (player.getSwordPower()) {
            case 0:
                player.getBasicSword() = "Basic Longsword";
                break;
            case 1:
                player.getBasicSword() = "Keen Longsword";
                break;
            case 2:
                player.getBasicSword() = "Honed Longsword";
                break;
            case 3:
                player.getBasicSword() = "Godsplitting Longsword";
                break;
            }
        }
        else if (player.getSmithingStones() <= 0) {
            assets.text.setString("You lack the required smithing stones to improve your sword...");
        }
    }
}

//Bonfire Text Events
void Event::zinEvents(sf::RenderWindow& window, Assets& assets, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //Zin Conversations at Bonfire
    if (assets.spriteElements[3].getGlobalBounds().contains(mousePosF)) {
        this->zinTalkCounter = 0;
    }

    switch (this->zinTalkCounter) {
    case -1:
        animate.getZinTalkNot() = true;
        break;
    case 0:
        this->zinInitialTalk(assets, animate);
        break;
    case 1:
        break;
    }
}

//Zin Events
void Event::zinInitialTalk(Assets& assets, Animation& animate)
{
    switch (this->dialogue) {
    case 0:
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'So, what was it you wanted to talk about?'");
        assets.answerBoxText[1].setString("2. 'What's your name, kid?'");
        animate.getZinTalkNot() = false;
        break;
    case 1:
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("'Well... Uhhh... Are you a monster like those others?'\n\n*You look down at your skin, slowly rotting.*");
            break;
        case 1:
            assets.text.setString("'I'm Zin... When did you get the decay?'\n\n*You look down at your skin, slowly rotting.*");
            break;
        }
        break;
    case 2:
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'The decay has been rotting away at me for the past year. I caught it during my time as a knight at the castle...'");
        assets.answerBoxText[1].setString("2. 'Look, I'm gonna be honest with you, I probably don't have a lot of time left, kid...'");
        break;
    case 3:
        assets.getShowAnsBoxesCounter() = -1;
        assets.text.setString("*Without another word, Zin reaches her hand out and places it on your shoulder, a bright light coming from her hand.\n\nIt burns quite badly, however you notice the decay slowly receding from your body...*");
        break;
    case 4:
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'You have the power to cleanse the decay?!'");
        assets.answerBoxText[1].setString("2. 'You CAN help the decay?!'");
        break;
    case 5:
        assets.getShowAnsBoxesCounter() = -1;
        assets.text.setString("'Sorry for lying to you earlier. My dad told me to never tell someone I can cleanse it unless I trust them.'");
        break;
    case 6:
        assets.text.setString("Your mind comes to a dire realization. Despite your armor and sword being lost, you must still carry out your duties as a knight.\n\nShe must be protected at all costs as she is one of the last bastions of preserving life in this horrible world...");
        break;
    case 7:
        assets.text.setString("");
        this->reInitialize = true;
        break;
    }
}

//Forest Events
void Event::forestSiwardEncounter(Assets& assets)
{
    this->reInit(assets);
    switch (this->dialogue) {
    case 0:
        assets.getSpriteViewerCounter() = 0; //Make entity viewer visible
        assets.getEntityViewerCounter() = 0; //Make siward entity visible
        assets.setInitMapFalse(); //Hide the map if its open
        assets.setInitStatsFalse(); //Hide stats if open
        assets.setInitInventoryFalse(); //Hide inventory if open
        assets.getSiwardLoadOnce() = false; //Allow to be used again
        assets.getSiwardCounter() = 0; //Make Siwards Sprite Appear
        assets.getEventAssets() = true; //Hide map, inv, stat, forward && back buttons
        assets.text.setString("A knight suddenly appears from around a tree, practically ambushing your view. Though he seems to get startled from your presence as well...");
        break;
    case 1:
        assets.text.setString("'Pardon my intrusion! I did not believe I would be finding people this deep in the woods! You both must be strong!\n\n'My name is Siward, Siward Howler. A pleasure to meet you both. What brings you two out here so late in the night might I ask?'");
        break;
    case 2:
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'Why are you so acting so friendly and joyful? We're surrounded by hell out here.'");
        assets.answerBoxText[1].setString("2. 'I'm trying to get this kid far away from here. Somewhere safer. Well, if that still exists...'");
        break;
    case 3:
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("'You're not wrong good sir, the forefront and battles ahead seem grueling, however laying my sword and attitude down may serve nothing more than to swiften thy death!'\n\n'I hath not been taught to kneel so easily at the hands of cruelety and I see that in you as well, my friend. Though your mind may currently be weary, your stoicism will bring you unto the end of your journey unscathed!'");
            break;
        case 1:
            assets.text.setString("'Ah, I see, quite the noble task! Most that claim such righteous duties lie and deceit, claiming to be doing the right thing when only sin truly captures their mind...'\n\n'But not you, friend! I cant tell, the look in your eye, you truly are a good man. I have a keen sense for these things! Ha, I know it be true!'");
            break;
        }
        break;
    case 4:
        assets.getShowAnsBoxesCounter() = 0;
        assets.answerBoxText[0].setString("1. 'Thanks, but we should be taking our leave now...'");
        assets.answerBoxText[1].setString("2. 'Would you care to join us, Siward?'");
        break;
    case 5:
        assets.getShowAnsBoxesCounter() = -1;
        switch (assets.getChoiceCounter()) {
        case 0:
            assets.text.setString("'Ah, yes, lingering for too long in the same place in these woods would be a poor idea. Perhaps take a word of advice before you travel onwards...' *He looks down to the rotting decay on your flesh.*\n\n'It looks freshly tended to, which I presume was handled by the little one?' *He points to Zin as he speaks.*\n\n'I too am inflincted with such a curse, though I do not ask for treatment. I ask that you merely keep the strain on the young one to a minimum. This curse touches no hand without cost...'");
            break;
        case 1:
            assets.text.setString("'I would love to, however...' *The knight lifts his right arm, exposing a chunk of his metal armor that has been destroyed, revealing a rotting black wound.*\n\n'The time I have left is limited until I undoubtedly become another one of those wretched beasts that roam and slaughter others. Before this fate, I shall slay as many beasts in this forest as I can...'\n\n'Before I head off, I merely leave you with a piece of advice...' *He points to the decay barely visible on your arm.*\n\n'You too are strained by this curse, though it seems you have recently been treated, I presume by the little one... Keep that strain to a minimum on that girl, for no hand that touches the curse does so without cost...'");
            break;
        }
        break;
    case 6:
        assets.getShowAnsBoxesCounter() = 0;
        assets.answerBoxText[0].setString("1. 'What do you mean? What 'cost' could come from healing the decay?'");
        assets.answerBoxText[1].setString("2. 'What exactly are you trying to say?'");
        break;
    case 7:
        assets.getShowAnsBoxesCounter() = -1;
        assets.text.setString("You will come to understand, but neither choice is correct in this world of chaos...' *He stares at the ground for a moment as silence consumes the air. Suddenly, he picks his sword up and begins walking deeper into the woods.*\n\n'I'm off you two! I know you'll both do fine, as will I! If fate deems it so, perhaps we shall meet again!'\n\n*Before you're able to call him back, he disappears into the forest entirely...*");
        assets.getSiwardCounter() = -1;
        break;
    case 8:
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.setZinCounterZero(); //Set correct frame for zins sprite to appear
        assets.text.setString("Well... That dude was strange. I'm sure you want to talk about what he said but... Let's wait till we get back to the bonfire.");
        break;
    case 9:
        assets.getZinCounter() = -1;
        assets.text.setString("");
        assets.getEventAssets() = false;
        //Make siwards entity invisible
        assets.getEntityViewerCounter() = -1;
        break;
    }
}

void Event::treeEncounter(Assets& assets)
{
    this->reInit(assets);
    switch (this->dialogue) {
    case 0:
        assets.getSpriteViewerCounter() = 0; //Make entity viewer visible
        assets.getEntityViewerCounter() = 2; //Make siward entity visible
        assets.setInitMapFalse(); //Hide the map if its open
        assets.setInitStatsFalse(); //Hide stats if open
        assets.setInitInventoryFalse(); //Hide inventory if open
        assets.getEventAssets() = true; //Hide map, inv, stat, forward && back buttons
        assets.text.setString("You hear a voice nearby, stopping you in your tracks. You were certain no one was nearby but you most definitely hear somebody.\nYou turn to your left, then your right. You lock eyes with it. A tree... Speaking to you...?\n\nIt keeps repeating some odd chanting sound to you but you can't quite make out what it's saying...");
        break;
    case 1:
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. 'Uh... Hello?'");
        assets.answerBoxText[1].setString("2. 'What are you...?'");
        break;
    case 2:
        assets.getShowAnsBoxesCounter() = -1;
        assets.text.setString("Eyes slowly embed into the tree, staring at you as you stare back horrified. The branches of the tree slowly move towards you as you stand there, staring, unsure of what to do...");
        break;
    case 3:
        assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        assets.answerBoxText[0].setString("1. *Attempt to escape*");
        assets.answerBoxText[1].setString("2. *Try to warn Zin*");
        break;
    case 4:
        assets.getShowAnsBoxesCounter() = -1;
        assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        assets.getZinCounter() = 0; //Set correct frame for zins sprite to appear
        if (!this->sfxUsed) {
            assets.soundSmite.play(); //Play smite sfx
            this->sfxUsed = true;
        }
        assets.text.setString("As you turn, you lock eyes with Zin. Her hands both enclosed together as she slowly turned them, a horrifying crack deafening you.\n\nYou realize that she had just used smite, obliterating the tree and splitting it in half with the bolt of lightning...");
        break;
    case 5:
        this->sfxUsed = false;
        assets.getZinCounter() = 1;//Switch Zins emotions
        assets.text.setString("'Got him! Heh!'");
        break;
    }
}

//Castle Events
void Event::spadeEncounter(Assets& assets)
{
    //Initiate Dialogue
    switch (assets.getDialogueCounter()) {
    case 0:
        if (this->encounterInit == true) {
            assets.setSpriteInitTrue(); //Initialize Sprite Border
            assets.setSpadeCounterZero(); //Pick which Spade Sprite to use via switch statement
            assets.text.setString("Hey, what are you doing here...?"); //Set text for what's happening
            this->encounterInit = false; //Ensure this only runs once...
        }
        break;
    case 1:
        if (this->encounterInitTwo == true) {
            assets.setSpadeCounterOne();
            assets.text.setString("Get OUT!");
            assets.soundAngry.play();
            this->encounterInitTwo = false;
        }
        break;
    case 2:
        std::cout << "Success";
        break;
    }
}
