#ifndef __FishingJoy__FishingJoyUserData__
#define __FishingJoy__FishingJoyUserData__
#include "cocos-ext.h"
#include "spine/Json.h"

USING_NS_CC;
using namespace Json;
USING_NS_CC_EXT;
 using namespace std; 

class FishingUserData : public cocos2d::Data
{
public:

    static FishingUserData* create( Json::Value  data);
    bool init( Json::Value data );

	CC_SYNTHESIZE(int , id, Id);
    CC_SYNTHESIZE(std::string, ident, Ident);
	CC_SYNTHESIZE(std::string, imageurl, ImageUrl);
	CC_SYNTHESIZE(int , imgid, ImgId);
    CC_SYNTHESIZE(int , gold, Gold);
    CC_SYNTHESIZE(int, ep, Ep);
	CC_SYNTHESIZE(int, fag, Fag);
	CC_SYNTHESIZE(int, equip, Equip);
	CC_SYNTHESIZE(int,  grade, Grade);
	CC_SYNTHESIZE(int, crystal, Crystal);
	CC_SYNTHESIZE(std::string, nickname, NickName);
	CC_SYNTHESIZE(int, pktotal, PkTotalCount);
	CC_SYNTHESIZE(int, pkwin, PkWinCount);
	CC_SYNTHESIZE(int, pklose, PkLoseCount);

	CC_SYNTHESIZE(int, weapon_id, WeaponId);
	CC_SYNTHESIZE(int, speed, Speed);
	CC_SYNTHESIZE(int, frequence, Frequence);
	CC_SYNTHESIZE(int, scope, Scope);
	CC_SYNTHESIZE(int, crit, Crit);

protected:
};
#endif