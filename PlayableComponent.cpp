#include "PlayableComponent.h"

namespace pzr
{
    PlayableComponent::PlayableComponent()
        : InputComponent()
    {
    }


    PlayableComponent::~PlayableComponent()
    {
    }

    void PlayableComponent::processInput(GameObject* gameObject)
    {
        if (_actionMap.isActive("walkup"))
        {
            gameObject->_position.y--;
        }
        if (_actionMap.isActive("walkdown"))
        {
            gameObject->_position.y++;
        }
        if (_actionMap.isActive("walkleft"))
        {
            gameObject->_position.x--;
        }
        if (_actionMap.isActive("walkright"))
        {
            gameObject->_position.x++;
        }
    }
}
