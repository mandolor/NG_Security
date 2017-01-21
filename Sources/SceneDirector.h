#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "cocos2d.h"
#include "GlobalGameStates.h"

//---------------------------------------------------------------------
enum class SecurityScene
{
	TestScene1,
	TestScene2,
	TestScene3
};

//---------------------------------------------------------------------
class TargetInformation
{
public:
	cocos2d::Vec2 getTargetPosition() const;
	SecurityTargetType getTargetType() const;

protected:
	void _setTargetInformation( const cocos2d::Vec2& i_position, const SecurityTargetType& i_type );

private:
	cocos2d::Vec2							m_target_position;
	SecurityTargetType						m_target_type;

private:
	friend class SceneRule;
};

//---------------------------------------------------------------------
class SceneRule
{
public:
	SceneRule() : m_target_index_counter( 0 ) {};
	cocos2d::Vec2							getMainSecurityObjectPosition() const;
	std::map<int, TargetInformation*>		getSecurityTargets() const;
	std::vector<SecurityTargetType>			getInteractionOrder() const;

protected:
	void _setMainObjectPosition( const cocos2d::Vec2& i_position );
	void _addTarget( const cocos2d::Vec2& i_position, const SecurityTargetType& i_type );
	void _setInteractionOrder( const std::vector<SecurityTargetType>& i_order );

private:
	cocos2d::Vec2							m_main_object_position;
	std::map<int, TargetInformation*>		m_target_configurations;
	std::vector<SecurityTargetType>			m_interaction_order;
	unsigned int							m_target_index_counter;
	
private:
	friend class SceneDirector;
};

//---------------------------------------------------------------------
class SceneDirector
{
public:
	void buildSecurityScenes();
	SceneRule* getSecuritySceneRule( const SecurityScene& i_scene );

protected:
	void _setUpSceneWithSecurityTargets( SceneRule* i_scene_rule );

private:
	std::map<SecurityScene, SceneRule*>		m_scene_rules;
};

#endif