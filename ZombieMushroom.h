#pragma once
#include "Mob.h"
class ZombieMushroom : public Mob
{

public:
	ZombieMushroom() {};
	~ZombieMushroom() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void dead();

};

