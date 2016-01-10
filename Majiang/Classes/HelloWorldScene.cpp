#include "HelloWorldScene.h"
#include "CCLoginReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//wchar_t buf[1000];
	//GetCurrentDirectory(1000, buf);  //得到当前工作路径
	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("CCLoginReader", (ObjectFactory::Instance)CCLoginReader::getInstance);

    auto rootNode = CSLoader::createNode("LoginScene.csb");

    addChild(rootNode);

    return true;
}
