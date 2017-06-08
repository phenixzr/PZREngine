#include "Sprite.h"
#include "RenderMgr.h"

Sprite::Sprite(const std::string& textName, const sf::IntRect& rectSourceSprite, RenderMgr& rndMgr)
{
	_sprite.setTexture(rndMgr.getTextureFromName(textName));
	_sprite.setTextureRect(rectSourceSprite);

}

void Sprite::setPosition(const sf::Vector2f& pos)
{
	_sprite.setPosition(pos);
}

Sprite::~Sprite()
{
}
