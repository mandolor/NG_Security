#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//---------------------------------------------------------------------
class WinScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene( int i_win_mass );
    virtual bool init();
	
	static WinScreen* create( int i_win_mass );
	
private:
	void setScore( int i_win_mass );

private:
	cocos2d::ui::Text*		m_label_score;
	
};

#endif