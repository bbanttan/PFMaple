#pragma once
#include "gameNode.h"
#include "MobEffect.h"
#include <vector>

class Character;

class Junior_fireball : public gameNode
{
private:
	struct tagFireball
	{
		RECT collision;
		image* img_fireball;
		float x, y, sx, sy, angle, direction;
	};

	animation* ani_fireball_left;
	animation* ani_fireball_right;

	Character* C;
	MobEffect* eft;

	vector<tagFireball>					_vFb;
	vector<tagFireball>::iterator		_viFb;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fireball(float _x, float _y, float _angle, int _direction, Character* c) 
	{ 
		tagFireball tFireball;
	
		if (_direction == 1) {
			int arrAni[] = { 3, 4, 5 };
			tFireball.img_fireball = IMAGEMANAGER->findImage("파이어볼");
			ani_fireball_right = new animation;
			ani_fireball_right->init(tFireball.img_fireball->getWidth(), tFireball.img_fireball->getHeight(), tFireball.img_fireball->getFrameWidth(), tFireball.img_fireball->getFrameHeight());
			ani_fireball_right->setPlayFrame(arrAni, 3, true);
			ani_fireball_right->setFPS(1);
			ani_fireball_right->start();
		}
		else if (_direction == -1) {
			int arrAni[] = { 0, 1, 2 };
			tFireball.img_fireball = IMAGEMANAGER->findImage("파이어볼");
			ani_fireball_left = new animation;
			ani_fireball_left->init(tFireball.img_fireball->getWidth(), tFireball.img_fireball->getHeight(), tFireball.img_fireball->getFrameWidth(), tFireball.img_fireball->getFrameHeight());
			ani_fireball_left->setPlayFrame(arrAni, 3, true);
			ani_fireball_left->setFPS(1);
			ani_fireball_left->start();
		}
		tFireball.x = tFireball.sx = _x;
		tFireball.y = tFireball.sy = _y;
		tFireball.angle = _angle; 
		tFireball.direction = _direction;
		C = c;
		_vFb.push_back(tFireball);
	}

};

