#pragma once

#include "MapTypes.h"
#include "Button.h"
#include "EventManager.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <memory>

class MapCore
{
public:
    explicit MapCore(const MapDefinition& mapDef,
        const std::vector<const AreaDefinition*>& areaDefs);
    ~MapCore() = default;

    // Non-copyable
    MapCore(const MapCore&) = delete;
    MapCore& operator=(const MapCore&) = delete;

    // Core
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);

    // Visibility
    void show();
    void hide();
    bool isHidden() const;

    // Area frame loading — called by MapViewer when the player navigates to an area
    void loadFrames(const std::string& framesFile);
    void clearFrames();
    const std::vector<std::string>& getFrames() const;

    // Area button queries
    // Returns the area id string of whichever area button was just pressed, or "" if none
    std::string getPressedAreaId() const;

    // Returns the frames file path for a given area id (empty string if not found)
    std::string getFramesFileForArea(const std::string& areaId) const;

    // Progression
    void  markAreaExplored(const std::string& areaId);
    bool  isAreaExplored(const std::string& areaId) const;
    bool  isFullyExplored() const;   // all areas explored = this map is "complete"
    int   getTotalAreas() const;
    int   getExploredCount() const;

    // Unlock / lock the next area button — called after an area is completed
    void  revealNextAreaButton();

    // Getters
    const std::string& getMapId()   const;
    const std::string& getMapName() const;

    // Event
    bool rollEvent();
    bool isEventActive() const;

private:
    void initButtons(const std::vector<const AreaDefinition*>& areaDefs);
    void refreshButtonVisibility();

    // Map visuals
    sf::Texture mapTexture;
    sf::Sprite  mapSprite;

    std::string mapId;
    std::string mapName;

    bool hidden;

    // Area data — indexed by area id
    struct AreaState
    {
        std::string         areaId;
        std::string         framesFile;
        std::unique_ptr<Button> button;
        bool                explored;
        float               buttonX = 0.f;
        float               buttonY = 0.f;
    };

    // Ordered by areaIndex so reveal logic is straightforward
    std::vector<AreaState>  areaStates;

    // How many area buttons are currently visible/unlocked
    int buttonsRevealed;

    // Frame images for the currently-loaded area
    std::vector<std::string> frameContainer;

    std::unique_ptr<EventManager> event;
};