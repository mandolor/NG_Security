#include "GameScene.h"
#include "AppMacros.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Sphere.h"

#include "SphereContainer.h"
#include "GamePhysics.h"
#include "GlobalSceneSensor.h"
#include "SceneDirector.h"
#include "GlobalGameStates.h"

#pragma comment(lib, "libcocos2d.lib")

USING_NS_CC;

//---------------------------------------------------------------------
SphereContainer*		GameScene::mp_sphere_container = nullptr;
GamePhysics*			GameScene::mp_game_physics = nullptr;
GlobalSceneSensor*		GameScene::mp_game_sensor = nullptr;
SceneDirector*			GameScene::mp_scene_director = nullptr;

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
	
	auto sceneNode = CSLoader::createNode( "scenes/GameScene.csb" );
	addChild( sceneNode );
	
	auto rootNode = sceneNode->getChildByName( "root" );
	mp_game_layer = static_cast< cocos2d::Node* >( rootNode->getChildByName( "game_layer" ) );
	
	mp_sphere_container = new SphereContainer;
	mp_game_physics = new GamePhysics( mp_sphere_container );
	mp_game_sensor = new GlobalSceneSensor( mp_sphere_container );
	mp_scene_director = new SceneDirector;

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches( true );

	touchListener->onTouchBegan = CC_CALLBACK_2( GameScene::onTouchBegan, this );
	touchListener->onTouchMoved = CC_CALLBACK_2( GameScene::onTouchMoved, this );
	touchListener->onTouchEnded = CC_CALLBACK_2( GameScene::onTouchEnded, this );

	_eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );
	mp_game_physics->initialise();

	mp_scene_director->buildSecurityScenes();
	_generateSecurityObjects();

	_parallaxCreate();	
	mp_sphere_container->showAll();
	
	scheduleUpdate();
	return true;
}

//---------------------------------------------------------------------
void GameScene::update( float dt )
{
	mp_game_physics->update();
	mp_sphere_container->update();
}

//---------------------------------------------------------------------
GlobalSceneSensor* GameScene::getGlobalGameSensor()
{
	return mp_game_sensor;
}

//---------------------------------------------------------------------
void GameScene::_generateSecurityObjects()
{
	// creating main security object
	SecurityScene scene_in_process = SecurityScene::TestScene1;
	SceneRule* p_scene_rule = mp_scene_director->getSecuritySceneRule( scene_in_process );

	cocos2d::Vec2 main_security_object_position = p_scene_rule->getMainSecurityObjectPosition();

	int index_type = static_cast< int > ( SecurityTargetType::FireSphere );
	Sphere* p_sphere = mp_sphere_container->generate( SecurityTargetType::FireSphere, g_object_collision_sprite[index_type], true );
	p_sphere->attachTo( mp_game_layer, GlobalStates::object_layer_order );

	mp_sphere_container->addPhysicsObject( p_sphere );
	p_sphere->setPosition( main_security_object_position );

	p_sphere->setCollideCallback( std::bind( &GameScene::_collidePlayer, this ) );

	// creating security objects
	std::map<int, TargetInformation*> p_security_objects = p_scene_rule->getSecurityTargets();

	for ( unsigned int index = 0; index < GlobalStates::target_objects_count; ++index )
	{
		TargetInformation* p_security_target_information = p_security_objects.at( index );
		SecurityTargetType security_object_type = p_security_target_information->getTargetType();
		cocos2d::Vec2 security_object_position = p_security_target_information->getTargetPosition();

		int index_type = static_cast< int > ( security_object_type );
		Sphere* p_sphere = mp_sphere_container->generate( security_object_type, g_object_collision_sprite[index_type] );

		p_sphere->attachTo( mp_game_layer, GlobalStates::object_layer_order );
		mp_sphere_container->addPhysicsObject( p_sphere );

		p_sphere->setPosition( security_object_position );
	}
}

//---------------------------------------------------------------------
void GameScene::_collidePlayer()
{
	Sphere* p_player = mp_sphere_container->getPlayerSphere();
	cocos2d::Vec2 mass_red_yellow = p_player->getMass();

	// 	if ( !mp_game_sensor->getClosestEnemy( p_player->getPosition() ) )
	// 	{
	// 		int mass = static_cast<GameObject*>( p_player )->getMass();
	// 		mass -= GameConstants::base_mass;
	// 	
	// 		auto scene = WinScreen::createScene( mass );
	// 		Director::getInstance()->replaceScene( TransitionFade::create( 1, scene ) );
	// 	}
}

//---------------------------------------------------------------------
void GameScene::_parallaxCreate()
{
	float screen_size = Director::getInstance()->getVisibleSize().width;
	m_parallax = ParallaxNode::create();

	for ( int i = 1; i <= GlobalStates::parallax_layer_order; ++i )
	{
		std::string layer_name = "layer_" + TO_STRING( i );
		Node* p_layer = static_cast< cocos2d::Node* >( mp_game_layer->getChildByName( layer_name ) );

		float width = p_layer->getContentSize().width * p_layer->getScaleX();
		float x_ratio = ( width - screen_size ) / (GameConstants::world_width - screen_size );
	
		p_layer->removeFromParent();
		m_parallax->addChild( p_layer, GlobalStates::parallax_layer_order - i, Vec2( x_ratio, 0 ), Vec2::ZERO );
	}

	mp_game_layer->addChild( m_parallax );
}

//---------------------------------------------------------------------
// void GameScene::_generateSecurityEnemies()
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
void GameScene::draw( cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformUpdated )
{
	this->setColor( cocos2d::Color3B::BLUE );

	Layer::draw( renderer, transform, transformUpdated );
	Director* director = Director::getInstance();

	GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );

	director->pushMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW );
	director->popMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW );
}
