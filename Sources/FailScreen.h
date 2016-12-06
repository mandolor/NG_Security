#ifndef FAIL_SCREEN_H
#define FAIL_SCREEN_H

#include "cocos2d.h"

//---------------------------------------------------------------------
class FailScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(FailScreen);
};

#endif