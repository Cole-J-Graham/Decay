#include "Event.h"

//Constructors & Destructors
Event::Event()
{
    //Control Flow Bools
    this->reInitialize = true;
    this->sfxUsed = false;
    this->itemGained = false;

    this->encounterInit = true;
    this->encounterInitTwo = true;

    //Event Availability Bools
    this->siwardEncounteredForest = false;
    this->spadeEncounteredForest = false;

    this->treeEncountered = false;
    this->obeliskEncountered = false;

    this->nunEncountered = false;

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

void Event::hideOpenAssets(Assets& assets)
{
    assets.setInitMapFalse(); //Hide the map if its open
    assets.setInitStatsFalse(); //Hide stats if open
    assets.setInitInventoryFalse(); //Hide inventory if open
    assets.getEventAssets() = true; //Hide map, inv, stat, forward && back buttons
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
                player.printInventory(assets);
                break;
            case 1:
                player.getBasicSword() = "Keen Longsword";
                player.printInventory(assets);
                break;
            case 2:
                player.getBasicSword() = "Honed Longsword";
                player.printInventory(assets);
                break;
            case 3:
                player.getBasicSword() = "Godsplitting Longsword";
                player.printInventory(assets);
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
    if (assets.rectMap.getGlobalBounds().contains(mousePosF) && assets.getInitMap()) {
        //Catch the input if you click on the map instead of Zin's sprite
    }
    else if (assets.spriteElements[3].getGlobalBounds().contains(mousePosF)) {
        //Zin Conversations at Bonfire
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

//Forest Entrance Events
void Event::forestSiwardEncounter(Assets& assets)
{
    if (!this->siwardEncounteredForest) {
        this->reInit(assets);
        switch (this->dialogue) {
        case 0:
            assets.getSpriteViewerCounter() = 0; //Make entity viewer visible
            assets.getEntityViewerCounter() = 0; //Make siward entity visible
            assets.getSiwardLoadOnce() = false; //Allow to be used again
            assets.getSiwardCounter() = 0; //Make Siwards Sprite Appear
            this->hideOpenAssets(assets);
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
            this->siwardEncounteredForest = true;
            break;
        }
    }
}

//Forest Depths Events
void Event::forestDepthsSpadeEncounter(Assets& assets)
{
    if (!this->spadeEncounteredForest) {
        this->reInit(assets);
        switch (this->dialogue) {
        case 0:
            assets.getSpriteViewerCounter() = 0; //Make entity viewer visible
            assets.getEntityViewerCounter() = 3; //Make spade entity visible
            assets.getSpadeLoadOnce() = false; //Allow to be used again
            assets.getSpadeCounter() = 0; //Make Spades Sprite Appear
            this->hideOpenAssets(assets);
            assets.text.setString("Suddenly, a strange girl ambushes you. Your keen senses were unable to detect her.");
            break;
        case 1:
            assets.text.setString("Hahaha! You looked almost scared for a minute there! It's just me! You're fine.");
            break;
        case 2:
            assets.getShowAnsBoxesCounter() = 0;
            assets.answerBoxText[0].setString("1. 'Lady, I have never met you in my entire life.'");
            assets.answerBoxText[1].setString("2. 'Who the fuck are you?'");
            break;
        case 3:
            assets.getShowAnsBoxesCounter() = -1;
            assets.text.setString("'Aweeee, lost our memory have we? It's me! Spade! The court jester...! No...? How could you NOT remember ME?! I'm fantastic!'");
            break;
        case 4:
            assets.getShowAnsBoxesCounter() = 0;
            assets.answerBoxText[0].setString("1. 'Apologies, but I definitely don't remember you.'");
            assets.answerBoxText[1].setString("2. 'I don't see the appeal.'");
            break;
        case 5:
            assets.getShowAnsBoxesCounter() = -1;
            switch (assets.getChoiceCounter()) {
            case 0:
                assets.text.setString("'Hmmmm, well I'll make you remember REAL quick!'");
                break;
            case 1:
                assets.getSpadeCounter() = 1;
                assets.text.setString("'Oh yeah? Well maybe I SHOULD SHOW YOU! Urghhhh!' *She is quite visibly upset, holding herself back from yelling too loudly in the woods...*\n\n'I'll tell you what, I'll MAKE you remember me, knight!'");
                break;
            }
            break;
        case 6:
            assets.getShowAnsBoxesCounter() = 0;
            assets.answerBoxText[0].setString("1. 'Make me? What're you gonna do exactly?'");
            assets.answerBoxText[1].setString("2. 'So you're trying to say that we met in the castle?'");
            break;
        case 7:
            assets.getShowAnsBoxesCounter() = -1;
            switch (assets.getChoiceCounter()) {
            case 0:
                assets.text.setString("'I dunno, knock you over the head? SOMETHING, cause clearly your head aint working if you don't remember meeting me.'");
                break;
            case 1:
                assets.getSpadeCounter() = 1;
                assets.text.setString("'Yes, we obviously did! How can you not remember me? You were smart back at the castle, but it seems like you've turned dense!'");
                break;
            }
            break;
        case 8:
            assets.text.setString("*You try your best to remember her. You think back to every face you can remember from the castle but you just can't quite recognize her no matter how hard you try.*\n\n'I genuinely just don't remember you.'");
            break;
        case 9:
            assets.text.setString("'Oh, I know!' *She yells in excitment* 'I know a witch that can bring peoples memory back!'");
            break;
        case 10:
            assets.getShowAnsBoxesCounter() = 0;
            assets.answerBoxText[0].setString("1. 'I don't want anything to do with a witch.'");
            assets.answerBoxText[1].setString("2. 'I don't want anything to do with you.'");
            break;
        case 11:
            assets.getShowAnsBoxesCounter() = -1;
            assets.getSpadeCounter() = 0;
            assets.text.setString("'Awwwe, come on! I know you won't regret it! I'll go talk to the witch, see you soon!'\n\n*She runs off deeper into the woods, skipping with excitment. You hope to God you never see her again.*");
            break;
        case 12:
            assets.getSpadeCounter() = -1;
            assets.text.setString("");
            assets.getEventAssets() = false;
            //Make spades entity invisible
            assets.getEntityViewerCounter() = -1;
            this->spadeEncounteredForest = true;
            break;
        }
    }
}

void Event::treeEncounter(Assets& assets, Player& player)
{
    if (!this->treeEncountered) {
        this->reInit(assets);
        switch (this->dialogue) {
        case 0:
            assets.getSpriteViewerCounter() = 0; //Make entity viewer visible
            assets.getEntityViewerCounter() = 2; //Make tree entity visible
            this->hideOpenAssets(assets);
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
            assets.text.setString("As you turn, you lock eyes with Zin. You notice her hands are enclosed and shes slowly moving her palms against one another as she stares at the tree. Suddenly, a horrifying crack deafening you.\n\nYou realize that she had just used smite, obliterating the tree and splitting it in half with the bolt of lightning...");
            break;
        case 5:
            this->sfxUsed = false;
            assets.getZinCounter() = 1;//Switch Zins emotions
            assets.text.setString("'Got him! Heh!'");
            break;
        case 6:
            assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            assets.answerBoxText[0].setString("1. 'What in the hell was that thing?'");
            assets.answerBoxText[1].setString("2. 'Are you TRYING to start a forest fire?!'");
            break;
        case 7:
            assets.getShowAnsBoxesCounter() = -1;
            switch (assets.getChoiceCounter()) {
            case 0:
                assets.text.setString("'No idea! But it's gone now!'");
                break;
            case 1:
                assets.text.setString("'Maybe...'");
                break;
            }
            break;
        case 8:
            assets.text.setString("You look at the floor of the burning tree and notice something. One of the eyes that was forming on it seems to have turned to a hard rock after being struck.\n\n+1 Smithing Stone");
            if (!this->itemGained) {
                player.getSmithingStones()++;
                this->itemGained = true;
            }
            break;
        case 9:
            this->itemGained = false;
            assets.getZinCounter() = -1;
            assets.text.setString("");
            assets.getEventAssets() = false;
            assets.getEntityViewerCounter() = -1;
            this->treeEncountered = true;
            break;
        }
    }
}

//Forest Abyssal Events
void Event::obeliskEncounter(Assets& assets, Player& player)
{
    if (!this->obeliskEncountered) {
        this->reInit(assets);
        switch (this->dialogue) {
        case 0:
            assets.getSpriteViewerCounter() = 0; //Make entity viewer visible
            assets.getEntityViewerCounter() = 6; //Make obelisk entity visible
            this->hideOpenAssets(assets);
            assets.text.setString("You feel a strange presence in the area... You notice something strange ahead. A glowing obelisk, seemingly calling to you.");
            break;
        case 1:
            assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            assets.answerBoxText[0].setString("1. *Move towards the obelisk*");
            assets.answerBoxText[1].setString("2. *Back away from the obelisk*");
            break;
        case 2:
            assets.getShowAnsBoxesCounter() = -1;
            switch (assets.getChoiceCounter()) {
            case 0:
                assets.text.setString("*You move towards the obelisk, but as you do you notice that it seems like the distance between you and the object is not changing. Instead, you're somehow staying the same distance from it despite moving towards it. You feel a horrible pain in your gut as you keep walking...*");
                break;
            case 1:
                assets.text.setString("*You move away from the obelisk, but as you do you notice that it seems like the distance between you and the object is not changing. Instead, you're somehow staying the same distance from it despite moving away from it. You feel a horrible pain in your gut as you keep backing up...*");
                break;
            }
            break;
        case 3:
            assets.text.setString("*Suddenly, you hear a voice inside of your head begin to speak to you. It sounds inhuman, almost otherwordly.*\n\n'What is it you wish for? Riches, or power?");
            break;
        case 4:
            assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            assets.answerBoxText[0].setString("1. *Play along with it*");
            assets.answerBoxText[1].setString("2. 'What the hell are you?'");
            break;
        case 5:
            assets.getShowAnsBoxesCounter() = -1;
            switch (assets.getChoiceCounter()) {
            case 0:
                assets.text.setString("*You decide to play along with it, thinking about its question for a moment before answering... Zin stares at the interaction between you and the object with clear fear*");
                break;
            case 1:
                assets.text.setString("*It only repeats its question, ignoring yours. You realize that at this rate there's no escaping it. Best bet is to play along for now...*");
                break;
            }
            break;
        case 6:
            assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            assets.answerBoxText[0].setString("1. 'Riches'");
            assets.answerBoxText[1].setString("2. 'Power'");
            break;
        case 7:
            assets.getShowAnsBoxesCounter() = -1;
            switch (assets.getChoiceCounter()) {
            case 0:
                assets.text.setString("*The obelisk slowly destroys itself and crumbles to the floor, no longer trapping you with its presence. You notice that you have significantly more gold in your pouch suddenly. Looks like it wasn't a trap after all...*\n\n+50 Gold");
                if (!this->itemGained) {
                    player.getGold() += 50;
                    this->itemGained = true;
                }
                break;
            case 1:
                assets.text.setString("*The obelisk slowly destroys itself and crumbles to the floor, no longer trapping you with its presence. You feel as though for some reason you have a greater knowledge than you did prior. Perhaps it gave you some kind of power after all.*\n\n+500 Exp");
                if (!this->itemGained) {
                    player.getExp() += 500;
                    this->itemGained = true;
                }
                break;
            }
            break;
        case 8:
            assets.text.setString("");
            assets.getEventAssets() = false;
            assets.getEntityViewerCounter() = -1;
            this->itemGained = false;
            this->obeliskEncountered = true;
            break;
        }
    }
}

void Event::lostNunEncounter(Assets& assets)
{
    if (!this->nunEncountered) {
        this->reInit(assets);
        switch (this->dialogue) {
        case 0:
            assets.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
            assets.getZinCounter() = 0; //Set concerned frame
            assets.getSpriteViewerCounter() = 0; //Make entity viewer visible
            assets.getEntityViewerCounter() = 7; //Make nun entity visible
            this->hideOpenAssets(assets);
            assets.text.setString("*You notice a woman standing alone in a clearing up ahead in the woods. She seems distraught until she notices you and Zin walking. She runs up to you both and goes to try and hug Zin, however Zin backs away...*\n\n'I have been looking for you everywhere, sweetie! Where did you run off to?' *The woman exclaims*");
            break;
        case 1:
            assets.getZinCounter() = 2;
            assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            assets.answerBoxText[0].setString("1. 'Who are you?'");
            assets.answerBoxText[1].setString("2. *Turn to Zin* 'Do you know her?'");
            break;
        case 2:
            assets.getShowAnsBoxesCounter() = -1;
            switch (assets.getChoiceCounter()) {
            case 0:
                assets.text.setString("*The woman glares at you before ignoring your words and continuing to talk to Zin...*\n\n'Let's go home and get away from this horrible place, sound good hun?' *Zin looks at the lady with confusion* 'I have no idea who you are, lady...' *Zin replies to her*");
                break;
            case 1:
                assets.text.setString("*Zin shakes her head, looking at the woman with confusion.* 'I have no idea who you are, lady.' *Zin replies to the woman*\n\n*The woman steps closer, visibly angrier from the reply. You notice what looks to be melting decay rotting off of her arm under her cloak. This woman has been rotting from decay for quite some time...*\n\n*You recall back to your time aiding the citizens in the castle. Some rotting with decay would have adverse effects such as this with the decay.\n\nRather than losing their mind and strength, only their mind would rot as their body would grow stronger.*");
                break;
            }
            break;
        case 3:
            assets.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            assets.answerBoxText[0].setString("1. *Try to turn and escape with Zin*");
            assets.answerBoxText[1].setString("2. 'Get the fuck away from us.'");
            break;
        case 4:
            assets.getShowAnsBoxesCounter() = -1;
            switch (assets.getChoiceCounter()) {
            case 0:
                assets.text.setString("*You grab Zin and begin to run, not looking back. You hear a horrific screaming behind you as the footsteps grow closer at an obsurd pace.*\n\n*Suddenly, she launches directly in front of both of your paths despite your best efforts at running.*\n\n*You plant your feet into the ground and draw your sword as Zin readies her spells. It's do or die.*");
                break;
            case 1:
                assets.text.setString("*The woman slowly turns her head away from Zin, not bothering to move her body to face you. Instead, you hear her neck audibly snapping as she makes eye contact with you.* 'I'm going to string you up like dried meat.' *The woman states as she moves towards you.*\n\n*You plant both of your feet into the ground and draw your sword, noticing Zin also readying her spells behind her. It's do or die.");
                break;
            }
            break;
        case 5:
            assets.getZinCounter() = -1;
            assets.text.setString("");
            assets.getEventAssets() = false;
            this->nunEncountered = true;
            break;
        }
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
