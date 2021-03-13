#include "stdafx.h"
#include "magic.h"
#include "MobManager.h"
#include "Character.h"
#include "Map.h"

void magic::update() 
{
	if (cnt != 0)
	{
		if ((cnt % 10) == 0)
		{
			Mob_Knock();
		}
		if (cnt == 10)
		{
			temp = 10000;
			who = -1;
		}
		cnt--;
	}
}

void magic::Mob_Search(Character* _c, MobManager* _mm, Map* _map, charEffect* _eft)
{

		_c->setAddHpMp(0, -need_mp);
		c = _c;
		mm = _mm;
		m = _map;
		eft = _eft;

		RECT attack_scale = RectMakeCenter(c->getX(), c->getY() - 15, 580, 170);

		if (c->getRL() == RIGHT)	 eft->clo_1(c->getX(), c->getY() - 20);
		else if (c->getRL() == LEFT) eft->clo_2(c->getX(), c->getY() - 20);

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
					if (temp > rich)
					{
						temp = rich;
						who = i;
					}
				}
				else if (c->getRL() == LEFT && (c->getX() - mm->_getvMob()[i]->getX()) > 0)			//왼쪽을보고 공격했을때
				{
					if (temp > rich)
					{
						temp = rich;
						who = i;
					}
				}
			}
		}
}

void magic::Mob_Knock()
{
	if (who != -1)
	{
		if (mm->_getvMob()[who]->getHP() <= 0) return;

		eft->clo_blow(mm->_getvMob()[who]->getX(), mm->_getvMob()[who]->getY());

		if (mm->_getvMob()[who]->getJumpOk() == true)
		{
			mm->_getvMob()[who]->setY(m->mapExplorer(mm->_getvMob()[who]->getX(), mm->_getvMob()[who]->getY(), 150.0f));
		}
		if (c->getRL() == RIGHT)
		{
			mm->_getvMob()[who]->setHIT(M_RIGHT, (cnt == 20) * -25.0f, RND->getInt(c->getSTR()));
		}
		else if (c->getRL() == LEFT)
		{
			mm->_getvMob()[who]->setHIT(M_LEFT, (cnt == 20) * -25.0f, RND->getInt(c->getSTR()));
		}
	}
}