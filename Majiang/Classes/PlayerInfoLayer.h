#ifndef __Mahjong__PlayerInfoLayer__
#define __Mahjong__PlayerInfoLayer__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
class PlayerInfoLayer : public Layer
{
public:
	CREATE_FUNC(PlayerInfoLayer);
	bool init();

protected:
	void getPlayerInfo();          //��ȡ�û���Ϣ
	Node*playerinfobox;
private:

};

#endif /* defined(__Mahjong__PlayerInfoLayer__) */
