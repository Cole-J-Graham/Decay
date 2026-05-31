#include "AnimationEffectManager.h"

#include <algorithm>

void AnimationEffectManager::play(const AnimationEffectRequest& request)
{
    auto animation = std::make_unique<AnimationPlayer>();

    if (request.sourceType == AnimationEffectRequest::SourceType::TextureIds) {
        animation->setFramesFromTextureIds(request.textureIds);
    }
    else if (request.sourceType == AnimationEffectRequest::SourceType::SpriteSheet) {
        animation->setFramesFromSpriteSheet(
            request.spriteSheetTextureId,
            request.frameWidth,
            request.frameHeight,
            request.frameCount,
            request.row
        );
    }

    animation->setFrameTime(request.frameTime);

    if (!request.frameTimes.empty()) {
        animation->setFrameTimes(request.frameTimes);
    }

    animation->setLooping(request.looping);

    if (request.useFitBox) {
        animation->fitInside(
            request.boxX,
            request.boxY,
            request.boxWidth,
            request.boxHeight,
            request.boxPadding
        );
    }
    else {
        animation->setPosition(request.x, request.y);
        animation->setScale(request.scaleX, request.scaleY);
    }

    animation->play();

    this->activeAnimations.push_back(std::move(animation));
}

void AnimationEffectManager::update()
{
    for (auto& animation : this->activeAnimations) {
        animation->update();
    }

    this->activeAnimations.erase(
        std::remove_if(
            this->activeAnimations.begin(),
            this->activeAnimations.end(),
            [](const std::unique_ptr<AnimationPlayer>& animation) {
                return animation == nullptr || animation->isFinished();
            }
        ),
        this->activeAnimations.end()
    );
}

void AnimationEffectManager::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    for (auto& animation : this->activeAnimations) {
        if (animation != nullptr) {
            animation->render(target);
        }
    }
}

void AnimationEffectManager::clear()
{
    this->activeAnimations.clear();
}