#include "SceneBuilder.h"
#include "GlobalGameStates.h"

//---------------------------------------------------------------------
void SceneRule::setMainObjectPosition( const cocos2d::Vec2& i_position )
{
	m_main_object_position = i_position;
}

//---------------------------------------------------------------------
void SceneRule::addTarget( const cocos2d::Vec2& i_position, const TargetType& i_type )
{
	static unsigned int target_index = 0;
	TargetInformation* p_target = new TargetInformation;

	p_target->setTargetInformation( i_position, i_type );
	m_target_positions.insert( std::make_pair( target_index++, p_target ) );
}

//---------------------------------------------------------------------
SceneDirector::SceneDirector( cocos2d::Node* i_scene )
{
	m_game_scene = i_scene;
}

//---------------------------------------------------------------------
void SceneDirector::buildSecurityScenes()
{
	SceneRule* p_scene_rule_1 = new SceneRule;
	p_scene_rule_1->setMainObjectPosition( cocos2d::Vec2( 200.0f, 200.0f ) );

	const unsigned int targets_count = 10;

	for ( int index = 0; index < 10; ++index )
	{
		cocos2d::Vec2 target_position = GlobalInterface::getRandomizedPosition();
		TargetType needed_color = GlobalInterface::getActionProbability() == 0 ? TargetType::YellowObject : TargetType::RedObject;
		p_scene_rule_1->addTarget( target_position, needed_color );
	}


}

//---------------------------------------------------------------------
void SceneDirector::updateSecurityScenes()
{

}

//---------------------------------------------------------------------
void TargetInformation::setTargetInformation( const cocos2d::Vec2& i_position, const TargetType& i_type )
{

}
