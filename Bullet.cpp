#include "stdafx.h"
#include "Bullet.h"
#include "Character.h"
#include "MobManager.h"
#include "charEffect.h"

HRESULT Bullet::init()
{
	IMAGEMANAGER->addFrameImage("뇌전", "이미지/이펙트/총알류/뇌전.bmp", 96, 18, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("화살", "이미지/이펙트/총알류/화살.bmp", 39, 14, 1, 2, true, RGB(255, 0, 255));

	return S_OK;
}

void Bullet::release()
{

}

void Bullet::update()
{
	/* 현재 생성된 투사체벡터를 돌면서 만약에 투사체 구조체 정보에 who변수 즉, 몹의 번호와 충돌할때 
	벡터에서 투사체를 지워버리고 몹에게 hit관련 함수를 발동시킨다.
	그리고 도적 대표스킬과 궁수 대표스킬이 어찌보면 서로 같은 기능이라 도적, 궁수 조건문이 있다.*/
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		if (getDistance(_viBullet->x, _viBullet->y, _viBullet->sx, _viBullet->sy) >= 300)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			if (_viBullet->who != -1)
			{
				RECT temp;
				if (M->_getvMob()[_viBullet->who]->getHP() >= 0)
				{
					if (IntersectRect(&temp, &M->_getvMob()[_viBullet->who]->getRECT(), &_viBullet->collision))
					{					
						if (C->getRL() == RIGHT)
						{
							eft->seven_blow(_viBullet->x + 60, _viBullet->y);
							M->_getvMob()[_viBullet->who]->setHIT(M_RIGHT, _viBullet->damageY, RND->getInt(C->getSTR()));
							_viBullet = _vBullet.erase(_viBullet);

						}
						else if (C->getRL() == LEFT)
						{
							eft->seven_blow(_viBullet->x + 4, _viBullet->y);
							M->_getvMob()[_viBullet->who]->setHIT(M_LEFT, _viBullet->damageY, RND->getInt(C->getSTR()));
							_viBullet = _vBullet.erase(_viBullet);
						}
						continue;
						//만약 몹과닿았을때 벡터를 지워버리기에 아랫쪽으로가면 ++_viBullet; 가 터뜨리기때문에 컨티뉴
					}
				}
				else
				{
					_viBullet = _vBullet.erase(_viBullet);
					continue;
				}
			}
			if (_viBullet->direction == 1) {
				if (_viBullet->job == "도적") ani_Bullet_right->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
				_viBullet->collision = RectMakeCenter(_viBullet->x + 45, _viBullet->y + 15, 100, 100);
			}
			else if (_viBullet->direction == -1) {
				if(_viBullet->job == "도적") ani_Bullet_left->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
				_viBullet->collision = RectMakeCenter(_viBullet->x + 15, _viBullet->y + 15, 100, 100);
			}

			_viBullet->x += cosf(_viBullet->angle) * 10;
			if (_viBullet->who != -1)
			{
				if ((M->_getvMob()[_viBullet->who]->getRECT().top > _viBullet->y)||
					M->_getvMob()[_viBullet->who]->getRECT().bottom < _viBullet->y)
				{
					_viBullet->y += -sinf(_viBullet->angle) * 10;
				}
			}

			++_viBullet;
		}
	}
}

void Bullet::render()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (KEYMANAGER->isToggleKey('1'))
		{
			HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);

			Rectangle(getMemDC(), _vBullet[i].collision);

			SelectObject(getMemDC(), oPen);
			DeleteObject(Pen);
		}

		if (_vBullet[i].direction == 1) {
			if (_vBullet[i].job == "도적") _vBullet[i].img_Bullet->aniRender(getMemDC(), _vBullet[i].x, _vBullet[i].y, ani_Bullet_right);
			if (_vBullet[i].job == "궁수") _vBullet[i].img_Bullet->frameRender(getMemDC(), _vBullet[i].x, _vBullet[i].y);
		}
		if (_vBullet[i].direction == -1) {
			if (_vBullet[i].job == "도적") _vBullet[i].img_Bullet->aniRender(getMemDC(), _vBullet[i].x, _vBullet[i].y, ani_Bullet_left);
			if (_vBullet[i].job == "궁수") _vBullet[i].img_Bullet->frameRender(getMemDC(), _vBullet[i].x, _vBullet[i].y);
		}
		
	}
}
