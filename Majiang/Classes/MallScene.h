#ifndef __HELLOWORLD_MallScene_H__
#define __HELLOWORLD_MallScene_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;
class MallScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MallScene);

public:
	Node* rootNode_Diamond;
	Node* rootNode_Bean;
	Text* goldcount;
	Text* diamondcount;
	Button* bean_title_btn;
	Button* diamond_title_btn;
	Button* bean6;
	Button* bean18;
	Button* bean38;
	Button* bean65;
	Button* diamond60;
	Button* diamond210;
	Button *diamond320;
	Button *diamond650;
	Sprite *twist1;
	Sprite *twist2;
	Sprite* twist3;
	Sprite* twist4;
	Sprite* twist5;
	Sprite* twist6;
	Sprite* twist7;
	Sprite* twist8;
	int purchase_type;
	void goback(Ref *ref);
	void diamond_to_bean(Ref *ref);
	void bean_to_diamond(Ref *ref);
	void bean_select6(Ref *ref);
	void bean_select18(Ref *ref);
	void bean_select38(Ref *ref);
	void bean_select65(Ref *ref);
	void diamond_select60(Ref *ref);
	void diamond_select210(Ref *ref);
	void diamond_select320(Ref *ref);
	void diamond_select650(Ref *ref);
	void bean_diamond_select(Button* btn1, Button* btn2, Button* btn3, Button* btn4, Sprite* spr1, Sprite* spr2, Sprite* spr3, Sprite* spr4, int type);

	void pay_menu(Ref *ref);
	void purchase_bean(int bean, int diamond);
};

#endif // __HELLOWORLD_MallScene_H__
