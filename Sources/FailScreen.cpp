#include "FailScreen.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//---------------------------------------------------------------------
Scene* FailScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = FailScreen::create();
    
    scene->addChild( layer );
    return scene;
}

//---------------------------------------------------------------------
bool FailScreen::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto sceneNode = CSLoader::createNode( "scenes/FailScreen.csb" );
    addChild(sceneNode);

    auto rootNode = sceneNode->getChildByName( "root" );
	
	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setPositionX( size.width / 2 );
	
    auto play_callback = [] ( Ref* )
    {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );
    };
	
    ui::Button* bttn_play = static_cast< ui::Button* >( rootNode->getChildByName( "bttn_replay" ) );
    bttn_play->addClickEventListener( play_callback );
	
// 	auto more_callback = [] ( Ref* )
// 	{
// 		auto scene = MainMenu::createScene();
// 		Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );
// 	};
	
// 	ui::Button* bttn_more = static_cast< ui::Button* >( rootNode->getChildByName( "bttn_more" ) );
// 	bttn_more->addClickEventListener( more_callback );
// 
// 	ui::Button* bttn_menu = static_cast< ui::Button* >( rootNode->getChildByName( "bttn_exit" ) );
// 	bttn_menu->addClickEventListener( more_callback );
	
    return true;
}