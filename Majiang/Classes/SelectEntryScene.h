#ifndef __SELECTENTRY_SCENE_H__
#define __SELECTENTRY_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
class SelectEntryScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SelectEntryScene);
	
	void goback(cocos2d::Ref *ref);
	void click_hainan_btn(cocos2d::Ref *ref);
	void click_common_btn(cocos2d::Ref *ref);
	~SelectEntryScene();
};
#endif // #define __SELECTENTRY_SCENE_H__


