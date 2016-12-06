#include "GlobalSceneSensor.h"
#include "SphereContainer.h"

//---------------------------------------------------------------------
GameObject*	GlobalSceneSensor::getClosestFoodSphere( const cocos2d::Vec2& i_position ) const
{
	float minimal_distance = 2000000.0f;
	GameObject* p_nearest_object = nullptr;

	const std::vector<GameObject*>& p_object_container = mp_sphere_container->getPhysicsObjects();

	for ( auto object : p_object_container )
	{
		ObjectCollisionType collision_type = object->getObjectCollisionType();
		bool not_collided_with_food_sphere = ( collision_type != ObjectCollisionType::YellowSphere && collision_type != ObjectCollisionType::RedSphere );

		if ( not_collided_with_food_sphere || !object->isVisible() || object->getPosition().equals( i_position ) )
		{
			continue;
		}

		float length = ( object->getPosition() - i_position ).length();

		if ( length < minimal_distance )
		{
			minimal_distance = length;
			p_nearest_object = object;
		}
	}

	return p_nearest_object;
}

//---------------------------------------------------------------------
GameObject*	GlobalSceneSensor::getClosestEnemy( const cocos2d::Vec2& i_position ) const
{
	float minimal_distance = 2000000.0f;
	GameObject* p_nearest_object = nullptr;

	const std::vector<GameObject*>& p_object_container = mp_sphere_container->getPhysicsObjects();
	
	for ( auto object : p_object_container )
	{
		ObjectCollisionType collision_type = object->getObjectCollisionType();
		bool collided_with_food_sphere = ( collision_type == ObjectCollisionType::YellowSphere || collision_type == ObjectCollisionType::RedSphere );

		if ( collided_with_food_sphere || collision_type == ObjectCollisionType::TransformSphere || !object->isVisible() || object->getPosition().equals( i_position ) )
			continue;
		
		float length = ( object->getPosition() - i_position ).length();
		
		if ( length < minimal_distance )
		{
			minimal_distance = length;
			p_nearest_object = object;
		}
	}
	
	return p_nearest_object;
}