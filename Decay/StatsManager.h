#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
#include"StatsModule.h"

class StatsManager {
public:
    //Constructors and Destructors
    StatsManager();
    ~StatsManager();

    //Core Functions
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    void createInstance(std::string id);

    //Button Functions
    void updateButtons(const sf::Vector2f mousePos);

    //Modifiers
    void setHidden() { this->hidden = true; };
    void setShown() { this->hidden = false; };

private:

    bool hidden;

    sf::Font font;
    std::map<std::string, Button*> buttons;
    std::unordered_map<std::string, std::unique_ptr<StatsModule>> stats;
};