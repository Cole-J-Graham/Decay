#include "MapViewer.h"
#include <iostream>

// Constructor and Destructor
MapViewer::MapViewer()
    : x(100),
    y(100),
    hidden(true),
    map(0),
    currentMapId(0),
    mapFramesMaxSize(-1),
    mapIdMaxSize(-1),
    move_time(0.1f),
    mapSelected(false),
    areaEnd(false),
    areaReset(false)
{

    mapSprite.setPosition(560, 5);
    mapSprite.setScale(0.78f, 0.78f);

    // Initialization
    initRects();
    initButtons();
}

MapViewer::~MapViewer() 
{

}

// Core Functions
void MapViewer::update(const sf::Vector2f& mousePos) {
    updateButtons(mousePos);
    updateMaps(mousePos);
    move();
    detectAreaEnd();
    detectNewArea(
        maps[currentMapId]->getMapLoadAreaInputs()[0],
        maps[currentMapId]->getMapLoadAreaInputs()[1],
        maps[currentMapId]->getMapLoadAreaInputs()[2],
        maps[currentMapId]->getMapLoadAreaInputs()[3],
        maps[currentMapId]->getMapLoadAreaInputs()[4]
    );
}

void MapViewer::render(sf::RenderTarget* target) {
    target->draw(mapSprite);
    if (!hidden) {
        renderRects(target);
        renderMaps(target);
    }
    renderButtons(target);
}

// Map Functions
void MapViewer::updateMaps(const sf::Vector2f& mousePos) {
    maps[currentMapId]->update(mousePos);
}

void MapViewer::renderMaps(sf::RenderTarget* target) {
    maps[currentMapId]->render(target);
}

void MapViewer::createMapCore(const std::string& mapName, int mapId, float scale, const std::string& mapInput,
    const sf::Vector2f& pos1, const std::string& in1, const std::string& str1,
    const sf::Vector2f& pos2, const std::string& in2, const std::string& str2,
    const sf::Vector2f& pos3, const std::string& in3, const std::string& str3,
    const sf::Vector2f& pos4, const std::string& in4, const std::string& str4,
    const sf::Vector2f& pos5, const std::string& in5, const std::string& str5)
{
    maps[mapId] = std::make_unique<MapCore>(mapName, scale, mapInput,
        pos1, in1, str1, pos2, in2, str2, pos3, in3, str3,
        pos4, in4, str4, pos5, in5, str5);
    mapIdMaxSize++;
}

void MapViewer::detectNewArea(const std::string& in1, const std::string& in2,
    const std::string& in3, const std::string& in4, const std::string& in5)
{
    if (maps[currentMapId]->getButtons()[0]->isPressed()) {
        loadMap(in1);
    }
    if (maps[currentMapId]->getButtons()[1]->isPressed()) {
        loadMap(in2);
    }
    if (maps[currentMapId]->getButtons()[2]->isPressed()) {
        loadMap(in3);
    }
    if (maps[currentMapId]->getButtons()[3]->isPressed()) {
        loadMap(in4);
    }
    if (maps[currentMapId]->getButtons()[4]->isPressed()) {
        loadMap(in5);
    }
}

void MapViewer::detectAreaEnd() {
    if (areaReset) {
        if (mapFrame == mapFramesMaxSize) {
            areaEnd = true;
            if (areaEnd) {
                if (maps[currentMapId]->getActiveButtonId() == maps[currentMapId]->getLocationsExplored()) {
                    maps[currentMapId]->increaseButtonsShown();
                    maps[currentMapId]->increaseLocationsExplored();
                    areaEnd = false;
                    areaReset = false;
                }
                else {
                    std::cout << "# of Buttons Not Increased due to Area # != locations #" << "\n";
                }
            }
        }
    }
}

void MapViewer::move() {
    if (mapSelected) {
        time = clock.getElapsedTime();
        if (time.asSeconds() >= move_time) {
            if (maps[currentMapId]->event->rightArrowClicked() && mapFrame < mapFramesMaxSize) {
                mapFrame++;
                setMapFrame(mapFrame);
                maps[currentMapId]->event->eventChance();
                clock.restart();
            }
            else if (maps[currentMapId]->event->leftArrowClicked() && mapFrame > 0) {
                mapFrame--;
                setMapFrame(mapFrame);
                maps[currentMapId]->event->eventChance();
                clock.restart();
            }
        }
    }
}

// Rectangle Functions
void MapViewer::initRects() {
    rectangles["MAPVIEWER"] = std::make_unique<Rectangle>(x, y, 400, 400,
        sf::Color::Transparent, sf::Color::White, 1.f, false);
}

void MapViewer::renderRects(sf::RenderTarget* target) {
    for (const auto& it : rectangles) {
        it.second->render(target);
    }
}

// Button Functions
void MapViewer::initButtons() {
    buttons["OPENMAP"] = std::make_unique<Button>(450, 775, 100, 25, 0.5f, "Map",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void MapViewer::updateButtons(const sf::Vector2f& mousePos) {
    for (const auto& it : buttons) {
        it.second->update(mousePos);
    }

    // Open Map Functionality
    if (buttons["OPENMAP"]->isPressed() && hidden) {
        maps[currentMapId]->setShown();
        rectangles["MAPVIEWER"]->show();
        hidden = false;
    }
    else if (buttons["OPENMAP"]->isPressed() && !hidden) {
        maps[currentMapId]->setHidden();
        rectangles["MAPVIEWER"]->show();
        hidden = true;
    }
}

void MapViewer::renderButtons(sf::RenderTarget* target) {
    for (const auto& it : buttons) {
        it.second->render(target);
    }
}

// Asset Functions
void MapViewer::loadMap(const std::string& file_input) {
    mapFramesMaxSize = -1;
    std::ifstream ifs(file_input);
    if (ifs.is_open()) {
        // Clear the map outside the loop if necessary
        maps[currentMapId]->clearMap();
        // Reset map frame to make map flow more concise
        mapFrame = 0;
        // Set map to selected to safeguard vector subscript errors
        mapSelected = true;
        areaEnd = false;
        areaReset = true;

        std::string input;
        while (std::getline(ifs, input)) {
            // Load texture from file
            maps[currentMapId]->loadMap(input);
            mapFramesMaxSize++;
        }
        ifs.close();
        setMapFrame(mapFrame);
    }
    else {
        std::cerr << "Failed to open file: " << file_input << std::endl;
    }
}
