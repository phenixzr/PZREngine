#include "InputComponent.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Thor/Input/InputNames.hpp"
#include "GameObject.h"

namespace pzr
{
    InputComponent::InputComponent()
    {
    }
 
    InputComponent::~InputComponent()
    {
    }

    void InputComponent::registerAction(const rapidjson::Value & inputDesc)
    {
        std::string key;
        for (rapidjson::SizeType i = 0; i < inputDesc.Size(); i++)
        {
            const rapidjson::GenericValue <rapidjson::UTF8<>>& input = inputDesc[i];
            key.clear();
            key.append(input["key"].GetString());
            thor::Action action(thor::toKeyboardKey(key), input["hold"].GetBool() ? thor::Action::Hold : thor::Action::PressOnce);
            _actionMap[input["name"].GetString()] = action;
        }
    }

    void InputComponent::update(GameObject* gameObject)
    {
        _actionMap.update(gameObject->getWindow());
        processInput(gameObject);
    }
}
