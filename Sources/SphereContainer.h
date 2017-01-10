#ifndef SPHERE_CONTAINER_H
#define SPHERE_CONTAINER_H

#include "cocos2d.h"

class Sphere;
class GameObject;
enum class SecurityTargetType;

//---------------------------------------------------------------------
class SphereContainer
{
public:
	SphereContainer();
	~SphereContainer();

	void update();
	
	void showAll();
	void hideAll();

	Sphere* generate( const SecurityTargetType& i_coll_type, cocos2d::Node* ip_sprite, bool is_player = false );
	Sphere* generate( const SecurityTargetType& i_coll_type, std::string i_sprite_path, bool is_player = false );
	
	Sphere* getPlayerSphere();
	const std::vector<Sphere*>& getSphereCollection() const;

	void addPhysicsObject( GameObject* ip_object );
	const std::vector<GameObject*>& getPhysicsObjects() const;

private:
	Sphere*							mp_player_sphere;
	std::vector<GameObject*>		mp_physics_objects;
	std::vector<Sphere*>			m_sphere_collection;

private:
	SphereContainer( const SphereContainer& ) {}

};

//---------------------------------------------------------------------

#endif