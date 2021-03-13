#pragma once
#include "gameNode.h"
#include <vector>

class Character;
class MobManager;
class charEffect;

class Bullet : public gameNode
{
private:
	struct tagBullet
	{
		RECT collision;
		image* img_Bullet;
		string job;
		float x, y, sx, sy, angle, direction, damageY, mx, my;
		int who;
	};

	animation* ani_Bullet_left;
	animation* ani_Bullet_right;

	Character* C;
	MobManager* M;
	charEffect* eft;

	vector<tagBullet>					_vBullet;
	vector<tagBullet>::iterator			_viBullet;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Throw(float _x, float _y, float _angle, int _direction, int _who, Character* c, MobManager* m, float _setDmgY, string _job, charEffect* _eft)
	{
		tagBullet tBullet;

		if (_direction == 1) {
			if (_job == "µµÀû")
			{
				int arrAni[] = { 2, 3 };
				tBullet.img_Bullet = IMAGEMANAGER->findImage("³úÀü");
				ani_Bullet_right = new animation;
				ani_Bullet_right->init(tBullet.img_Bullet->getWidth(), tBullet.img_Bullet->getHeight(), tBullet.img_Bullet->getFrameWidth(), tBullet.img_Bullet->getFrameHeight());
				ani_Bullet_right->setPlayFrame(arrAni, 2, true);
				ani_Bullet_right->setFPS(1);
				ani_Bullet_right->start();
			}
			else if(_job == "±Ã¼ö")
			{
				tBullet.img_Bullet = IMAGEMANAGER->findImage("È­»ì");
				tBullet.img_Bullet->setFrameY(1);
			}
		}
		else if (_direction == -1) {
			if (_job == "µµÀû")
			{
				int arrAni[] = { 0, 1 };
				tBullet.img_Bullet = IMAGEMANAGER->findImage("³úÀü");
				ani_Bullet_left = new animation;
				ani_Bullet_left->init(tBullet.img_Bullet->getWidth(), tBullet.img_Bullet->getHeight(), tBullet.img_Bullet->getFrameWidth(), tBullet.img_Bullet->getFrameHeight());
				ani_Bullet_left->setPlayFrame(arrAni, 2, true);
				ani_Bullet_left->setFPS(1);
				ani_Bullet_left->start();
			}
			else if (_job == "±Ã¼ö")
			{
				tBullet.img_Bullet = IMAGEMANAGER->findImage("È­»ì");
				tBullet.img_Bullet->setFrameY(0);
			}
		}

		tBullet.who = _who;
		tBullet.x = tBullet.sx = _x;
		tBullet.y = tBullet.sy = _y;
		tBullet.angle = _angle;
		tBullet.direction = _direction;
		tBullet.damageY = _setDmgY;
		tBullet.job = _job;
		C = c;
		M = m;
		eft = _eft;
		_vBullet.push_back(tBullet);
	}
};

