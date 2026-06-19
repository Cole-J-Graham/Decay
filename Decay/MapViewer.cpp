#include "MapViewer.h"
#include "MapDatabase.h"
#include "AssetDatabase.h"
#include "CharacterManager.h"
#include "TriggerManager.h"

#include <iostream>

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------

MapViewer::MapViewer()
    : currentMapIndex(0)
    , mapFrame(0)
    , mapFramesMaxSize(-1)
    , mapSelected(false)
    , areaReset(false)
    , areaEnd(false)
    , moveTime(0.1f)
{
    this->message = std::make_unique<Text>(16, "Cannot travel with no party members!",
        sf::Color::White, true, 5);

    this->mapIconSprite.setPosition(560, 5);
    this->mapIconSprite.setScale(0.78f, 0.78f);

    this->frameSprite.setPosition(560, 5);
    this->frameSprite.setScale(0.78f, 0.78f);
}

// ---------------------------------------------------------------------------
// Build from database — call this after MapDatabase::loadFromFile()
// ---------------------------------------------------------------------------

void MapViewer::buildFromDatabase()
{
    const auto& db = MapDatabase::getInstance();
    this->mapOrder = db.getMapOrder();

    this->maps.clear();
    this->mapUnlocked.clear();
    this->mapUnlocked.resize(this->mapOrder.size(), false);

    for (int i = 0; i < static_cast<int>(this->mapOrder.size()); ++i) {
        const std::string& mapId = this->mapOrder[i];
        const MapDefinition* mapDef = db.getMap(mapId);

        if (!mapDef) {
            std::cerr << "MapViewer: MapDatabase has no definition for mapId: " << mapId << "\n";
            continue;
        }

        auto areaDefs = db.getAreasForMap(mapId);
        this->maps[mapId] = std::make_unique<MapCore>(*mapDef, areaDefs);

        // A map is unlocked at startup if its unlock condition is "none"
        if (mapDef->unlockCondition == "none") {
            this->mapUnlocked[i] = true;
        }
    }

    // Ensure index is valid
    this->currentMapIndex = 0;

    // Map view is always open now — show the starting map immediately
    // instead of waiting for a button press that no longer exists.
    if (!this->mapOrder.empty()) {
        auto it = this->maps.find(this->mapOrder[this->currentMapIndex]);
        if (it != this->maps.end()) {
            it->second->show();
        }
    }
}

// ---------------------------------------------------------------------------
// Core update/render
// ---------------------------------------------------------------------------

void MapViewer::update(const sf::Vector2f& mousePos, bool moveRight, bool moveLeft)
{
    // Map view is always open now, so this can't be gated behind a button
    // press anymore — check every frame instead. Message text only needs
    // to be set once when the empty state is first detected.
    const bool partyEmpty = CharacterManager::getInstance().getParty().size() <= 0;
    if (partyEmpty && !this->partyEmptyLastFrame) {
        this->message->setShown();
        this->message->setString("Cannot travel with no party members!");
    }
    this->partyEmptyLastFrame = partyEmpty;

    this->updateMaps(mousePos);
    this->moveFrames(moveRight, moveLeft);

    // Check if the current map has an area button pressed
    if (!this->mapOrder.empty()) {
        const std::string& currentMapId = this->mapOrder[this->currentMapIndex];
        auto it = this->maps.find(currentMapId);
        if (it != this->maps.end()) {
            std::string pressedArea = it->second->getPressedAreaId();
            if (!pressedArea.empty()) {
                this->handleAreaPressed(pressedArea);
            }
        }
    }

    // Detect frame sequence completion
    if (this->areaReset && this->mapFrame == this->mapFramesMaxSize) {
        this->onAreaExplorationComplete(this->activeAreaId);
    }
}

void MapViewer::render(sf::RenderTarget* target)
{
    target->draw(this->mapIconSprite);

    this->renderMaps(target);

    // Draw frame playback sprite if an area is being explored
    if (this->mapSelected) {
        target->draw(this->frameSprite);
    }

    this->message->render(target);
}

void MapViewer::navigateRight()
{
    if (this->canNavigateRight()) {
        this->navigateToMap(this->currentMapIndex + 1);
    }
}

void MapViewer::navigateLeft()
{
    if (this->canNavigateLeft()) {
        this->navigateToMap(this->currentMapIndex - 1);
    }
}


void MapViewer::navigateToMap(int index, bool bypassUnlockCheck)
{
    if (index < 0 || index >= static_cast<int>(this->mapOrder.size())) return;
    if (!bypassUnlockCheck && !this->isMapUnlocked(index)) return;
    if (index == this->currentMapIndex) return; // no-op if already here (e.g. load onto starting map)

    // Hide current
    const std::string& currentId = this->mapOrder[this->currentMapIndex];
    auto currentIt = this->maps.find(currentId);
    if (currentIt != this->maps.end()) {
        currentIt->second->hide();
    }

    this->currentMapIndex = index;

    // Show new
    const std::string& newId = this->mapOrder[this->currentMapIndex];
    auto newIt = this->maps.find(newId);
    if (newIt != this->maps.end()) {
        newIt->second->show();
    }
}

bool MapViewer::canNavigateRight() const
{
    int next = this->currentMapIndex + 1;
    return next < static_cast<int>(this->mapOrder.size()) && this->isMapUnlocked(next);
}

bool MapViewer::canNavigateLeft() const
{
    return this->currentMapIndex > 0 && this->isMapUnlocked(this->currentMapIndex - 1);
}

// ---------------------------------------------------------------------------
// Area logic
// ---------------------------------------------------------------------------

void MapViewer::handleAreaPressed(const std::string& areaId)
{
    const std::string& currentMapId = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(currentMapId);
    if (it == this->maps.end()) return;

    const std::string framesFile = it->second->getFramesFileForArea(areaId);
    if (framesFile.empty()) {
        std::cerr << "MapViewer: no frames file for area: " << areaId << "\n";
        return;
    }

    this->activeAreaId = areaId;
    this->loadAreaFrames(framesFile);
}

void MapViewer::onAreaExplorationComplete(const std::string& areaId)
{
    if (areaId.empty()) return;

    const std::string& currentMapId = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(currentMapId);
    if (it == this->maps.end()) return;

    MapCore* core = it->second.get();

    // Avoid double-counting if somehow called again before reset
    if (core->isAreaExplored(areaId)) return;

    core->markAreaExplored(areaId);
    core->revealNextAreaButton();

    // Check if this completes the entire map
    if (core->isFullyExplored()) {
        this->tryUnlockNextMap(currentMapId);
    }

    // Reset frame playback state
    this->areaEnd = false;
    this->areaReset = false;
    this->activeAreaId.clear();
}

// ---------------------------------------------------------------------------
// Frame animation
// ---------------------------------------------------------------------------

void MapViewer::loadAreaFrames(const std::string& framesFile)
{
    const std::string& currentMapId = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(currentMapId);
    if (it == this->maps.end()) return;

    it->second->loadFrames(framesFile);
    const auto& frames = it->second->getFrames();

    if (frames.empty()) {
        std::cerr << "MapViewer: no frames loaded from: " << framesFile << "\n";
        return;
    }

    this->mapFramesMaxSize = static_cast<int>(frames.size()) - 1;
    this->mapFrame = 0;
    this->mapSelected = true;
    this->areaEnd = false;
    this->areaReset = true;

    this->setFrame(this->mapFrame);
}

void MapViewer::setFrame(int frame)
{
    const std::string& currentMapId = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(currentMapId);
    if (it == this->maps.end()) return;

    const auto& frames = it->second->getFrames();
    if (frame < 0 || frame >= static_cast<int>(frames.size())) return;

    // frames[frame] is now an asset id (registered in assets.db), not a
    // raw file path — load via AssetDatabase's cache instead of disk.
    try {
        this->frameSprite.setTexture(AssetDatabase::getInstance().getTexture(frames[frame]));
    }
    catch (const std::exception& e) {
        std::cerr << "MapViewer: failed to load frame asset \"" << frames[frame]
            << "\": " << e.what() << "\n";
    }
}

void MapViewer::moveFrames(bool moveRight, bool moveLeft)
{
    if (!this->mapSelected) return;

    this->time = this->clock.getElapsedTime();
    if (this->time.asSeconds() < this->moveTime) return;

    if (moveRight && this->mapFrame < this->mapFramesMaxSize) {
        this->mapFrame++;
        this->setFrame(this->mapFrame);
        this->clock.restart();
    }
    else if (moveLeft && this->mapFrame > 0) {
        this->mapFrame--;
        this->setFrame(this->mapFrame);
        this->clock.restart();
    }
}

// ---------------------------------------------------------------------------
// Unlock logic
// ---------------------------------------------------------------------------

bool MapViewer::isMapUnlocked(int mapOrderIndex) const
{
    if (mapOrderIndex < 0 || mapOrderIndex >= static_cast<int>(this->mapUnlocked.size())) {
        return false;
    }
    return this->mapUnlocked[mapOrderIndex];
}

void MapViewer::tryUnlockNextMap(const std::string& completedMapId)
{
    const auto& db = MapDatabase::getInstance();

    // Walk through mapOrder and unlock any map whose unlockCondition == completedMapId
    for (int i = 0; i < static_cast<int>(this->mapOrder.size()); ++i) {
        const MapDefinition* def = db.getMap(this->mapOrder[i]);
        if (def && def->unlockCondition == completedMapId) {
            if (!this->mapUnlocked[i]) {
                this->mapUnlocked[i] = true;

                // Reveal the first area button of the newly unlocked map
                auto it = this->maps.find(this->mapOrder[i]);
                if (it != this->maps.end()) {
                    it->second->revealNextAreaButton();
                }

                std::cout << "MapViewer: unlocked map \"" << this->mapOrder[i] << "\"\n";

                // Fire the unlock notification trigger.
                // Key pattern: "map_unlocked:<displayName>"
                // Registrations live in GameTriggers.cpp.
                const MapDefinition* newDef = db.getMap(this->mapOrder[i]);
                if (newDef) {
                    TriggerManager::getInstance().fire("map_unlocked:" + newDef->name);
                }

            }
        }
    }
}

// ---------------------------------------------------------------------------
// Visibility
// ---------------------------------------------------------------------------

// The map view is always open now — kept for API compatibility with
// MapComponent::mapIsOpen(), which callers still use to mean "the map
// view is currently visible," which is now unconditionally true.
bool MapViewer::isHidden()      const { return false; }
bool MapViewer::isMapSelected() const { return this->mapSelected; }

std::string MapViewer::getCurrentMapId() const
{
    if (this->mapOrder.empty()) return "";
    return this->mapOrder[this->currentMapIndex];
}


std::string MapViewer::getCurrentMapName() const
{
    if (this->mapOrder.empty()) return "";
    const std::string& id = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(id);
    if (it == this->maps.end()) return "";
    return it->second->getMapName();
}

// ---------------------------------------------------------------------------
// Event passthrough
// ---------------------------------------------------------------------------

bool MapViewer::rollEventForCurrentMap()
{
    if (this->mapOrder.empty()) return false;
    const std::string& id = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(id);
    if (it == this->maps.end() || !it->second) return false;
    return it->second->rollEvent();
}

bool MapViewer::currentEventIsActive() const
{
    if (this->mapOrder.empty()) return false;
    const std::string& id = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(id);
    if (it == this->maps.end() || !it->second) return false;
    return it->second->isEventActive();
}

// ---------------------------------------------------------------------------
// Update/render helpers
// ---------------------------------------------------------------------------

void MapViewer::updateMaps(const sf::Vector2f& mousePos)
{
    if (this->mapOrder.empty()) return;
    const std::string& id = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(id);
    if (it != this->maps.end()) it->second->update(mousePos);
}

void MapViewer::renderMaps(sf::RenderTarget* target)
{
    if (this->mapOrder.empty()) return;
    const std::string& id = this->mapOrder[this->currentMapIndex];
    auto it = this->maps.find(id);
    if (it != this->maps.end()) it->second->render(target);
}

// ---------------------------------------------------------------------------
// Save/Load support
// ---------------------------------------------------------------------------

std::vector<std::string> MapViewer::getUnlockedMapIds() const
{
    std::vector<std::string> result;

    for (size_t i = 0; i < this->mapOrder.size(); ++i) {
        if (i < this->mapUnlocked.size() && this->mapUnlocked[i]) {
            result.push_back(this->mapOrder[i]);
        }
    }

    return result;
}

void MapViewer::setUnlockedMapIds(const std::vector<std::string>& unlockedIds)
{
    for (size_t i = 0; i < this->mapUnlocked.size(); ++i) {
        this->mapUnlocked[i] = false;
    }

    for (const std::string& id : unlockedIds) {
        for (size_t i = 0; i < this->mapOrder.size(); ++i) {
            if (this->mapOrder[i] == id) {
                this->mapUnlocked[i] = true;

                // Reveal at least the first area button so a freshly-rebuilt
                // MapCore (post-load) isn't unlocked but buttonless.
                // NOTE: doesn't restore per-area exploration progress within
                // the map — that would need MapCore-level save/restore.
                auto it = this->maps.find(id);
                if (it != this->maps.end()) {
                    it->second->revealNextAreaButton();
                }

                break;
            }
        }
    }
}

bool MapViewer::setCurrentMapById(const std::string& mapId)
{
    for (int i = 0; i < static_cast<int>(this->mapOrder.size()); ++i) {
        if (this->mapOrder[i] == mapId) {
            this->navigateToMap(i, true);
            return true;
        }
    }

    return false;
}