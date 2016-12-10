#ifndef GLOBAL_GAME_STATES_H
#define GLOBAL_GAME_STATES_H

#include <string>
#include "cocos2d.h"
#include <map>

//---------------------------------------------------------------------
enum class SphereLogicState
{
	NoMove,
	SeekForFood,
	ChaseForEnemy
};

//---------------------------------------------------------------------
enum class ObjectCollisionType
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
enum class SecurityScene
{
	TestScene1,
	TestScene2,
	TestScene3
};

//---------------------------------------------------------------------
struct SecurityObjectConfiguration
{
	unsigned int id;
	float x;
	float y;
	cocos2d::Color3B color;
};

//---------------------------------------------------------------------
struct SecuritySetupConfiguration
{
	std::vector<SecurityObjectConfiguration*> object_configurations;
	std::vector<int> object_ids;
};

//---------------------------------------------------------------------
const std::map<SecurityScene, SecuritySetupConfiguration*> security_levels;

//---------------------------------------------------------------------
const int g_object_collision_radius[] = { 0, 26, 26, 38, 38, 38, 38, 38, 30 };

//---------------------------------------------------------------------
namespace GameConstants
{
	const unsigned int world_width	= 2560;
	const unsigned int world_height = 720;

	const float red_sphere_mass		= 2.0f;
	const float yellow_sphere_mass	= 2.0f;

	const float base_scale			= 0.5f;
	const float base_mass			= 100.0f;
	
	const cocos2d::Vec2 base_speed	= { 2.0f, 2.0f };
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