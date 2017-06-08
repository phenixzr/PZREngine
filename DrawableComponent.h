#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H

#include <memory>
#include "SFML/System/Vector2.hpp"

#include "Component.h"

namespace sf
{
    class RenderWindow;
    class Sprite;
}

namespace pzr
{
    class DrawableComponent : public Component
    {
    public:
        DrawableComponent(std::unique_ptr<sf::Sprite>& sprite);
        ~DrawableComponent();
        void update(const sf::Vector2f& position, sf::RenderWindow* renderWnd);

    private:
        std::unique_ptr<sf::Sprite> _sprite;
    };
} //ns pzr
#endif // DRAWABLE_COMPONENT_H


