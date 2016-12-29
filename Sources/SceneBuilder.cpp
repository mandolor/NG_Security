#include "SceneBuilder.h"

//---------------------------------------------------------------------
void SceneBuilder::buildSceneByRule( const SecurityScene& i_scene, SceneRule* i_rule )
{

}

//---------------------------------------------------------------------
SceneDirector::SceneDirector( cocos2d::Node* i_scene )
{
	m_scene_builder = new SceneBuilder( i_scene );
}

//---------------------------------------------------------------------
void SceneDirector::buildSecurityScenes()
{

}

//---------------------------------------------------------------------
void SceneDirector::updateSecurityScenes()
{

}
