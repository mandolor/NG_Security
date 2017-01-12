#ifndef SPHERE_H
#define SPHERE_H

#include <functional>
#include "GameObject.h"
#include "GlobalSceneSensor.h"

typedef std::function<void( GameObject* )> function_callback;

//---------------------------------------------------------------------
class Sphere : public GameObject
{
public:
	virtual const cocos2d::Vec2& getPosition() const override;
	virtual void setPosition(const cocos2d::Vec2&) override;

	virtual bool isVisible() const override;
	virtual void setVisible( bool i_visible ) override;

    virtual const float getCollisionRadius() const override;
	virtual void collideWithObject( GameObject* const i_object ) override;

    virtual void randomChangeSphereType();
	virtual void setTargetPoint( const cocos2d::Vec2& i_point );

	virtual void update();
	virtual void regenerateSphere();
	
	virtual void killed();
	virtual cocos2d::Vec2 getMass() const;
	
	void attachTo( cocos2d::Node* ip_parent, int i_order = 0 );
	void setNewRandomPosition();
	
	void setCollideCallback( function_callback i_func );
	void setKilledCallback( function_callback i_func );

protected:
	friend class SphereContainer;
    void _initialise( SecurityTargetType i_type, cocos2d::Node* ip_sprite );

    Sphere();
	~Sphere() {};
    
protected:
	void _updateLogic();
	void _updatePosition();

protected:
	cocos2d::Node*			mp_sprite;
	cocos2d::Vec2			m_velocity;

	cocos2d::Vec2			m_position;
	cocos2d::Vec2			m_target_position;

	SphereLogicState		m_logic_state;
	
private:
	GameObject*				mp_enemy;

	float					m_red_mass;
	float					m_yel_mass;
	
/*	void_callback			m_killed_callback;*/
	function_callback			m_collide_callback;
};

#endif