#include "stdafx.h"
#include "warrior.h"
#include "MobManager.h"
#include "Character.h"
#include "Map.h"
#include "charEffect.h"

void warrior::update()
{
	if (cnt != 0)
	{
		if ((cnt % 10) == 0)
		{
			if (Who_Target_Mob[s] != -1000)	//만약Who_Target_Mob[]배열에 값이 -1000 != 즉, 비어있지않을경우
			{								//몹때리는 함수발동
				Mob_Knock(_c, _mm, _map, s);
				eft->blust_blow(_mm->_getvMob()[Who_Target_Mob[s]]->getX(), _mm->_getvMob()[Who_Target_Mob[s]]->getY()-30);
				s++;
			}
		}
		cnt--;
	}

	//이놈때문에 어제(20,12,24 밤 10시~ 25일 새벽 2시, 25일 아침 11시~1시)까지 왜 그러는지 도저히 모르겠다가
	//결국 혼자만의 힘으로 고침 문제가 이, update함수는 캐릭터내에서 돌고있음, 왜냐하면 때리고 뒷쪽에있는놈들이 따다닥 약간의
	//인터벌을 가지고 맞아야하기때문, 그런데 난 공격이 나가는 모션에다가도 이 함수(Mob_Knock)를 넣어줬고 cnt가 30이되는 함수는
	//그 Mob_Knock함수 아래에다가 넣어줬음 그러니 계속 뻑이 나는거임 , update도 계속 이 함수를 조건에 맞으면 호출하고있고,
	//공격나가는 모션에서 이걸 호출하니까 서로 이빨이 안맞아서 뻑이나던거같음.
}

void warrior::render()
{

}

/* 우선 슬래시 블러스트를 3마리의 적을 따다닥 공격하게 하기위해 크게 바깥쪽에 q for문, 안쪽에 몹벡터.size만큼돌게 하는 i for문
과 같은놈을 3번때리기 방지하기위해 저장된 who와 현재 돌고잇는 i가 같은지 비교하는 r for문이있다.*/

void warrior::Mob_Search(Character* c, MobManager* mm, Map* map, charEffect* _eft)
{
		c->setAddHpMp(0, -need_mp);
		cnt = s = r = add_attack_scale = 0;

		_c = c;
		_mm = mm;
		_map = map;
		eft = _eft;

		Who_Target_Mob[0] = Who_Target_Mob[1] = Who_Target_Mob[2] = -1000;
		Dis_Target_Mob[0] = Dis_Target_Mob[1] = Dis_Target_Mob[2] = -1000;

		RECT attack_scale;

		eft->blust(c->getX(), c->getY());

		//가장 가까운 몬스터찾기
		for (int q = 0; q < 3; q++)
		{
			tempRich = 10000;

			//만약 한번이상 돌았는데 배열값이 -1000이라는건 못찾았다는 얘기니까 리턴(뒤에있는 렉트찾으려고 추가됨)
			if (q != 0 && Who_Target_Mob[0] == -1000) return;

			//현재 몹들에 대한 for문
			for (int i = 0; i < mm->_getvMob().size(); i++)
			{
				if (mm->_getvMob()[i]->getHP() <= 0) continue;

				//배열내에 같은 배열의 번호를 가진놈을 찾는for문
				for (r = 0; r < 3; r++)
				{
					if (Who_Target_Mob[r] == i)
					{
						break;
					}
				}
				//만약 r이 3이아니라는건 같은 배열에 있는놈이 있다는뜻이므로 i for문을 컨티뉴
				if (r != 3) continue;

				//만약 q for문이 한번이상은 돌았을때 렉트의 범위를 늘려준다.
				if (q != 0) add_attack_scale = 200;

				attack_scale = RectMakeCenter(c->getX(), c->getY() - 15, 145 + add_attack_scale, 60);

				RECT tempRECT;
				if (IntersectRect(&tempRECT, &attack_scale, &mm->_getvMob()[i]->getRECT()))
				{
					int rich = getDistance(c->getX(), c->getY(), mm->_getvMob()[i]->getRECT().left + (mm->_getvMob()[i]->getRECT().right - mm->_getvMob()[i]->getRECT().left) / 2, mm->_getvMob()[i]->getRECT().top + (mm->_getvMob()[i]->getRECT().bottom - mm->_getvMob()[i]->getRECT().top) / 2);

					if (c->getRL() == RIGHT && (c->getX() - mm->_getvMob()[i]->getX()) < 0)	//오른쪽을보고 공격했을때
					{
						if (tempRich > rich)
						{
							tempRich = rich;
							tempWho = i;
						}
					}
					else if (c->getRL() == LEFT && (c->getX() - mm->_getvMob()[i]->getX()) > 0)			//왼쪽을보고 공격했을때
					{
						if (tempRich > rich)
						{
							tempRich = rich;
							tempWho = i;
						}
					}
				}
			}
			if (tempRich != 10000)//만약 i for문이 다 돌고나서 tempRich이 10000이 아닐때 저장한다.
			{
				for (int i = 0; i < 3; i++)
				{
					if (Who_Target_Mob[i] == -1000)
					{
						Who_Target_Mob[i] = tempWho;
						Dis_Target_Mob[i] = tempRich;
						break;
					}
				}
			}
		}
}

void warrior::Mob_Knock(Character* c, MobManager* mm, Map* map, int y)
{

	if (mm->_getvMob()[Who_Target_Mob[y]]->getJumpOk() == true)
	{
		mm->_getvMob()[Who_Target_Mob[y]]->setY(map->mapExplorer(mm->_getvMob()[Who_Target_Mob[y]]->getX(), mm->_getvMob()[Who_Target_Mob[y]]->getY(), 150.0f));
	}
	if (c->getRL() == RIGHT)
	{
		mm->_getvMob()[Who_Target_Mob[y]]->setHIT(M_RIGHT, 0, RND->getInt(c->getSTR()));
	}
	else if (c->getRL() == LEFT)
	{
		mm->_getvMob()[Who_Target_Mob[y]]->setHIT(M_LEFT, 0, RND->getInt(c->getSTR()));
	}
}