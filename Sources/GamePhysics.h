#ifndef COLLISIONS_H
#define COLLISIONS_H

class SphereContainer;
enum class ObjectCollisionType;

//---------------------------------------------------------------------
class GamePhysics
{
public:
	GamePhysics( SphereContainer* ip_sphere_container ) : mp_sphere_container( ip_sphere_container ) {};
	~GamePhysics() {};

	void initialise();
	void update();

protected:
	void _initCollisionsList();
	void _fillCollisionsList();
	bool _checkCollisionConflicts( const ObjectCollisionType& i_first_collision, const ObjectCollisionType& i_second_collision );
	
private:
	GamePhysics( const GamePhysics& ) {};

private:
	SphereContainer*							mp_sphere_container;
};

#endif











