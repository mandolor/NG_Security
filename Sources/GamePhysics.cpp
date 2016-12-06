#include "GamePhysics.h"
#include "GameObject.h"
#include "SphereContainer.h"
#include <map>

//---------------------------------------------------------------------
namespace
{
	typedef std::map<ObjectCollisionType, std::vector<ObjectCollisionType>> CollisionList;
	CollisionList define_collisitions_list;
}

//---------------------------------------------------------------------
void GamePhysics::initialise()
{
	_initCollisionsList();
	_fillCollisionsList();
}

//---------------------------------------------------------------------
void GamePhysics::_initCollisionsList()
{
	define_collisitions_list.insert( make_pair( ObjectCollisionType::BlackSphere, std::vector<ObjectCollisionType>() ) );
}

//---------------------------------------------------------------------
void GamePhysics::_fillCollisionsList()
{
	define_collisitions_list[ObjectCollisionType::RedSphere].push_back( ObjectCollisionType::NoCollision );
	define_collisitions_list[ObjectCollisionType::YellowSphere].push_back( ObjectCollisionType::NoCollision );

	define_collisitions_list[ObjectCollisionType::BlackSphere].push_back( ObjectCollisionType::RedSphere );
	define_collisitions_list[ObjectCollisionType::BlackSphere].push_back( ObjectCollisionType::YellowSphere );

	define_collisitions_list[ObjectCollisionType::FireSphere].push_back( ObjectCollisionType::RedSphere );
	define_collisitions_list[ObjectCollisionType::FireSphere].push_back( ObjectCollisionType::YellowSphere );

	define_collisitions_list[ObjectCollisionType::WaterSphere].push_back( ObjectCollisionType::RedSphere );
	define_collisitions_list[ObjectCollisionType::WaterSphere].push_back( ObjectCollisionType::YellowSphere );

	define_collisitions_list[ObjectCollisionType::AirSphere].push_back( ObjectCollisionType::RedSphere );
	define_collisitions_list[ObjectCollisionType::AirSphere].push_back( ObjectCollisionType::YellowSphere );

	define_collisitions_list[ObjectCollisionType::StoneSphere].push_back( ObjectCollisionType::RedSphere );
	define_collisitions_list[ObjectCollisionType::StoneSphere].push_back( ObjectCollisionType::YellowSphere );

	//--------------------------------------------------------------------
	// sphere collision lists
	//--------------------------------------------------------------------
	define_collisitions_list[ObjectCollisionType::BlackSphere].push_back( ObjectCollisionType::AirSphere );
	define_collisitions_list[ObjectCollisionType::BlackSphere].push_back( ObjectCollisionType::WaterSphere );
	define_collisitions_list[ObjectCollisionType::BlackSphere].push_back( ObjectCollisionType::FireSphere );
	define_collisitions_list[ObjectCollisionType::BlackSphere].push_back( ObjectCollisionType::StoneSphere );
	define_collisitions_list[ObjectCollisionType::BlackSphere].push_back( ObjectCollisionType::BlackSphere );

	define_collisitions_list[ObjectCollisionType::AirSphere].push_back( ObjectCollisionType::BlackSphere );
	define_collisitions_list[ObjectCollisionType::AirSphere].push_back( ObjectCollisionType::WaterSphere );
	define_collisitions_list[ObjectCollisionType::AirSphere].push_back( ObjectCollisionType::FireSphere );
	define_collisitions_list[ObjectCollisionType::AirSphere].push_back( ObjectCollisionType::StoneSphere );
	define_collisitions_list[ObjectCollisionType::AirSphere].push_back( ObjectCollisionType::AirSphere );

	define_collisitions_list[ObjectCollisionType::WaterSphere].push_back( ObjectCollisionType::BlackSphere );
	define_collisitions_list[ObjectCollisionType::WaterSphere].push_back( ObjectCollisionType::AirSphere );
	define_collisitions_list[ObjectCollisionType::WaterSphere].push_back( ObjectCollisionType::FireSphere );
	define_collisitions_list[ObjectCollisionType::WaterSphere].push_back( ObjectCollisionType::StoneSphere );
	define_collisitions_list[ObjectCollisionType::WaterSphere].push_back( ObjectCollisionType::WaterSphere );

	define_collisitions_list[ObjectCollisionType::FireSphere].push_back( ObjectCollisionType::BlackSphere );
	define_collisitions_list[ObjectCollisionType::FireSphere].push_back( ObjectCollisionType::AirSphere );
	define_collisitions_list[ObjectCollisionType::FireSphere].push_back( ObjectCollisionType::WaterSphere );
	define_collisitions_list[ObjectCollisionType::FireSphere].push_back( ObjectCollisionType::StoneSphere );
	define_collisitions_list[ObjectCollisionType::FireSphere].push_back( ObjectCollisionType::FireSphere );

	define_collisitions_list[ObjectCollisionType::TransformSphere].push_back( ObjectCollisionType::BlackSphere );
	define_collisitions_list[ObjectCollisionType::TransformSphere].push_back( ObjectCollisionType::FireSphere );
	define_collisitions_list[ObjectCollisionType::TransformSphere].push_back( ObjectCollisionType::WaterSphere );
	define_collisitions_list[ObjectCollisionType::TransformSphere].push_back( ObjectCollisionType::AirSphere );
	define_collisitions_list[ObjectCollisionType::TransformSphere].push_back( ObjectCollisionType::StoneSphere );
	//--------------------------------------------------------------------
}

//---------------------------------------------------------------------
bool GamePhysics::_checkCollisionConflicts( const ObjectCollisionType& i_first_collision, const ObjectCollisionType& i_second_collision )
{
	const std::vector<ObjectCollisionType>& collision_vector = define_collisitions_list[i_first_collision];
	auto it_find = std::find( collision_vector.begin(), collision_vector.end(), i_second_collision );

	if ( it_find == collision_vector.end() )
		return true;
	else
		return false;
}

//---------------------------------------------------------------------
void GamePhysics::update()
{
	const std::vector<GameObject*>& p_physics_objects = mp_sphere_container->getPhysicsObjects();

	for ( auto it_first_collided_object : p_physics_objects )
	{
		GameObject* p_first_object = it_first_collided_object;

		if ( p_first_object->isAlreadyCollided() )
			continue;

		for ( auto it_second_collided_object : p_physics_objects )
		{
			GameObject* p_second_object = it_second_collided_object;

			if ( p_second_object->isAlreadyCollided() )
				continue;

			if ( it_first_collided_object == it_second_collided_object )
				continue;

			const ObjectCollisionType& first_collision_type = p_first_object->getObjectCollisionType();
			const ObjectCollisionType& second_collision_type = p_second_object->getObjectCollisionType();

			if ( _checkCollisionConflicts( first_collision_type, second_collision_type ) )
				continue;

			const cocos2d::Vec2& first_position = p_first_object->getPosition();
			const cocos2d::Vec2& second_position = p_second_object->getPosition();

			cocos2d::Vec2 distance_vector = first_position - second_position;
			float distance_value = distance_vector.length();

			float first_radius = p_first_object->getCollisionRadius();
			float second_radius = p_second_object->getCollisionRadius();

			bool distance_checked = distance_value < ( first_radius + second_radius ) ? true : false;

			if ( distance_checked )
			{
				p_first_object->collideWithObject( p_second_object );
				p_second_object->collideWithObject( p_first_object );

				p_first_object->needsUpdate();
				p_second_object->needsUpdate();
			}
		}
	}

	for ( auto it_collided_object : p_physics_objects )
	{
		if ( it_collided_object->isVisible() )
			it_collided_object->readyForCollision();
	}
}

