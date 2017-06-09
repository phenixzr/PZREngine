#include "GameObject.h"

#include "DrawableComponent.h"
#include "AnimationComponent.h"
#include "InputComponent.h"

namespace pzr
{
    GameObject::GameObject(const std::string & id, sf::RenderWindow* renderWnd)
        : _id(id)
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

    void GameObject::clear()
    {
        _id.clear();
        _inputCpnt = NULL;
        _drawCpnt = NULL;
        _animCpnt = NULL;
        _renderWnd = NULL;
        _position.x = _position.y = 0.0;
    }

    void GameObject::update(sf::Time elapsed)
    {
        _elapsedTime = elapsed;

        if (_inputCpnt != NULL)
            _inputCpnt->update(this);
        if (_animCpnt != NULL)
            _animCpnt->update(this);
        if (_drawCpnt != NULL)
            _drawCpnt->update(this);
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
    }

    sf::RenderWindow& GameObject::getWindow()
    {
        return *_renderWnd;
    }
    sf::Time GameObject::getElapsedTime()
    {
        return sf::Time();
    }
}
