#pragma once

#include "MapCore.h"
#include "Button.h"
#include "Rectangle.h"
#include "Text.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

class MapViewer
{
public:
    MapViewer();
    ~MapViewer() = default;

    // Non-copyable
    MapViewer(const MapViewer&) = delete;
    MapViewer& operator=(const MapViewer&) = delete;

    // Core
    void update(const sf::Vector2f& mousePos, bool moveRight, bool moveLeft);
    void render(sf::RenderTarget* target);

    // Called by MapComponent after MapDatabase is loaded
    void buildFromDatabase();

    // Map tab navigation — MapComponent calls these; unlock gating is internal
    void navigateRight();
    void navigateLeft();

    // Visibility controls (for MapComponent to show/hide the open button)
    void showOpenMapButton();
    void hideOpenMapButton();

    // Getters used by MapComponent
    bool        isHidden()       const;
    bool        isMapSelected()  const;
    std::string getCurrentMapName() const;
    std::string getCurrentMapId()   const;

    // Frame position queries — used to show/hide directional arrows
    bool isAtFrameStart() const { return this->mapFrame <= 0; }
    bool isAtFrameEnd()   const { return this->mapFramesMaxSize >= 0 && this->mapFrame >= this->mapFramesMaxSize; }

    // Event passthrough
    bool rollEventForCurrentMap();
    bool currentEventIsActive() const;

    // ------------------------------------------------------------------
    // Save/Load support
    // ------------------------------------------------------------------
    // Returns the map ids (in mapOrder) that are currently unlocked.
    std::vector<std::string> getUnlockedMapIds() const;

    // Restores unlock state from a save. Any map not in unlockedIds is
    // treated as locked. Newly-unlocked maps get their first area button
    // revealed (mirrors tryUnlockNextMap), though per-area exploration
    // progress within a map isn't restored here — that would need
    // MapCore-level save/restore.
    void setUnlockedMapIds(const std::vector<std::string>& unlockedIds);

    // Jumps directly to a map by id, bypassing the unlock check (the save
    // already represents a previously-valid, unlocked state). Returns
    // false if mapId isn't found in mapOrder.
    bool setCurrentMapById(const std::string& mapId);

private:
    // Map navigation
    // bypassUnlockCheck lets save/load jump to a map regardless of
    // mapUnlocked state (used by setCurrentMapById).
    void navigateToMap(int index, bool bypassUnlockCheck = false);
    bool canNavigateRight() const;
    bool canNavigateLeft()  const;

    // Area logic
    void handleAreaPressed(const std::string& areaId);
    void onAreaExplorationComplete(const std::string& areaId);

    // Frame animation
    void loadAreaFrames(const std::string& framesFile);
    void setFrame(int frame);
    void moveFrames(bool moveRight, bool moveLeft);

    // Unlock logic
    // Returns true if the map at the given order-index is unlocked
    bool isMapUnlocked(int mapOrderIndex) const;
    // Called when a map becomes fully explored — unlocks the next map if conditions are met
    void tryUnlockNextMap(const std::string& completedMapId);

    // Init helpers
    void initRects();
    void initButtons();

    // Update/render helpers
    void updateButtons(const sf::Vector2f& mousePos);
    void renderButtons(sf::RenderTarget* target);
    void renderRects(sf::RenderTarget* target);
    void updateMaps(const sf::Vector2f& mousePos);
    void renderMaps(sf::RenderTarget* target);

    // -----------------------------------------------------------------------
    // Data
    // -----------------------------------------------------------------------

    // Ordered list of map ids matching MapDatabase::getMapOrder()
    std::vector<std::string> mapOrder;

    // One MapCore per map id
    std::map<std::string, std::unique_ptr<MapCore>> maps;

    // Which maps are currently accessible (unlocked)
    std::vector<bool> mapUnlocked;

    // Current position in mapOrder
    int currentMapIndex;

    // Frame playback state
    int  mapFrame;
    int  mapFramesMaxSize;
    bool mapSelected;
    bool areaReset;       // true while a frame sequence is playing
    bool areaEnd;         // true when frame sequence finishes

    // Currently active area id (the one the player is exploring)
    std::string activeAreaId;

    // UI state
    float x, y;
    bool  hidden;

    sf::Clock clock;
    sf::Time  time;
    float     moveTime;

    sf::Sprite  mapIconSprite;   // small map icon always visible
    sf::Texture mapIconTexture;

    sf::Sprite  frameSprite;     // area frame playback sprite
    sf::Texture frameTexture;

    std::unique_ptr<Text> message;

    std::map<std::string, std::unique_ptr<Button>>    buttons;
    std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
};