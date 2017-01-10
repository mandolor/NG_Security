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
	cocos2d::Vec2							getMainSecurityObjectPosition() const;
	std::map<int, TargetInformation*>		getSecurityTargets() const;
	std::vector<int>						getInteractionOrder() const;

protected:
	void _setMainObjectPosition( const cocos2d::Vec2& i_position );
	void _addTarget( const cocos2d::Vec2& i_position, const SecurityTargetType& i_type );

private:
	cocos2d::Vec2							m_main_object_position;
	std::map<int, TargetInformation*>		m_target_configurations;
	std::vector<int>						m_interaction_order;
	
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