#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

namespace sf { class RenderWindow; }

namespace pzr
{
    class DrawableComponent;
    class AnimationComponent;
    class InputComponent;

    class GameObject
    {
    public:
        GameObject(const std::string& id, sf::RenderWindow* renderWnd);
        ~GameObject();
        void clear();
        void update(sf::Time elapsed);
        void setInputCpnt(InputComponent* inputCpnt);
        void setDrawCpnt(DrawableComponent* drawCpnt);
        void setAnimCpnt(AnimationComponent* animCpnt);
        sf::RenderWindow& getWindow();
        sf::Time getElapsedTime();

    private:
        std::string  _id;
        InputComponent* _inputCpnt;
        DrawableComponent* _drawCpnt;
        AnimationComponent* _animCpnt;
        sf::RenderWindow* _renderWnd;
        sf::Time _elapsedTime;
    
    public:
        sf::Vector2f _position;
    };
}

#endif // GAME_OBJECT_H