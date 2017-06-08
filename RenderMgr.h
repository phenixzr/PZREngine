#ifndef RENDER_MGR
#define RENDER_MGR 

#include <unordered_map>
#include "Sprite.h"
#include "UuidGenerator.h"
#include <SFML/Graphics.hpp>

class RenderMgr
{
public:
	RenderMgr(sf::RenderWindow* renderWnd);
	~RenderMgr();
	void update();
    void loadAllTextures(const char* texturesFile);
    sf::Texture& getTextureFromName(const std::string& textName);
    void registerSprite(UniqueId id, sf::Sprite& sprite);

private:
	std::unordered_map<UniqueId, sf::Sprite*> _spriteMap;
    std::unordered_map<UniqueId, sf::Texture*> _textureMap;
	sf::RenderWindow* _renderWnd;
};

#endif