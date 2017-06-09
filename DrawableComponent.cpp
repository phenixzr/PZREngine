#include "DrawableComponent.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "GameObject.h"

namespace pzr
{
    DrawableComponent::DrawableComponent(std::unique_ptr<sf::Sprite>& sprite)
    {
        _sprite = std::move(sprite);
    }


    DrawableComponent::~DrawableComponent()
    {
    }

    void DrawableComponent::update(GameObject* gameObject)
    {
        _sprite->setPosition(gameObject->_position);
        gameObject->getWindow().draw(*_sprite);        
    }
}
