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
class SceneRule
{
public:
	cocos2d::Vec2							m_main_object_position;
	std::map<int, cocos2d::Vec2>			m_target_object_positions;
	std::map<int, TargetType>				m_interaction_order;
};

//---------------------------------------------------------------------
class SceneBuilder
{
public:
	SceneBuilder( cocos2d::Node* i_scene ) { m_game_scene = i_scene; };
	virtual void buildSceneByRule( const SecurityScene& i_scene, SceneRule* i_rule );

private:
	cocos2d::Node* m_game_scene;
	std::map<SecurityScene, SceneRule*> m_scene_rules;
};

//---------------------------------------------------------------------
class SceneDirector
{
public:
	SceneDirector( cocos2d::Node* i_scene );
	void buildSecurityScenes();
	void updateSecurityScenes();

private:
	SceneBuilder* m_scene_builder;
};

#endif