#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>

class RenderMgr;

class Sprite
{
public:
	Sprite(const std::string& textName, const sf::IntRect& rectSourceSprite, RenderMgr& rndMgr);
	void setPosition(const sf::Vector2f & pos);
	sf::Sprite& getSprite() { return _sprite; }
	~Sprite();

private:
	sf::Sprite _sprite;
};

#endif