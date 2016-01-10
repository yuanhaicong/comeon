#include "StaticData.h"
#include "UserData.h"
#include "PlayerInfoLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
// on "init" you need to initialize your instance
bool PlayerInfoLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	playerinfobox = CSLoader::createNode("PlayerInfo.csb");
	addChild(playerinfobox);

	auto modelDialogListener = EventListenerTouchOneByOne::create();
	modelDialogListener->onTouchBegan = [](Touch *touch, Event *event){
		return true;
	};
	modelDialogListener->setSwallowTouches(true);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(modelDialogListener, this);

	auto Panel_info = dynamic_cast<Layout*>(playerinfobox->getChildByName("Panel_info"));
	auto btnClose = dynamic_cast<Button*>(Helper::seekWidgetByName(Panel_info, "Button_close"));
	btnClose->addClickEventListener([this](Ref*) {
		this->removeAllChildrenWithCleanup(true);
		this->getParent()->removeFromParentAndCleanup(true);
	});

	getPlayerInfo();//�����û���Ϣ
	return true;
}
void PlayerInfoLayer::getPlayerInfo()
{
	auto Panel_info = dynamic_cast<Layout*>(playerinfobox->getChildByName("Panel_info"));

	//����ͷ��
	//wchar_t buf[1000];
	//GetCurrentDirectory(1000, buf);  //�õ���ǰ����·��
	int r = 2;
	String* headicoformate = NULL;
	int LoginType = UserData::sharedUserData()->getLoginType();
	std::string path_dir = "login_in/";
	switch (LoginType)
	{
	case 0:
		r = (int)(CCRANDOM_0_1() * 9) + 1;
		headicoformate = String::createWithFormat("%sheadico%d", path_dir.c_str(),r);
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
	auto logo = dynamic_cast<Sprite*>(Panel_info->getChildByName("logo"));
	logo->setTexture(headicoformate->getCString());
	//�����ǳ�
	auto nickname = dynamic_cast<Text*>(Helper::seekWidgetByName(Panel_info, "Text_name"));
	nickname->setText(UserData::sharedUserData()->getNickName());
	//ʤ��
	auto Text_wins = dynamic_cast<Text*>(Helper::seekWidgetByName(Panel_info, "Text_wins"));
	Value value(UserData::sharedUserData()->getWins());
	Text_wins->setText(value.asString());
	//�Ա�
	string gender = UserData::sharedUserData()->getGender();
	auto Text_gender = dynamic_cast<Text*>(Helper::seekWidgetByName(Panel_info, "Text_gender"));
	Text_gender->setText(STATIC_DATA_STRING(gender));
	
	//������
	auto Text_escape = dynamic_cast<Text*>(Helper::seekWidgetByName(Panel_info, "Text_escape"));
	value = UserData::sharedUserData()->getEscape_rate();
	Text_escape->setText(value.asString());
	//���
	auto Text_goldcnt = dynamic_cast<Text*>(Helper::seekWidgetByName(Panel_info, "Text_goldcnt"));
	value = UserData::sharedUserData()->getBean();
	Text_goldcnt->setText(value.asString());
	//����
	auto Text_points = dynamic_cast<Text*>(Helper::seekWidgetByName(Panel_info, "Text_points"));
	value = UserData::sharedUserData()->getPoints();
	Text_points->setText(value.asString());
	//��ʯ��
	auto Text_diamondcnt = dynamic_cast<Text*>(Helper::seekWidgetByName(Panel_info, "Text_diamondcnt"));
	value = UserData::sharedUserData()->getDiamond();
	Text_diamondcnt->setText(value.asString());
	//�ܾ���
	auto Text_times = dynamic_cast<Text*>(Helper::seekWidgetByName(Panel_info, "Text_times"));
	value = UserData::sharedUserData()->getPlaying_times();
	Text_times->setText(value.asString());
}