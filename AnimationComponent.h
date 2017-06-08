#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <string>
#include <Thor/Animations/Animator.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <RapidJson/document.h>

#include "Component.h"
#include "GameObject.h"

namespace thor { class FrameAnimation; }

namespace pzr
{
    class AnimationComponent : public Component
    {
    public:
        AnimationComponent(sf::Sprite* sprite);
        ~AnimationComponent();
        void update(sf::Time elapsed, GObjectState newState);
        bool loadAnimation(const rapidjson::Value& animationDesc);
        void playAnimation(const std::string& id, bool loop = true);

    private:
        void addFrames(thor::FrameAnimation& animation
            , const sf::IntRect& textureRect
            , int startFrame, int endFrame, int line, float duration = 1.f);

        void requiredAnimation(GObjectState state, std::string& buf);
        std::string getPlayingAnimation();
    private:
        thor::Animator<sf::Sprite, std::string> _animator;
        sf::Sprite* _sprite;
    };
} // ns pzr

#endif