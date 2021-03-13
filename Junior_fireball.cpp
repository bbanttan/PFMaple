#include "stdafx.h"
#include "Junior_fireball.h"
#include "Character.h"

HRESULT Junior_fireball::init()
{
	IMAGEMANAGER->addFrameImage("파이어볼", "이미지/이펙트/주발/파이어볼.bmp", 204, 68, 3, 2, true, RGB(255, 0, 255));
	eft = new MobEffect;
	eft->init();
	return S_OK;
}

void Junior_fireball::release()
{
}

void Junior_fireball::update()
{
	for (_viFb = _vFb.begin(); _viFb != _vFb.end(); )
	{
		if (getDistance(_viFb->x, _viFb->y, _viFb->sx, _viFb->sy) >= 300)
		{
			_viFb = _vFb.erase(_viFb);
		}
		else
		{
			RECT temp;
			if (IntersectRect(&temp, &C->getRECT(), &_viFb->collision))
			{
				C->setHIT();
				eft->JuniorBomb(C->getX(), C->getY());
				_viFb = _vFb.erase(_viFb);
			}
			else
			{
				if (_viFb->direction == 1) {
					ani_fireball_right->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
					_viFb->collision = RectMakeCenter(_viFb->x + 45, _viFb->y + 15, 30, 30);
				}
				else if (_viFb->direction == -1) {
					ani_fireball_left->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
					_viFb->collision = RectMakeCenter(_viFb->x + 15, _viFb->y + 15, 30, 30);
				}
				_viFb->x += cosf(_viFb->angle) * 4;
				_viFb->y += -sinf(_viFb->angle) * 4;
				
				++_viFb;
			}
		}
	}
	eft->update();
}

void Junior_fireball::render()
{
	for (int i = 0; i < _vFb.size(); ++i)
	{
		if (_vFb[i].direction == 1) {
			_vFb[i].img_fireball->aniRender(getMemDC(), _vFb[i].x, _vFb[i].y, ani_fireball_right);
		}
		if (_vFb[i].direction == -1) {
			_vFb[i].img_fireball->aniRender(getMemDC(), _vFb[i].x, _vFb[i].y, ani_fireball_left);		
		}	
	}
	eft->render();
}
