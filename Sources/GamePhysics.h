#ifndef COLLISIONS_H
#define COLLISIONS_H

class SphereContainer;
enum class SecurityTargetType;

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
	bool _checkCollisionConflicts( const SecurityTargetType& i_first_collision, const SecurityTargetType& i_second_collision );
	
private:
	GamePhysics( const GamePhysics& ) {};

private:
	SphereContainer*							mp_sphere_container;
};

#endif











