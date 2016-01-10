#include "UserData.h"
#include "StateLayer.h"
#include "MallScene.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PlayerInfoLayer.h"

USING_NS_CC;
using namespace ui;
StateLayer::~StateLayer()
{

}
StateLayer* StateLayer::create()
{
	StateLayer*statelayer = new StateLayer();
	if (statelayer&&statelayer->init())
	{
		statelayer->autorelease();
		
	}
	else
	{
		statelayer = NULL;
	}
	return statelayer;
}
bool StateLayer::init () {
	if (!Layer::init())
	{
		return false;
	}
	statebarNode = CSLoader::createNode("StateLayer.csb");
	addChild(statebarNode);
	statebarNode->setName("statebarnode");
	//statebarNode->setScaleX(0.8769);
	/*Size size = statebarNode->getContentSize();
	setContentSize(size);*/

	auto statusbar = dynamic_cast<Layout*>(statebarNode->getChildByName("statusbar"));
	auto Button_QQ = dynamic_cast<Button*>(Helper::seekWidgetByName(statusbar, "Button_QQ"));
	auto plus_btn = dynamic_cast<Button*>(Helper::seekWidgetByName(statusbar, "plus_btn"));
	auto plus_btn1 = dynamic_cast<Button*>(Helper::seekWidgetByName(statusbar, "plus_btn1"));

	Button_QQ->addClickEventListener([this](Ref*) {
		auto bkg = LayerColor::create(Color4B(0, 0, 0, 200));
		PlayerInfoLayer*playerinfolayer = PlayerInfoLayer::create();
		bkg->addChild(playerinfolayer);
		this->getParent()->addChild(bkg);
		});

	//  跳转到商城页面
	plus_btn->addClickEventListener([](Ref*)
	{
		auto transitions = TransitionCrossFade::create(0.5f, MallScene::createScene());
		Director::getInstance()->replaceScene(transitions);
	});

	plus_btn1->addClickEventListener([](Ref*)
	{
		auto transitions = TransitionCrossFade::create(0.5f, MallScene::createScene());
		Director::getInstance()->replaceScene(transitions);
	});

	//更新头像
	int r = 2;
	String* headicoformate = NULL;
	int LoginType = UserData::sharedUserData()->getLoginType();
	std::string path_dir = "login_in/";
	switch (LoginType)
	{
	case 0:
		r = (int)(CCRANDOM_0_1() * 9) + 1;
		headicoformate = String::createWithFormat("%sheadico%d", path_dir.c_str(), r);
		break;
	case 1:
		path_dir = FileUtils::getInstance()->getWritablePath();
		headicoformate = String::createWithFormat("%sheadico0", path_dir.c_str());
		break;
	case 2:
		r = UserData::sharedUserData()->getImg_Id();
		headicoformate = String::createWithFormat("%sheadico%d.png", path_dir.c_str(), r);
		break;
	default:break;
	}
	Button_QQ->loadTextureNormal(headicoformate->getCString());
	Button_QQ->loadTexturePressed(headicoformate->getCString());
	//更新昵称
	auto nickname = dynamic_cast<Text*>(Helper::seekWidgetByName(statusbar, "inputname"));
	nickname->setText(UserData::sharedUserData()->getNickName());
	UpDateInfo();          //更新用户信息
	return true;
}
void StateLayer::UpDateInfo()          //更新用户信息
{
	auto statusbar = dynamic_cast<Layout*>(statebarNode->getChildByName("statusbar"));
	//更新金币数量
	auto goldcount = dynamic_cast<Text*>(Helper::seekWidgetByName(statusbar, "goldcount"));
	Value value(UserData::sharedUserData()->getBean());
	goldcount->setText(value.asString());
	//更新钻石数量
	auto diamondcount = dynamic_cast<Text*>(Helper::seekWidgetByName(statusbar, "diamondcount"));
	value = UserData::sharedUserData()->getDiamond();
	diamondcount->setText(value.asString());

}
