#include "DrawableComponent.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"

namespace pzr
{
    DrawableComponent::DrawableComponent(std::unique_ptr<sf::Sprite>& sprite)
    {
        _sprite = std::move(sprite);
    }


    DrawableComponent::~DrawableComponent()
    {
    }

    void DrawableComponent::update(const sf::Vector2f& position, sf::RenderWindow* renderWnd)
    {
        _sprite->setPosition(position);
        renderWnd->draw(*_sprite);
    }
}
