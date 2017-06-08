#include "InputComponent.h"

namespace pzr
{
    InputComponent::InputComponent()
        : _velocity(1.0f), _pos(0.0f,0.0f), _state(GObjectState::IDLE)
    {
    }
 
    InputComponent::~InputComponent()
    {
    }

    void InputComponent::update(sf::Vector2f& pos, GObjectState& state)
    {
        pos.x += (_pos.x - pos.x)*_velocity;
        pos.y += (_pos.y - pos.y)*_velocity;
        state = _state;
        resetInput(pos, state);
    }

    void InputComponent::onNotified(KeyBoardEvent evt)
    {
        if (evt == KeyBoardEvent::EVT_DOWN)
        {
            _pos.y++;
            _state = GObjectState::WALKING_DOWN;
        }
        if (evt == KeyBoardEvent::EVT_UP)
        {
            _pos.y--;
            _state = GObjectState::WALKING_UP;
        }
        if (evt == KeyBoardEvent::EVT_LEFT)
        {
            _pos.x--;
            _state = GObjectState::WALKING_LEFT;
        }
        if (evt == KeyBoardEvent::EVT_RIGHT)
        {
            _pos.x++;
            _state = GObjectState::WALKING_RIGHT;
        }
        if (evt == KeyBoardEvent::EVT_NONE)
        {
            _state = GObjectState::IDLE;
        }

    }

    void InputComponent::resetInput(const sf::Vector2f& pos, const GObjectState state)
    {
        _pos = pos;
        _state = state;
    }
}
