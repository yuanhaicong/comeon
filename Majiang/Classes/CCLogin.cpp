#include "CCLogin.h"
#include "ui/UIText.h"
#include "curl/curl.h"
#include "spine/Json.h"
#include "UserData.h"
#include "SelectEntryScene.h"
#include "network/HttpClient.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "NDKHelper/NDKHelper.h"
#endif

USING_NS_CC;
using namespace cocos2d::network;
using namespace std;
using namespace cocos2d::ui;

size_t onHttpRequestCompleted(char* data, size_t size, size_t nmemb, string* writedata);
CCLogin::CCLogin()
{}
Widget::ccWidgetTouchCallback CCLogin::onLocateTouchCallback(const string &callBackName)
{
	if (callBackName == "onTouch")//判断事件名，返回对应的函数。下同
	{
		return CC_CALLBACK_2(CCLogin::onTouch, this);
	}
	return nullptr;
} 

Widget::ccWidgetClickCallback CCLogin::onLocateClickCallback(const string &callBackName)
{
	if (callBackName == "Click_QQ")
	{
		return CC_CALLBACK_1(CCLogin::onClickQQ, this);
	}
	if (callBackName == "Click_YK")
	{
		return CC_CALLBACK_1(CCLogin::onClickYK, this);
	}
	return nullptr;
}

Widget::ccWidgetEventCallback CCLogin::onLocateEventCallback(const string &callBackName)
{
	if (callBackName == "onEvent")
	{
		return CC_CALLBACK_2(CCLogin::onEvent, this);
	}
	return nullptr;
}

void CCLogin::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("onTouch");
}
void CCLogin::getImage(std::string image_url)
{
	HttpClient* httpClient = HttpClient::getInstance();
	HttpRequest* httpReq = new HttpRequest();
	httpReq->setRequestType(HttpRequest::Type::GET);
	httpReq->setUrl(image_url.c_str());
	//CCLOG("image_url:%s", image_url.c_str());
	httpReq->setResponseCallback(CC_CALLBACK_2(CCLogin::onGetFinished,this));
	httpReq->setTag("ImageGet");
	httpClient->setTimeoutForConnect(10);
	httpClient->send(httpReq);
	httpReq->release();
	httpReq = NULL;
}
void CCLogin::onGetFinished(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	const char* tag = response->getHttpRequest()->getTag();
	std::vector<char> *buffer = response->getResponseData();
	std::string buff = std::string(buffer->begin(), buffer->end());
	std::string path_dir = FileUtils::getInstance()->getWritablePath();
	std::string path = CCString::createWithFormat("%sheadico0", path_dir.c_str())->getCString();
	FILE *fp = fopen(path.c_str(), "wb+");
	fwrite(buff.c_str(), 1, buffer->size(), fp);
	fflush(fp);
	fclose(fp);
	//判断是否是jpg、PNG图片
	unsigned char pnghead[2];
	unsigned char jpghead[2];
	unsigned char imghead[2];
	pnghead[0] = 0x89;
	pnghead[1] = 0x50;
	jpghead[0] = 0xff;
	jpghead[1] = 0xd8;
	imghead[0] = buffer->at(0);
	imghead[1] = buffer->at(1);
	if (memcmp(pnghead, imghead, 2) != 0 && memcmp(jpghead, imghead, 2) != 0)
	{
		remove(path.c_str());
	}
	auto transitions = TransitionCrossFade::create(0.3f, SelectEntryScene::createScene());
	Director::getInstance()->replaceScene(transitions);
}
CCLogin::~CCLogin()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// 移除相关联的选择器，因为我们将要销毁当前实例
	NDKHelper::RemoveSelectorsInGroup("CCLoginSelectors");
#endif
}

// 一个回调选择器，native语言（java）将会调用它
void CCLogin::SampleSelector(Node *sender, void *data)
{

	CCDictionary *convertedData = (CCDictionary *)data;
	String *str1 = (String *)convertedData->objectForKey("ident");
	String *str2 = (String *)convertedData->objectForKey("nickname");
	String *str3 = (String *)convertedData->objectForKey("image_url");
	String *str4 = (String *)convertedData->objectForKey("gender");
	std::string ident = str1->getCString();
	std::string nickname = str2->getCString();
	std::string img_url = str3->getCString();
	std::string gender = "unknown";
	if (str4->compare("男")) gender = "male";
	else if (str4->compare("女") == 0)gender = "female";


	//处理用户信息
	CURL *curl = curl_easy_init();
	string getbackdata;
	curl_easy_setopt(curl, CURLOPT_URL, "http:\/\/203.195.160.86\/Mahjong\/interface\/login.php");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	CCString* poststr = CCString::createWithFormat("ident=%s&fromtype=1&nickname=%s&img_url=%s&gender=%s", ident.c_str(), nickname.c_str(), img_url.c_str(),gender.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, poststr->getCString());//此处ident以及nickname要改成从QQ认证返回的数据，此处只做演示
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onHttpRequestCompleted);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &getbackdata);
	int res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (res == 0)
	{
		//CCLOG("get data from is: %s\n", getbackdata.c_str());
		//以下解析json数据，读出用户id、金币、经验、精力、疲劳；然后再跳转到关卡选择页面在底部标签栏显示。
		Json* parsedata = Json_create(getbackdata.c_str());
		res = Json_getInt(parsedata, "res", 0);
		if (res == 0 || res == 1)
		{
			int id = Json_getInt(parsedata, "id", -10);
			string nickname = Json_getString(parsedata, "nickname", "");
			string gender = Json_getString(parsedata, "gender", "unknown");
			string ident = Json_getString(parsedata, "ident", "");
			string img_url = Json_getString(parsedata, "img_url", "");
			int img_id = Json_getInt(parsedata, "img_id", -10);
			int bean = Json_getInt(parsedata, "bean", -10);
			int diamond = Json_getInt(parsedata, "diamond", -10);
			int playing_times = Json_getInt(parsedata, "playing_times", -10);
			int wins = Json_getInt(parsedata, "wins", -10);
			int escape_rate = Json_getInt(parsedata, "escape_rate", -10);
			int points = Json_getInt(parsedata, "points", -10);

			UserData::sharedUserData()->setId(id);
			UserData::sharedUserData()->setNickName(nickname);
			UserData::sharedUserData()->setIdent(ident);
			UserData::sharedUserData()->setImg_Url(img_url);
			UserData::sharedUserData()->setImg_Id(img_id);
			UserData::sharedUserData()->setBean(bean);
			UserData::sharedUserData()->setDiamond(diamond);
			UserData::sharedUserData()->setGender(gender);
			UserData::sharedUserData()->setPlaying_times(playing_times);
			UserData::sharedUserData()->setWins(wins);
			UserData::sharedUserData()->setEscape_rate(escape_rate);
			UserData::sharedUserData()->setPoints(points);
			getImage(img_url);
		}
		else
		{
			if (res == 2) {
				this->addtip("注册失败");
			}
			else if (res == 3) {
				this->addtip("更新数据失败");
			}
		}

	}
	else
	{
		this->addtip("网络异常");
	}
	//getImage(image_url);//加载QQ头像

}

void CCLogin::onClickQQ(cocos2d::Ref* sender)
{
	UserData::sharedUserData()->setLoginType(1);
	//注册一个selector，那么当我们的native环境（java环境）调用这个字符串名字的函数（此处为名字为SampleSelector的函    数）的时候，这个selector可以响应请求
	//注意：设置组名是为了在析构函数中能够清除掉selector
	//SampleSelector();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	NDKHelper::AddSelector("CCLoginSelectors",
		"SampleSelector",
		callfuncND_selector(CCLogin::SampleSelector),
		this);

	// 为这个将要传递到native（也就是Java）语言中的消息设置参数
	// 在c++中发送要调用的函数名
	CCDictionary* prms = CCDictionary::create();
	prms->setObject(CCString::create("SampleSelector"), "to_be_called");
	//Map<std::string,String> prms;
	//prms.insert("to_be_called", "SampleSelector");
	// 最后在当前环境（c++）中调用native方法
	SendMessageWithParams(string("SampleSelector"), prms);
#else
	CURL *curl = curl_easy_init();
	string getbackdata;
	curl_easy_setopt(curl, CURLOPT_URL, "http:\/\/203.195.160.86\/Mahjong\/interface\/login.php");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	string ident = "1D79630B1260AE70E2F0119F022222";
	string nickname = "ENJOY";
	string gender = "male";
	string img_url = "http://203.195.160.86/Mahjong/head/5.png";
	CCString* poststr = CCString::createWithFormat("ident=%s&fromtype=1&nickname=%s&img_url=%s&gender=%s", ident.c_str(), nickname.c_str(), img_url.c_str(),gender.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, poststr->getCString());//此处ident以及nickname要改成从QQ认证返回的数据，此处只做演示
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onHttpRequestCompleted);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &getbackdata);
	int res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (res == 0)
	{
		CCLOG("get data from is: %s\n", getbackdata.c_str());
		//以下解析json数据，读出用户id、金币、经验、精力、疲劳；然后再跳转到关卡选择页面在底部标签栏显示。
		Json* parsedata = Json_create(getbackdata.c_str());
		res = Json_getInt(parsedata, "res", 0);
		if (res == 0 || res == 1)
		{
			int id = Json_getInt(parsedata, "id", -10);
			string nickname = Json_getString(parsedata, "nickname", "");
			string gender = Json_getString(parsedata, "gender", "unknown");
			string ident = Json_getString(parsedata, "ident", "");
			string img_url = Json_getString(parsedata, "img_url", "");
			int img_id = Json_getInt(parsedata, "img_id", -10);
			int bean = Json_getInt(parsedata, "bean", -10);
			int diamond = Json_getInt(parsedata, "diamond", -10);
			int playing_times = Json_getInt(parsedata, "playing_times", -10);
			int wins = Json_getInt(parsedata, "wins", -10);
			int escape_rate = Json_getInt(parsedata, "escape_rate", -10);
			int points = Json_getInt(parsedata, "points", -10);

			UserData::sharedUserData()->setId(id);
			UserData::sharedUserData()->setNickName(nickname);
			UserData::sharedUserData()->setIdent(ident);
			UserData::sharedUserData()->setImg_Url(img_url);
			UserData::sharedUserData()->setImg_Id(img_id);
			UserData::sharedUserData()->setBean(bean);
			UserData::sharedUserData()->setDiamond(diamond);
			UserData::sharedUserData()->setGender(gender);
			UserData::sharedUserData()->setPlaying_times(playing_times);
			UserData::sharedUserData()->setWins(wins);
			UserData::sharedUserData()->setEscape_rate(escape_rate);
			UserData::sharedUserData()->setPoints(points);

			//UserData::sharedUserData()->flush();
			getImage(img_url);
			/*auto transitions = TransitionCrossFade::create(0.5f, SelectEntryScene::createScene());
			Director::getInstance()->replaceScene(transitions);*/
		}
		else
		{
			if (res == 2) {
				this->addtip("注册失败");
			}
			else if (res == 3) {
				this->addtip("更新数据失败");
			}
		}

	}
	else
	{
		this->addtip("网络异常");
	}
#endif
}

void CCLogin::onClickYK(cocos2d::Ref* sender)
{
	//String str=FileUtils::getInstance()->getWritablePath();
	UserData::sharedUserData()->setLoginType(2);
	string ident = UserDefault::sharedUserDefault()->getStringForKey("ident", "");
	CURL *curl = curl_easy_init();
	string getbackdata;
	curl_easy_setopt(curl, CURLOPT_URL, "http:\/\/203.195.160.86\/Mahjong\/interface\/login.php");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	CCString* poststr = CCString::createWithFormat("ident=%s&fromtype=0", ident.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, poststr->getCString());//此处ident以及nickname要改成从QQ认证返回的数据，此处只做演示
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onHttpRequestCompleted);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &getbackdata);
	int res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (res == 0)
	{
		CCLOG("get data from is: %s\n", getbackdata.c_str());
		//以下解析json数据，读出用户id、金币、经验、精力、疲劳；然后再跳转到关卡选择页面在底部标签栏显示。
		Json* parsedata = Json_create(getbackdata.c_str());
		res = Json_getInt(parsedata, "res", 0);
		if (res == 0 || res == 1)
		{
			int id = Json_getInt(parsedata, "id", -10);
			string nickname = Json_getString(parsedata, "nickname", "");
			string gender = Json_getString(parsedata, "gender", "unknown");
			string ident = Json_getString(parsedata, "ident", "");
			string img_url = Json_getString(parsedata, "img_url", "");
			int img_id = Json_getInt(parsedata, "img_id", -10);
			int bean = Json_getInt(parsedata, "bean", -10);
			int diamond = Json_getInt(parsedata, "diamond", -10);
			int playing_times = Json_getInt(parsedata, "playing_times", -10);
			int wins = Json_getInt(parsedata, "wins", -10);
			int escape_rate = Json_getInt(parsedata, "escape_rate", -10);
			int points = Json_getInt(parsedata, "points", -10);

			UserData::sharedUserData()->setId(id);
			UserData::sharedUserData()->setNickName(nickname);
			UserData::sharedUserData()->setIdent(ident);
			UserData::sharedUserData()->setImg_Url(img_url);
			UserData::sharedUserData()->setImg_Id(img_id);
			UserData::sharedUserData()->setBean(bean);
			UserData::sharedUserData()->setDiamond(diamond);
			UserData::sharedUserData()->setGender(gender);
			UserData::sharedUserData()->setPlaying_times(playing_times);
			UserData::sharedUserData()->setWins(wins);
			UserData::sharedUserData()->setEscape_rate(escape_rate);
			UserData::sharedUserData()->setPoints(points);

			UserData::sharedUserData()->flush();
			auto transitions = TransitionCrossFade::create(0.5f, SelectEntryScene::createScene());
			Director::getInstance()->replaceScene(transitions);

		}
		else
		{
			if (res == 2) {
				this->addtip("注册失败");
			}
			else if (res == 3) {
				this->addtip("更新数据失败");
			}
		}

	}
	else
	{
		this->addtip("网络异常");
	}

}

void CCLogin::onEvent(cocos2d::Ref* sender, int eventType)
{
	CCLOG("onEvent");
}

void CCLogin::addtip(std::string str)
{
	const char * pTitle = str.c_str();
	CCLabelTTF* label = CCLabelTTF::create(pTitle, "Arial", 18);
	ccColor3B color = ccc3(240, 10, 134);
	label->setColor(color);
	this->addChild(label, 1);
	CCSize winSize = Director::getInstance()->getWinSize();
	label->setPosition(ccp(winSize.width*0.5, winSize.height*0.7));
}