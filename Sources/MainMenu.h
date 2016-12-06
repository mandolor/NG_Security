#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "cocos2d.h"

//---------------------------------------------------------------------
class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif