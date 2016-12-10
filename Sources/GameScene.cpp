
#include "GameScene.h"
#include "AppMacros.h"
#include "WinScreen.h"
#include "FailScreen.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Sphere.h"

#pragma comment(lib, "libcocos2d.lib")

USING_NS_CC;

//---------------------------------------------------------------------
namespace
{
	static const unsigned int FOOD_OBJECT_COUNT		= 30;
	static const unsigned int SPHERE_OBJECT_ORDER	= 10;
	const unsigned int PARALLAX_LAYERS_COUNT		= 6;
}

SphereContainer*		GameScene::mp_sphere_container	= nullptr;
GamePhysics*			GameScene::mp_game_physics		= nullptr;
GlobalSceneSensor*		GameScene::mp_game_sensor		= nullptr;

//---------------------------------------------------------------------
GameScene::~GameScene()
{
	cleanup();
}

//---------------------------------------------------------------------
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	GameScene* layer = GameScene::create();

	scene->addChild( layer );
	return scene;
}

//---------------------------------------------------------------------
bool GameScene::init()
{
	if ( !LayerColor::initWithColor( Color4B( 0, 0, 200, 255 ) ) )
	{
		return false;
	}

	float delta_width = designResolutionSize.width - Director::getInstance()->getVisibleSize().width;
	
	mp_sphere_container = new SphereContainer;
	mp_game_physics = new GamePhysics( mp_sphere_container );
	mp_game_sensor = new GlobalSceneSensor( mp_sphere_container );

	auto sceneNode = CSLoader::createNode( "scenes/GameScene.csb" );
	addChild( sceneNode );
	
	auto rootNode = sceneNode->getChildByName( "root" );
	mp_game_layer = static_cast< cocos2d::Node* >( rootNode->getChildByName( "game_layer" ) );

// 	auto ux_node		= static_cast< cocos2d::Node* >( rootNode->getChildByName( "ux_node" ) );
// 	auto label_yellow	= static_cast< cocos2d::ui::Text* >( ux_node->getChildByName( "label_yellow" ) );
// 
// 	mp_label_red_count	= static_cast< cocos2d::ui::Text* >( ux_node->getChildByName( "label_red_count" ) );
// 	mp_label_yell_count = static_cast< cocos2d::ui::Text* >( ux_node->getChildByName( "label_yellow_count" ) );
// 	
// 	label_yellow->setPositionX( label_yellow->getPositionX() - delta_width );
// 	mp_label_yell_count->setPositionX( mp_label_yell_count->getPositionX() - delta_width );
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches( true );

	touchListener->onTouchBegan = CC_CALLBACK_2( GameScene::onTouchBegan, this );
	touchListener->onTouchMoved = CC_CALLBACK_2( GameScene::onTouchMoved, this );
	touchListener->onTouchEnded = CC_CALLBACK_2( GameScene::onTouchEnded, this );

	_eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );
	mp_game_physics->initialise();

	//_generateFoods();
	//_generatePlayer();

	//_generateEnemies();
	_parallaxCreate();
	
	mp_sphere_container->showAll();
	
	scheduleUpdate();
	return true;
}

//---------------------------------------------------------------------
void GameScene::_parallaxCreate()
{
	float screen_size = Director::getInstance()->getVisibleSize().width;
	m_parallax = ParallaxNode::create();

	for ( int i = 1; i <= PARALLAX_LAYERS_COUNT; ++i )
	{
		std::string layer_name = "layer_" + TO_STRING( i );
		Node* p_layer = static_cast< cocos2d::Node* >( mp_game_layer->getChildByName( layer_name ) );

		float width = p_layer->getContentSize().width * p_layer->getScaleX();
		float x_ratio = ( width - screen_size ) / (GameConstants::world_width - screen_size );
	
		p_layer->removeFromParent();
		m_parallax->addChild( p_layer, PARALLAX_LAYERS_COUNT - i, Vec2( x_ratio, 0 ), Vec2::ZERO );
	}

	mp_game_layer->addChild( m_parallax );
}

//---------------------------------------------------------------------
// void GameScene::_parallaxProcess()
// {
// 	Vec2 pos = mp_sphere_container->getPlayerSphere()->getPosition();
// 	float screen_size = Director::getInstance()->getVisibleSize().width;
// 	
// 	float x_start_scroll = screen_size / 2;
// 	float x_end_scroll = GameConstants::world_width - x_start_scroll;
// 	
// 	if ( ( pos.x > x_start_scroll ) && ( pos.x < x_end_scroll ) )
// 	{
// 		float pos_x = pos.x - x_start_scroll;
// 		mp_game_layer->setPositionX( -pos_x );
// 	}
// }

//---------------------------------------------------------------------
void GameScene::_generateFoods()
{
	for ( unsigned int index = 0; index < FOOD_OBJECT_COUNT; ++index )
	{
		ObjectCollisionType type = ObjectCollisionType::RedSphere;

		int random_number = rand() % 10;

		if ( random_number < 5 )
			type = ObjectCollisionType::YellowSphere;

		int index_type = static_cast<int> ( type );
		Sphere* p_sphere = mp_sphere_container->generate( type, g_object_collision_sprite[ index_type ] );

		p_sphere->attachTo( mp_game_layer, SPHERE_OBJECT_ORDER );
		mp_sphere_container->addPhysicsObject( p_sphere );
	}
}

//---------------------------------------------------------------------
void GameScene::_collidePlayer()
{
	Sphere* p_player = mp_sphere_container->getPlayerSphere();
	cocos2d::Vec2 mass_red_yellow = p_player->getMass();
	
	mp_label_red_count->setString( TO_STRING( mass_red_yellow.x ) );
	mp_label_yell_count->setString( TO_STRING( mass_red_yellow.y ) );
	
	if ( !mp_game_sensor->getClosestEnemy( p_player->getPosition() ) )
	{
		int mass = static_cast<GameObject*>( p_player )->getMass();
		mass -= GameConstants::base_mass;
	
		auto scene = WinScreen::createScene( mass );
		Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );
	}
}

//---------------------------------------------------------------------
// void GameScene::_killedPlayer()
// {
// 	auto scene = FailScreen::createScene();
// 	Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );
// }

//---------------------------------------------------------------------
void GameScene::_generatePlayer()
{
	ObjectCollisionType type = ObjectCollisionType::FireSphere;
	int index_type = static_cast<int> ( type );
	
	Sphere* p_sphere = mp_sphere_container->generate( type, g_object_collision_sprite[ index_type ], true );
	p_sphere->attachTo( mp_game_layer, SPHERE_OBJECT_ORDER );

	mp_sphere_container->addPhysicsObject( p_sphere );
	p_sphere->setPosition( cocos2d::Vec2( 100, 100 ) );
	
	p_sphere->setCollideCallback( std::bind( &GameScene::_collidePlayer, this ) );
	//p_sphere->setKilledCallback( std::bind( &GameScene::_killedPlayer, this ) );
}

//---------------------------------------------------------------------
// void GameScene::_generateEnemies()
// {
// 	int start_index = static_cast<int> ( ObjectCollisionType::BlackSphere );
// 	int end_index = static_cast<int> ( ObjectCollisionType::TransformSphere );
// 
// 	for ( int index = start_index; index <= end_index; ++index )
// 	{
// 		ObjectCollisionType type = static_cast<ObjectCollisionType> ( index );
// 		Sphere* p_sphere = mp_sphere_container->generate( type, g_object_collision_sprite[ index ] );
// 	
// 		p_sphere->attachTo( mp_game_layer, SPHERE_OBJECT_ORDER );
// 		p_sphere->setNewRandomPosition();
// 
// 		mp_sphere_container->addPhysicsObject( p_sphere );
// 	}
// }

//---------------------------------------------------------------------
bool GameScene::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event )
{
	m_touch_began_pos = touch->getLocation();
	return true;
}

//---------------------------------------------------------------------
void GameScene::onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event )
{
	if ( m_touch_began_pos.distance( touch->getLocation() ) < 5.0f )
		return;
	
	m_touchMoved = true;
}

//---------------------------------------------------------------------
void GameScene::onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event )
{
	if ( !m_touchMoved )
 	{
		cocos2d::Vec2 vecPos = mp_game_layer->convertTouchToNodeSpace( touch );
		mp_sphere_container->getPlayerSphere()->setTargetPoint( vecPos );
	}

	m_touchMoved = false;
}

//---------------------------------------------------------------------
void GameScene::_correctionMapBorders( cocos2d::Vec2& i_camera_pos )
{
	int x_border = designResolutionSize.width - GameConstants::world_width;
	int y_border = designResolutionSize.height - GameConstants::world_height;
	
	if ( i_camera_pos.x > 0 )
		i_camera_pos.x = 0;
	else if ( i_camera_pos.x < x_border )
		i_camera_pos.x = x_border;

	if ( i_camera_pos.y > 0 )
		i_camera_pos.y = 0;
	else if ( i_camera_pos.y < y_border )
		i_camera_pos.y = y_border;
}

//---------------------------------------------------------------------
void GameScene::draw( cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformUpdated )
{
	this->setColor( cocos2d::Color3B::BLUE );

	Layer::draw( renderer, transform, transformUpdated );
	Director* director = Director::getInstance();

	GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );

	director->pushMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW );
	director->popMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW );
}

//---------------------------------------------------------------------
void GameScene::update( float dt )
{
	mp_game_physics->update();
	mp_sphere_container->update();
	
	//_parallaxProcess();
}

//---------------------------------------------------------------------
GlobalSceneSensor* GameScene::getGlobalGameSensor()
{
	return mp_game_sensor;
}
