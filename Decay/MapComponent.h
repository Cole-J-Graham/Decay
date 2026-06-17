#pragma once

#include "MapViewer.h"
#include "Button.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

class MapComponent
{
public:
    MapComponent();
    ~MapComponent() = default;

    // Non-copyable
    MapComponent(const MapComponent&) = delete;
    MapComponent& operator=(const MapComponent&) = delete;

    // Core
    void update(const sf::Vector2f& mousePos, bool moveRight, bool moveLeft);
    void render(sf::RenderTarget* target);

    // Map open/close button visibility
    void showMapButton() { this->mapView->showOpenMapButton(); }
    void hideMapButton() { this->mapView->hideOpenMapButton(); }

    // State queries
    bool        mapIsOpen()      const;
    bool        mapIsSelected()  const;
    std::string getCurrentAreaId() const;
    std::string getCurrentMapId()  const;

    // Event passthrough
    bool rollEvent() { return this->mapView->rollEventForCurrentMap(); }
    bool eventIsActive() const { return this->mapView->currentEventIsActive(); }

    // Frame position — used by TravelState to show/hide directional arrows independently
    bool isAtFrameStart() const { return this->mapView->isAtFrameStart(); }
    bool isAtFrameEnd()   const { return this->mapView->isAtFrameEnd(); }

    // Save/Load support
    std::vector<std::string> getUnlockedMapIds() const { return this->mapView->getUnlockedMapIds(); }
    void setUnlockedMapIds(const std::vector<std::string>& unlockedIds) { this->mapView->setUnlockedMapIds(unlockedIds); }
    bool setCurrentMapById(const std::string& mapId) { return this->mapView->setCurrentMapById(mapId); }

private:
    void initButtons();
    void updateButtons(const sf::Vector2f& mousePos);
    void renderButtons(sf::RenderTarget* target);
    void syncCenterButtonLabel();

    std::unique_ptr<MapViewer> mapView;
    std::map<std::string, std::unique_ptr<Button>> buttons;
};