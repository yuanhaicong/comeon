#ifndef __STATE_LAYER_H__
#define __STATE_LAYER_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
class StateLayer:public Layer
{
public:
	static StateLayer* create();
	bool init();
	void UpDateInfo();          //��ȡ�û���Ϣ
	~StateLayer();
	Node* statebarNode;
};
#endif // #define __STATE_LAYER_H__