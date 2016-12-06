#include "SphereContainer.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameObject.h"
#include "Sphere.h"

//---------------------------------------------------------------------
SphereContainer::SphereContainer() : mp_player_sphere( nullptr )
{
}

//---------------------------------------------------------------------
SphereContainer::~SphereContainer()
{
	for ( auto sphere : m_sphere_collection )
		delete sphere;
	
	m_sphere_collection.clear();
}

//---------------------------------------------------------------------
Sphere* SphereContainer::getPlayerSphere()
{
	return mp_player_sphere;
}

//---------------------------------------------------------------------
void SphereContainer::update()
{
	for ( auto sphere : m_sphere_collection )
	{
		sphere->update();
	}
}

//---------------------------------------------------------------------
void SphereContainer::showAll()
{
	for ( auto sphere : m_sphere_collection )
	{
		sphere->setVisible( true );
	}
}

//---------------------------------------------------------------------
void SphereContainer::hideAll()
{
	for ( auto sphere : m_sphere_collection )
	{
		sphere->setVisible( false );
	}
}

//---------------------------------------------------------------------
void SphereContainer::addPhysicsObject( GameObject* ip_object )
{
	mp_physics_objects.push_back( ip_object );
}

//---------------------------------------------------------------------
const std::vector<GameObject*>& SphereContainer::getPhysicsObjects() const
{
	return mp_physics_objects;
}

//---------------------------------------------------------------------
const std::vector<Sphere*>& SphereContainer::getSphereCollection() const
{
	return m_sphere_collection;
}

//---------------------------------------------------------------------
Sphere* SphereContainer::generate( const ObjectCollisionType& i_coll_type, std::string i_sprite_path, bool is_player )
{
	cocos2d::FileUtils* p_file_utils = cocos2d::FileUtils::getInstance();
	std::string file_ext = p_file_utils->getFileExtension( i_sprite_path );

	cocos2d::Node* p_sprite = nullptr;

	if ( file_ext == ".png" )
	{
		p_sprite = cocos2d::Sprite::create( i_sprite_path );
	}
	else
	{
		p_sprite = cocos2d::CSLoader::createNode( i_sprite_path );
		cocostudio::timeline::ActionTimeline* p_action = cocos2d::CSLoader::createTimeline( i_sprite_path );

		p_action->gotoFrameAndPlay( 0, true );
		p_sprite->runAction( p_action );
	}
	
	return generate( i_coll_type, p_sprite, is_player );
}

//---------------------------------------------------------------------
Sphere* SphereContainer::generate( const ObjectCollisionType& i_coll_type, cocos2d::Node* ip_sprite, bool is_player )
{
	Sphere*	p_sphere = new Sphere;
	p_sphere->_initialise( i_coll_type, ip_sprite );

	p_sphere->setNewRandomPosition();
	p_sphere->setVisible( false );

	m_sphere_collection.push_back( p_sphere );

	if ( is_player )
	{
		if ( mp_player_sphere )
			mp_player_sphere->setPlayer( false );
	
		mp_player_sphere = p_sphere;
		mp_player_sphere->setPlayer( is_player );
	}
	
	return p_sphere;
}