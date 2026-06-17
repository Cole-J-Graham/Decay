#pragma once

// ---------------------------------------------------------------------------
// IntroState
//
// Plays a fullscreen slideshow before the game begins.
// Each slide is a fullscreen image with an optional text caption.
// Click, Space, or Enter advances. ESC skips the entire intro.
// When all slides are done, IntroState pops itself and pushes TravelState.
//
// Slide file format (Assets/Intro/intro.txt):
//
//   [SLIDE]
//   IMAGE: Assets/Intro/slide1.png
//   TEXT: The world did not end all at once...
//
//   [SLIDE]
//   IMAGE: Assets/Intro/slide2.png
//   TEXT: It decayed. Slowly. Then all at once.
//
// IMAGE is required. TEXT is optional.
// ---------------------------------------------------------------------------

#include "State.h"
#include "Text.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

class IntroState : public State
{
public:
    IntroState(sf::RenderWindow* window, std::stack<State*>* states,
        const std::string& slideFilePath = "Assets/Intro/intro.txt");
    ~IntroState() = default;

    // State interface
    void endState();
    void updateKeybinds();
    void update();
    void render(sf::RenderTarget* target = nullptr);

private:
    struct Slide
    {
        std::string imagePath;
        std::string text;
    };

    void loadSlides(const std::string& path);
    void applySlide(int index);
    void advance();
    bool advancePressed() const;
    void launchGame();

private:
    std::vector<Slide>   slides;
    int                  currentIndex = 0;

    sf::Texture          slideTexture;
    sf::Sprite           slideSprite;
    bool                 textureLoaded = false;

    // Bottom overlay so caption text is readable over bright images
    sf::RectangleShape   textOverlay;

    // Caption and hint — use your Text class so they pick up ticker_font
    std::unique_ptr<Text> captionText;
    std::unique_ptr<Text> hintText;

    // Fade overlay
    sf::RectangleShape   fadeRect;
    float                fadeAlpha = 255.f;
    bool                 fadingIn = true;
    bool                 fadingOut = false;
    sf::Clock            fadeClock;
    static constexpr float kFadeDuration = 0.6f;

    // Edge-detect for input
    bool                 mouseWasDown = false;
    bool                 spaceWasDown = false;
    bool                 enterWasDown = false;

    bool                 finished = false;
};