#include "UserData.h"
#include "LevelScene.h"
#include "SelectEntryScene.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StateLayer.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* LevelScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LevelScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	//	scene->autorelease();
	// return the scene
	return scene;
}


bool LevelScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	UserData::sharedUserData()->setLevelType(-1);
	scheduleOnce(schedule_selector(LevelScene::updateOnce), 0);
	rootNode = CSLoader::createNode("LevelScene.csb");
	addChild(rootNode);
	auto stateLayer = StateLayer::create();
	addChild(stateLayer);
	stateLayer->setPosition(-1.27, 784.37);
	Scene_to_MallScene_type = 2;

	auto btn_level1 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level1"));
	btn_level1->addClickEventListener(CC_CALLBACK_1(LevelScene::click_btn_level1,this));

	auto btn_level2 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level2"));
	btn_level2->addClickEventListener(CC_CALLBACK_1(LevelScene::click_btn_level2, this));

	auto btn_level3 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level3"));
	btn_level3->addClickEventListener(CC_CALLBACK_1(LevelScene::click_btn_level3, this));

	auto btn_level4 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level4"));
	btn_level4->addClickEventListener(CC_CALLBACK_1(LevelScene::click_btn_level4, this));

	auto goback_btn = dynamic_cast<Button*>(rootNode->getChildByName("btn_back"));
	goback_btn->addClickEventListener(CC_CALLBACK_1(LevelScene::goback, this));
	return true;
}
void LevelScene::click_btn_level1(Ref*ref)
{
	auto btn_level1 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level1"));
	auto btn_level2 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level2"));
	auto btn_level3 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level3"));
	auto btn_level4 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level4"));
	int level = UserData::sharedUserData()->getLevelType();
	switch (level)
	{
	case 1:
		break;
	case 2:
		btn_level2->loadTextureNormal("LevelScene/level2_0.png");
		break;
	case 3:
		btn_level3->loadTextureNormal("LevelScene/level3_0.png");
		break;
	case 4:
		btn_level4->loadTextureNormal("LevelScene/level4_0.png");
		break;
	}
	btn_level1->loadTextureNormal("LevelScene/level1_1.png");
	UserData::sharedUserData()->setLevelType(1);
}
void LevelScene::click_btn_level2(Ref*ref)
{
	auto btn_level1 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level1"));
	auto btn_level2 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level2"));
	auto btn_level3 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level3"));
	auto btn_level4 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level4"));
	int level = UserData::sharedUserData()->getLevelType();
	switch (level)
	{
	case 1:
		btn_level1->loadTextureNormal("LevelScene/level1_0.png");
		break;
	case 2:
		break;
	case 3:
		btn_level3->loadTextureNormal("LevelScene/level3_0.png");
		break;
	case 4:
		btn_level4->loadTextureNormal("LevelScene/level4_0.png");
		break;
	}
	btn_level2->loadTextureNormal("LevelScene/level2_1.png");
	UserData::sharedUserData()->setLevelType(2);
}
void LevelScene::click_btn_level3(Ref*ref)
{
	auto btn_level1 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level1"));
	auto btn_level2 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level2"));
	auto btn_level3 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level3"));
	auto btn_level4 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level4"));
	int level = UserData::sharedUserData()->getLevelType();
	switch (level)
	{
	case 1:
		btn_level1->loadTextureNormal("LevelScene/level1_0.png");
		break;
	case 2:
		btn_level2->loadTextureNormal("LevelScene/level2_0.png");
		break;
	case 3:
		
		break;
	case 4:
		btn_level4->loadTextureNormal("LevelScene/level4_0.png");
		break;
	}
	btn_level3->loadTextureNormal("LevelScene/level3_1.png");
	UserData::sharedUserData()->setLevelType(3);
}
void LevelScene::click_btn_level4(Ref*ref)
{
	auto btn_level1 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level1"));
	auto btn_level2 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level2"));
	auto btn_level3 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level3"));
	auto btn_level4 = dynamic_cast<Button*>(rootNode->getChildByName("btn_level4"));
	int level = UserData::sharedUserData()->getLevelType();
	switch (level)
	{
	case 1:
		btn_level1->loadTextureNormal("LevelScene/level1_0.png");
		break;
	case 2:
		btn_level2->loadTextureNormal("LevelScene/level2_0.png");
		break;
	case 3:
		btn_level3->loadTextureNormal("LevelScene/level3_0.png");
		break;
	case 4:
		
		break;
	}
	btn_level4->loadTextureNormal("LevelScene/level4_1.png");
	UserData::sharedUserData()->setLevelType(4);
}
void LevelScene::goback(cocos2d::Ref *ref)
{
	auto transitions = TransitionCrossFade::create(0.5f, SelectEntryScene::createScene());
	Director::getInstance()->replaceScene(transitions);
}
void LevelScene::updateOnce(float dt)
{
	
	switch (1)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}
LevelScene::~LevelScene()
{

}

