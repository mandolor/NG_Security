#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "cocos2d.h"

//---------------------------------------------------------------------
enum class TargetType
{
	YellowObject,
	RedObject
};

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
	void setTargetInformation( const cocos2d::Vec2& i_position, const TargetType& i_type );

private:
	cocos2d::Vec2 m_target_position;
	TargetType m_target_type;
};

//---------------------------------------------------------------------
class SceneRule
{
public:
	void setMainObjectPosition( const cocos2d::Vec2& i_position );
	void addTarget( const cocos2d::Vec2& i_position, const TargetType& i_type );

private:
	cocos2d::Vec2							m_main_object_position;
	std::map<int, TargetInformation*>		m_target_positions;
	std::vector<int>						m_interaction_order;
};

//---------------------------------------------------------------------
class SceneDirector
{
public:
	SceneDirector( cocos2d::Node* i_scene );
	void buildSecurityScenes();
	void updateSecurityScenes();

protected:
	void _setUpSceneWithTargets( SceneRule* i_scene_rule );

private:
	cocos2d::Node* m_game_scene;
	std::map<SecurityScene, SceneRule*> m_scene_rules;
};

#endif