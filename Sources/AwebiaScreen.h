#ifndef AWEBIA_SCREEN_H
#define AWEBIA_SCREEN_H

#include "cocos2d.h"

//---------------------------------------------------------------------
class AwebiaScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC( AwebiaScreen );

	~AwebiaScreen();
};

#endif