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

void AnimationEffectManager::registerAnimation(const std::string& name,
    const AnimationEffectRequest& requestTemplate)
{
    this->namedAnimations[name] = requestTemplate;
}

void AnimationEffectManager::playNamed(const std::string& name,
    float x, float y,
    float scaleX, float scaleY)
{
    if (name.empty() || name == "none") return;

    auto it = this->namedAnimations.find(name);
    if (it == this->namedAnimations.end()) return;

    // Copy the template and override position/scale
    AnimationEffectRequest req = it->second;
    req.x = x;
    req.y = y;
    req.scaleX = scaleX;
    req.scaleY = scaleY;

    this->play(req);
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
    if (target == nullptr) return;

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