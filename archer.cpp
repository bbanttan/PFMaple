#include "stdafx.h"
#include "archer.h"
#include "MobManager.h"
#include "Character.h"

void archer::Mob_Search(Character* c, MobManager* mm)
{
	c->setAddHpMp(0, -need_mp);

	RECT attack_scale = RectMakeCenter(c->getX(), c->getY() - 15, 580, 170);
	//가장 가까운 몬스터찾기
	for (int i = 0; i < mm->_getvMob().size(); i++)
	{
		if (mm->_getvMob()[i]->getHP() <= 0) continue;

		RECT tempRECT;
		if (IntersectRect(&tempRECT, &attack_scale, &mm->_getvMob()[i]->getRECT()))
		{
			int rich = getDistance(c->getX(), c->getY(), mm->_getvMob()[i]->getRECT().left + (mm->_getvMob()[i]->getRECT().right - mm->_getvMob()[i]->getRECT().left) / 2, mm->_getvMob()[i]->getRECT().top + (mm->_getvMob()[i]->getRECT().bottom - mm->_getvMob()[i]->getRECT().top) / 2);

			if (c->getRL() == RIGHT && (c->getX() - mm->_getvMob()[i]->getX()) < 0)	//오른쪽을보고 공격했을때
			{
				if (c->getTemp() > rich)
				{
					c->setTemp(rich);
					c->setWho(i);
				}
			}
			else if (c->getRL() == LEFT && (c->getX() - mm->_getvMob()[i]->getX()) > 0)			//왼쪽을보고 공격했을때
			{
				if (c->getTemp() > rich)
				{
					c->setTemp(rich);
					c->setWho(i);
				}
			}
		}
	}
}