#pragma once

#include "AnimationPlayer.h"

#include <memory>
#include <string>
#include <vector>

struct AnimationEffectRequest
{
    enum class SourceType
    {
        TextureIds,
        SpriteSheet
    };

    SourceType sourceType = SourceType::TextureIds;

    // Texture frame animation
    std::vector<std::string> textureIds;

    // Sprite sheet animation
    std::string spriteSheetTextureId = "";
    int frameWidth = 0;
    int frameHeight = 0;
    int frameCount = 0;
    int row = 0;

    // Timing
    float frameTime = 0.08f;
    std::vector<float> frameTimes;
    bool looping = false;

    // Transform
    float x = 0.f;
    float y = 0.f;
    float scaleX = 1.f;
    float scaleY = 1.f;

    // Optional fit box
    bool useFitBox = false;
    float boxX = 0.f;
    float boxY = 0.f;
    float boxWidth = 0.f;
    float boxHeight = 0.f;
    float boxPadding = 0.f;
};

class AnimationEffectManager
{
public:
    void play(const AnimationEffectRequest& request);

    void update();
    void render(sf::RenderTarget* target);
    void clear();

private:
    std::vector<std::unique_ptr<AnimationPlayer>> activeAnimations;
};