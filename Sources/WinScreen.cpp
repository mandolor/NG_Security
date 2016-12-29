#include "WinScreen.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//---------------------------------------------------------------------
Scene* WinScreen::createScene( int i_win_mass )
{
    auto scene = Scene::create();
    auto layer = WinScreen::create( i_win_mass );
	
    scene->addChild( layer );	
    return scene;
}

//---------------------------------------------------------------------
WinScreen* WinScreen::create( int i_win_mass )
{
	WinScreen *ret = new (std::nothrow) WinScreen();
	if (ret && ret->init())
	{
		ret->autorelease();
		ret->setScore( i_win_mass );
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

//---------------------------------------------------------------------
void WinScreen::setScore( int i_win_mass )
{
	m_label_score->setString( cocos2d::StringUtils::toString( i_win_mass ) );
}

//---------------------------------------------------------------------
bool WinScreen::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto sceneNode = CSLoader::createNode( "scenes/WinScreen.csb" );
    addChild(sceneNode);

    auto rootNode = sceneNode->getChildByName( "root" );
	m_label_score = static_cast< cocos2d::ui::Text* >( rootNode->getChildByName( "label_score" ) );
	
    auto next_callback = [] ( Ref* )
    {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );
    };
	
    ui::Button* bttn_play = static_cast< ui::Button* >( rootNode->getChildByName( "bttn_replay" ) );
    bttn_play->addClickEventListener( next_callback );

	ui::Button* bttn_next = static_cast< ui::Button* >( rootNode->getChildByName( "bttn_next" ) );
	bttn_next->addClickEventListener( next_callback );

// 	auto more_callback = [] ( Ref* )
// 	{
// 		auto scene = MainMenu::createScene();
// 		Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );
// 	};
	
// 	ui::Button* bttn_more = static_cast< ui::Button* >( rootNode->getChildByName( "bttn_more" ) );
// 	bttn_more->addClickEventListener( more_callback );
	
    return true;
}