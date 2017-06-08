#include "AssetsMgr.h"

#include <Thor/Resources.hpp>
#include <RapidJson/filestream.h>
#include <Logger.h>

namespace pzr
{

    AssetsMgr::AssetsMgr()
    {
    }


    AssetsMgr::~AssetsMgr()
    {
    }

    bool AssetsMgr::loadAssetsFromJson(const char * jsfile)
    {
        bool bRet = false;

        FILE* fileHndlr = NULL;
        if (fopen_s(&fileHndlr, jsfile, "r") == 0)
        {
            rapidjson::FileStream isw(fileHndlr);
            rapidjson::Document doc;

            if (!doc.ParseStream<NULL>(isw).HasParseError())
            {
                bRet = loadAllTextures(doc["textures"]);
            }
            else
            {
                LOG_ERROR("Fichier json invalide");
            }
            fclose(fileHndlr);
        }

        return bRet;
    }

    bool AssetsMgr::loadAllTextures(const rapidjson::Value & textureArray)
    {
        bool bRet = false;

        try
        {
            for (rapidjson::SizeType i = 0; i < textureArray.Size(); i++)
            {
                const rapidjson::GenericValue <rapidjson::UTF8<>>& jsTexture = textureArray[i];

                _textureMap.acquire(jsTexture["name"].GetString()
                    , thor::Resources::fromFile<sf::Texture>(jsTexture["file"].GetString()));
                LOG_DEBUG("Texture charge : %s", jsTexture["name"].GetString());
            }
            bRet = true;
        }
        catch (thor::ResourceLoadingException& e)
        {
            LOG_ERROR("%s", e.what());
        }

        return bRet;
    }

    sf::Texture & AssetsMgr::getTextureFromId(const std::string & id)
    {
        return _textureMap[id];
    }
}