#include "MainMenu.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//---------------------------------------------------------------------
Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    
    scene->addChild( layer );
    return scene;
}

//---------------------------------------------------------------------
bool MainMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto sceneNode = CSLoader::createNode( "scenes/MainMenu.csb" );
    addChild(sceneNode);

    auto rootNode = sceneNode->getChildByName( "root" );
	
	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setPositionX( size.width / 2 );
	
    auto play_callback = [] ( Ref* )
    {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );
    };
	
    ui::Button* bttn_play = static_cast< ui::Button* >( rootNode->getChildByName( "bttn_play" ) );
    bttn_play->addClickEventListener( play_callback );
    
    return true;
}