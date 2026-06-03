#pragma once

#include "MapViewer.h"
#include "Button.h"

#include <map>
#include <memory>
#include <string>

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

private:
    void initButtons();
    void updateButtons(const sf::Vector2f& mousePos);
    void renderButtons(sf::RenderTarget* target);
    void syncCenterButtonLabel();

    std::unique_ptr<MapViewer> mapView;
    std::map<std::string, std::unique_ptr<Button>> buttons;
};