#pragma once
#include "Mob.h"


class HornyMushroom : public Mob
{
private:

public:
	HornyMushroom() {};
	~HornyMushroom() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void dead();
};

