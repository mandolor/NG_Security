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
	std::map<int, cocos2d::Vec2>			m_target_object_positions;
	std::map<int, TargetType>				m_interaction_order;
};

//---------------------------------------------------------------------
class SceneBuilder
{
public:
	SceneBuilder( cocos2d::Node* i_scene ) { m_game_scene = i_scene; };
	virtual void buildSceneByRule( SecurityScene i_scene );

protected:
	void _getRandomizedPosition( cocos2d::Vec2& i_position );

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