#include "AnimationComponent.h"
#include <iostream>
#include <Thor/Animations/FrameAnimation.hpp>

namespace pzr
{
    AnimationComponent::AnimationComponent(sf::Sprite* sprite)
        : Component(), _sprite(sprite)
    {
    }

    AnimationComponent::~AnimationComponent()
    {
    }

    void AnimationComponent::update(GameObject* gameObject)
    {
        _animator.update(gameObject->getElapsedTime());
        _animator.animate(*_sprite);
    }

    bool AnimationComponent::loadAnimation(const rapidjson::Value& animationDesc)
    {
        bool bRet = false; 
        
        if (animationDesc.IsArray())
        {
            const sf::IntRect& rect = _sprite->getTextureRect();
            for (rapidjson::SizeType i = 0; i < animationDesc.Size(); i++)
            {
                const rapidjson::GenericValue <rapidjson::UTF8<>>& animStruct = animationDesc[i];
                thor::FrameAnimation animation;

                const rapidjson::Value& framesStruct = animStruct["frames"];
                if (framesStruct.IsArray())
                {
                    for (rapidjson::SizeType j = 0; j < framesStruct.Size(); j++)
                    {
                        const rapidjson::GenericValue <rapidjson::UTF8<>>& frame = framesStruct[j];
                        addFrames(animation, rect, frame["frame1"].GetInt(), frame["frame2"].GetInt(), frame["line"].GetInt());
                    }

                    _animator.addAnimation(animStruct["name"].GetString(), animation, sf::seconds(animStruct["duration"].GetDouble()));
                    bRet = true;
                }
            }
        }
        return bRet;
    }

    void AnimationComponent::playAnimation(const std::string& id, bool loop)
    {
        _animator.playAnimation(id, loop);
    }

    void AnimationComponent::addFrames(thor::FrameAnimation& animation
        , const sf::IntRect& textureRect
        , int startFrame, int endFrame, int line, float duration)
    {
        const int step = (startFrame < endFrame) ? +1 : -1;
        endFrame += step;
        for (int x = startFrame; x != endFrame; x += step)
            animation.addFrame(duration, sf::IntRect(textureRect.width * x, line * textureRect.height, textureRect.width, textureRect.height));
    }
}
