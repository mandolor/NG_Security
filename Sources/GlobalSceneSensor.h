#ifndef SENSOR_H
#define SENSOR_H

#include "GameObject.h"

class SphereContainer;

//---------------------------------------------------------------------
class GlobalSceneSensor
{
public:
	GlobalSceneSensor( SphereContainer* ip_sphere_container ) : mp_sphere_container( ip_sphere_container ) {};
	~GlobalSceneSensor() {};

	GameObject*	getClosestFoodSphere( const cocos2d::Vec2& i_position ) const;
	GameObject*	getClosestEnemy( const cocos2d::Vec2& i_position ) const;

private:
	GlobalSceneSensor( const std::vector<GameObject*>& object_collection );

private:
	SphereContainer*				mp_sphere_container;
};

#endif