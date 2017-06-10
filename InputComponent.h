#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <Thor/Input/ActionMap.hpp>
#include <RapidJson/document.h>
#include "Component.h"

class Gameobject;

namespace pzr
{
    class InputComponent : public Component
    {
    public:
        InputComponent();
        ~InputComponent();
        void registerAction(const rapidjson::Value& inputDesc);
        void update(GameObject* gameObject) override;

    protected:
        virtual void processInput(GameObject* gameObject) = 0;
    
    protected:
        thor::ActionMap<std::string> _actionMap;
    };
}

#endif