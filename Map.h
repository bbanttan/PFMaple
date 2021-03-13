#pragma once
#include "gameNode.h"
#include <vector>

class Character;
class MobManager;
class ItemManager;

struct ropeladder
{
	RECT rect;
	float x, y;
	bool isExist;
};

struct tagPortal
{
	RECT rect;
	float x, y, msg_x, msg_y;
	char map[128];
	bool isExist;
	image* img_portal;
	animation* ani_portal;
};

class Map : public gameNode
{
private:	
	tagPortal portal[2];
	
	Character* C;
	MobManager* Mb;

	ItemManager* _itemManager;

	ropeladder rpld[10];

	char currentMap[128];		//ÇöÀç¸Ê
	char currentMapland[128];	//ÇöÀç¸ÊÅõ¸í¶¥

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setropeladder(string map);

	float mapExplorer(float Ex, float Ey, float Rich);

	char* getCurrentMap() { return currentMap; }
	ropeladder* getRopeLadderInfo() { return rpld; }
	void setCharacter(Character* cha) { C = cha; }
	void setMobManager(MobManager* mb) { Mb = mb; }
	void setItemManagerAdress(ItemManager* _imanager) { _itemManager = _imanager; }
};