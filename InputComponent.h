#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <SFML/System/Vector2.hpp>
#include <Thor/Input/ActionMap.hpp>
#include "Component.h"

class Gameobject;

namespace pzr
{
    class InputComponent : public Component
    {
    public:
        InputComponent();
        ~InputComponent();
        virtual void registerAction() = 0;
        void update(GameObject* gameObject) override;
        virtual void processInput() = 0;

    private:
        thor::ActionMap<std::string> _actionMap;
    };
}

#endif