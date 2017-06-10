#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>
#include <rapidjson/document.h>
#include <rapidjson/filestream.h>
#include <Logger.h>

#include "AssetsMgr.h"
#include "GameObject.h"
#include "AnimationComponent.h"
#include "DrawableComponent.h"
#include "PlayableComponent.h"


int main(int argc, char** argv)
{
	int res = 0;
    
    tools::Logger::getInstance().init();
    pzr::AssetsMgr assetsMgr;

    if (assetsMgr.loadAssetsFromJson("Data/assets.json"))
    {

        sf::RenderWindow window(sf::VideoMode(500, 500), "SFML test!");
        window.setVerticalSyncEnabled(true);


        std::vector<pzr::GameObject*> gameObjects;

#pragma region read_json_create_go
        FILE* fileHndlr = NULL;
        fopen_s(&fileHndlr, "Data/objects.json", "r");
        rapidjson::FileStream isw(fileHndlr);
        rapidjson::Document doc;
        if (!doc.ParseStream<NULL>(isw).HasParseError())
        {
            const rapidjson::Value& gObjs = doc["gameobjects"];
            for (rapidjson::SizeType i = 0; i < gObjs.Size(); i++)
            {
                const rapidjson::GenericValue <rapidjson::UTF8<>>& gObj = gObjs[i];

                pzr::GameObject* gameObjPtr = new pzr::GameObject(gObj["id"].GetString(), &window);

                if (gObj["texture"].IsString())
                {
                    std::unique_ptr<sf::Sprite> sprite(new sf::Sprite(assetsMgr.getTextureFromId(gObj["texture"].GetString())
                        , sf::IntRect(gObj["x"].GetInt()
                            , gObj["y"].GetInt()
                            , gObj["u"].GetInt()
                            , gObj["v"].GetInt())));

                    if (gObj["animations"].IsArray())
                    {
                        pzr::AnimationComponent* animCompo = new pzr::AnimationComponent(sprite.get());
                        animCompo->loadAnimation(gObj["animations"]);
                        gameObjPtr->setAnimCpnt(animCompo);
                    }
                    pzr::DrawableComponent* drawCompo = new pzr::DrawableComponent(sprite);
                    gameObjPtr->setDrawCpnt(drawCompo);
                }

                if (gObj["input"].IsArray())
                {
                    pzr::PlayableComponent* playComponent = new pzr::PlayableComponent();
                    playComponent->registerAction(gObj["input"]);
                    gameObjPtr->setInputCpnt(playComponent);
                }

                gameObjPtr->_position.x = gObj["posX"].GetDouble();
                gameObjPtr->_position.y = gObj["posY"].GetDouble();

                gameObjects.push_back(gameObjPtr);
            }
        }
        fclose(fileHndlr);
#pragma endregion

        sf::Clock clock;
        while (window.isOpen())
        {
            window.clear();

            sf::Time dt = clock.restart();
            for (pzr::GameObject* gObj : gameObjects)
            {
                gObj->update(dt);
            }

            window.display();
        }
    }
	return res;
}