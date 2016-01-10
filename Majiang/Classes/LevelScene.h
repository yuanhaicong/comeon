#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
class LevelScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LevelScene);
	void click_btn_level1(Ref*ref);
	void click_btn_level2(Ref*ref);
	void click_btn_level3(Ref*ref);
	void click_btn_level4(Ref*ref);
	void goback(cocos2d::Ref *ref);
	void updateOnce(float dt);
	~LevelScene();
protected:
	Node *rootNode;
};
#endif // #define __LEVEL_SCENE_H__


