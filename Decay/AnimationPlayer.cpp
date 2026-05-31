#include "AnimationPlayer.h"

#include <algorithm>
#include <iostream>

// Constructors and Destructors
AnimationPlayer::AnimationPlayer()
{
    this->sourceType = SourceType::None;

    this->frameTime = 0.1f;
    this->currentFrame = 0;

    this->playing = false;
    this->looping = false;
    this->finished = false;
    this->hidden = false;
}

// Frame Source Functions
void AnimationPlayer::setFramesFromTextureIds(const std::vector<std::string>& textureIds)
{
    this->sourceType = SourceType::TextureIds;

    this->frameTextureIds = textureIds;
    this->frameRects.clear();
    this->spriteSheetTextureId = "";

    this->currentFrame = 0;
    this->finished = false;

    this->applyCurrentFrame();
}

void AnimationPlayer::setFramesFromSpriteSheet(const std::string& textureId, int frameWidth, int frameHeight, int frameCount, int row)
{
    this->sourceType = SourceType::SpriteSheet;

    this->spriteSheetTextureId = textureId;
    this->frameTextureIds.clear();
    this->frameRects.clear();

    for (int i = 0; i < frameCount; i++) {
        this->frameRects.push_back(sf::IntRect(
            i * frameWidth,
            row * frameHeight,
            frameWidth,
            frameHeight
        ));
    }

    this->currentFrame = 0;
    this->finished = false;

    this->applyCurrentFrame();
}

void AnimationPlayer::setFramesFromSpriteSheet(const std::string& textureId, int frameWidth, int frameHeight, int frameCount, int startX, int startY)
{
    this->sourceType = SourceType::SpriteSheet;

    this->spriteSheetTextureId = textureId;
    this->frameTextureIds.clear();
    this->frameRects.clear();

    for (int i = 0; i < frameCount; i++) {
        this->frameRects.push_back(sf::IntRect(
            startX + (i * frameWidth),
            startY,
            frameWidth,
            frameHeight
        ));
    }

    this->currentFrame = 0;
    this->finished = false;

    this->applyCurrentFrame();
}

// Core Functions
void AnimationPlayer::update()
{
    if (!this->playing || this->finished || this->hidden) {
        return;
    }

    if (this->frameClock.getElapsedTime().asSeconds() >= this->getCurrentFrameTime()) {
        this->advanceFrame();
        this->frameClock.restart();
    }
}

void AnimationPlayer::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    if (!this->hidden && this->sourceType != SourceType::None) {
        target->draw(this->sprite);
    }
}

// Playback Functions
void AnimationPlayer::play()
{
    if (this->sourceType == SourceType::None) {
        std::cerr << "Cannot play animation. No frames assigned." << "\n";
        return;
    }

    this->playing = true;
    this->finished = false;
    this->frameClock.restart();
}

void AnimationPlayer::pause()
{
    this->playing = false;
}

void AnimationPlayer::stop()
{
    this->playing = false;
    this->finished = true;
    this->currentFrame = 0;
    this->applyCurrentFrame();
}

void AnimationPlayer::reset()
{
    this->currentFrame = 0;
    this->finished = false;
    this->frameClock.restart();
    this->applyCurrentFrame();
}

// Position / Display Functions
void AnimationPlayer::setPosition(float x, float y)
{
    this->sprite.setPosition(x, y);
}

void AnimationPlayer::setScale(float x, float y)
{
    this->sprite.setScale(x, y);
}

void AnimationPlayer::setRotation(float angle)
{
    this->sprite.setRotation(angle);
}

void AnimationPlayer::setOriginCenter()
{
    const sf::FloatRect bounds = this->sprite.getLocalBounds();

    this->sprite.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );
}

void AnimationPlayer::fitInside(float boxX, float boxY, float boxWidth, float boxHeight, float padding)
{
    const sf::FloatRect bounds = this->sprite.getLocalBounds();

    if (bounds.width <= 0.f || bounds.height <= 0.f) {
        return;
    }

    const float availableWidth = boxWidth - (padding * 2.f);
    const float availableHeight = boxHeight - (padding * 2.f);

    if (availableWidth <= 0.f || availableHeight <= 0.f) {
        return;
    }

    const float scaleX = availableWidth / bounds.width;
    const float scaleY = availableHeight / bounds.height;

    const float scale = std::min(scaleX, scaleY);

    this->sprite.setScale(scale, scale);

    const float scaledWidth = bounds.width * scale;
    const float scaledHeight = bounds.height * scale;

    const float centeredX = boxX + (boxWidth - scaledWidth) / 2.f;
    const float centeredY = boxY + (boxHeight - scaledHeight) / 2.f;

    this->sprite.setPosition(centeredX, centeredY);
}

// Settings
void AnimationPlayer::setFrameTime(float seconds)
{
    if (seconds <= 0.f) {
        seconds = 0.1f;
    }

    this->frameTime = seconds;
}

void AnimationPlayer::setLooping(bool looping)
{
    this->looping = looping;
}

void AnimationPlayer::setHidden(bool hidden)
{
    this->hidden = hidden;
}

void AnimationPlayer::setFrameTimes(const std::vector<float>& frameTimes)
{
    this->frameTimes = frameTimes;
}

void AnimationPlayer::clearFrameTimes()
{
    this->frameTimes.clear();
}

float AnimationPlayer::getCurrentFrameTime() const
{
    if (this->currentFrame >= 0 && this->currentFrame < this->frameTimes.size()) {
        return this->frameTimes[this->currentFrame];
    }

    return this->frameTime;
}

// Visibility
void AnimationPlayer::show()
{
    this->hidden = false;
}

void AnimationPlayer::hide()
{
    this->hidden = true;
}

// Getters
bool AnimationPlayer::isPlaying() const
{
    return this->playing;
}

bool AnimationPlayer::isFinished() const
{
    return this->finished;
}

bool AnimationPlayer::isHidden() const
{
    return this->hidden;
}

int AnimationPlayer::getCurrentFrame() const
{
    return this->currentFrame;
}

int AnimationPlayer::getFrameCount() const
{
    if (this->sourceType == SourceType::TextureIds) {
        return static_cast<int>(this->frameTextureIds.size());
    }

    if (this->sourceType == SourceType::SpriteSheet) {
        return static_cast<int>(this->frameRects.size());
    }

    return 0;
}

// Private Functions
void AnimationPlayer::applyCurrentFrame()
{
    if (this->sourceType == SourceType::TextureIds) {
        if (this->frameTextureIds.empty()) {
            return;
        }

        if (this->currentFrame < 0 || this->currentFrame >= this->frameTextureIds.size()) {
            this->currentFrame = 0;
        }

        this->sprite.setTexture(AssetDatabase::getInstance().getTexture(this->frameTextureIds[this->currentFrame]), true);
        return;
    }

    if (this->sourceType == SourceType::SpriteSheet) {
        if (this->spriteSheetTextureId.empty() || this->frameRects.empty()) {
            return;
        }

        if (this->currentFrame < 0 || this->currentFrame >= this->frameRects.size()) {
            this->currentFrame = 0;
        }

        this->sprite.setTexture(AssetDatabase::getInstance().getTexture(this->spriteSheetTextureId), true);
        this->sprite.setTextureRect(this->frameRects[this->currentFrame]);
        return;
    }
}

void AnimationPlayer::advanceFrame()
{
    const int frameCount = this->getFrameCount();

    if (frameCount <= 0) {
        return;
    }

    this->currentFrame++;

    if (this->currentFrame >= frameCount) {
        if (this->looping) {
            this->currentFrame = 0;
        }
        else {
            this->currentFrame = frameCount - 1;
            this->playing = false;
            this->finished = true;
        }
    }

    this->applyCurrentFrame();
}