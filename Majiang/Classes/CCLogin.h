#ifndef __TestCpp__CCLogin__
#define __TestCpp__CCLogin__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;
class CCLogin: public cocos2d::Node, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
	CREATE_FUNC(CCLogin)
	CCLogin();
	virtual cocos2d::ui::Widget::ccWidgetTouchCallback
	onLocateTouchCallback(const std::string &callBackName);
	virtual cocos2d::ui::Widget::ccWidgetClickCallback
	onLocateClickCallback(const std::string &callBackName);
	virtual cocos2d::ui::Widget::ccWidgetEventCallback
	onLocateEventCallback(const std::string &callBackName);
	void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onClickQQ(cocos2d::Ref* sender);
	void onClickYK(cocos2d::Ref* sender);
	void onEvent(cocos2d::Ref* sender, int eventType);

	void addtip(std::string str);

	~CCLogin();
	void SampleSelector(Node *sender, void *data);
	void getImage(std::string image_url);
	void onGetFinished(HttpClient *sender, HttpResponse *response);
private:
	std::vector<std::string> _touchTypes;
	std::string _click;
	std::vector<std::string> _eventTypes;
};
#endif