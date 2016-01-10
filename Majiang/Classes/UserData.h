#ifndef __TTest__UserData__
#define __TTest__UserData__
//#include "cocos-ext.h"
//#include "spine/Json.h"
#include "cocos2d.h"

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace std; 

class UserData : public cocos2d::CCObject
{
public:
	static UserData* sharedUserData();

	CC_SYNTHESIZE(int, id, Id);
	CC_SYNTHESIZE(string, nickname, NickName);
    CC_SYNTHESIZE(string, ident, Ident);
	CC_SYNTHESIZE(string, img_url, Img_Url);
	CC_SYNTHESIZE(int, img_id, Img_Id);
	CC_SYNTHESIZE(int, bean, Bean);
	CC_SYNTHESIZE(int, diamond, Diamond);
	CC_SYNTHESIZE(int, wins,Wins);
	CC_SYNTHESIZE(int, escape_rate, Escape_rate);
	CC_SYNTHESIZE(int, points, Points);
	CC_SYNTHESIZE(int, playing_times, Playing_times);
	CC_SYNTHESIZE(string, gender, Gender);
	CC_SYNTHESIZE(int, LoginType, LoginType);
	CC_SYNTHESIZE(int, LevelType, LevelType);
	CC_SYNTHESIZE(int, GameType, GameType);
	void flush();
	
protected:
	UserData();
	~UserData();
	bool init();	
};
extern int Scene_to_MallScene_type;
#endif