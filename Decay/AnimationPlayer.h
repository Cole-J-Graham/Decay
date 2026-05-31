#pragma once

#include "AssetDatabase.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class AnimationPlayer
{
public:
    // Constructors and Destructors
    AnimationPlayer();
    ~AnimationPlayer() = default;

    // Frame Source Functions
    void setFramesFromTextureIds(const std::vector<std::string>& textureIds);
    void setFramesFromSpriteSheet(const std::string& textureId, int frameWidth, int frameHeight, int frameCount, int row = 0);
    void setFramesFromSpriteSheet(const std::string& textureId, int frameWidth, int frameHeight, int frameCount, int startX, int startY);

    // Core Functions
    void update();
    void render(sf::RenderTarget* target);

    // Playback Functions
    void play();
    void pause();
    void stop();
    void reset();

    // Position / Display Functions
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void setRotation(float angle);
    void setOriginCenter();
    void fitInside(float boxX, float boxY, float boxWidth, float boxHeight, float padding = 0.f);

    // Settings
    void setFrameTime(float seconds);
    void setLooping(bool looping);
    void setHidden(bool hidden);
    void setFrameTimes(const std::vector<float>& frameTimes);
    void clearFrameTimes();

    // Visibility
    void show();
    void hide();

    // Getters
    bool isPlaying() const;
    bool isFinished() const;
    bool isHidden() const;
    int getCurrentFrame() const;
    int getFrameCount() const;


private:
    enum class SourceType
    {
        None,
        TextureIds,
        SpriteSheet
    };

private:
    void applyCurrentFrame();
    void advanceFrame();

    float getCurrentFrameTime() const;

private:
    SourceType sourceType;

    sf::Sprite sprite;

    std::vector<std::string> frameTextureIds;
    std::vector<sf::IntRect> frameRects;
    std::vector<float> frameTimes;

    std::string spriteSheetTextureId;

    sf::Clock frameClock;

    float frameTime;
    int currentFrame;

    bool playing;
    bool looping;
    bool finished;
    bool hidden;
};