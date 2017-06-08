#include "RenderMgr.h"
#include <rapidjson/document.h>
#include <rapidjson/filestream.h>
#include "UuidGenerator.h"

RenderMgr::RenderMgr(sf::RenderWindow* renderWnd)
	:_renderWnd(renderWnd)
{
}

RenderMgr::~RenderMgr()
{
    for (auto texture : _textureMap)
    {
        delete texture.second;
    }

}

void RenderMgr::update()
{
	_renderWnd->clear();

	for (auto sprite : _spriteMap)
	{
		_renderWnd->draw(*sprite.second);
	}

	_renderWnd->display();
}

void RenderMgr::loadAllTextures(const char* texturesFile)
{
    FILE* fileHndlr = NULL;
    assert(fopen_s(&fileHndlr, texturesFile, "r") == 0);
    rapidjson::FileStream isw(fileHndlr);
    rapidjson::Document doc;

    if (!doc.ParseStream<NULL>(isw).HasParseError())
    {
        const rapidjson::Value& a = doc["textures"];
        assert(a.IsArray());
        for (rapidjson::SizeType i = 0; i < a.Size(); i++)
        {
            const rapidjson::GenericValue <rapidjson::UTF8<>>& jsTexture = a[i];
            sf::Texture* text = new sf::Texture();
            text->loadFromFile(jsTexture["file"].GetString());
            std::string name(jsTexture["name"].GetString());

            std::cout << "texture loading : " << name
                << " hash : " << std::hash<std::string>() (name)
                << std::endl;

            _textureMap.insert( std::pair<std::size_t, sf::Texture*> (std::hash<std::string>() (name)
                              , text) );
        }
    }
    fclose(fileHndlr);
}

sf::Texture& RenderMgr::getTextureFromName(const std::string& textName)
{
    return *_textureMap.at(std::hash<std::string>()(textName));
}

void RenderMgr::registerSprite(UniqueId id, sf::Sprite& sprite)
{
    _spriteMap.insert(std::pair<UniqueId, sf::Sprite*>(id, &sprite));
}
