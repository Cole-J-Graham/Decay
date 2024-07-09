#include "MapViewer.h"
//Constructor and Deconstructor
MapViewer::MapViewer()
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->x = 100;
    this->y = 100;
    this->hidden = true;
    this->map = 0;
    this->mapSprite.setPosition(560, 5);
    this->mapSprite.setScale(0.78, 0.78);
    this->currentMapId = 0;
    this->mapFramesMaxSize = 59;
    this->mapIdMaxSize = -1;
    this->move_time = 0.1f;
    this->mapSelected = false;
    this->areaEnd = false;
    this->areaReset = false;

    //Initialization
    this->initRects();
    this->initButtons();
}

MapViewer::~MapViewer()
{
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }

    //Delete Maps
    auto im = this->maps.begin();
    for (im = this->maps.begin(); im != this->maps.end(); ++im) {
        delete im->second;
    }
}

//Core Functions
void MapViewer::update(const sf::Vector2f mousePos)
{
    this->updateButtons(mousePos);
    this->updateMaps(mousePos);
    this->move();
    this->detectAreaEnd();
    this->detectNewArea(this->maps[currentMapId]->getMapLoadAreaInputs()[0],
        this->maps[currentMapId]->getMapLoadAreaInputs()[1],
        this->maps[currentMapId]->getMapLoadAreaInputs()[2],
        this->maps[currentMapId]->getMapLoadAreaInputs()[3],
        this->maps[currentMapId]->getMapLoadAreaInputs()[4]);
}

void MapViewer::render(sf::RenderTarget* target)
{
    target->draw(this->mapSprite);
    if (!this->hidden) {
        this->renderRects(target);
        this->renderMaps(target);
    }
    this->renderButtons(target);
}

//Map Functions
void MapViewer::updateMaps(const sf::Vector2f mousePos)
{
    this->maps[currentMapId]->update(mousePos);
}

void MapViewer::renderMaps(sf::RenderTarget* target)
{
    this->maps[currentMapId]->render(target);
}

void MapViewer::createMapCore(std::string mapName, int mapId, float scale, std::string mapInput,
    sf::Vector2f pos1, std::string in1, std::string str1, sf::Vector2f pos2, std::string in2,
    std::string str2, sf::Vector2f pos3, std::string in3, std::string str3, sf::Vector2f pos4,
    std::string in4, std::string str4, sf::Vector2f pos5, std::string in5, std::string str5)
{
    this->maps[mapId] = new MapCore(mapName, scale, mapInput,
        sf::Vector2f(pos1), in1, str1,
        sf::Vector2f(pos2), in2, str2,
        sf::Vector2f(pos3), in3, str3,
        sf::Vector2f(pos4), in4, str4,
        sf::Vector2f(pos5), in5, str5);
    this->mapIdMaxSize++;
}

void MapViewer::detectNewArea(std::string in1, std::string in2,
    std::string in3, std::string in4, std::string in5)
{
    if (this->maps[currentMapId]->getButtons()["POS1"]->isPressed()) {
        this->loadMap(in1);
    }
    if (this->maps[currentMapId]->getButtons()["POS2"]->isPressed()) {
        this->loadMap(in2);
    }
    if (this->maps[currentMapId]->getButtons()["POS3"]->isPressed()) {
        this->loadMap(in3);
    }
    if (this->maps[currentMapId]->getButtons()["POS4"]->isPressed()) {
        this->loadMap(in4);
    }
    if (this->maps[currentMapId]->getButtons()["POS5"]->isPressed()) {
        this->loadMap(in5);
    }
}

void MapViewer::detectAreaEnd()
{
    if (this->areaReset) {
        if (this->mapFrame == this->mapFramesMaxSize) {
            this->areaEnd = true;
            if (this->areaEnd) {
                this->increaseButtonsShown();
                std::cout << "HERE" << "\n";
                this->areaEnd = false;
                this->areaReset = false;
            }
        }
    }
}

void MapViewer::move()
{
    if (this->mapSelected) {
        this->time = this->clock.getElapsedTime();
        if (this->time.asSeconds() >= this->move_time) {
            if (this->maps[currentMapId]->event->rightArrowClicked() && this->mapFrame < this->mapFramesMaxSize) {
                this->mapFrame++;
                this->setMapFrame(mapFrame);
                this->maps[currentMapId]->event->eventChance();
                this->clock.restart();
            }
            else if (this->maps[currentMapId]->event->leftArrowClicked() && this->mapFrame > 0) {
                this->mapFrame--;
                this->setMapFrame(mapFrame);
                this->maps[currentMapId]->event->eventChance();
                this->clock.restart();
            }
        }
    }
}

//Rectangle Functions
void MapViewer::initRects()
{
    this->rectangles["MAPVIEWER"] = new Rectangle(this->x, this->y, 400, 400,
        sf::Color::Transparent, sf::Color::White, 1.f, false);
}

void MapViewer::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}

//Button Functions
void MapViewer::initButtons()
{
    this->buttons["OPENMAP"] = new Button(450, 775, 100, 25, 0.5f, this->font, "Map",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void MapViewer::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }

    //Open Map Functionality
    if (this->buttons["OPENMAP"]->isPressed() && this->hidden) {
        this->maps[currentMapId]->setShown();
        this->rectangles["MAPVIEWER"]->show();
        this->hidden = false;
    }
    else if (this->buttons["OPENMAP"]->isPressed() && !this->hidden) {
        this->maps[currentMapId]->setHidden();
        this->rectangles["MAPVIEWER"]->show();
        this->hidden = true;
    }
}

void MapViewer::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

//Asset Functions
void MapViewer::loadMap(std::string file_input)
{
    ifs.open(file_input);
    if (ifs.is_open()) {
        // Clear the map outside the loop if necessary
        this->maps[currentMapId]->clearMap();
        //Reset map frame to make map flow more concise
        this->mapFrame = 0;
        //Set map to selected to safe guard vector subscript errors
        this->getMapSelected() = true;
        this->areaEnd = false;
        this->areaReset = true;

        std::string input;
        while (getline(ifs, input)) {
            // Load texture from file
            this->maps[currentMapId]->loadMap(input);
        }
        ifs.close();
        this->setMapFrame(mapFrame);
    }
    else {
        std::cerr << "Failed to open file: " << file_input << std::endl;
    }
}