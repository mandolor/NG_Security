#ifndef SPRITE_CACHE_H
#define SPRITE_CACHE_H

#include "cocos2d.h"
#include <string>

//---------------------------------------------------------------------
class SpriteCache
{
public:
	static SpriteCache* getInstance();
	static void create( const cocos2d::Node* ip_cache_node );

public:
	cocos2d::Node* cloneSprite( const std::string& i_sprite_path );

private:
	SpriteCache( const cocos2d::Node* ip_cache_node );
	~SpriteCache();
	SpriteCache( const SpriteCache& ) {}

private:
	static SpriteCache*			mp_instance;
	const cocos2d::Node*		mp_cache_node;
};

#endif