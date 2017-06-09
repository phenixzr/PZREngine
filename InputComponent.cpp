#include "InputComponent.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"

namespace pzr
{
    InputComponent::InputComponent()
    {
    }
 
    InputComponent::~InputComponent()
    {
    }

    void InputComponent::update(GameObject* gameObject)
    {
        _actionMap.update(gameObject->getWindow());
        //processInput();
    }
}
