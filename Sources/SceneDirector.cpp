#include "SceneDirector.h"

//---------------------------------------------------------------------
cocos2d::Vec2 SceneRule::getMainSecurityObjectPosition() const
{
	return m_main_object_position;
}

//---------------------------------------------------------------------
std::map<int, TargetInformation*> SceneRule::getSecurityTargets() const
{
	return m_target_configurations;
}

//---------------------------------------------------------------------
std::vector<SecurityTargetType> SceneRule::getInteractionOrder() const
{
	return m_interaction_order;
}

//---------------------------------------------------------------------
void SceneRule::_setMainObjectPosition( const cocos2d::Vec2& i_position )
{
	m_main_object_position = i_position;
}

//---------------------------------------------------------------------
void SceneRule::_addTarget( const cocos2d::Vec2& i_position, const SecurityTargetType& i_type )
{
	TargetInformation* p_target = new TargetInformation;
	p_target->_setTargetInformation( i_position, i_type );
	m_target_configurations.insert( std::make_pair( m_target_index_counter++, p_target ) );
}

//---------------------------------------------------------------------
void SceneRule::_setInteractionOrder( const std::vector<SecurityTargetType>& i_order )
{
	m_interaction_order = i_order;
}

//---------------------------------------------------------------------
void SceneDirector::buildSecurityScenes()
{
	//---------------------------------------------------------------------
	SceneRule* p_scene_rule_1 = new SceneRule;
	p_scene_rule_1->_setMainObjectPosition( cocos2d::Vec2( 200.0f, 200.0f ) );

	_setUpSceneWithSecurityTargets( p_scene_rule_1 );

	std::vector<SecurityTargetType> p_target_orders_scene_1 = { SecurityTargetType::YellowSphere, SecurityTargetType::RedSphere, SecurityTargetType::YellowSphere };
	p_scene_rule_1->_setInteractionOrder( p_target_orders_scene_1 );

	m_scene_rules.insert( std::make_pair( SecurityScene::TestScene1, p_scene_rule_1 ) );

	//---------------------------------------------------------------------
	SceneRule* p_scene_rule_2 = new SceneRule;
	p_scene_rule_2->_setMainObjectPosition( cocos2d::Vec2( 400.0f, 200.0f ) );

	_setUpSceneWithSecurityTargets( p_scene_rule_2 );

	std::vector<SecurityTargetType> p_target_orders_scene_2 = { SecurityTargetType::RedSphere, SecurityTargetType::YellowSphere, SecurityTargetType::RedSphere };
	p_scene_rule_2->_setInteractionOrder( p_target_orders_scene_2 );

	m_scene_rules.insert( std::make_pair( SecurityScene::TestScene2, p_scene_rule_2 ) );

	//---------------------------------------------------------------------
	SceneRule* p_scene_rule_3 = new SceneRule;
	p_scene_rule_3->_setMainObjectPosition( cocos2d::Vec2( 400.0f, 400.0f ) );

	_setUpSceneWithSecurityTargets( p_scene_rule_3 );

	std::vector<SecurityTargetType> p_target_orders_scene_3 = { SecurityTargetType::YellowSphere, SecurityTargetType::YellowSphere, SecurityTargetType::RedSphere };
	p_scene_rule_3->_setInteractionOrder( p_target_orders_scene_3 );

	m_scene_rules.insert( std::make_pair( SecurityScene::TestScene3, p_scene_rule_3 ) );
}

//---------------------------------------------------------------------
SceneRule* SceneDirector::getSecuritySceneRule( const SecurityScene& i_scene )
{
	return m_scene_rules.at( i_scene );
}

//---------------------------------------------------------------------
void SceneDirector::_setUpSceneWithSecurityTargets( SceneRule* i_scene_rule )
{
	for ( int index = 0; index < GlobalStates::target_objects_count; ++index )
	{
		cocos2d::Vec2 target_position = GlobalInterface::getRandomizedPosition();
		SecurityTargetType needed_color = GlobalInterface::getActionProbability() == 0 ? SecurityTargetType::YellowSphere : SecurityTargetType::RedSphere;
		i_scene_rule->_addTarget( target_position, needed_color );
	}
}

//---------------------------------------------------------------------
cocos2d::Vec2 TargetInformation::getTargetPosition() const
{
	return m_target_position;
}

//---------------------------------------------------------------------
SecurityTargetType TargetInformation::getTargetType() const
{
	return m_target_type;
}

//---------------------------------------------------------------------
void TargetInformation::_setTargetInformation( const cocos2d::Vec2& i_position, const SecurityTargetType& i_type )
{
	m_target_position = i_position;
	m_target_type = i_type;
}
