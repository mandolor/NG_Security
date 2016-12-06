#include "SpriteCache.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

SpriteCache* SpriteCache::mp_instance = nullptr;

//---------------------------------------------------------------------
SpriteCache::SpriteCache( const cocos2d::Node* ip_cache_node )
	: mp_cache_node( ip_cache_node )
{}

//---------------------------------------------------------------------
SpriteCache::~SpriteCache()
{}

//---------------------------------------------------------------------
void SpriteCache::create( const cocos2d::Node* ip_cache_node )
{
	assert( !mp_instance && "SpriteCache is already created" );
	
	static SpriteCache cache( ip_cache_node );
	mp_instance = &cache;
}

//---------------------------------------------------------------------
SpriteCache* SpriteCache::getInstance()
{
	assert( mp_instance && "SpriteCache is not created" );
	return mp_instance;
}

//---------------------------------------------------------------------
cocos2d::Node* SpriteCache::cloneSprite( const std::string& i_sprite_path )
{
	cocos2d::FileUtils* p_file_utils = cocos2d::FileUtils::getInstance();
	std::string file_ext = p_file_utils->getFileExtension( i_sprite_path );
	
	cocos2d::Node* p_sprite = nullptr;

	if ( file_ext == ".png" )
	{
		p_sprite = cocos2d::Sprite::create( i_sprite_path );
	}
	else
	{
		p_sprite = cocos2d::CSLoader::createNode( i_sprite_path );
		cocostudio::timeline::ActionTimeline* p_action = cocos2d::CSLoader::createTimeline( i_sprite_path );
		
		p_action->gotoFrameAndPlay( 0, true );
		p_sprite->runAction( p_action );
	}
	
	return p_sprite;
}
