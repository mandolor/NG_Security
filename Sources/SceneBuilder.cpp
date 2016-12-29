#include "SceneBuilder.h"
#include "GlobalGameStates.h"

//---------------------------------------------------------------------
void SceneRule::setMainObjectPosition( const cocos2d::Vec2& i_position )
{

}

//---------------------------------------------------------------------
void SceneRule::addTarget( const cocos2d::Vec2& i_position, const TargetType& i_type )
{

}

//---------------------------------------------------------------------
void SceneBuilder::buildSceneByRule( SecurityScene i_scene )
{

}

//---------------------------------------------------------------------
void SceneBuilder::_getRandomizedPosition( cocos2d::Vec2& i_position )
{
	std::random_device rd;
	std::mt19937 rng( rd() );

	std::uniform_int_distribution<int> uni_width( 40, GameConstants::world_width - 40 );
	std::uniform_int_distribution<int> uni_height( 40, GameConstants::world_height - 40 );

	i_position.x = uni_width( rng );
	i_position.y = uni_height( rng );
}

//---------------------------------------------------------------------
SceneDirector::SceneDirector( cocos2d::Node* i_scene )
{
	m_scene_builder = new SceneBuilder( i_scene );
}

//---------------------------------------------------------------------
void SceneDirector::buildSecurityScenes()
{
	SceneRule* p_rule_1 = new SceneRule;
	
}

//---------------------------------------------------------------------
void SceneDirector::updateSecurityScenes()
{

}

//---------------------------------------------------------------------
void TargetInformation::setTargetInformation( const cocos2d::Vec2& i_position, const TargetType& i_type )
{

}
