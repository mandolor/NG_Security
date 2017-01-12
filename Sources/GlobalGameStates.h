#ifndef GLOBAL_GAME_STATES_H
#define GLOBAL_GAME_STATES_H

#include <string>
#include "cocos2d.h"
#include <map>

namespace GlobalStates
{
	const unsigned int	target_objects_count = 10;
	const unsigned int	object_layer_order = 10;
	const unsigned int	parallax_layer_order = 6;
}

//---------------------------------------------------------------------
enum class SphereLogicState
{
	NoMove,
	SeekForFood,
	ChaseForEnemy
};

//---------------------------------------------------------------------
enum class SecurityTargetType
{
	NoCollision,
	RedSphere,
	YellowSphere,
	FireSphere,
	BlackSphere,
	WaterSphere,
	AirSphere,
	StoneSphere,
	TransformSphere
};

//---------------------------------------------------------------------
const std::string g_object_collision_sprite[] = { "",
	"textures/red-ball.png",
	"textures/yellow-ball.png",
	"anims/point_fire.csb",
	"anims/point_black.csb",
	"anims/point_ice.csb",
	"anims/point_rubber.csb",
	"anims/point_rock.csb",
	"textures/transform-sphere.png",
};

//---------------------------------------------------------------------
const int g_object_collision_radius[] = { 0, 26, 26, 38, 38, 38, 38, 38, 30 };

//---------------------------------------------------------------------
namespace GameConstants
{
	const unsigned int world_width	= 1366;
	const unsigned int world_height = 768;

	const float red_sphere_mass		= 2.0f;
	const float yellow_sphere_mass	= 2.0f;

	const float base_scale			= 0.5f;
	const float base_mass			= 100.0f;
	
	const cocos2d::Vec2 base_speed	= { 2.0f, 2.0f };
};

//---------------------------------------------------------------------
class GlobalInterface
{
public:
	static cocos2d::Vec2 getRandomizedPosition()
	{
		std::random_device rd;
		std::mt19937 rng( rd() );

		std::uniform_int_distribution<int> uni_width( 40, GameConstants::world_width - 40 );
		std::uniform_int_distribution<int> uni_height( 40, GameConstants::world_height - 40 );

		return cocos2d::Vec2( uni_width( rng ), uni_height( rng ) );
	}

	static bool getActionProbability()
	{
		std::random_device rd;
		std::mt19937 rng( rd() );

		std::uniform_int_distribution<int> probability( 0, 1 );
		return probability( rng );
	}
};

//---------------------------------------------------------------------
class GlobalGameStates
{
public:
	static GlobalGameStates& getInstance()
	{
		static GlobalGameStates instance;
		return instance;
	}

	void setGameState( const std::string& state_key, bool state_value )
	{ 
	}

	bool getGameState( const std::string& state_key )
	{
		return true;
	}

private:
	GlobalGameStates() {}
	GlobalGameStates( const GlobalGameStates& ) {}
	~GlobalGameStates() {}

};

#endif