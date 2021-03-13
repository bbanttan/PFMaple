#pragma once
#include "gameNode.h"

class login : public gameNode
{
private:
	int next;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	int getNext() { return next; }
};

