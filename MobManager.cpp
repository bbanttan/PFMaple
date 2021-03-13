#include "stdafx.h"
#include "MobManager.h"
#include "Map.h"
#include "Character.h"
#include "ItemManager.h"


HRESULT MobManager::init()
{
	IMAGEMANAGER->addFrameImage("뿔버섯", "이미지/몬스터/뿔버섯.bmp", 228, 448, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("좀비버섯", "이미지/몬스터/좀비버섯.bmp", 264, 750, 4, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("주니어발록", "이미지/몬스터/주니어발록.bmp", 5103, 2316, 9, 12, true, RGB(255, 0, 255));

	dmg = new damage;
	dmg->init();

	return S_OK;
}

void MobManager::release()
{
}

void MobManager::update()
{
	if (c_map == "개미굴1" || c_map == "저주받은신전")
	{
		for (_viMob = _vMob.begin(); _viMob != _vMob.end(); ++_viMob)
		{
			if ((*_viMob)->getExist() == false)  continue;
			(*_viMob)->update();
			if ((*_viMob)->getHit())
			{
				//데미지표시
				dmg->create_damage((*_viMob)->getX(), (*_viMob)->getRECT().top + (*_viMob)->getPlusDamageY(), (*_viMob)->getDMG(), true);
				if((*_viMob)->getType() != BOSS) (*_viMob)->setY(_map->mapExplorer((*_viMob)->getX(), (*_viMob)->getY(), 150.0f));	//몹을때렸을때 땅으로 박아버리기
				(*_viMob)->setPlusDamageY(0);
				(*_viMob)->setFalseHit();
			}
		}
	}
	map_collision();
	dmg->update();
}

void MobManager::render()
{
	if (c_map == "개미굴1" || c_map == "저주받은신전")
	{
		for (_viMob = _vMob.begin(); _viMob != _vMob.end(); ++_viMob)
		{
			if ((*_viMob)->getExist() == false) continue;
			if (CAMERA->getcamX() < (*_viMob)->getX() + ((*_viMob)->getImage()->getWidth() / 2) && CAMERA->getcamX() + WINSIZEX > (*_viMob)->getX() - ((*_viMob)->getImage()->getWidth() / 2) &&
				CAMERA->getcamY() < (*_viMob)->getY() + ((*_viMob)->getImage()->getHeight() / 2) && CAMERA->getcamY() + WINSIZEY > (*_viMob)->getY() - ((*_viMob)->getImage()->getWidth() / 2))
			{
				(*_viMob)->render();
				dmg->render();
			}
		}
	}
}

void MobManager::setMonster(string currentMap)
{
	
	for (int i = 0; i < _vMob.size(); i++)
	{
		_vMob[i]->setExist(false);
	}

	_vMob.clear();

	c_map = currentMap;

	if (c_map == "개미굴1")
	{
		float monsterX[] = { 371.8, 746.5, 1076.5, 332.8, 645.8, 973.5, 1009.5, 1301.5, 1145.5, 1509.3, 1796.3, 1171.5, 1513.3, 1929.3, 2012.3, 1955.3, 2105.3, 2442.0, 1876.3, 2105.3, 2525.0 };

		float monsterY[] = { 304.8, 292.8, 357.8, 544.7, 552.8, 716.5, 956.5, 956.5, 962.5, 996.5, 1040.5, 1334.3, 1330.5, 1702.3, 1702.3, 1854.3, 1850.3, 1850.3, 2052.0, 2058.0, 2052.0 };

		for (int i = 0; i < 20; i++)
		{		
			if (i >= 0 && i <= 9)//뿔버섯생성
			{
				Mob* mob;
				mob = new HornyMushroom;
				mob->init("뿔버섯", PointMake(monsterX[i], monsterY[i]));
				mob->setExist(true);
				mob->setItemManagerAdress(_itemM);
				_vMob.push_back(mob);
			}
			else if (i >= 10 && i <= 20)//좀비버섯생성
			{
				Mob* mob;
				mob = new ZombieMushroom;
				mob->init("좀비버섯", PointMake(monsterX[i], monsterY[i]));
				mob->setExist(true);
				mob->setItemManagerAdress(_itemM);
				_vMob.push_back(mob);
			}
		}	
	}
	if (c_map == "저주받은신전")
	{
		float monsterX = 1289.0f;
		float monsterY = 568.0f;

		Mob* mob;
		mob = new Junior;
		mob->init("주니어발록", PointMake(monsterX, monsterY));
		mob->setCharAdress(cha);
		mob->setExist(true);
		mob->setItemManagerAdress(_itemM);
		_vMob.push_back(mob);

	}

	//생성후 땅에 박아버리는 구문
	char str[128];
	sprintf_s(str, "%s투명땅", _map->getCurrentMap());

	for (_viMob = _vMob.begin(); _viMob != _vMob.end(); ++_viMob)
	{
		for (int i = (int)(*_viMob)->getY() - 100; i < (int)(*_viMob)->getY() + 100; i++)
		{
			COLORREF mapColor = GetPixel(IMAGEMANAGER->findImage(str)->getMemDC(), (int)(*_viMob)->getX(), i);
			if (GetRValue(mapColor) == 255 && GetGValue(mapColor) == 0 && GetBValue(mapColor) == 255)
			{
				(*_viMob)->setY(i);
				(*_viMob)->setSpawnY(i);
			}
		}
	}
	//생땅박구문종료
}

void MobManager::map_collision()
{
	char str[128];
	sprintf_s(str, "%s투명땅", _map->getCurrentMap());

	//몬스터 땅처리
	for (_viMob = _vMob.begin(); _viMob != _vMob.end(); ++_viMob)
	{
		if (((*_viMob)->getJP() <= (*_viMob)->getGRA()))
		{
			for (int i = (int)(*_viMob)->getY() - 5; i < (int)(*_viMob)->getY() + 10; i++)
			{
				COLORREF mapColor = GetPixel(IMAGEMANAGER->findImage(str)->getMemDC(), (int)(*_viMob)->getX(), i);
				if (GetRValue(mapColor) == 255 && GetGValue(mapColor) == 0 && GetBValue(mapColor) == 255)
				{
					(*_viMob)->setY(i);
					(*_viMob)->setGRA();
					if ((*_viMob)->getSMJA() == M_JUMP || (*_viMob)->getJP() != 0.0f)
					{ 
						(*_viMob)->set_aniUpdate();
						(*_viMob)->setJP();
					}
					break;
				}
			}
		}
		//중력값이 커지면 땅을 벗어난것으로 간주, 반대방향으로 돌리고 그 X축을 기억해서 다음부턴 그 X축으로는 못넘어가게 하기
		if ((*_viMob)->getJP() == 0.0f && (*_viMob)->getGRA() > 0.0f)
		{
			if ((*_viMob)->getspdKnockback() > 0)	//속도가 오른쪽을 향할때
			{
				if ((*_viMob)->getmaxX() == 0.0f) (*_viMob)->setmaxX();
			}
			if ((*_viMob)->getspdKnockback() < 0)	//속도가 왼쪽을 향할때
			{
				if ((*_viMob)->getminX() == 0.0f) (*_viMob)->setminX();
			}
		}
	}
}