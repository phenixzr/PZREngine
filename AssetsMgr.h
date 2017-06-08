#ifndef ASSET_MGR_H
#define ASSET_MGR_H

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <Thor/Resources/ResourceHolder.hpp>
#include <RapidJson/document.h>

namespace pzr
{
    class AssetsMgr
    {
    public:
        AssetsMgr();
        ~AssetsMgr();
        bool loadAssetsFromJson(const char* file);
        sf::Texture& getTextureFromId(const std::string& id);

    private:
        bool loadAllTextures(const rapidjson::Value& textureArray);

        thor::ResourceHolder<sf::Texture, std::string> _textureMap;
    };
}

#endif


