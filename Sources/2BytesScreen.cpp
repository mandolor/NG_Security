#include "2BytesScreen.h"
#include "MainMenu.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//---------------------------------------------------------------------
Scene* TwoBytesScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = TwoBytesScreen::create();
    
    scene->addChild( layer );
    return scene;
}

//---------------------------------------------------------------------
bool TwoBytesScreen::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto sceneNode = CSLoader::createNode( "scenes/2BytesScreen.csb" );
    addChild( sceneNode );

	auto rootNode = sceneNode->getChildByName( "root" );

	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setPositionX( size.width / 2 );
	
    auto callback = []( Touch* touch, Event* event ) -> bool
    {
        auto scene = MainMenu::createScene();
        Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );

        return true;
    };
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches( true );

    touchListener->onTouchBegan = callback;
    _eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );

    return true;
}