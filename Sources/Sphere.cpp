#include "Sphere.h"
#include "GlobalSceneSensor.h"
#include "SpriteCache.h"
#include "GlobalGameStates.h"
#include "GameScene.h"

//---------------------------------------------------------------------
namespace
{
	const float g_warning_distance = 96.0f;
}

//---------------------------------------------------------------------
Sphere::Sphere()
	: m_red_mass( 0 )
	, m_yel_mass( 0 )
	, mp_enemy( nullptr )
	, mp_sprite( nullptr )
	, m_velocity( cocos2d::Vec2(0, 0) )
	, m_position( cocos2d::Vec2(0, 0) )
	, m_target_position( cocos2d::Vec2(0, 0) )
{}

//---------------------------------------------------------------------
void Sphere::_initialise( SecurityTargetType i_type, cocos2d::Node* ip_sprite )
{
	mp_sprite = ip_sprite;
	m_object_collision_type = i_type;

	m_position = mp_sprite->getPosition();
	m_logic_state = SphereLogicState::NoMove;

	mp_sprite->setVisible( true );
	mp_sprite->setScale( GameConstants::base_scale );
}

//---------------------------------------------------------------------
const cocos2d::Vec2& Sphere::getPosition() const
{
	return m_position;
}

//---------------------------------------------------------------------
void Sphere::setPosition(const cocos2d::Vec2& i_position)
{
	m_position = i_position;
	mp_sprite->setPosition( m_position );
}

//---------------------------------------------------------------------
bool Sphere::isVisible() const
{
	return mp_sprite->isVisible();
}

//---------------------------------------------------------------------
void Sphere::setVisible( bool i_visible )
{
	mp_sprite->setVisible( i_visible );
}

//---------------------------------------------------------------------
const float Sphere::getCollisionRadius() const
{
	int index = static_cast< int >( m_object_collision_type );
	return g_object_collision_radius[ index ] * mp_sprite->getScale();
}

// TO DO: rewrite this segment
//---------------------------------------------------------------------
void Sphere::collideWithObject( GameObject* const i_object )
{
	const SecurityTargetType& collision_type = i_object->getObjectCollisionType();
	
	switch ( collision_type )
	{
		case SecurityTargetType::RedSphere:
		{
			m_red_mass += GameConstants::red_sphere_mass;
			m_mass += GameConstants::red_sphere_mass;
		} break;

		case SecurityTargetType::YellowSphere:
		{
			m_yel_mass += GameConstants::yellow_sphere_mass;
			m_mass += GameConstants::yellow_sphere_mass;
		} break;

		case SecurityTargetType::TransformSphere:
		{
			randomChangeSphereType();
		} break;

		// collide with other sphere
		default:
		{
			unsigned int sphere_mass = i_object->getMass();

			if ( sphere_mass < m_mass )
			{
				m_mass += ( sphere_mass - GameConstants::base_mass );
				setCollided();

				i_object->setCollided();
				i_object->killed();
			}
			else
			{
				GlobalSceneSensor* p_sensor = GameScene::getGlobalGameSensor();
				GameObject* p_food_sphere = p_sensor->getClosestFoodSphere( m_position );

				const cocos2d::Vec2& food_sphere_position = p_food_sphere->getPosition();
				setTargetPoint( p_food_sphere->getPosition() );

				m_logic_state = SphereLogicState::SeekForFood;

				m_action_finished = true;
				mp_enemy = nullptr;
			}
		} break;
	}

	float scaled_value = GameConstants::base_scale * m_mass / GameConstants::base_mass;
	mp_sprite->setScale( scaled_value );

	if ( m_collide_callback )
		m_collide_callback();
}

//---------------------------------------------------------------------
void Sphere::randomChangeSphereType()
{
	std::random_device rd;
	std::mt19937 rng( rd() );
	
	int start_index = ( int ) SecurityTargetType::FireSphere;
	int end_index = ( int ) SecurityTargetType::TransformSphere - 1;
	
	std::uniform_int_distribution<int> uni( start_index, end_index );
	int random_type_num = uni( rng );
	
	while ( random_type_num == ( int ) m_object_collision_type )
		random_type_num = uni( rng );

	m_object_collision_type = ( SecurityTargetType ) random_type_num;
	cocos2d::Node* p_parent = mp_sprite->getParent();

	// -- temp fix
	mp_sprite->setVisible( false );
	
	float scale = mp_sprite->getScale();
	float order = mp_sprite->getZOrder();
	
	std::string sprite_path = g_object_collision_sprite[ random_type_num ];
	mp_sprite = SpriteCache::getInstance()->cloneSprite( sprite_path );
	
	attachTo(p_parent, order);
	mp_sprite->setScale( scale );

	mp_sprite->setPosition( m_position );
	setTargetPoint( m_target_position );
}

//---------------------------------------------------------------------
void Sphere::setTargetPoint( const cocos2d::Vec2& i_point )
{
	m_target_position = i_point;

	if ( m_velocity.length() <= 0.0001f )
		m_velocity = GameConstants::base_speed;

	cocos2d::Vec2 direction = m_target_position - m_position;
	direction.normalize();

	float tmp_length = m_velocity.length();
	m_velocity = direction;

	m_velocity *= tmp_length;

	float sphere_angle = CC_RADIANS_TO_DEGREES( m_velocity.getAngle() );
	mp_sprite->setRotation( 270 - sphere_angle );
}

//---------------------------------------------------------------------
void Sphere::killed()
{
	GameObject::killed();
	setVisible( false );
	
	if ( m_killed_callback )
		m_killed_callback();
}

//---------------------------------------------------------------------
void Sphere::update()
{
	bool collided_with_food_sphere = ( m_object_collision_type == SecurityTargetType::YellowSphere || m_object_collision_type == SecurityTargetType::RedSphere );

	if ( collided_with_food_sphere || m_object_collision_type == SecurityTargetType::TransformSphere )
	{
		if ( m_action_finished )
			setNewRandomPosition();
	
		m_action_finished = false;
	}
	else
	{
		_updateLogic();
		_updatePosition();
	}
}

//---------------------------------------------------------------------
void Sphere::regenerateSphere()
{
	m_velocity = GameConstants::base_speed;
	m_mass = GameConstants::base_mass;

	m_target_position = cocos2d::Vec2( 0.0f, 0.0f );
	mp_sprite->setScale( GameConstants::base_scale );

	mp_sprite->setVisible( true );

	m_logic_state = SphereLogicState::NoMove;
	m_killed = false;

	m_action_finished = false;
	setNewRandomPosition();
}

//---------------------------------------------------------------------
void Sphere::_updatePosition()
{
	m_position += m_velocity;
	mp_sprite->setPosition( m_position );
}

//---------------------------------------------------------------------
void Sphere::setNewRandomPosition()
{
	std::random_device rd;
	std::mt19937 rng( rd() );

	std::uniform_int_distribution<int> uni_width( 40, GameConstants::world_width - 40 );
	std::uniform_int_distribution<int> uni_height( 40, GameConstants::world_height - 40 );

	float random_position_x = uni_width( rng );
	float random_position_y = uni_height( rng );

	m_position = cocos2d::Vec2( random_position_x, random_position_y );
	mp_sprite->setPosition( m_position );
}

//---------------------------------------------------------------------
void Sphere::_updateLogic()
{
	if ( isPlayer() )
		return;

	if ( m_killed )
	{
		regenerateSphere();
		return;
	}

	GlobalSceneSensor* p_sensor = GameScene::getGlobalGameSensor();
	
	if ( m_logic_state == SphereLogicState::NoMove )
	{
		GameObject* p_food_sphere = p_sensor->getClosestFoodSphere( m_position );
		setTargetPoint( p_food_sphere->getPosition() );
		m_logic_state = SphereLogicState::SeekForFood;
	}
	else if ( m_logic_state == SphereLogicState::SeekForFood )
	{
		if ( m_action_finished )
		{
			m_logic_state = SphereLogicState::NoMove;
		}
		
		GameObject* p_enemy = p_sensor->getClosestEnemy( m_position );
		const cocos2d::Vec2& enemy_position = p_enemy->getPosition();
		
		GameObject* p_food_sphere = p_sensor->getClosestFoodSphere( m_position );
		const cocos2d::Vec2& food_sphere_position = p_food_sphere->getPosition();
		
		m_action_finished = false;
		setTargetPoint( p_food_sphere->getPosition() );
		
		if ( ( enemy_position - m_position ).length() <= g_warning_distance )
		{
			if ( p_enemy->getMass() < m_mass )
			{
				m_logic_state = SphereLogicState::ChaseForEnemy;
				mp_enemy = p_enemy;
			}
		}
	}
	else if ( m_logic_state == SphereLogicState::ChaseForEnemy )
	{
		if ( mp_enemy->getMass() < m_mass )
		{
			const cocos2d::Vec2& enemy_position = mp_enemy->getPosition();
			setTargetPoint( enemy_position );
		}
		else
		{
			m_logic_state == SphereLogicState::NoMove;
		}
	}
}

//---------------------------------------------------------------------
void Sphere::attachTo( cocos2d::Node* ip_parent, int i_order )
{
	ip_parent->addChild( mp_sprite, i_order );
}

//---------------------------------------------------------------------
cocos2d::Vec2 Sphere::getMass() const
{
	return cocos2d::Vec2( m_red_mass, m_yel_mass );
}

//---------------------------------------------------------------------
void Sphere::setCollideCallback( void_callback i_func )
{
	m_collide_callback = i_func;
}

//---------------------------------------------------------------------
void Sphere::setKilledCallback( void_callback i_func )
{
	m_killed_callback = i_func;
}
