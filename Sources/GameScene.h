#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#define DEBUG_DRAW

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GlobalSceneSensor;
class SphereContainer;
class GamePhysics;
class SceneDirector;

//---------------------------------------------------------------------
class GameScene : public cocos2d::LayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool init() override;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

	virtual void update( float dt );
	static GlobalSceneSensor* getGlobalGameSensor();

	bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event );
	void onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event );
	void onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event );

	virtual void draw( cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags ) override;	
	virtual ~GameScene();

private:
	void _generateTargetSecurityObjects();
	void _generateMainSecurityObject();
	
	//void _generateSecurityEnemies();
	
	void _correctionMapBorders( cocos2d::Vec2& i_camera_pos );
	void _collidePlayer();

	void _parallaxCreate();
	//void _parallaxProcess();
	
private:
	bool							m_touchMoved;

	cocos2d::Node*					mp_game_layer;
	cocos2d::Vec2					m_touch_began_pos;

	cocos2d::ui::Text*				mp_label_red_count;
	cocos2d::ui::Text*				mp_label_yell_count;
	
	cocos2d::ParallaxNode*			m_parallax;

	static SphereContainer*			mp_sphere_container;
	static GamePhysics*				mp_game_physics;
	static GlobalSceneSensor*		mp_game_sensor;
	static SceneDirector*			mp_scene_director;
};

#endif // __GAME_SCENE_H__
