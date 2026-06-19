#include "MapCore.h"
#include "AssetDatabase.h"

#include <fstream>
#include <iostream>
#include <algorithm>

MapCore::MapCore(const MapDefinition& mapDef,
    const std::vector<const AreaDefinition*>& areaDefs)
    : hidden(true)
    , buttonsRevealed(1)   // First area is always visible at start
{
    this->mapId = mapDef.mapId;
    this->mapName = mapDef.name;

    // Load background map image via AssetDatabase (cached, id-based) instead
    // of loading the file directly. AssetDatabase::getTexture() throws on a
    // missing/invalid id, so this is wrapped to preserve the previous
    // log-and-continue behavior rather than crashing on a bad data entry.
    try {
        this->mapSprite.setTexture(AssetDatabase::getInstance().getTexture(mapDef.mapImageId));
    }
    catch (const std::exception& e) {
        std::cerr << "MapCore: failed to load map image asset \"" << mapDef.mapImageId
            << "\": " << e.what() << "\n";
    }

    this->mapSprite.setPosition(100, 100);
    this->mapSprite.setScale(mapDef.scale, mapDef.scale);

    // Build area states from definitions (already sorted by areaIndex by MapDatabase)
    this->initButtons(areaDefs);

    this->event = std::make_unique<EventManager>(std::string(this->mapName));
}

// ---------------------------------------------------------------------------
// Core
// ---------------------------------------------------------------------------

void MapCore::update(const sf::Vector2f& mousePos)
{
    if (!this->hidden) {
        for (auto& state : this->areaStates) {
            state.button->update(mousePos);
        }
        this->refreshButtonVisibility();
    }

    this->event->update(mousePos);
}

void MapCore::render(sf::RenderTarget* target)
{
    if (!this->hidden) {
        target->draw(this->mapSprite);

        for (int i = 0; i < static_cast<int>(this->areaStates.size()); ++i)
        {
            const auto& state = this->areaStates[i];
            state.button->render(target);

            if (i >= this->buttonsRevealed) continue;

            // Position indicator above the button using stored coords
            const float cx = state.buttonX;
            const float indicatorY = state.buttonY - 10.f;

            if (state.explored)
            {
                // Small muted green circle — explored
                sf::CircleShape dot(4.f);
                dot.setFillColor(sf::Color(90, 150, 110, 180));
                dot.setPosition(cx - 4.f, indicatorY - 4.f);
                target->draw(dot);
            }
            else if (i == this->buttonsRevealed - 1)
            {
                // Muted amber diamond — frontier / next area
                sf::CircleShape diamond(6.f, 4);
                diamond.setFillColor(sf::Color(210, 165, 70, 210));
                diamond.setRotation(45.f);
                diamond.setPosition(cx - 6.f, indicatorY - 6.f);
                target->draw(diamond);
            }
        }
    }

    this->event->render(target);
}

// ---------------------------------------------------------------------------
// Visibility
// ---------------------------------------------------------------------------

void MapCore::show() { this->hidden = false; }
void MapCore::hide() { this->hidden = true; }
bool MapCore::isHidden() const { return this->hidden; }

// ---------------------------------------------------------------------------
// Frame loading
// ---------------------------------------------------------------------------

void MapCore::loadFrames(const std::string& framesFile)
{
    this->frameContainer.clear();

    std::ifstream ifs(framesFile);
    if (!ifs.is_open()) {
        std::cerr << "MapCore: failed to open frames file: " << framesFile << "\n";
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (!line.empty()) {
            this->frameContainer.push_back(line);
        }
    }
}

void MapCore::clearFrames()
{
    this->frameContainer.clear();
}

const std::vector<std::string>& MapCore::getFrames() const
{
    return this->frameContainer;
}

// ---------------------------------------------------------------------------
// Area button queries
// ---------------------------------------------------------------------------

std::string MapCore::getPressedAreaId() const
{
    for (const auto& state : this->areaStates) {
        if (state.button->isPressed()) {
            return state.areaId;
        }
    }
    return "";
}

std::string MapCore::getFramesFileForArea(const std::string& areaId) const
{
    for (const auto& state : this->areaStates) {
        if (state.areaId == areaId) {
            return state.framesFile;
        }
    }
    return "";
}

// ---------------------------------------------------------------------------
// Progression
// ---------------------------------------------------------------------------

void MapCore::markAreaExplored(const std::string& areaId)
{
    for (auto& state : this->areaStates) {
        if (state.areaId == areaId) {
            state.explored = true;
            return;
        }
    }
    std::cerr << "MapCore::markAreaExplored — unknown areaId: " << areaId << "\n";
}

bool MapCore::isAreaExplored(const std::string& areaId) const
{
    for (const auto& state : this->areaStates) {
        if (state.areaId == areaId) {
            return state.explored;
        }
    }
    return false;
}

bool MapCore::isFullyExplored() const
{
    for (const auto& state : this->areaStates) {
        if (!state.explored) return false;
    }
    return true;
}

int MapCore::getTotalAreas() const
{
    return static_cast<int>(this->areaStates.size());
}

int MapCore::getExploredCount() const
{
    int count = 0;
    for (const auto& state : this->areaStates) {
        if (state.explored) count++;
    }
    return count;
}

void MapCore::revealNextAreaButton()
{
    // Reveal one more button beyond what's currently shown, up to the total
    if (this->buttonsRevealed < static_cast<int>(this->areaStates.size())) {
        this->buttonsRevealed++;
        this->refreshButtonVisibility();
    }
}

// ---------------------------------------------------------------------------
// Getters
// ---------------------------------------------------------------------------

const std::string& MapCore::getMapId()   const { return this->mapId; }
const std::string& MapCore::getMapName() const { return this->mapName; }

// ---------------------------------------------------------------------------
// Event
// ---------------------------------------------------------------------------

bool MapCore::rollEvent()
{
    if (!this->event) return false;
    return this->event->eventChance();
}

bool MapCore::isEventActive() const
{
    if (!this->event) return false;
    return this->event->isEventActive();
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------

void MapCore::initButtons(const std::vector<const AreaDefinition*>& areaDefs)
{
    // Matches the idle/hover/active palette used by TravelInputComponent
    // and TravelHudComponent so area buttons read as part of the same
    // bottom-bar/panel UI system rather than a separate visual style.
    const sf::Color idle(20, 20, 20, 160);
    const sf::Color hover(80, 80, 80, 255);
    const sf::Color active(10, 10, 10, 200);

    this->areaStates.reserve(areaDefs.size());

    for (const auto* def : areaDefs) {
        AreaState state;
        state.areaId = def->id;
        state.framesFile = def->framesFile;
        state.explored = false;
        state.buttonX = def->buttonX;
        state.buttonY = def->buttonY;
        state.button = std::make_unique<Button>(
            sf::Vector2f(def->buttonX, def->buttonY),
            0, 25.f, 0.5f, def->name,
            idle, hover, active,
            false
        );
        this->areaStates.push_back(std::move(state));
    }
}

void MapCore::refreshButtonVisibility()
{
    for (int i = 0; i < static_cast<int>(this->areaStates.size()); ++i) {
        if (i < this->buttonsRevealed) {
            this->areaStates[i].button->show();
        }
        else {
            this->areaStates[i].button->hide();
        }
    }
}