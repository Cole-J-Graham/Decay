#include "Event.h"

//Constructors & Destructors
Event::Event()
{
    //Control Flow Bools
    this->reInitialize = true;
    this->sfxUsed = false;
    this->itemGained = false;

    //Event Availability Bools
    this->thomEncountered = false;
    this->siwardEncounteredForest = false;
    this->siwardEncounteredCastle = false;
    this->siwardEncounteredFinal = false;

    this->spadeEncounteredForest = false;
    this->spadeEncounteredCastle = false;

    this->treeEncountered = false;
    this->obeliskEncountered = false;

    this->nunEncountered = false;

    //Counters
    this->zinTalkCounter = -1;
    this->choiceCounter = -1;

    //Dialogue Counter
    this->dialogue = 0;
}

Event::~Event()
{

}

//Core Functions
void Event::reInit(Sprites& sprites)
{
    if (this->reInitialize) {
        this->dialogue = 0;
        this->reInitialize = false;
    }
}

void Event::hideOpenAssets(Sprites& sprites)
{
    sprites.setInitMapFalse(); //Hide the map if its open
    sprites.setInitStatsFalse(); //Hide stats if open
    sprites.setInitInventoryFalse(); //Hide inventory if open
    sprites.getEventAssets() = true; //Hide map, inv, stat, forward && back buttons
}

//Bonfire Events
void Event::healCharactersText(sf::RenderWindow& window, Sprites& sprites)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (sprites.bonfireHealDetectionRect.getGlobalBounds().contains(mousePosF)) {
        sprites.bonfireHealDetectionText.setString("Rest to restore health...?");
    }
    else {
        sprites.bonfireHealDetectionText.setString("");
    }
}

void Event::healCharacters(sf::RenderWindow& window, Sprites& sprites, Combat& combat)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (sprites.bonfireHealDetectionRect.getGlobalBounds().contains(mousePosF)) {
        combat.getPlayerHp() = combat.getPlayerHpMax();
        combat.getZinHp() = combat.getZinHpMax();
        if (sprites.getThomUnlocked()) {
            combat.getThomHp() = combat.getThomHpMax();
        }
        sprites.text.setString("All party members Hp restored...");
        sprites.spriteText[0].setString(sprites.getPlayerName() + "     " + std::to_string(combat.getPlayerHp()) + "/" + std::to_string(combat.getPlayerHpMax()));
        sprites.spriteText[1].setString("Zin            " + std::to_string(combat.getZinHp()) + "/" + std::to_string(combat.getZinHpMax()));
        sprites.spriteText[5].setString("Thom          " + std::to_string(combat.getThomHp()) + "/" + std::to_string(combat.getThomHpMax()));
    }
}

void Event::smithingText(sf::RenderWindow& window, Sprites& sprites)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //Show Hover Text
    if (sprites.bonfireSmithDetectionRect.getGlobalBounds().contains(mousePosF)) {
        sprites.bonfireSmithDetectionText.setString("Smith Weapons...?");
    }
    else {
        sprites.bonfireSmithDetectionText.setString("");
    }
}

void Event::smithingSharpenBlade(sf::RenderWindow& window, Sprites& sprites, Player& player)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (sprites.bonfireSmithDetectionRect.getGlobalBounds().contains(mousePosF)) {
        if (player.getSmithingStones() >= 1) {
            player.setSmithingStonesDec();
            sprites.text.setString("You use the smithing stone to improve your sword further...");
            player.setSwordPowerInc();
            switch (player.getSwordPower()) {
            case 0:
                player.getBasicSword() = "Basic Longsword";
                player.printInventory(sprites);
                break;
            case 1:
                player.getBasicSword() = "Keen Longsword";
                player.printInventory(sprites);
                break;
            case 2:
                player.getBasicSword() = "Honed Longsword";
                player.printInventory(sprites);
                break;
            case 3:
                player.getBasicSword() = "Godsplitting Longsword";
                player.printInventory(sprites);
                break;
            }
        }
        else if (player.getSmithingStones() <= 0) {
            sprites.text.setString("You lack the required smithing stones to improve your sword...");
        }
    }
}

//Bonfire Text Events
void Event::zinEvents(sf::RenderWindow& window, Sprites& sprites, Animation& animate)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (sprites.rectMap.getGlobalBounds().contains(mousePosF) && sprites.getInitMap()) {
        //Catch the input if you click on the map instead of Zin's sprite
    }
    else if (sprites.spriteElements[3].getGlobalBounds().contains(mousePosF)) {
        //Zin Conversations at Bonfire
        this->zinTalkCounter = 0;
    }

    switch (this->zinTalkCounter) {
    case -1:
        animate.getZinTalkNot() = true;
        break;
    case 0:
        this->zinInitialTalk(sprites, animate);
        break;
    case 1:
        break;
    }
}

//Zin Events
void Event::zinInitialTalk(Sprites& sprites, Animation& animate)
{
    switch (this->dialogue) {
    case 0:
        sprites.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
        sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'So, what was it you wanted to talk about?'");
        sprites.answerBoxText[1].setString("2. 'What's your name, kid?'");
        animate.getZinTalkNot() = false;
        break;
    case 1:
        sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
        sprites.getShowAnsBoxesCounter() = -1;
        switch (this->choiceCounter) {
        case 0:
            sprites.text.setString("'Well... Uhhh... Are you a monster like those others?'\n\n*You look down at your skin, slowly rotting.*");
            break;
        case 1:
            sprites.text.setString("'I'm Zin... When did you get the decay?'\n\n*You look down at your skin, slowly rotting.*");
            break;
        }
        break;
    case 2:
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'The decay has been rotting away at me for the past year. I caught it during my time as a knight at the castle...'");
        sprites.answerBoxText[1].setString("2. 'Look, I'm gonna be honest with you, I probably don't have a lot of time left, kid...'");
        break;
    case 3:
        sprites.getShowAnsBoxesCounter() = -1;
        sprites.text.setString("*Without another word, Zin reaches her hand out and places it on your shoulder, a bright light coming from her hand.\n\nIt burns quite badly, however you notice the decay slowly receding from your body...*");
        break;
    case 4:
        sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
        sprites.answerBoxText[0].setString("1. 'You have the power to cleanse the decay?!'");
        sprites.answerBoxText[1].setString("2. 'You CAN help the decay?!'");
        break;
    case 5:
        sprites.getShowAnsBoxesCounter() = -1;
        sprites.text.setString("'Sorry for lying to you earlier. My dad told me to never tell someone I can cleanse it unless I trust them.'");
        break;
    case 6:
        sprites.text.setString("Your mind comes to a dire realization. Despite your armor and sword being lost, you must still carry out your duties as a knight.\n\nShe must be protected at all costs as she is one of the last bastions of preserving life in this horrible world...");
        break;
    case 7:
        sprites.text.setString("");
        this->reInitialize = true;
        break;
    }
}

//Forest Entrance Events
void Event::forestSiwardEncounter(Sprites& sprites)
{
    if (!this->siwardEncounteredForest) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.getSpriteViewerCounter() = 0; //Make entity viewer visible
            sprites.getEntityViewerCounter() = 0; //Make siward entity visible
            sprites.getSiwardCounter() = 0; //Make Siwards Sprite Appear
            this->hideOpenAssets(sprites);
            sprites.text.setString("A knight suddenly appears from around a tree, practically ambushing your view. Though he seems to get startled from your presence as well...");
            break;
        case 1:
            sprites.text.setString("'Pardon my intrusion! I did not believe I would be finding people this deep in the woods! You both must be strong!\n\n'My name is Siward, Siward Howler. A pleasure to meet you both. What brings you two out here so late in the night might I ask?'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Why are you so acting so friendly and joyful? We're surrounded by hell out here.'");
            sprites.answerBoxText[1].setString("2. 'I'm trying to get this kid far away from here. Somewhere safer. Well, if that still exists...'");
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'You're not wrong good sir, the forefront and battles ahead seem grueling, however laying my sword and attitude down may serve nothing more than to swiften thy death!'\n\n'I hath not been taught to kneel so easily at the hands of cruelety and I see that in you as well, my friend. Though your mind may currently be weary, your stoicism will bring you unto the end of your journey unscathed!'");
                break;
            case 1:
                sprites.text.setString("'Ah, I see, quite the noble task! Most that claim such righteous duties lie and deceit, claiming to be doing the right thing when only sin truly captures their mind...'\n\n'But not you, friend! I cant tell, the look in your eye, you truly are a good man. I have a keen sense for these things! Ha, I know it be true!'");
                break;
            }
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Thanks, but we should be taking our leave now...'");
            sprites.answerBoxText[1].setString("2. 'Would you care to join us, Siward?'");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Ah, yes, lingering for too long in the same place in these woods would be a poor idea. Perhaps take a word of advice before you travel onwards...' *He looks down to the rotting decay on your flesh.*\n\n'It looks freshly tended to, which I presume was handled by the little one?' *He points to Zin as he speaks.*\n\n'I too am inflincted with such a curse, though I do not ask for treatment. I ask that you merely keep the strain on the young one to a minimum. This curse touches no hand without cost...'");
                break;
            case 1:
                sprites.text.setString("'I would love to, however...' *The knight lifts his right arm, exposing a chunk of his metal armor that has been destroyed, revealing a rotting black wound.*\n\n'The time I have left is limited until I undoubtedly become another one of those wretched beasts that roam and slaughter others. Before this fate, I shall slay as many beasts in this forest as I can...'\n\n'Before I head off, I merely leave you with a piece of advice...' *He points to the decay barely visible on your arm.*\n\n'You too are strained by this curse, though it seems you have recently been treated, I presume by the little one... Keep that strain to a minimum on that girl, for no hand that touches the curse does so without cost...'");
                break;
            }
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'What do you mean? What 'cost' could come from healing the decay?'");
            sprites.answerBoxText[1].setString("2. 'What exactly are you trying to say?'");
            break;
        case 7:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("You will come to understand, but neither choice is correct in this world of chaos...' *He stares at the ground for a moment as silence consumes the air. Suddenly, he picks his sword up and begins walking deeper into the woods.*\n\n'I'm off you two! I know you'll both do fine, as will I! If fate deems it so, perhaps we shall meet again!'\n\n*Before you're able to call him back, he disappears into the forest entirely...*");
            sprites.getSiwardCounter() = -1;
            break;
        case 8:
            sprites.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
            sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
            sprites.text.setString("Well... That dude was strange. I'm sure you want to talk about what he said but... Let's wait till we get back to the bonfire.");
            break;
        case 9:
            sprites.getZinCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            //Make siwards entity invisible
            sprites.getEntityViewerCounter() = -1;
            this->siwardEncounteredForest = true;
            break;
        }
    }
}

//Forest Depths Events
void Event::forestDepthsSpadeEncounter(Sprites& sprites)
{
    if (!this->spadeEncounteredForest) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.getSpriteViewerCounter() = 0; //Make entity viewer visible
            sprites.getEntityViewerCounter() = 3; //Make spade entity visible
            sprites.getSpadeLoadOnce() = false; //Allow to be used again
            sprites.getSpadeCounter() = 0; //Make Spades Sprite Appear
            this->hideOpenAssets(sprites);
            sprites.text.setString("Suddenly, a strange girl ambushes you. Your keen senses were unable to detect her.");
            break;
        case 1:
            sprites.text.setString("Hahaha! You looked almost scared for a minute there! It's just me! You're fine.");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Lady, I have never met you in my entire life.'");
            sprites.answerBoxText[1].setString("2. 'Who the fuck are you?'");
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("'Aweeee, lost our memory have we? It's me! Spade! The court jester...! No...? How could you NOT remember ME?! I'm fantastic!'");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Apologies, but I definitely don't remember you.'");
            sprites.answerBoxText[1].setString("2. 'I don't see the appeal.'");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Hmmmm, well I'll make you remember REAL quick!'");
                break;
            case 1:
                sprites.getSpadeCounter() = 1;
                sprites.text.setString("'Oh yeah? Well maybe I SHOULD SHOW YOU! Urghhhh!' *She is quite visibly upset, holding herself back from yelling too loudly in the woods...*\n\n'I'll tell you what, I'll MAKE you remember me, knight!'");
                break;
            }
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Make me? What're you gonna do exactly?'");
            sprites.answerBoxText[1].setString("2. 'So you're trying to say that we met in the castle?'");
            break;
        case 7:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'I dunno, knock you over the head? SOMETHING, cause clearly your head aint working if you don't remember meeting me.'");
                break;
            case 1:
                sprites.getSpadeCounter() = 1;
                sprites.text.setString("'Yes, we obviously did! How can you not remember me? You were smart back at the castle, but it seems like you've turned dense!'");
                break;
            }
            break;
        case 8:
            sprites.text.setString("*You try your best to remember her. You think back to every face you can remember from the castle but you just can't quite recognize her no matter how hard you try.*\n\n'I genuinely just don't remember you.'");
            break;
        case 9:
            sprites.text.setString("'Oh, I know!' *She yells in excitment* 'I know a witch that can bring peoples memory back!'");
            break;
        case 10:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'I don't want anything to do with a witch.'");
            sprites.answerBoxText[1].setString("2. 'I don't want anything to do with you.'");
            break;
        case 11:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.getSpadeCounter() = 0;
            sprites.text.setString("'Awwwe, come on! I know you won't regret it! I'll go talk to the witch, see you soon!'\n\n*She runs off deeper into the woods, skipping with excitment. You hope to God you never see her again.*");
            break;
        case 12:
            sprites.getSpadeCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            //Make spades entity invisible
            sprites.getEntityViewerCounter() = -1;
            this->spadeEncounteredForest = true;
            break;
        }
    }
}

void Event::treeEncounter(Sprites& sprites, Player& player)
{
    if (!this->treeEncountered) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.getSpriteViewerCounter() = 0; //Make entity viewer visible
            sprites.getEntityViewerCounter() = 2; //Make tree entity visible
            this->hideOpenAssets(sprites);
            sprites.text.setString("You hear a voice nearby, stopping you in your tracks. You were certain no one was nearby but you most definitely hear somebody.\nYou turn to your left, then your right. You lock eyes with it. A tree... Speaking to you...?\n\nIt keeps repeating some odd chanting sound to you but you can't quite make out what it's saying...");
            break;
        case 1:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Uh... Hello?'");
            sprites.answerBoxText[1].setString("2. 'What are you...?'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("Eyes slowly embed into the tree, staring at you as you stare back horrified. The branches of the tree slowly move towards you as you stand there, staring, unsure of what to do...");
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Attempt to escape*");
            sprites.answerBoxText[1].setString("2. *Try to warn Zin*");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
            sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
            if (!this->sfxUsed) {
                sprites.soundSmite.play(); //Play smite sfx
                this->sfxUsed = true;
            }
            sprites.text.setString("As you turn, you lock eyes with Zin. You notice her hands are enclosed and shes slowly moving her palms against one another as she stares at the tree. Suddenly, a horrifying crack deafening you.\n\nYou realize that she had just used smite, obliterating the tree and splitting it in half with the bolt of lightning...");
            break;
        case 5:
            this->sfxUsed = false;
            sprites.getZinCounter() = 1;//Switch Zins emotions
            sprites.text.setString("'Got him! Heh!'");
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'What in the hell was that thing?'");
            sprites.answerBoxText[1].setString("2. 'Are you TRYING to start a forest fire?!'");
            break;
        case 7:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'No idea! But it's gone now!'");
                break;
            case 1:
                sprites.text.setString("'Maybe...'");
                break;
            }
            break;
        case 8:
            sprites.text.setString("You look at the floor of the burning tree and notice something. One of the eyes that was forming on it seems to have turned to a hard rock after being struck.\n\n+1 Smithing Stone");
            if (!this->itemGained) {
                player.getSmithingStones()++;
                this->itemGained = true;
            }
            break;
        case 9:
            this->itemGained = false;
            sprites.getZinCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            sprites.getEntityViewerCounter() = -1;
            this->treeEncountered = true;
            break;
        }
    }
}

void Event::thomEncounter(Sprites& sprites)
{
    if (!this->thomEncountered) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            //Make Thom's entity visible
            sprites.getEntityViewerCounter() = 22;
            sprites.text.setString("*You hear a rustling in the bushes which alerts you. You draw your sword as you notice the creature reveal itself.*\n\n*It's a very small creature, about the size of two human hands. It looks up to you confused...*");
            break;
        case 1:
            sprites.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
            sprites.getZinCounter() = 1; //Set correct frame for zins sprite to appear
            sprites.text.setString("Look at that little guy! *Zin bends down and reaches to pet the small creature. The creature actually responds well, rubbing against her hand in joy.*\n\n*You stare at the creature as Zin pets it, trying to figure out exactly what it is. It looks almost like a small dog, but you also know that it's definitely not a dog...\b");
            break;
        case 2:
            sprites.text.setString("*You notice that the black fur on its body is actually decay. The entire small animal is just some amalgamation of decay, however it's not hostile...*");
            break;
        case 3:
            sprites.text.setString("'Can we take it with us?! I bet he'd make a great pet!' *Zin is clearly quite excited over this creature*");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'I mean, I guess it seems harmless...? But you realize it's covered in decay, right?'");
            sprites.answerBoxText[1].setString("2. 'Zin, that entire thing is a decay cesspool. We are not taking it with us.'");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'I know, I can feel the presence of decay. But it seems like this little dude can control it to some extent! So what do you say, can we take him?'\n\n*Zin continues petting it as you realize the creature is definitely manipulating the decay on its own... Somehow...*");
                break;
            case 1:
                sprites.text.setString("'Awwwe, come on! I'll take good care of it! It's not like I can't handle decay! I'm practically made for this little creature! Plus, look at him, he can control the decay! Come on, can we please take him?'\n\n*Zin continues petting it as you realize the creature is definitely manipulating the decay on its own... Somehow...*");
                break;
            }
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Alright, we'll take the little guy.'");
            sprites.answerBoxText[1].setString("2. 'We are not taking that thing with us. It's just too much of a risk.'");
            break;
        case 7:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.getThomUnlocked() = true;
                sprites.text.setString("'Yay! I know we won't regret it! I'm gonna name him 'Thom', after my dad! Before he died! Not after!\n\nParty member gained.'");
                break;
            case 1:
                sprites.getZinCounter() = 4;
                sprites.text.setString("'Alright, fine... I'm sorry...'\n\n*You feel a bit bad but you're sure she'll get over it soon. She is a kid after all.*");
                break;
            }
            break;
        case 8:
            sprites.getZinCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            sprites.getEntityViewerCounter() = -1;
            this->thomEncountered = true;
            break;
        }
    }
}

//Forest Abyssal Events
void Event::obeliskEncounter(Sprites& sprites, Player& player)
{
    if (!this->obeliskEncountered) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.getSpriteViewerCounter() = 0; //Make entity viewer visible
            sprites.getEntityViewerCounter() = 6; //Make obelisk entity visible
            this->hideOpenAssets(sprites);
            sprites.text.setString("You feel a strange presence in the area... You notice something strange ahead. A glowing obelisk, seemingly calling to you.");
            break;
        case 1:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Move towards the obelisk*");
            sprites.answerBoxText[1].setString("2. *Back away from the obelisk*");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*You move towards the obelisk, but as you do you notice that it seems like the distance between you and the object is not changing. Instead, you're somehow staying the same distance from it despite moving towards it. You feel a horrible pain in your gut as you keep walking...*");
                break;
            case 1:
                sprites.text.setString("*You move away from the obelisk, but as you do you notice that it seems like the distance between you and the object is not changing. Instead, you're somehow staying the same distance from it despite moving away from it. You feel a horrible pain in your gut as you keep backing up...*");
                break;
            }
            break;
        case 3:
            sprites.text.setString("*Suddenly, you hear a voice inside of your head begin to speak to you. It sounds inhuman, almost otherwordly.*\n\n'What is it you wish for? Riches, or power?");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Play along with it*");
            sprites.answerBoxText[1].setString("2. 'What the hell are you?'");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*You decide to play along with it, thinking about its question for a moment before answering... Zin stares at the interaction between you and the object with clear fear*");
                break;
            case 1:
                sprites.text.setString("*It only repeats its question, ignoring yours. You realize that at this rate there's no escaping it. Best bet is to play along for now...*");
                break;
            }
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Riches'");
            sprites.answerBoxText[1].setString("2. 'Power'");
            break;
        case 7:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*The obelisk slowly destroys itself and crumbles to the floor, no longer trapping you with its presence. You notice that you have significantly more gold in your pouch suddenly. Looks like it wasn't a trap after all...*\n\n+50 Gold");
                if (!this->itemGained) {
                    player.getGold() += 50;
                    this->itemGained = true;
                }
                break;
            case 1:
                sprites.text.setString("*The obelisk slowly destroys itself and crumbles to the floor, no longer trapping you with its presence. You feel as though for some reason you have a greater knowledge than you did prior. Perhaps it gave you some kind of power after all.*\n\n+500 Exp");
                if (!this->itemGained) {
                    player.getExp() += 500;
                    this->itemGained = true;
                }
                break;
            }
            break;
        case 8:
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            sprites.getEntityViewerCounter() = -1;
            this->itemGained = false;
            this->obeliskEncountered = true;
            break;
        }
    }
}

void Event::lostNunEncounter(Sprites& sprites)
{
    if (!this->nunEncountered) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.setZinInitFalse(); //Allow Zins sprite to be used again through the boolean
            sprites.getZinCounter() = 0; //Set concerned frame
            sprites.getSpriteViewerCounter() = 0; //Make entity viewer visible
            sprites.getEntityViewerCounter() = 7; //Make nun entity visible
            this->hideOpenAssets(sprites);
            sprites.text.setString("*You notice a woman standing alone in a clearing up ahead in the woods. She seems distraught until she notices you and Zin walking. She runs up to you both and goes to try and hug Zin, however Zin backs away...*\n\n'I have been looking for you everywhere, sweetie! Where did you run off to?' *The woman exclaims*");
            break;
        case 1:
            sprites.getZinCounter() = 2;
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Who are you?'");
            sprites.answerBoxText[1].setString("2. *Turn to Zin* 'Do you know her?'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*The woman glares at you before ignoring your words and continuing to talk to Zin...*\n\n'Let's go home and get away from this horrible place, sound good hun?' *Zin looks at the lady with confusion* 'I have no idea who you are, lady...' *Zin replies to her*");
                break;
            case 1:
                sprites.text.setString("*Zin shakes her head, looking at the woman with confusion.* 'I have no idea who you are, lady.' *Zin replies to the woman*\n\n*The woman steps closer, visibly angrier from the reply. You notice what looks to be melting decay rotting off of her arm under her cloak. This woman has been rotting from decay for quite some time...*\n\n*You recall back to your time aiding the citizens in the castle. Some rotting with decay would have adverse effects such as this with the decay.\n\nRather than losing their mind and strength, only their mind would rot as their body would grow stronger.*");
                break;
            }
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Try to turn and escape with Zin*");
            sprites.answerBoxText[1].setString("2. 'Get the fuck away from us.'");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*You grab Zin and begin to run, not looking back. You hear a horrific screaming behind you as the footsteps grow closer at an obsurd pace.*\n\n*Suddenly, she launches directly in front of both of your paths despite your best efforts at running.*\n\n*You plant your feet into the ground and draw your sword as Zin readies her spells. It's do or die.*");
                break;
            case 1:
                sprites.text.setString("*The woman slowly turns her head away from Zin, not bothering to move her body to face you. Instead, you hear her neck audibly snapping as she makes eye contact with you.* 'I'm going to string you up like dried meat.' *The woman states as she moves towards you.*\n\n*You plant both of your feet into the ground and draw your sword, noticing Zin also readying her spells behind her. It's do or die.");
                break;
            }
            break;
        case 5:
            sprites.getZinCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            this->nunEncountered = true;
            break;
        }
    }
}

//Castle Hall Events
void Event::spadeEncounter(Sprites& sprites)
{
    if (!this->spadeEncounteredCastle) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            break;
        case 1:
            break;
        }
    }
}

//Castle Depth Events
void Event::castleSiwardEncounter(Sprites& sprites)
{
    if (!this->siwardEncounteredCastle) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.text.setString("*You notice a familiar set of armor standing amongst a pile of corpses.*\n\n'Hello there sir! It's good to see a friendly face amongst the chaos! I see you and the little one appear to be doing alright. This is great news!'");
            sprites.getEntityViewerCounter() = 23;
            sprites.getSpriteViewerCounter() = 0;
            sprites.getSiwardCounter() = 1;
            break;
        case 1:
            break;
        }
    }
}

//Castle Labyrinth Events
void Event::castleSiwardFinalEncounter(Sprites& sprites)
{
    if (!this->siwardEncounteredFinal) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            break;
        case 1:
            break;
        }
    }
}