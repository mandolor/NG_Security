#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

//---------------------------------------------------------------------
class Rule
{
public:

};

//---------------------------------------------------------------------
class Builder
{
public:
	virtual void buildScenePartition( const Rule& i_rule ) = 0;
};

//---------------------------------------------------------------------
class Director
{
public:
	void buildScene( const Builder& i_builder );
};

#endif