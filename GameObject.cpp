#include "GameObject.h"

#include "DrawableComponent.h"
#include "AnimationComponent.h"
#include "InputComponent.h"

namespace pzr
{
    GameObject::GameObject(const std::string & id, sf::RenderWindow * renderWnd)
        : _id(id)
        , _curState(GObjectState::IDLE)
        , _inputCpnt(NULL)
        , _drawCpnt(NULL)
        , _animCpnt(NULL)
        , _renderWnd(renderWnd)
        , _position(0.0, 0.0)
    {
    }

    GameObject::~GameObject()
    {
        if (_animCpnt != NULL)
            delete _animCpnt;
        if (_drawCpnt != NULL)
            delete _drawCpnt;
        if (_inputCpnt != NULL)
            delete _inputCpnt;
    }

    void GameObject::update(sf::Time elapsed)
    {
        if (_inputCpnt != NULL)
            _inputCpnt->update(_position, _curState);
        if (_animCpnt != NULL)
            _animCpnt->update(elapsed, _curState);
        if (_drawCpnt != NULL)
            _drawCpnt->update(_position, _renderWnd);
    }

    void GameObject::setDrawCpnt(DrawableComponent* drawCpnt)
    {
        _drawCpnt = drawCpnt;
    }

    void GameObject::setAnimCpnt(AnimationComponent* animCpnt)
    {
        _animCpnt = animCpnt;
    }

    void GameObject::setInputCpnt(InputComponent* inputCpnt)
    {
        _inputCpnt = inputCpnt;
        _inputCpnt->resetInput(_position, _curState);
    }
}
