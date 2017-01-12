#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//---------------------------------------------------------------------
class WinScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	
	static WinScreen* create();
};

#endif