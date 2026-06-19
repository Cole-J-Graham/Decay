#include "IntroState.h"
#include "BonfireState.h"
#include "CharacterManager.h"
#include "TravelState.h"
#include "MusicManager.h"
#include "AssetDatabase.h"

#include <fstream>
#include <iostream>

// ── Constructor ───────────────────────────────────────────────────────────

IntroState::IntroState(sf::RenderWindow* window, std::stack<State*>* states,
    MusicPlayer* musicPlayer, const std::string& slideFilePath)
    : State(window, states)
    , musicPlayer(musicPlayer)
{
    loadSlides(slideFilePath);

    if (slides.empty())
    {
        std::cerr << "IntroState: no slides loaded from " << slideFilePath
            << " — skipping intro.\n";
        finished = true;
        return;
    }

    const sf::Vector2u winSize = window->getSize();
    const float winW = static_cast<float>(winSize.x);
    const float winH = static_cast<float>(winSize.y);

    // Fade overlay — full window, starts black
    fadeRect.setSize(sf::Vector2f(winW, winH));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 255));

    // Bottom panel so caption is readable over any image
    textOverlay.setSize(sf::Vector2f(winW, 200.f));
    textOverlay.setPosition(0.f, winH - 200.f);
    textOverlay.setFillColor(sf::Color(0, 0, 0, 180));

    // Caption text — Text class pulls ticker_font from AssetDatabase
    captionText = std::make_unique<Text>(
        60.f, winH - 170.f,
        20,
        "",
        sf::Color(220, 200, 170, 255),
        false
    );

    // Hint text — bottom right
    hintText = std::make_unique<Text>(
        winW - 380.f, winH - 36.f,
        13,
        "[ Click or Space to continue  |  Esc to skip ]",
        sf::Color(160, 160, 160, 160),
        false
    );

    // Play music

    MusicManager::getInstance().play("intro_music");

    applySlide(0);
}

// ── State interface ───────────────────────────────────────────────────────

void IntroState::endState()
{
    std::cout << "IntroState: ending.\n";
}

void IntroState::updateKeybinds()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        finished = true;
}

void IntroState::update()
{
    updateKeybinds();

    if (finished)
    {
        launchGame();
        return;
    }

    const float elapsed = fadeClock.getElapsedTime().asSeconds();

    if (fadingIn)
    {
        fadeAlpha = 255.f * (1.f - std::min(elapsed / kFadeDuration, 1.f));
        fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));

        if (elapsed >= kFadeDuration)
        {
            fadeAlpha = 0.f;
            fadingIn = false;
            fadeClock.restart();
        }
        return; // block input during fade-in
    }

    if (fadingOut)
    {
        fadeAlpha = 255.f * std::min(elapsed / kFadeDuration, 1.f);
        fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));

        if (elapsed >= kFadeDuration)
        {
            fadingOut = false;
            advance();
        }
        return; // block input during fade-out
    }

    // Fully visible — clear the fade rect and accept input
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));

    if (advancePressed())
    {
        fadingOut = true;
        fadeClock.restart();
    }

    // Edge-detect state update — after the check above
    mouseWasDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    spaceWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    enterWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
}

void IntroState::render(sf::RenderTarget* target)
{
    if (target == nullptr || finished) return;

    // Slide image
    if (textureLoaded)
        target->draw(slideSprite);

    // Caption
    const bool hasText = !slides[currentIndex].text.empty();
    if (hasText)
    {
        target->draw(textOverlay);
        captionText->render(target);
    }

    // Hint — only when fully visible
    if (!fadingIn && !fadingOut)
        hintText->render(target);

    // Fade overlay on top of everything
    target->draw(fadeRect);
}

// ── Slides ────────────────────────────────────────────────────────────────

void IntroState::loadSlides(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "IntroState: could not open slide file: " << path << "\n";
        return;
    }

    std::string line;
    Slide current;
    bool inSlide = false;

    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        if (line == "[SLIDE]")
        {
            if (inSlide && !current.imageAssetId.empty())
                slides.push_back(current);
            current = Slide{};
            inSlide = true;
            continue;
        }

        if (!inSlide) continue;

        const auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        const std::string key = line.substr(0, sep);
        const std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "IMAGE")     current.imageAssetId = val;
        else if (key == "TEXT") current.text = val;
    }

    if (inSlide && !current.imageAssetId.empty())
        slides.push_back(current);

    std::cout << "IntroState: loaded " << slides.size() << " slides from " << path << "\n";
}

void IntroState::applySlide(int index)
{
    if (index < 0 || index >= static_cast<int>(slides.size())) return;

    currentIndex = index;
    const Slide& slide = slides[index];

    // slide.imageAssetId is an asset id registered in assets.db, not a raw
    // file path — load via AssetDatabase's cache instead of disk.
    textureLoaded = false;
    try {
        slideSprite.setTexture(AssetDatabase::getInstance().getTexture(slide.imageAssetId), true);
        textureLoaded = true;
    }
    catch (const std::exception& e) {
        std::cerr << "IntroState: failed to load slide image asset \"" << slide.imageAssetId
            << "\": " << e.what() << "\n";
    }

    if (textureLoaded)
    {
        const sf::Vector2u winSize = window->getSize();
        const float winW = static_cast<float>(winSize.x);
        const float winH = static_cast<float>(winSize.y);
        const sf::FloatRect bounds = slideSprite.getLocalBounds();

        if (bounds.width > 0.f && bounds.height > 0.f)
        {
            // std::min = letterbox (fit inside window, no cropping)
            const float scale = std::min(winW / bounds.width, winH / bounds.height);

            slideSprite.setScale(scale, scale);
            slideSprite.setPosition(
                (winW - bounds.width * scale) / 2.f,
                (winH - bounds.height * scale) / 2.f);
        }
    }

    if (captionText)
        captionText->setString(slide.text);

    // Wrap text to fit within the window width, accounting for margins
    if (captionText)
    {
        const float captionX = 60.f;
        const float winW = static_cast<float>(window->getSize().x);
        const float maxWidth = winW - (captionX * 2.f);   // 60px margin each side
        captionText->setString(Text::wrapText(slide.text, maxWidth, 20));
    }

    // Fade in the new slide
    fadeAlpha = 255.f;
    fadingIn = true;
    fadingOut = false;
    fadeClock.restart();
}

void IntroState::advance()
{
    const int next = currentIndex + 1;

    if (next >= static_cast<int>(slides.size()))
        finished = true;
    else
        applySlide(next);
}

bool IntroState::advancePressed() const
{
    const bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    const bool spaceDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    const bool enterDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

    return (!mouseWasDown && mouseDown) ||
        (!spaceWasDown && spaceDown) ||
        (!enterWasDown && enterDown);
}

void IntroState::launchGame()
{
    endState();

    // Seed the starting party before any state that needs it
    CharacterManager::getInstance().addCharacterToParty("PLAYER");
    CharacterManager::getInstance().addCharacterToParty("ZIN");

    if (!states->empty())
        states->pop();

    states->push(new TravelState(window, states, musicPlayer));
    // areaId must match the starting map's id in maps.db ("forest") so the
    // bonfire background resolves on the very first visit — without this,
    // BonfireState::initUi() builds "bonfire_" + "" and skips loading,
    // only working correctly after a later area-aware bonfire return.
    states->push(new BonfireState(window, states, "forest", musicPlayer));
}