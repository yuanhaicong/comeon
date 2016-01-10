#include "MallScene.h"
#include "UserData.h"
#include "SelectEntryScene.h"
#include "LevelScene.h"
#include "StateLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* MallScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MallScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	//	scene->autorelease();
	// return the scene
	return scene;
}

bool MallScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//add Mall_Scene 和 获取购买按钮
	auto rootNode = CSLoader::createNode("Mall_Scene.csb");
	addChild(rootNode);
	auto pay_menu = dynamic_cast<Button*>(rootNode->getChildByName("pay_menu"));
	pay_menu->addClickEventListener(CC_CALLBACK_1(MallScene::pay_menu, this));

	//add state bar
	auto stateLayer = StateLayer::create();
	addChild(stateLayer);
	stateLayer->setPosition(-1.27, 784.37);

	// 获取状态条
	auto node2 = dynamic_cast<Node*>(stateLayer->getChildByName("statebarnode"));
	auto statusbar = dynamic_cast<Layout*>(node2->getChildByName("statusbar"));
	auto plus_btn = dynamic_cast<Button*>(Helper::seekWidgetByName(statusbar, "plus_btn"));
	auto plus_btn1 = dynamic_cast<Button*>(Helper::seekWidgetByName(statusbar, "plus_btn1"));
	plus_btn->setVisible(false);
	plus_btn1->setVisible(false);
	//金币 钻石 标签
	goldcount = dynamic_cast<Text*>(Helper::seekWidgetByName(statusbar, "goldcount"));
	diamondcount = dynamic_cast<Text*>(Helper::seekWidgetByName(statusbar, "diamondcount"));

	// add Mall_Diamond_Layer
	rootNode_Diamond = CSLoader::createNode("Mall_Diamond_Layer.csb");
	addChild(rootNode_Diamond);

	// add Mall_Diamond_Layer
	rootNode_Bean = CSLoader::createNode("Mall_Bean_Layer.csb");
	addChild(rootNode_Bean);
	rootNode_Bean->setVisible(false);

	// get goback button 
	auto goback_btn = dynamic_cast<Button*>(rootNode->getChildByName("goback"));
	goback_btn->addClickEventListener(CC_CALLBACK_1(MallScene::goback, this));

	// get bean_title and diamond_title
	auto mall_lable_node = dynamic_cast<Node*>(rootNode->getChildByName("mall_lable"));
	bean_title_btn = dynamic_cast<Button*>(mall_lable_node->getChildByName("bean_title"));
	bean_title_btn->addClickEventListener(CC_CALLBACK_1(MallScene::diamond_to_bean, this));
	diamond_title_btn = dynamic_cast<Button*>(mall_lable_node->getChildByName("diamond_title"));
	diamond_title_btn->addClickEventListener(CC_CALLBACK_1(MallScene::bean_to_diamond, this));
	diamond_title_btn->setTouchEnabled(false);
	diamond_title_btn->setBright(false);

	//  获取欢乐豆元素
	twist1 = dynamic_cast<Sprite*>(rootNode_Bean->getChildByName("twist1"));
	bean6 = dynamic_cast<Button*>(rootNode_Bean->getChildByName("bean_6"));
	bean6->addClickEventListener(CC_CALLBACK_1(MallScene::bean_select6, this));

	twist2 = dynamic_cast<Sprite*>(rootNode_Bean->getChildByName("twist2"));
	bean18 = dynamic_cast<Button*>(rootNode_Bean->getChildByName("bean_18"));
	bean18->addClickEventListener(CC_CALLBACK_1(MallScene::bean_select18, this));

	twist3 = dynamic_cast<Sprite*>(rootNode_Bean->getChildByName("twist3"));
	bean38 = dynamic_cast<Button*>(rootNode_Bean->getChildByName("bean_38"));
	bean38->addClickEventListener(CC_CALLBACK_1(MallScene::bean_select38, this));

	twist4 = dynamic_cast<Sprite*>(rootNode_Bean->getChildByName("twist4"));
	bean65 = dynamic_cast<Button*>(rootNode_Bean->getChildByName("bean_65"));
	bean65->addClickEventListener(CC_CALLBACK_1(MallScene::bean_select65, this));

	//  获取钻石元素
	twist5 = dynamic_cast<Sprite*>(rootNode_Diamond->getChildByName("twist5"));
	diamond60 = dynamic_cast<Button*>(rootNode_Diamond->getChildByName("diamond_60"));
	diamond60->addClickEventListener(CC_CALLBACK_1(MallScene::diamond_select60, this));

	twist6 = dynamic_cast<Sprite*>(rootNode_Diamond->getChildByName("twist6"));
	diamond210 = dynamic_cast<Button*>(rootNode_Diamond->getChildByName("diamond_210"));
	diamond210->addClickEventListener(CC_CALLBACK_1(MallScene::diamond_select210, this));

	twist7 = dynamic_cast<Sprite*>(rootNode_Diamond->getChildByName("twist7"));
	diamond320 = dynamic_cast<Button*>(rootNode_Diamond->getChildByName("diamond_320"));
	diamond320->addClickEventListener(CC_CALLBACK_1(MallScene::diamond_select320, this));

	twist8 = dynamic_cast<Sprite*>(rootNode_Diamond->getChildByName("twist8"));
	diamond650 = dynamic_cast<Button*>(rootNode_Diamond->getChildByName("diamond_650"));
	diamond650->addClickEventListener(CC_CALLBACK_1(MallScene::diamond_select650, this));

	purchase_type = 0;
	return true;
}

void MallScene::goback(Ref *ref)
{
	if (Scene_to_MallScene_type == 1)
	{
		auto transitions = TransitionCrossFade::create(0.5f, SelectEntryScene::createScene());
		Director::getInstance()->replaceScene(transitions);
	}
	else if (Scene_to_MallScene_type == 2)
	{
		auto transitions = TransitionCrossFade::create(0.5f, LevelScene::createScene());
		Director::getInstance()->replaceScene(transitions);
	}
}

void MallScene::diamond_to_bean(Ref *ref)
{
	rootNode_Diamond->setVisible(false);
	rootNode_Bean->setVisible(true);
	diamond_title_btn->setTouchEnabled(true);
	diamond_title_btn->setBright(true);
	bean_title_btn->setTouchEnabled(false);
	bean_title_btn->setBright(false);
}

void MallScene::bean_to_diamond(Ref *ref)
{
	rootNode_Bean->setVisible(false);
	rootNode_Diamond->setVisible(true);
	bean_title_btn->setTouchEnabled(true);
	bean_title_btn->setBright(true);
	diamond_title_btn->setTouchEnabled(false);
	diamond_title_btn->setBright(false);
}

void MallScene::bean_select6(Ref *ref)
{
	bean_diamond_select(bean6, bean18, bean38, bean65, twist1, twist2, twist3, twist4, 1);
}

void MallScene::bean_select18(Ref *ref)
{
	bean_diamond_select(bean18, bean6, bean38, bean65, twist2, twist1, twist3, twist4, 2);
}

void MallScene::bean_select38(Ref *ref)
{
	bean_diamond_select(bean38, bean18, bean6, bean65, twist3, twist2, twist1, twist4, 3);
}

void MallScene::bean_select65(Ref *ref)
{
	bean_diamond_select(bean65, bean18, bean38, bean6, twist4, twist2, twist3, twist1, 4);
}

void MallScene::diamond_select60(Ref *ref)
{
	bean_diamond_select(diamond60, diamond210, diamond320, diamond650, twist5, twist6, twist7, twist8, 5);
}

void MallScene::diamond_select210(Ref *ref)
{
	bean_diamond_select(diamond210, diamond60, diamond320, diamond650, twist6, twist5, twist7, twist8, 6);
}

void MallScene::diamond_select320(Ref *ref)
{
	bean_diamond_select(diamond320, diamond210, diamond60, diamond650, twist7, twist6, twist5, twist8, 7);
}

void MallScene::diamond_select650(Ref *ref) 
{
	bean_diamond_select(diamond650, diamond210, diamond320, diamond60, twist8, twist6, twist7, twist5, 8);
}

void MallScene::bean_diamond_select(Button* btn1, Button* btn2, Button* btn3, Button* btn4, Sprite* spr1, Sprite* spr2, Sprite* spr3, Sprite* spr4, int type)
{
	purchase_type = type;

	btn1->setTouchEnabled(false);
	btn1->setBright(false);
	btn2->setTouchEnabled(true);
	btn2->setBright(true);
	btn3->setTouchEnabled(true);
	btn3->setBright(true);
	btn4->setTouchEnabled(true);
	btn4->setBright(true);
	
	spr1->setVisible(true);
	spr1->runAction(CCRotateTo::create(150, 9000));
	spr2->setVisible(false);
	spr3->setVisible(false);
	spr4->setVisible(false);
}

void MallScene::pay_menu(Ref *ref)
{
	switch (purchase_type)
	{
	case 1:
		purchase_bean(60000, 50);
		break;
	case 2:
		purchase_bean(185000, 150);
		break;
	case 3:
		purchase_bean(380000, 300);
		break;
	case 4:
		purchase_bean(650000, 500);
		break;
	default:
		break;
	}
}

void MallScene::purchase_bean(int bean, int diamond)
{
	int beanValue = UserData::sharedUserData()->getBean();
	int diamondValue = UserData::sharedUserData()->getDiamond();
	if (diamondValue < diamond)
	{
		// 钻石不足提示
		return;
	}
	beanValue += bean;
	diamondValue -= diamond;
	UserData::sharedUserData()->setBean(beanValue);
	UserData::sharedUserData()->setDiamond(diamondValue);
	Value val(UserData::sharedUserData()->getBean());
	goldcount->setText(val.asString());
	val = UserData::sharedUserData()->getDiamond();
	diamondcount->setText(val.asString());
}