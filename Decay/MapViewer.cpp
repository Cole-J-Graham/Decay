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
    this->mapMaxSize = 60;
    this->move_time = 0.5f;

    //Initialization
    this->event = new EventModule();
    this->initRects();
    this->initButtons();
}

MapViewer::~MapViewer()
{
    delete this->event;
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
    //Delete Maps
    while (!maps.empty()) {
        MapCore* obj = maps.top();
        maps.pop();
        delete obj;
    }
}

//Core Functions
void MapViewer::update(const sf::Vector2f mousePos)
{
    this->event->update(mousePos);
    this->updateButtons(mousePos);
    this->updateMaps(mousePos);
    this->move();
    this->detectNewArea(this->maps.top()->getMapPositionsContainer()[0],
        this->maps.top()->getMapPositionsContainer()[1],
        this->maps.top()->getMapPositionsContainer()[2],
        this->maps.top()->getMapPositionsContainer()[3],
        this->maps.top()->getMapPositionsContainer()[4]);
}

void MapViewer::render(sf::RenderTarget* target)
{
    target->draw(this->mapSprite);
    if (!this->hidden) {
        this->renderRects(target);
        this->renderMaps(target);
    }
    this->event->render(target);
    this->renderButtons(target);
}

//Map Functions
void MapViewer::updateMaps(const sf::Vector2f mousePos)
{
    this->maps.top()->update(mousePos);
}

void MapViewer::renderMaps(sf::RenderTarget* target)
{
    this->maps.top()->render(target);
}

void MapViewer::createMapCore(float scale, std::string mapInput,
    sf::Vector2f pos1, std::string in1, std::string str1, sf::Vector2f pos2, std::string in2,
    std::string str2, sf::Vector2f pos3, std::string in3, std::string str3, sf::Vector2f pos4,
    std::string in4, std::string str4, sf::Vector2f pos5, std::string in5, std::string str5)
{
    this->maps.push(new MapCore(scale, mapInput,
        sf::Vector2f(pos1), in1, str1,
        sf::Vector2f(pos2), in2, str2,
        sf::Vector2f(pos3), in3, str3,
        sf::Vector2f(pos4), in4, str4,
        sf::Vector2f(pos5), in5, str5));
}

void MapViewer::changeMap(MapCore* input)
{
    if (!this->maps.empty()) {
        delete this->maps.top();
        this->maps.pop();
    }
    this->maps.push(input);
}

void MapViewer::detectNewArea(std::string in1, std::string in2,
    std::string in3, std::string in4, std::string in5)
{
    if (this->maps.top()->getButtons()["POS1"]->isPressed()) {
        this->loadMap(in1);
    }
    if (this->maps.top()->getButtons()["POS2"]->isPressed()) {
        this->loadMap(in2);
    }
    if (this->maps.top()->getButtons()["POS3"]->isPressed()) {
        this->loadMap(in3);
    }
    if (this->maps.top()->getButtons()["POS4"]->isPressed()) {
        this->loadMap(in4);
    }
    if (this->maps.top()->getButtons()["POS5"]->isPressed()) {
        this->loadMap(in5);
    }
}

void MapViewer::move()
{
    this->time = this->clock.getElapsedTime();
    if (this->time.asSeconds() >= this->move_time) {
        if (this->mapFrame != this->getMapMaxSize() + 1) {
            if (this->event->userInput->rightArrowClicked()) {
                this->mapFrame++;
                this->setMapFrame(mapFrame);
                this->clock.restart();
            }
            if (this->event->userInput->leftArrowClicked()) {
                this->mapFrame--;
                this->setMapFrame(mapFrame);
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
        this->maps.top()->setShown();
        this->rectangles["MAPVIEWER"]->show();
        this->hidden = false;
    }
    else if (this->buttons["OPENMAP"]->isPressed() && !this->hidden) {
        this->maps.top()->setHidden();
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
        this->maps.top()->clearMap();

        std::string input;
        while (getline(ifs, input)) {
            // Load texture from file
            this->maps.top()->loadMap(input);
        }
        ifs.close();
        this->setMapFrame(mapFrame);
    }
    else {
        std::cerr << "Failed to open file: " << file_input << std::endl;
    }
}