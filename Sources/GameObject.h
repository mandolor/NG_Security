#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "cocos2d.h"
#include "GlobalGameStates.h"

//---------------------------------------------------------------------
class GameObject
{
public:
	GameObject() 
		: m_mass( GameConstants::base_mass )
		, m_killed( false )
		, m_action_finished( false )
		, m_is_player( false )
		, m_waiting_for_next_update( false )
		, m_object_collision_type( SecurityTargetType::NoCollision )
	{}

	virtual ~GameObject() {};

	virtual const cocos2d::Vec2& getPosition() const 	= 0;
	virtual void setPosition(const cocos2d::Vec2&)	 	= 0;

	virtual bool isVisible() const						= 0;
	virtual void setVisible( bool i_visible )  			= 0;

    virtual const float getCollisionRadius() const 		= 0;
	virtual void collideWithObject( GameObject* const i_object ) = 0;

	bool isPlayer() const 				{ return m_is_player; };
	void setPlayer( bool i_is_player ) 	{ m_is_player = i_is_player; };

	void needsUpdate() 					{ m_action_finished = true; };
	void setCollided() 					{ m_waiting_for_next_update = true; };

	bool isAlreadyCollided() const 		{ return m_waiting_for_next_update; };
	void readyForCollision() 			{ m_waiting_for_next_update = false; };
	
	unsigned int getMass() const	{ return m_mass; }
	virtual void killed()			{ m_killed = true; }

	const SecurityTargetType& getSecurityTargetType() const { return m_object_collision_type; }

protected:
	unsigned int							m_mass;
	bool									m_killed;

	bool									m_action_finished;
	bool									m_is_player;

	bool									m_waiting_for_next_update;
	SecurityTargetType						m_object_collision_type;
};


#endif