#include "SceneDirector.h"
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
	//---------------------------------------------------------------------
	SceneRule* p_scene_rule_1 = new SceneRule;
	p_scene_rule_1->setMainObjectPosition( cocos2d::Vec2( 200.0f, 200.0f ) );

	_setUpSceneWithTargets( p_scene_rule_1 );
	m_scene_rules.insert( std::make_pair( SecurityScene::TestScene1, p_scene_rule_1 ) );

	//---------------------------------------------------------------------
	SceneRule* p_scene_rule_2 = new SceneRule;
	p_scene_rule_2->setMainObjectPosition( cocos2d::Vec2( 400.0f, 200.0f ) );

	_setUpSceneWithTargets( p_scene_rule_2 );
	m_scene_rules.insert( std::make_pair( SecurityScene::TestScene2, p_scene_rule_2 ) );

	//---------------------------------------------------------------------
	SceneRule* p_scene_rule_3 = new SceneRule;
	p_scene_rule_3->setMainObjectPosition( cocos2d::Vec2( 400.0f, 400.0f ) );

	_setUpSceneWithTargets( p_scene_rule_3 );
	m_scene_rules.insert( std::make_pair( SecurityScene::TestScene3, p_scene_rule_3 ) );
}

//---------------------------------------------------------------------
void SceneDirector::updateSecurityScenes()
{
	static SecurityScene scene_in_process = SecurityScene::TestScene1;
	static bool scene_passed = false;





}

//---------------------------------------------------------------------
void SceneDirector::_setUpSceneWithTargets( SceneRule* i_scene_rule )
{
	for ( int index = 0; index < GlobalStates::target_objects_count; ++index )
	{
		cocos2d::Vec2 target_position = GlobalInterface::getRandomizedPosition();
		TargetType needed_color = GlobalInterface::getActionProbability() == 0 ? TargetType::YellowObject : TargetType::RedObject;
		i_scene_rule->addTarget( target_position, needed_color );
	}
}

//---------------------------------------------------------------------
void TargetInformation::setTargetInformation( const cocos2d::Vec2& i_position, const TargetType& i_type )
{

}
