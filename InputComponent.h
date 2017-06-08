#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <SFML/System/Vector2.hpp>
#include "Component.h"
#include "EventNotifier.h"
#include "GameObject.h"
#include "global_declarations.h"

namespace pzr
{
    class InputComponent : public Component, public EventListner<KeyBoardEvent>
    {
    public:
        InputComponent();
        ~InputComponent();
        void update(sf::Vector2f& pos, GObjectState& state);
        void onNotified(KeyBoardEvent evt);
        void resetInput(const sf::Vector2f& pos, const GObjectState state);

    private:
        float _velocity;
        sf::Vector2f _pos;
        GObjectState _state;
    };
}

#endif