#include "AwebiaScreen.h"
#include "2BytesScreen.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SpriteCache.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//---------------------------------------------------------------------
Scene* AwebiaScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = AwebiaScreen::create();
    
    scene->addChild( layer );
    return scene;
}

//---------------------------------------------------------------------
bool AwebiaScreen::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto sceneNode = CSLoader::createNode( "scenes/AwebiaScreen.csb" );
    addChild( sceneNode );

	auto rootNode = sceneNode->getChildByName( "root" );
	
	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setPositionX( size.width / 2 );
	
    auto callback = []( Touch* touch, Event* event ) -> bool
    {
		auto scene = TwoBytesScreen::createScene();
		Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );

        return true;
    };
	
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches( true );

    touchListener->onTouchBegan = callback;
    _eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );

    // -- create sprite cache -- //
//    auto cacheNode = CSLoader::createNode( "CacheNode.csb" );
	SpriteCache::create( cocos2d::Node::create() );
    // ------------------------- //
    
    return true;
}

//---------------------------------------------------------------------
AwebiaScreen::~AwebiaScreen()
{
	removeAllChildren();
	removeAllComponents();
}
