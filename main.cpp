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
#include "EventNotifier.h"
#include "InputComponent.h"
#include "global_declarations.h"


int main(int argc, char** argv)
{
	int res = 0;
    tools::Logger::getInstance().init();
    pzr::AssetsMgr assetsMgr;

    if (assetsMgr.loadAssetsFromJson("Data/assets.json"))
    {

        sf::RenderWindow window(sf::VideoMode(500, 500), "SFML test!");
        window.setVerticalSyncEnabled(true);
        //window.setKeyRepeatEnabled(false);

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
                gameObjPtr->_position.x = gObj["posX"].GetDouble();
                gameObjPtr->_position.y = gObj["posY"].GetDouble();

                gameObjects.push_back(gameObjPtr);
            }
        }
        fclose(fileHndlr);
#pragma endregion

        thor::Action walkUp(sf::Keyboard::Up, thor::Action::Hold);
        thor::Action walkDown(sf::Keyboard::Down, thor::Action::Hold);
        thor::Action walkLeft(sf::Keyboard::Left, thor::Action::Hold);
        thor::Action walkRight(sf::Keyboard::Right, thor::Action::Hold);
        thor::Action close(sf::Event::Closed);

        thor::ActionMap<std::string> actionMap;
        actionMap["walkUp"] = walkUp;
        actionMap["walkDown"] = walkDown;
        actionMap["walkLeft"] = walkLeft;
        actionMap["walkRight"] = walkRight;
        actionMap["close"] = close;


#pragma region inputcompo
        pzr::InputComponent* iptcpt = new pzr::InputComponent();
        gameObjects[0]->setInputCpnt(iptcpt);
        pzr::EventNotifier<pzr::KeyBoardEvent> kntf;
        kntf.registerListener(iptcpt);
#pragma endregion

        bool walkingUp = false, walkingLeft = false, walkingRight = false, walkingDown = false, alreadyNotified = false;
        sf::Clock clock;
        while (window.isOpen())
        {
            actionMap.update(window);
            if (actionMap.isActive("close"))
                window.close();
            if (actionMap.isActive("walkUp"))
            {
                kntf.notify(pzr::EVT_UP);
                walkingUp = true;
            }
            else
            {
                walkingUp = false;
                alreadyNotified = false;
            }
                
            if (actionMap.isActive("walkDown"))
            {
                kntf.notify(pzr::EVT_DOWN);
                walkingDown = true;
            }
            else
            {
                walkingDown = false;
                alreadyNotified = false;
            }
            if (actionMap.isActive("walkLeft"))
            {
                kntf.notify(pzr::EVT_LEFT);
                walkingLeft = true;
            }
            else
            {
                walkingLeft = false;
                alreadyNotified = false;
            }
            if (actionMap.isActive("walkRight"))
            {
                kntf.notify(pzr::EVT_RIGHT);
                walkingRight = true;
            }
            else
            {
                walkingRight = false;
                alreadyNotified = false;
            }
            if (!walkingDown && !walkingRight && !walkingLeft && !walkingUp && alreadyNotified==false)
            {
                kntf.notify(pzr::EVT_NONE);
                alreadyNotified = true;
            }
            window.clear();

            sf::Time t = clock.restart();
            for (pzr::GameObject* gObj : gameObjects)
            {
                gObj->update(t);
            }

            window.display();
        }
    }
	return res;
}