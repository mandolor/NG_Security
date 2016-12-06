#ifndef TWOBYTES_SCREEN_H
#define TWOBYTES_SCREEN_H

#include "cocos2d.h"

//---------------------------------------------------------------------
class TwoBytesScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC( TwoBytesScreen );
};

#endif