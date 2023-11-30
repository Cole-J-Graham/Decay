#include "Event.h"

//Constructors & Destructors
Event::Event()
{
    //Control Flow Bools
    this->reInitialize = true;
    this->sfxUsed = false;
    this->itemGained = false;

    //Event Availability Bools
    this->thomEnced = false;
    this->siwardEncedForest = false;
    this->siwardEncedCastle = false;
    this->siwardEncedFinal = false;

    this->spadeEncedForest = false;
    this->spadeEncedAbyssalForest = false;
    this->spadeEncedCastle = false;
    this->spadeEncedCastlePoison = false;
    this->spadeEncedDecay = false;
    this->spadeEncedDecayPoison = false;

    this->riEncedForest = false;

    this->grifEncounteredCastle = false;

    this->treeEnced = false;
    this->obeliskEnced = false;

    this->nunEnced = false;

    this->rotBeastEnced = false;
    this->playerDeathEnced = false;

    //Event Control Flow Bools
    this->spadePoison = false;

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
        combat.getComTextRemoved() = false;
        combat.combatTextTime.restart();//Reset text
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

void Event::smithingSharpenBlade(sf::RenderWindow& window, Sprites& sprites, Player& player, Combat& combat)
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
            combat.getComTextRemoved() = false;
            combat.combatTextTime.restart();//Reset text
        }
        else if (player.getSmithingStones() <= 0) {
            sprites.text.setString("You lack the required smithing stones to improve your sword...");
            combat.getComTextRemoved() = false;
            combat.combatTextTime.restart();//Reset text
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
void Event::forestSiwardEnc(Sprites& sprites)
{
    if (!this->siwardEncedForest) {
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
            sprites.getZinCounter() = 0; //Set correct frame for zins sprite to appear
            sprites.text.setString("Well... That dude was strange... I think we can trust him though. I hope.");
            break;
        case 9:
            sprites.getZinCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            //Make siwards entity invisible
            sprites.getEntityViewerCounter() = -1;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->siwardEncedForest = true;
            break;
        }
    }
}

void Event::riEnc(Sprites& sprites)
{
    if (!this->riEncedForest) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            sprites.getEntityViewerCounter() = 28; //Make Ri entity visible
            sprites.getRiCounter() = 0;
            sprites.text.setString("*You suddenly notice what looks to be a little girl further in view. It looks as though she's searching for something quite intensely...*\n\n*Upon walking closer, you notice the child seems to be holding a sword almost the size of her. You wonder how it's even possible, though your pondering is cut short as she notices you...*");
            break;
        case 1:
            sprites.text.setString("'Hey, mister! Have you seen any demons around here?'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Can't say that I have. Mind telling me how you're holding that thing?'");
            sprites.answerBoxText[1].setString("2. *Ignore her question and keep ogling at the sword* 'Is that sword some kind of magic? Does it weigh nothing?'");
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'You haven't? Awe... darn. Oh! To answer your question the sword isn't heavy at all! Well, not to me anyways.'\n\n*Zin is clearly distraught just as much as yourself. You can tell she's prepared to cast smite incase of some sort of trick. A tad bit paranoid, are we?*");
                break;
            case 1:
                sprites.text.setString("'Oh, I can assure you, this thing is like BEYOND heavy! But it's easy to carry for me! Anywho, any demons?'\n\n*Zin is clearly distraught as well. You can tell she's prepared to cast smite incase of some sort of trick. A tad bit paranoid, are we?*");
                break;
            }
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Why exactly are you hunting for demons?'");
            sprites.answerBoxText[1].setString("2. 'Are you gonna clobber a demon with that thing you call a sword?'");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Well, I just don't like them running around rampant, you know? So I kill em. Like I just hate demons. Usually takes one smack with this thing. Just need to find em.'");
                break;
            case 1:
                sprites.text.setString("'That's the plan! As soon as it stops hiding from me!'");
                break;
            }
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'So, are you hunting like a specific demon? Or just demons in general?'");
            sprites.answerBoxText[1].setString("2. 'Are you just hunting aimlessly?'");
            break;
        case 7:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("'Well, normally I just wander around looking for them but I saw one just right over there!' *She points off in the distance in a clearing of trees.*\n\n'But it ran when it saw me! So now I'm hunting him!'");
            break;
        case 8:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Glare at her sword* 'I think I'd run too...'");
            sprites.answerBoxText[1].setString("2. 'Him?'");
            break;
        case 9:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.getRiCounter() = 2;
                sprites.text.setString("*The girl smiles back at you hauntingly...* 'Good!'");
                break;
            case 1:
                sprites.getRiCounter() = 2;
                sprites.text.setString("'Yeah! It looked like a dude! I think... I usually don't think that far!'");
                break;
            }
            break;
        case 10:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Where are your parents?'");
            sprites.answerBoxText[1].setString("2. 'Are you insane?'");
            break;
        case 11:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("'You ask more questions than a guard does to a street urchin!'");
            break;
        case 12:
            sprites.text.setString("*You glare back at her before replying...* 'Well, I used to be a guard. Head of the guard, actually.'");
            break;
        case 13:
            sprites.getEntityViewerCounter() = -1;
            sprites.getRiCounter() = -1;
            sprites.text.setString("*The little girl begins to wander off further into the woods after you finish your sentence.* 'Cool! Never asked. I'm gonna go kill more demons now! Bye guard guy!'\n\n*You stand there motionless in shock from the entire interaction, slowly waving her off... 'What a strange child', you think to yourself.*");
            break;
        case 14:
            sprites.getZinCounter() = 2;
            sprites.text.setString("*Zin finally speaks up after being silent the entire interaction.* 'Did you just get talked down to by a child?'");
            break;
        case 15:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Absolutely did.'");
            sprites.answerBoxText[1].setString("2. 'What else was I supposed to do? Yell at her?'");
            break;
        case 16:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Thought so. Let's get moving.'");
                break;
            case 1:
                sprites.text.setString("'Actually, you make a good point... In any case, let's get moving.'");
                break;
            }
            break;
        case 17:
            sprites.getZinCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            this->riEncedForest = true;
            break;
        }
    }
}

//Forest Depths Events
void Event::forestDepthsSpadeEnc(Sprites& sprites)
{
    if (!this->spadeEncedForest) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.getEntityViewerCounter() = 3; //Make spade entity visible
            sprites.getSpadeCounter() = 0; //Make Spades Sprite Appear
            this->hideOpenAssets(sprites);
            sprites.text.setString("*Suddenly, a strange girl ambushes you. Your keen senses were unable to detect her.*");
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
            this->reInitialize = true;//Reset dialogue counter for other events
            this->spadeEncedForest = true;
            break;
        }
    }
}

void Event::treeEnc(Sprites& sprites, Player& player)
{
    if (!this->treeEnced) {
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
            this->reInitialize = true;//Reset dialogue counter for other events
            this->treeEnced = true;
            break;
        }
    }
}

void Event::thomEnc(Sprites& sprites)
{
    if (!this->thomEnced) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            //Make Thom's entity visible
            sprites.getEntityViewerCounter() = 22;
            sprites.text.setString("*You hear a rustling in the bushes which alerts you. You draw your sword as you notice the creature reveal itself.*\n\n*It's a very small creature, about the size of two human hands. It looks up to you confused...*");
            break;
        case 1:
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
            this->reInitialize = true;//Reset dialogue counter for other events
            this->thomEnced = true;
            break;
        }
    }
}

//Forest Abyssal Events
void Event::obeliskEnc(Sprites& sprites, Player& player)
{
    if (!this->obeliskEnced) {
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
                sprites.text.setString("*You move towards the obelisk, but as you do you notice that it seems like the distance between you and the object is not changing.\n\nInstead, you're somehow staying the same distance from it despite moving towards it. You feel a horrible pain in your gut as you keep walking...*");
                break;
            case 1:
                sprites.text.setString("*You move away from the obelisk, but as you do you notice that it seems like the distance between you and the object is not changing.\n\nInstead, you're somehow staying the same distance from it despite moving away from it. You feel a horrible pain in your gut as you keep backing up...*");
                break;
            }
            break;
        case 3:
            sprites.text.setString("*Suddenly, you hear a voice inside of your head begin to speak to you. It sounds inhuman, almost otherwordly.*\n\n'What is it you wish for? Riches, or power?'");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Play along with it*");
            sprites.answerBoxText[1].setString("2. 'Chocolate shake? Burger? Uhh... Burger?'");
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
            this->reInitialize = true;//Reset dialogue counter for other events
            this->obeliskEnced = true;
            break;
        }
    }
}

void Event::lostNunEnc(Sprites& sprites)
{
    if (!this->nunEnced) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
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
            this->reInitialize = true;//Reset dialogue counter for other events
            this->nunEnced = true;
            break;
        }
    }
}

//Forest Abyssal Depths Events
void Event::forestAbyssalSpadeEnc(Sprites& sprites, Player& player)
{
    if (!this->spadeEncedAbyssalForest) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.getEntityViewerCounter() = 25;
            sprites.getSpadeCounter() = 0;
            this->hideOpenAssets(sprites);
            sprites.text.setString("'Helllloooo again! Did you miss me...?'");
            break;
        case 1:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Sigh heavily*");
            sprites.answerBoxText[1].setString("2. 'Have you been following us?'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'I knew you'd be happy to see me! Anyways, that witch fucking ran off when I started shouting at her but she left behind something interesting...'\n\n*She pulls out a potion from her back pocket labled with multiple skulls across it. Immediately she attempts to hide the labels and peel them off hoping you don't notice...*");
                break;
            case 1:
                sprites.text.setString("'Well of course. Why wouldn't I be? Anyways, that witch fucking ran off when I started shouting at her but she left behind something interesting...'\n\n*She pulls out a potion from her back pocket labled with multiple skulls across it. Immediately she attempts to hide the labels and peel them off hoping you don't notice...*");
                break;
            }
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. *Sigh even louder this time...*");
            sprites.answerBoxText[1].setString("2. 'You're delusional if you think I can't see the labels on that thing...'");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Whaaaaat? Why do you keep sighing? It'll bring back your memories.'");
                break;
            case 1:
                sprites.text.setString("'Pffffff, what labels? You sound fucking insane right now. You know that? That you sound insane? With the words coming from your mouth?'\n\n'You're fucking crazy.'");
                break;
            }
            break;
        case 5:
            sprites.text.setString("*Suddenly, Zin buds into the conversation, clearly looking annoyed...*\n\n'He is not drinking that stuff. I'm not letting him.'");
            sprites.getZinCounter() = 3; //Set correct frame for zins sprite to appear
            break;
        case 6:
            sprites.text.setString("'Oh, now suddenly his little rat wants to bud in now, does she?! Urgh, you little...' *The jester takes a step back and seems to try to calm herself.*\n\n'Remember Spade, remember, this is what your friends said NOT to do. Just breathe... BREATHE. BREATHE! AHHHHH I HATE YOU!'");
            sprites.getSpadeCounter() = 1;
            break;
        case 7:
            sprites.text.setString("*The jester takes a step back once more, taking a deep breath before speaking again.*\n\n'Hahaha, sorry about that sudden outburst... I just get very emotional sometimes is all. Anywho, let's start over! Could you pleeeasse drink this funny bottle I found?'");
            sprites.getSpadeCounter() = 3;
            break;
        case 8:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Yeah, aight.' *Down the potion.*");
            sprites.answerBoxText[1].setString("2. 'You're absolutely insane. I am not drinking that.'");
            break;
        case 9:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*Your stomach begins to tiwst and turn with horrible agony. She definitely poisoned you...* +25 Decay...\n\n'Do you remember me yet, do you, DO YOU? YOU WON'T FOR LONG, HA HA!' *The jester then proceeds to run off into the woods whilst cackling to herself...*\n\n*Zin chimes in after the jester leaves your sight.* 'She has some serious problems... Also why the HELL would you drink that? I need to cleanse you when we get back...'");
                sprites.getZinCounter() = 2;
                player.getDecay() += 25;
                this->spadePoison = true;
                break;
            case 1:
                sprites.text.setString("*Spade looks defeated from your reply, clearly upset...* 'Fine then, this stuff is sooooo good that I'll just keep it to myself then!'\n\n'I TRIED to share but I guess now I'll have to enjoy it all on my own.' *She gulps it down, instantly puking it up after...*\n\n'WHAT THE FUCK IS THIS SHIT? AGHHHHHH!' *She proceeds to hurl the empty glass bottle into the woods and run off screaming...*");
                sprites.getSpadeCounter() = 1;
                this->spadePoison = false;
                break;
            }
            break;
        case 10:
            sprites.getSpadeCounter() = -1;
            sprites.getZinCounter() = -1;
            sprites.getEntityViewerCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->spadeEncedAbyssalForest = true;
            break;
        }
    }
}

//Castle Hall Events
void Event::castleSpadeEnc(Sprites& sprites)
{
    if (!this->spadeEncedCastle) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.getEntityViewerCounter() = 4;
            sprites.getSpadeCounter() = 0;
            this->hideOpenAssets(sprites);
            sprites.text.setString("*Suddenly, a familiar face appears around the corner. You almost dread the fact you see her once more...* 'Oh, uh hello again... Are you doing alright?' *Her demeanor seems to have shifted entirely since you last spoke...*");
            break;
        case 1:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Uh, fine I guess? How's your stomach after drinking that shit?'");
            sprites.answerBoxText[1].setString("2. 'Better than you, bastard. I mean after you drank that shit it almost killed you.'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*She seems somewhat surprised that you're being civil with her after everything.*\n\n'Not so great to be honest, but I realized that something was extremely wrong with me. The way I acted, especially in front of the little one... It felt horribly wrong. How could I do such a thing?'");
                break;
            case 1:
                sprites.text.setString("*She frowns but doesn't retort as you'd expect...* 'Well, that's a fair response... I've acted absolutely obscene towards you and the little one. My actions cannot be forgiven and I apologize greatly for that.'");
                break;
            }
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'What the hell did that potion do to you?'");
            sprites.answerBoxText[1].setString("2. 'You seem much more level headed suddenly. Why is that?'");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("'Well, after the plague set in, I remember a horrible choice I had made. I was cowering for my life much like the many others in the castle when a lich spoke to me. They asked if I wished to die or to transform...'");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'So, you're saying a lich did that to you?'");
            sprites.answerBoxText[1].setString("2. 'What exactly were the terms of the deal with it?'");
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*She seems to feel ashamed of the fact she's speaking about this. She seems oddly familiar now that she isn't acting outrageous...*\n\n'Yes, I am. I shouldn't have accepted his deal but... I just wished to live. I am afraid to die.'");
                break;
            case 1:
                sprites.text.setString("*She seems to feel ashamed of the fact she's speaking about this. She seems oddly familiar now that she isn't acting outrageous...*\n\n'Well, it was quite simple in all honesty. It said I could either die right then and now... or keep living... under his curse of insanity. It found it amusing to watch people suffer. It makes me sick to think about.'");
                break;
            }
            break;
        case 7:
            sprites.getZinCounter() = 4;
            sprites.getSpadeCounter() = 2;
            sprites.text.setString("*Zin buds into the conversation suddenly as you notice sniffling coming from behind you.* 'I'm sorry I was rude to you. I thought you were bad and I didn't know...'\n\n*Spade kneels next to Zin attempting to reassure her.* 'There's nothing to apologize about! You didn't know, kiddo. You were just trying to protect the person you care about and I find that admirable.'");
            break;
        case 8:
            sprites.getZinCounter() = 1;
            sprites.text.setString("*As she kneels and kindly reassures Zin, you definitely recognize her from the castle. In your times at the medical ward helping with the ill, you recall her face smiling to other children.*");
            break;
        case 9:
            sprites.getZinCounter() = -1;
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Actually, do I know you from the castle?'");
            sprites.answerBoxText[1].setString("2. 'I think I recognize you from the medical ward of the castle...'");
            break;
        case 10:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("'Yes, that's where I worked in the day! I was the jester that was in charge of cheering up the ill. Most of the kingdom stayed away from the ill, sealing them away in their dark corners where they waited to die... But the thought of that made me sad, which is why I wanted to cheer them up the best I could.'");
            break;
        case 11:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Well, I apologize for thinking you were insane.'");
            sprites.answerBoxText[1].setString("2. 'It's good to know you aren't actually nuts.'");
            break;
        case 12:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'That's perfectly normal, I was being absolutely ridiculous, so my apologies for that. It feels so great to be talking normally again with people. After my memories flooded back and I felt normal again, I had no one to talk to. So this is nice. But once more, I apologize...'");
                break;
            case 1:
                sprites.text.setString("'I wouldn't call myself perfectly normal, but I'm certainly not who you thought I was. Once again, my apologies for my actions and words. I cannot be sorry enough...'");
                break;
            }
            break;
        case 13:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'It's quite alright. Don't worry about it.'");
            sprites.answerBoxText[1].setString("2. 'I'll look past it this once.'");
            break;
        case 14:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.getSpadeCounter() = 1;
            sprites.text.setString("*She stares into the distance momentarily before continuing...* 'Well, in any case I best get going. I wish you and the little one the best of luck and if we ever cross paths again never hesitate to ask for anything.'\n\n*She waves goodbye as she walks off in the distance. Suddenly, someone that seemed quite unstable in your book is now perfectly normal. What a strange world this has truly become, you think to yourself...*");
            break;
        case 15:
            sprites.getSpadeCounter() = -1;
            sprites.getZinCounter() = -1;
            sprites.getEntityViewerCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->spadeEncedCastle = true;
            break;
        }
    }
}

void Event::castleSpadeEncPoison(Sprites& sprites)
{
    if (!this->spadeEncedCastlePoison) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            sprites.getEntityViewerCounter() = 4;
            sprites.getSpadeCounter() = 0;
            this->hideOpenAssets(sprites);
            sprites.text.setString("'Heya, pal! How're you? I missed talking with you!'");
            break;
        case 1:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'Can't say likewise.'");
            sprites.answerBoxText[1].setString("2. 'Why shouldn't I just kill you right here right now?'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.getSpadeCounter() = 3;
            sprites.text.setString("'Awwwwwe, cmon! Don't be like that! You know I'm great! Hey hey hey, do you remember me yet?");
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'No, I don't remember you.'");
            sprites.answerBoxText[1].setString("2. 'Nope. But you're gonna remember me.'");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*The girl grins even wider...* 'What a shame! Turns out you drank that all for nothing now, hmmm? I can't believe someone that's survived out here for so long would be so foolish.'");
                break;
            case 1:
                sprites.text.setString("*The girl grins even wider...* 'Oh yeah, what are you gonna do? I'm real scared... Heh'");
                break;
            }
            break;
        case 5:
            sprites.getZinCounter() = 3;
            sprites.text.setString("*Zin suddenly speaks up, clearly pissed off at how she's treating you.* 'I wanna kill her. Can I kill her? Let me kill her...'");
            break;
        case 6:
            sprites.text.setString("*The jester grins even wider, staring at Zin as she towers over her.* 'Oh? And how are you gonna do that, little girl? Stab me? Cut me up into little pieces? Smite me maybe? Use some of that magic?'");
            break;
        case 7:
            sprites.getZinCounter() = 2;
            sprites.text.setString("*The jester continues to intimidate Zin, moving closer...*\n\n'Do you realize what I could do to you? How easily I could murder you without this shmuck over here being able to do a single thing about it? I'm merely toying with my prey until I rip you apart.'");
            break;
        case 8:
            sprites.getZinCounter() = 5;
            sprites.text.setString("*Morphing from a human shape, the girl slowly begins to melt as the form she take changes... Slowly but surely, she becomes that of a horrid tentacle like being made of human flesh!\n\nShe brings forth a tentacle, attempting to strike Zin!*");
            break;
        case 9:
            sprites.getPlayerCounter() = 1;
            sprites.text.setString("*Before the tentacle could connect and hit Zin, you rush to block the attack. You can tell you're going to be too late to block the attack, however you feel your rage seep into the decay thats slowly rotting your bones...\n\nSomething changes. You feel a spark of energy as you launch forwards!*\n\n*You stand your ground being hit by the brute force of what would've been a fatal attack to Zin. You finally speak once more...* 'Just another fucking abomination.'");
            break;
        case 10:
            sprites.getSpadeCounter() = 1;
            sprites.text.setString("*The jester stares at you with an annoyed look.* 'Oh my, now what do we have here? You look PISSED! I'd be afraid if I cared about dying. Maybe now would actually be a good time to run...'");
            break;
        case 11:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. *Attack without a word*");
            sprites.answerBoxText[1].setString("2. 'What makes you think I'd give you the chance to?'");
            break;
        case 12:
            sprites.getSpadeCounter() = -1;
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*You launch forwards, the jester narrowly dodging your attack as you clearly notice the fear in her eyes from your sudden assault.\n\nShe springs backwards and leaps out of a nearby castle window without any care as to what's below.\n\nShe seemed desperate to leave that situation. Makes you wonder... who's really the monster?*");
                break;
            case 1:
                sprites.text.setString("'Well, you speaking is a pretty good chance!' *The jester quips back before leaping out a nearby window out of the castle. Seems she's gone... For now.*");
                break;
            }
            break;
        case 13:
            sprites.text.setString("*Zin looks to you in shock after all of the chaos...* 'What the hell happened to you? How are you... glowing? It almost seems like it's slowly fading now?'");
            break;
        case 14:
            sprites.getPlayerCounter() = 0;
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'I have no idea. She just pisses me off...'");
            sprites.answerBoxText[1].setString("2. 'I'm a freak I guess.'");
            break;
        case 15:
            sprites.getZinCounter() = 0;
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*Zin looks to be relieved but still understandably troubled by the situation...* 'Yeah, maybe a little too much. Look, I get that you're sort of insane and all but this is some freaky shit even for you...'");
                break;
            case 1:
                sprites.text.setString("*Zin looks to be relieved but still understandably troubled by the situation...* 'Well, you're damn right about that. You're always pulling some freaky shit out of your sleeve.'");
                break;
            }
            break;
        case 16:
            sprites.getShowAnsBoxesCounter() = 0;
            sprites.answerBoxText[0].setString("1. 'This coming from the girl that literally turns my blood into blades?'");
            sprites.answerBoxText[1].setString("2. 'Well, I wouldn't be normal if I was on this journey...'");
            break;
        case 17:
            sprites.getZinCounter() = 2;
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*Zin looks as though she's about to retort, however she pauses herself before speaking and seems to regather her thoughts...* 'Yeah, no, that's actually a fair point. Let's just get moving...'");
                break;
            case 1:
                sprites.text.setString("*Zin looks momentarily puzzled before nodding her head* 'Yeah, that's honestly pretty fair. In any case, let's jsut keep moving...'");
                break;
            }
            break;
        case 18:
            sprites.getPlayerCounter() = -1;
            sprites.getZinCounter() = -1;
            sprites.getEntityViewerCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->spadeEncedCastlePoison = true;
            break;
        }
    }
}

//Castle Depth Events
void Event::castleSiwardEnc(Sprites& sprites)
{
    if (!this->siwardEncedCastle) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            sprites.text.setString("*You notice a familiar set of armor standing amongst a pile of corpses.*\n\n'Hello there sir! It's good to see a friendly face amongst the chaos! I see you and the little one appear to be doing alright. This is great news!\n\n*You look at Siwards face through his helmet, the darkness of decay slowly spilling out. He's getting much worse...*'");
            sprites.getEntityViewerCounter() = 23;
            sprites.getSpriteViewerCounter() = 0;
            sprites.getSiwardCounter() = 1;
            break;
        case 1:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Are you doing alright, Siward?'");
            sprites.answerBoxText[1].setString("2. 'Your decay... It's gotten a lot worse.'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Well, if I'm honest with you it's been quite rough, brother. But I've held on much longer than I thought I was going to! Through the woods and into the castle, I still tower over the foes of this wretched disease!'\n\n*He slowly looks down to his hands covered in blood as his smile fades...*\n\n'Though, my time is quite limited, brother...'");
                break;
            case 1:
                sprites.text.setString("'That is has, brother. But I won't let that drag me down! I still tower above the foes of this horrid plague!'\n\n*He slowly looks down to his hands covered in blood as his smile fades...*\n\n'Though, my time is quite limited, brother...'");
                break;
            }
            break;
        case 3:
            sprites.getZinCounter() = 4; //Set correct frame for zins sprite to appear
            sprites.text.setString("*Zin buds into the converstaion, clearly bothered by this news.* 'But there's got to be something we can do, right? We can't just let you die like everyone else! Let me cleanse you, please!'");
            break;
        case 4:
            sprites.text.setString("*The knight smiles at Zin as he steps off the pile of corpses he made. He kneels next to the child before speaking.*\n\n'Now now, don't cry over a warrior meeting his fate, young one. I knew what I was signing up for the day I joined the guard...'\n\n'As kind of an offer as it is to cleanse me, it's merely a temporary fix. I need you to save your strength to cleanse your friend here.' *The knight says as he points to you.*");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.getZinCounter() = -1;
            sprites.answerBoxText[0].setString("1. 'So what do you plan to do exactly if you aren't planning to cleanse yourself at all?'");
            sprites.answerBoxText[1].setString("2. 'Are you deciding to die here?'");
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'I plan to cleanse this area as much as possible to help travelers towards the heart of the decay. It is the only place we have hope to destroy this plague.'");
                break;
            case 1:
                sprites.text.setString("'When my body falters and I fall, I simply wish to not be a burden to anyone else. I pray to the Lord I do not end up as one of these things...' *Siward says as he points down to the bodies of the decayed he's slaughtered.*\n\n'All I wish to do is to cleanse the path for travelers attempting to reach the heart of the decay. To finally end this horrible disease.'");
                break;
            }
            break;
        case 7:
            sprites.text.setString("*You perk up in confusion* 'The heart of the decay? You know of a place we might be able to stop the decay?'");
            break;
        case 8:
            sprites.text.setString("*Siward raises his eyebrows as he seems to come to a realization.* 'Perhaps you two are the ones that must reach the heart. I've heard rumors only a priest can break the roots of the decay.'\n\n'But to answer your question, there is likely a place to stop the decay. I've only heard about it, though down past this castles labyrinth you will find a underground road leading to a crimson cave...'\n\n'This cave apparently continues for miles and is said it is the closest anyone has ever gotten to the start of where the decay came from. If you can get to the heart, there's a chance you two can stop this.'\n\n'Though it's merely a rumor, it makes sense to me.'");
            break;
        case 9:
            sprites.text.setString("*You look back to Siward...* 'If these rumors turn out to be true, we'll see if we can bring down this horrible disease.'");
            break;
        case 10:
            sprites.text.setString("*Siward raises his fist and clenches it as a sign of strength* 'That's what I like to hear! You and this little one will avenge us all!'\n\n*He looks back out towards the other paths in the castle that now echo the cries of the damned...* 'Now if you both would excuse me, I have more abominations to put to rest. Travel safely and remember the fallen!'");
            break;
        case 11:
            sprites.text.setString("*You watch as Siward steps off to slaughter more of the decayed. It seems as though you may now have your work cut out for you. Traveling to the very pits of hell sounds suicidal. Though you step forwards nonetheless...*");
            break;
        case 12:
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            sprites.getEntityViewerCounter() = -1;
            sprites.getSiwardCounter() = -1;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->siwardEncedCastle = true;
            break;
        }
    }
}

//Castle Chambers Events
void Event::castleGrifEnc(Sprites& sprites)
{
    if (!this->grifEncounteredCastle) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            sprites.getGrifCounter() = 0;
            sprites.getEntityViewerCounter() = 29;
            sprites.text.setString("*You notice what looks to be a battered skeleton approaching you. You ready yourself in a fighting stance until the skeleton puts his arms up in a defensive pose. It looks like the skeleton is out of breath from running...?*\n\n'Stop! Don't you dare! Let me- breathe a moment...'\n\n*You take a step back feeling quite confused. Every undead you've seen up to this point had no capabilities of speaking. But somehow, this one talks?'");
            break;
        case 1:
            sprites.text.setString("*The skeleton continues speaking while in a defensive posture...* 'Look, I know this looks bad but I swear I'm human! My name is Grif! Or well, used to be. Been a while but whatever... Spare the details, I'm, not your foe.'\n\n*Zin turns to you with the a look of no mercy in her eyes before she speaks.* 'Let's kill it.'");
            break;
        case 2:
            sprites.getZinCounter() = 3;
            sprites.getGrifCounter() = 2;
            sprites.text.setString("*Zin begins to raise her hands as she prepares a smite attack. The skeleton becomes visibly afraid as he panics to talk you both down.*\n\n'Woah woah woah, little lady! Let's all just relax here! Stop stop STOP STOP STOP STOP PLEASE STOP- OH SHIT!'\n\n*A burst of lightning crashes into the ground nearly hitting the skeleton as he barely avoids the blast!*\n\n*The skeleton looks back at you both looking angry yet terrified.* 'WHY?'");
            break;
        case 3:
            sprites.text.setString("*Zin steps closer to him, her bloodlust for the undead becoming even more apparent.* 'Because you're an undead. A demon. You shouldn't even know how to speak.'\n\n*You step forwards and place yor arm in between the skeleton and Zin before speaking.* 'Hold on there, tiger. Before you go smiting him into the floor let's hear what he has to say. Your name was Grif, right?'");
            break;
        case 4:
            sprites.getZinCounter() = 0;
            sprites.getGrifCounter() = 0;
            sprites.text.setString("*The skeleton seems more relieved now.* 'Thank God you have some sense. Like I said, I'm not even an undead! Or well, I used to not be. I got cursed, blah blah blah, flesh rotted off. You know?'\n\n*You stare back without a word as the skeleton continues to ramble...*\n\n'Everyone calls me a demon but I'm not! I'm just a store owner! Well, before the place burnt down... Man this shit sucks. If that wasn't bad enough this strange little girl has been hunting me down for DAYS now!'");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Who? Zin?'");
            sprites.answerBoxText[1].setString("2. 'A little girl?'");
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'No no no, not her. I mean it's strange that this is the SECOND child trying to kill me but whatever. The kid I'm talking about is like this tall I think?' *He places his hand out in front of him to try and visualize the height.*\n\n*The skeleton then continues rambling about details...* 'She carries around a massive ass sword the size of another human being. Practically a chunk of metal?'");
                break;
            case 1:
                sprites.text.setString("'Yeah, she's INSANE! She carries around a massive chunk of iron that I would hardly even call a sword and smashes creatures into bits with it. I saw her kill a haze demon with one strike!'\n\n'The second I saw that, I immediately ran away from those woods and ended up in here. Though... I can't help but get the feeling she's still near.'");
                break;
            }
            break;
        case 7:
            sprites.text.setString("*You recall Ri and figure he's talking about her.* 'I mean, she's nice. To some extent... But I could definitely see why she'd try to kill you due to your uh... current form?'\n\n*Grif looks back loking almost offended.* 'Current form? Look, man. You don't gotta make it sound so terrible.'\n\n*You look back at him with a shrug...* 'Just calling it how it is.' *Grif looks slightly saddened now...*");
            break;
        case 8:
            sprites.getGrifCounter() = -1;
            sprites.text.setString("*Suddenly, you hear what sounds like scuffling across the floor getting closer... It could be anything. Grif jumps as the sound startles him.*\n\n'Well, that's my queue to leave. See ya!' *Grif runs off into the corridors without a second thought to get away from the sound near him.*");
            break;
        case 9:
            sprites.text.setString("*Ri suddenly appears around the corner as she rapidly looks around... However she quickly locks onto the both of you the second she notices your presence.* 'Oh, hey guys! I didn't expect to see you both so soon!'\n\n'Did you guys happen to see an undead anywhere nearby? I've been hunting them as you know I like to do.'");
            break;
        case 10:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Point in the direction Grif went...* 'Yeah, he just ran away from you off over that way.'");
            sprites.answerBoxText[1].setString("2. *Lie to protect Grif.* 'Honestly, couldn't tell you. Don't think so.'");
            break;
        case 11:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Oh, okay! Thanks you two, I'll see you both around!'");
                break;
            case 1:
                sprites.text.setString("'Hmmm, well alright! I'm gonna keep looking around then! Thanks, bye!'");
                break;
            }
            break;
        case 12:
            sprites.text.setString("*She walks off with her massive sword dragging against the ground and the look of bloodlust in her eyes. Something is seriously wrong with that child...*\n\n*Zin turns to you looking concerned.* 'Why did we let that undead live?'");
            break;
        case 13:
            sprites.text.setString("'Well, Zin, undead can't talk. So as far as I'm aware, he had to be telling the truth.'");
            break;
        case 14:
            sprites.text.setString("'I guess maybe you're right... Let's just keep going, I am not a fan of inside of here.'");
            break;
        case 15:
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            sprites.getEntityViewerCounter() = -1;
            sprites.getZinCounter() = -1;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->grifEncounteredCastle = true;
            break;
        }
    }
}

//Castle Labyrinth Events
void Event::castleSiwardFinalEnc(Sprites& sprites)
{
    if (!this->siwardEncedFinal) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            sprites.text.setString("*You see Siward standing before you, clearly in immense pain. He stands alone, only dead bodies near him.* 'No... You two... Please- g ge...' *Siward stops muttering as you notice his legs begin to walk closer to you.\nIt looks as though he's lost the control of his legs...*\n\n*Suddenly, Siward clenches his sword and stabs himself through the chest with a great force! He screams in pain and drops to his knees...* 'I just... don't let me do it... don't let me...'");
            sprites.getEntityViewerCounter() = 24;
            sprites.getSpriteViewerCounter() = 0;
            sprites.getSiwardCounter() = 2;
            break;
        case 1:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Siward? Can you still hear me?'");
            sprites.answerBoxText[1].setString("2. 'We will do what we must, friend...'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("*Siward loses all control of his body as he rips the sword back out from his chest. The gaping hole leaks its last crimson drop of blood before quickly being replaced by a darkness blacker then the abyss itself. It's do or die.*");
            break;
        case 3:
            sprites.getEventAssets() = false;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->siwardEncedFinal = true;
            break;
        }
    }
}

//Decay Forest Events
void Event::decaySpadeEnc(Sprites& sprites)
{
    if (!this->spadeEncedDecay) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            sprites.getSpadeCounter() = 0;
            sprites.getEntityViewerCounter() = 26;
            sprites.text.setString("*You notice a strange woman ahead wearing a peasants dress... But once you get closer, you recognize the person. It's Spade the jester! You almost didn't recognize her in normal clothes...*\n\n'Hello! It's good to see you two again. I normally wouldn't want to be this far out near the root of the decay but... I have something for you both.'");
            break;
        case 1:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'What would that be?'");
            sprites.answerBoxText[1].setString("2. 'You didn't have to do that.'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Well, you both fight such horrific creatures constantly... so I figured that something practical to both of your survival would be best...'\n\n*She hands out what looks to be a stone made of pure light...* +1 Ancient Smithing Stone");
                break;
            case 1:
                sprites.text.setString("'Well... I wanted to. It's not like I'm neww to anything out here, even if I'd probably be less capable against them now. But anyways, take this...'\n\n*She hands out what looks to be a stone made of pure light...* +1 Ancient Smithing Stone");
                break;
            }
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'It's a smithing stone?'");
            sprites.answerBoxText[1].setString("2. 'This looks so delicate... What do I do with it?'");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'It is a smithing stone. I was told legends of a stone that's capable of making a sword as sharp as the edge of the void itself... Whatever that means exactly...'\n\n*She gives a kind smile before handing it towards you* 'I thought of you two and wanted you both to be safe.' *She hands out what looks to be a stone made of pure light...* +1 Ancient Smithing Stone");
                break;
            case 1:
                sprites.text.setString("'Well... I wanted to. It's not like I'm new to anything out here, even if I'd probably be less capable against them now. But anyways, take this...'\n\n*She hands out what looks to be a stone made of pure light...* +1 Ancient Smithing Stone");
                break;
            }
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Well, I appreciate it. This will certainly be of great use I'm sure.'");
            sprites.answerBoxText[1].setString("2. 'This will help with slaying the abominations that lay ahead.'");
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("*She gives a warm smile back to you.* 'I'm glad to hear that. And thanks again for uh- having patience with me when I was insane. That must have taken a lot of effort...'");
            break;
        case 7:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'Don't mention it.'");
            sprites.answerBoxText[1].setString("2. 'It was a pain in the ass and so are you.'");
            break;
        case 8:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("'Well, I'm going to go back to safer territory now. Best of luck you two. I truly hope you both will be what this world needs.'");
                break;
            case 1:
                sprites.text.setString("*She awkwardly laughs, seeming to take your sudden outburst as a joke. Or perhaps she simply doesn't want to acknowledge what you said...* 'Well, I'm going to go back to safer territory now. Best of luck you two. I truly hope you both will be what this world needs.'");
                break;
            }
            break;
        case 9:
            sprites.getSpadeCounter() = 0;
            sprites.getEntityViewerCounter() = -1;
            sprites.text.setString("And with that, you watch what seemed like an absolutely insane, irrate jester walk off as a normal and kind girl. You take it as a lesson to not judge books by their covers...*\n\n*Until you remember all the horrific shit you've fought that definitely looks like their goddamn cover. Fuck life lessons here, let's just get out alive.*");
            break;
        case 10:
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->spadeEncedDecay = true;
            break;
        }
    }
}

void Event::decaySpadeEncPoison(Sprites& sprites)
{
    if (!this->spadeEncedDecayPoison) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            //sprites.getSpadeCounter() = 0; //Normal Look
            sprites.getEntityViewerCounter() = 27;
            sprites.text.setString("*You notice a familiar jester sitting close in the distance next to a tree... It's Spade. You quickly prepare yourself to defend Zin if necessary, however it seems the jester is occupied with... digging in the dirt?*'");
            break;
        case 1:
            sprites.getSpadeCounter() = 5; //Insane Stare
            sprites.text.setString("*Suddenly, she notices you. You feel uneasy as she stares at you, not a word coming out of her mouth...*");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'What are you doing?'");
            sprites.answerBoxText[1].setString("2. 'Damn, bitch! Fuck you looking crazy for?!'");
            break;
        case 3:
            sprites.getSpadeCounter() = 6; //Extra Insane Stare
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("*She doesn't reply, instead she simply stares at you even harder. It almost looks like her eyes are about to pop out of her head...*\n\n*You notice the hole in the ground she was digging has a half eaten worm sticking out of it. She was eating crimson insects.*");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. *Attempt to leave*");
            sprites.answerBoxText[1].setString("2. 'If we go, will you leave us be?'");
            break;
        case 5:
            sprites.getSpadeCounter() = 2; //Happy
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.text.setString("*She suddenly changes entirely, following you as a smile appears on her face.* 'Hey hey hey, where are you going so fast? It's been a minute since I've seen you!'");
                break;
            case 1:
                sprites.text.setString("*A smile slowly appears across her face as she stares at you* 'Hey pal, why would you leave so quickly? It's been a minute since we've seen each other!'");
                break;
            }
            break;
        case 6:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'What is wrong with you?'");
            sprites.answerBoxText[1].setString("2. 'Were you eating bugs?'");
            break;
        case 7:
            sprites.getShowAnsBoxesCounter() = -1;
            switch (this->choiceCounter) {
            case 0:
                sprites.getSpadeCounter() = 6; //Extra Insane Stare
                sprites.text.setString("*She replies very bluntly, clearly bothered by your question.* 'Nothing.'");
                break;
            case 1:
                sprites.getSpadeCounter() = 6; //Extra Insane Stare
                sprites.text.setString("*She replies very bluntly, clearly bothered by your question.* 'No.'");
                break;
            }
            break;
        case 8:
            sprites.getZinCounter() = 2; //Zin gets concerned and appears
            sprites.text.setString("'You're clearly just tempting me by standing there, you know that? The meat on your bones. Don't even get me started with the kid. Though she doesn't have nearly as much.'");
            break;
        case 9:
            sprites.getZinCounter() = 5; //Zin gets scared
            sprites.text.setString("*Before you can reply back, the jester continues to ramble...*\n\n'I never enjoyed it in the beginning. The smell, the taste... Rotting flesh is fucking disgusting. Well, it was... But soon enough the aroma began to dance into my nose. By god...'");
            break;
        case 10:
            sprites.text.setString("*She continues to look you up and down as she steps towards you both...* 'I'm just wondering which one of you will taste better...'\n\n*Zin is clearly frightened, stepping behind you as she speaks up.* 'I knew she was nuts but she's fucking lost it! What do we do, what do we do?!'\n\n*The jester begins to slowly transform into a horrifying creature. Once a shadow of herself, she now stands taller and shrouded in melting decay.*");
            break;
        case 11:
            sprites.getZinCounter() = 0; //Zin gets her confidence back
            sprites.text.setString("*You take a step forwards, planting your feet in the floor and pulling your weapon in front.* 'Nothing we haven't taken on before, Zin. Just another fucking monster.'\n\n*Your words seem to bring confidence into Zin as she steps forwards closer to you, preparing her spells. It's do or die...*");
            break;
        case 12:
            sprites.getEventAssets() = false;
            sprites.text.setString("");
            this->reInitialize = true;//Reset dialogue counter for other events
            this->spadeEncedDecayPoison = true;
            break;
        }
    }
}

//Final Events
void Event::rotBeastEnc(Sprites& sprites)
{
    if (!this->rotBeastEnced) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            sprites.getEntityViewerCounter() = 30;
            sprites.getHostileCounter() = 18;
            sprites.text.setString("*As you and Zin step forwards through the treacherous crimson terrain, it comes into view. The Rot Beast. A horrifying abomination standing so tall that it seems impossible for a living organism.*\n\n*You feel a fear within yourself rising by the second, however you choke those fears down as you step forwards.*");
            break;
        case 1:
            sprites.getZinCounter() = 0;
            sprites.text.setString("'So that's what we've been hunting this whole time?'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'It is.'");
            sprites.answerBoxText[1].setString("2. 'Unfortunately...'");
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("*Zin looks to you, her determination seeming shaken.*\n\n'Can I be honest with you? I know we've faced a lot of shit, but this time around... I'm scared. Should we turn back? Does this fear mean we'll die?'");
            break;
        case 4:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'If not for fear, we would simply charge to our deaths like fools. Though this time around, we must be the fools. Millions have died to this thing. It's time to avenge them.'");
            sprites.answerBoxText[1].setString("2. 'To have fear facing such a monstrosity merely means you're human. Choke down the fear and allow us to end this suffering...'");
            break;
        case 5:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("*Zin takes a deep breath as she stands next to you. The only sound filling the air being the loud slow steps of the abomination walking towards the two of you.*\n\nThe beast only knows those that run, though oddly, it has finally encountered two souls that stand before it without trembling. The creature feels a fear slowly growing within it. It sees these two as a threat to its life. For once in its life, it is no longer the predator...");
            break;
        case 6:
            sprites.text.setString("*Yourself and Zin step forwards, killing all fear and zoning into yet another fight your lives. One last push...*");
            break;
        case 7:
            sprites.getZinCounter() = -1;
            sprites.text.setString("");
            sprites.getEventAssets() = false;
            this->reInitialize = true;//Reset dialogue counter for other events
            this->rotBeastEnced = true;
            break;
        }
    }
}

void Event::playerDeathEnding(Sprites& sprites)
{
    if (!this->playerDeathEnced) {
        this->reInit(sprites);
        switch (this->dialogue) {
        case 0:
            this->hideOpenAssets(sprites);
            sprites.getPlayerCounter() = 4;
            sprites.text.setString("*You slam against the floor from the last blow, feeling that something is most certainly wrong. You've been hit with many attacks throughout your life, but this felt very different.*\n\n*You instinctively try to stand, only to immediately collapse back onto the floor.*");
            break;
        case 1:
            sprites.getZinCounter() = 5;
            sprites.text.setString("*Zin turns in shock as she notices how grievously wounded that last attack has left you.* 'What's broken?!'");
            break;
        case 2:
            sprites.getShowAnsBoxesCounter() = 0; //Set dialogue options to appear
            sprites.answerBoxText[0].setString("1. 'My legs? Or my arms?'");
            sprites.answerBoxText[1].setString("2. 'Everything I think?'");
            break;
        case 3:
            sprites.getShowAnsBoxesCounter() = -1;
            sprites.text.setString("*You try to speak only for the words attempting to come from your tongue failing you. Only blood pours from your mouth, blackness slowly taking over as you watch Zin rush to your aid.*");
            break;
        }
    }
}