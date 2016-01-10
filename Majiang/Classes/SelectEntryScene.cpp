#include "UserData.h"
#include "SelectEntryScene.h"
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StateLayer.h"
#include "LevelScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* SelectEntryScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SelectEntryScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	//	scene->autorelease();
	// return the scene
	return scene;
}


bool SelectEntryScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	UserData::sharedUserData()->setGameType(-1);
	auto rootNode = CSLoader::createNode("SelectEntryScene.csb");
	addChild(rootNode);
	auto stateLayer = StateLayer::create();
	addChild(stateLayer);
	stateLayer->setPosition(-1.27, 784.37);
	Scene_to_MallScene_type = 1;

	auto userinfo = rootNode->getChildByName("ProjectNode_2");
	auto buttonleft = dynamic_cast<Button*>(rootNode->getChildByName("Button_left"));
	auto buttonright = dynamic_cast<Button*>(rootNode->getChildByName("Button_right"));
	auto levelSelector = dynamic_cast<PageView*>(userinfo->getChildByName("PageView_select"));

	/*levelSelector->addEventListener([levelSelector, buttonleft, buttonright]
		(Ref*, PageView::EventType) {
		switch (levelSelector->getCurPageIndex()) {
		case 0:
			buttonLeft->setVisible(false);
			buttonRight->setVisible(true);
			buttonStart->setVisible(true);
			break;
		case 1:
			buttonLeft->setVisible(true);
			buttonRight->setVisible(true);
			buttonStart->setVisible(false);
			break;
		case 2:
			buttonLeft->setVisible(true);
			buttonRight->setVisible(false);
			buttonStart->setVisible(false);
			break;
		default:
			buttonLeft->setVisible(true);
			buttonRight->setVisible(true);
			buttonStart->setVisible(true);
			break;
		}
	});*/

	buttonleft->addClickEventListener([levelSelector](Ref*) {
		levelSelector->scrollToPage(levelSelector->getCurPageIndex() - 1);
	});

	buttonright->addClickEventListener([levelSelector, this](Ref*) {
		levelSelector->scrollToPage(levelSelector->getCurPageIndex() + 1);
	});

	auto hainan_btn = dynamic_cast<Button*>(rootNode->getChildByName("Button_15"));
	hainan_btn->addClickEventListener(CC_CALLBACK_1(SelectEntryScene::click_hainan_btn, this));

	auto common_btn = dynamic_cast<Button*>(rootNode->getChildByName("Button_16"));
	common_btn->addClickEventListener(CC_CALLBACK_1(SelectEntryScene::click_common_btn, this));

	auto goback_btn = dynamic_cast<Button*>(rootNode->getChildByName("Button_20"));
	goback_btn->addClickEventListener(CC_CALLBACK_1(SelectEntryScene::goback, this));
	return true;
}
void SelectEntryScene::goback(cocos2d::Ref *ref)
{
	auto transitions = TransitionCrossFade::create(0.3f, LevelScene::createScene());
	Director::getInstance()->replaceScene(transitions);
}
void SelectEntryScene::click_hainan_btn(cocos2d::Ref *ref)
{
	UserData::sharedUserData()->setGameType(1);
	auto transitions = TransitionCrossFade::create(0.3f, LevelScene::createScene());
	Director::getInstance()->replaceScene(transitions);
}
void SelectEntryScene::click_common_btn(cocos2d::Ref *ref)
{
	UserData::sharedUserData()->setGameType(2);
	auto transitions = TransitionCrossFade::create(0.5f, LevelScene::createScene());
	Director::getInstance()->replaceScene(transitions);
}
SelectEntryScene::~SelectEntryScene()
{

}

