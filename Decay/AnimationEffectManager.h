#pragma once

#include "AnimationPlayer.h"

#include <memory>
#include <string>
#include <unordered_map>
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
    // Play a fully-specified request (existing API, unchanged)
    void play(const AnimationEffectRequest& request);

    // ── Named animation registry ──────────────────────────────────────
    // Register a template request under a name. Position/scale in the
    // template are ignored — callers supply those at play time.
    // Call once at startup (e.g. from CombatComponent constructor).
    void registerAnimation(const std::string& name,
        const AnimationEffectRequest& requestTemplate);

    // Play a registered animation at a specific position and scale.
    // If the name isn't registered, silently does nothing.
    void playNamed(const std::string& name,
        float x, float y,
        float scaleX = 3.f, float scaleY = 3.f);

    void update();
    void render(sf::RenderTarget* target);
    void clear();

private:
    std::vector<std::unique_ptr<AnimationPlayer>> activeAnimations;

    // Named templates — position/scale overridden at play time
    std::unordered_map<std::string, AnimationEffectRequest> namedAnimations;
};