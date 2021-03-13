#pragma once
#include "gameNode.h"

class Character;
class MobManager;
class Map;

class chobo : public gameNode
{

public:
	chobo() {};
	~chobo() {};

	void Mob_Search(Character* c, MobManager* mm);
	void Mob_Knock(Character* c, MobManager * mm, Map* map);
};