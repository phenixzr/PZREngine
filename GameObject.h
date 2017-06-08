#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

namespace sf { class RenderWindow; }

namespace pzr
{
    enum GObjectState
    {
        WALKING_UP,
        WALKING_DOWN,
        WALKING_LEFT,
        WALKING_RIGHT,
        DYING,
        DEAD,
        IDLE
    };

    class DrawableComponent;
    class AnimationComponent;
    class InputComponent;

    class GameObject
    {
    public:
        GameObject(const std::string& id, sf::RenderWindow* renderWnd);
        ~GameObject();
        void update(sf::Time elapsed);
        void setInputCpnt(InputComponent* inputCpnt);
        void setDrawCpnt(DrawableComponent* drawCpnt);
        void setAnimCpnt(AnimationComponent* animCpnt);

    private:
        std::string  _id;
        GObjectState _curState;
        InputComponent *_inputCpnt;
        DrawableComponent *_drawCpnt;
        AnimationComponent *_animCpnt;
        sf::RenderWindow* _renderWnd;
    
    public:
        sf::Vector2f _position;
    };
}

#endif // GAME_OBJECT_H