#include "stdafx.h"
#include "Map.h"
#include "character.h"
#include "MobManager.h"
#include "ItemManager.h"

HRESULT Map::init()
{
	//제각각 이름을 가진 맵이미지 리소스해주기
	IMAGEMANAGER->addImage("슬리피우드", "이미지/맵/슬리피우드.bmp", 2430, 1486, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("개미굴1", "이미지/맵/개미굴1.bmp", 2760, 2244, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("저주받은신전", "이미지/맵/저주받은신전.bmp", 1532, 940, false, RGB(255, 0, 255));
	
	//투명땅
	IMAGEMANAGER->addImage("슬리피우드투명땅", "이미지/맵/슬리피우드투명땅.bmp", 2430, 1486, true, RGB(0, 255, 0));
	IMAGEMANAGER->addImage("개미굴1투명땅", "이미지/맵/개미굴1투명땅.bmp", 2760, 2244, true, RGB(0, 255, 0));
	IMAGEMANAGER->addImage("저주받은신전투명땅", "이미지/맵/저주받은신전투명땅.bmp", 1532, 940, true, RGB(0, 255, 0));

	for (int i = 0; i < 2; i++)
	{
		portal[i].img_portal = IMAGEMANAGER->addFrameImage("포탈", "이미지/맵/포탈.bmp", 712, 257, 8, 1, true, RGB(255, 0, 255));
		portal[i].ani_portal = new animation;
		portal[i].ani_portal->init(portal[i].img_portal->getWidth(), portal[i].img_portal->getHeight(),
			portal[i].img_portal->getFrameWidth(), portal[i].img_portal->getFrameHeight());
		portal[i].ani_portal->setDefPlayFrame(true, true);
		portal[i].ani_portal->setFPS(1);
	}
	//currentMap에 현재맵 문자열 초기화
	sprintf_s(currentMap, "%s", "슬리피우드");
	sprintf_s(currentMapland, "%s투명땅", "슬리피우드");

	//currentMap의 이름을 가진 맵으로 셋팅
	setMap(currentMap);

	//맵의 사다리배치
	setropeladder(currentMap);

	return S_OK;
}

void Map::release()
{

}

void Map::update()
{
	CAMERA->setMapChange(0.02f);

	//캐릭터와 사다리밧줄 충돌체크
	for (int i = 0; i < 10; i++)
	{
		if (rpld[i].isExist == false) break;
		RECT temp;
		if (IntersectRect(&temp, &C->getRECT(), &rpld[i].rect))
		{
			C->setLadderRope(rpld[i].rect);
		}
	}
	//캐릭터와 포탈 충돌체크
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		for (int i = 0; i < 2; i++)
		{
			if (portal[i].isExist == false) break;
			RECT temp;
			if (IntersectRect(&temp, &C->getRECT(), &portal[i].rect))
			{
				C->setPortal_Collision();
				C->setCx(portal[i].msg_x);
				C->setCy(portal[i].msg_y);

				CAMERA->setMapChange(1.0f);

				sprintf_s(currentMap, "%s", portal[i].map);
				sprintf_s(currentMapland, "%s투명땅", portal[i].map);
				setMap(portal[i].map);
				setropeladder(currentMap);
				
				Mb->setMonster(currentMap);
				_itemManager->Item_all_clear();
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (portal[i].isExist == false) break;
		portal[i].ani_portal->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
}

void Map::render()
{
	//현재맵을 getMemDC로 보내 버퍼에 채운다.
	IMAGEMANAGER->findImage(currentMap)->render(getMemDC());

	for (int i = 0; i < 2; i++)
	{
		if (portal[i].isExist == false) break;
		portal[i].img_portal->aniRender(getMemDC(), portal[i].x, portal[i].y, portal[i].ani_portal);
	}
	
	if (KEYMANAGER->isToggleKey('1'))
	{
		IMAGEMANAGER->findImage(currentMapland)->render(getMemDC());
		for (int i = 0; i < 10; i++)
		{
			if (rpld[i].isExist == false) break;
			HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);
			Rectangle(getMemDC(), rpld[i].rect);
			SelectObject(getMemDC(), oPen);
			DeleteObject(Pen);
		}
	}
	if (KEYMANAGER->isToggleKey('1'))
	{
		for (int i = 0; i < 2; i++)
		{
			if (portal[i].isExist == false) break;
			HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);
			Rectangle(getMemDC(), portal[i].rect);		
			SelectObject(getMemDC(), oPen);
			DeleteObject(Pen);
		}
	}	
}

void Map::setropeladder(string map)
{
	for (int i = 0; i < 10; i++)
	{
		rpld[i].isExist = false;
	}
	for (int i = 0; i < 2; i++)
	{
		portal[i].isExist = false;
	}

	//사다리 로프 배치
	if (map == "슬리피우드")
	{

		int infoArrX[] = { 743.0f, 1508.0f };		//사다리 x축 위치
		int infoArrY[] = { 580.0f, 583.0f };		//사다리 y축 위치
		int infoArrW[] = { 36.0f, 36.0f };			//사다리 width축 길이
		int infoArrH[] = { 343.9f, 241.1f };		//사다리 height축 길이

		for (int i = 0; i < 2; i++)				//슬리피우드 사다리로프 2개니까 2개만 생성
		{
			rpld[i].isExist = true;
			rpld[i].x = infoArrX[i];
			rpld[i].y = infoArrY[i];
			rpld[i].rect = RectMake(rpld[i].x, rpld[i].y, infoArrW[i], infoArrH[i]);
		}

		//포탈배치
		portal[0].isExist = true;
		portal[0].x = 2129.4f;
		portal[0].y = 1024.6f;
		portal[0].msg_x = 252.4f;
		portal[0].msg_y = 264.4f;
		sprintf_s(portal[0].map, "%s", "개미굴1");
		portal[0].rect = RectMake(portal[0].x, portal[0].y, 89, 257);

		portal[0].ani_portal->start(); //애니메이션 재생
	}
	if (map == "개미굴1")
	{
		int infoArrX[] = { 249.9f , 1052.6f , 1085.1f, 1139.1f, 1013.6f, 1100.1f, 2009.2f, 1978.8f, 1991.8f, 2359.1f };
		int infoArrY[] = { 334.9f , 403.9f , 587.4f, 759.8f, 999.1f, 1183.7f, 1090.1f, 1256.7f, 1506.6f, 1881.3f };
		int infoArrW[] = { 36.0f, 14.0f, 36.0f, 14.0, 36.0f, 14.0f, 36.0f, 14.0f, 14.0f, 36.0f };
		int infoArrH[] = { 237.9f, 168.9f, 178.0f, 192.8f, 178.0f, 192.8f, 130.0f, 192.8f, 192.8f, 188.9f };

		for (int i = 0; i < 10; i++)
		{
			rpld[i].isExist = true;
			rpld[i].x = infoArrX[i];
			rpld[i].y = infoArrY[i];
			rpld[i].rect = RectMake(rpld[i].x, rpld[i].y, infoArrW[i], infoArrH[i]);
		}

		int portalinfoX[] = { 224.9f , 2602.8f };
		int portalinfoY[] = { 82.0f , 1621.8f };
		int portalinfoMSGX[] = { 2152.0f , 57.5f };	//캐릭터를 어디로 전송시킬거냐
		int portalinfoMSGY[] = { 1195.3f , 128.0f };	//캐릭터를 어디로 전송시킬거냐
		char mapMSG[2][128] = { "슬리피우드", "저주받은신전" };

		for (int i = 0; i < 2; i++)
		{
			portal[i].isExist = true;
			portal[i].x = portalinfoX[i];
			portal[i].y = portalinfoY[i];
			portal[i].msg_x = portalinfoMSGX[i];
			portal[i].msg_y = portalinfoMSGY[i];
			sprintf_s(portal[i].map, "%s", mapMSG[i]);
			portal[i].rect = RectMake(portal[i].x, portal[i].y, 89, 257);
			portal[i].ani_portal->start(); //애니메이션 재생
		}
	}
	if (map == "저주받은신전")
	{
		int infoArrX[] = { 175.0f , 101.0f , 1076.5f };
		int infoArrY[] = { 277.1f , 423.0f , 422.0f };
		int infoArrW[] = { 37.0f , 9.0f , 9.0f };
		int infoArrH[] = { 233.9f , 253.9f , 253.9f };

		for (int i = 0; i < 10; i++)
		{
			rpld[i].isExist = true;
			rpld[i].x = infoArrX[i];
			rpld[i].y = infoArrY[i];
			rpld[i].rect = RectMake(rpld[i].x, rpld[i].y, infoArrW[i], infoArrH[i]);
		}

		int portalinfoX[] = { 33.0f };
		int portalinfoY[] = { 5.0f };
		int portalinfoMSGX[] = { 2655.8f };	//캐릭터를 어디로 전송시킬거냐
		int portalinfoMSGY[] = { 1756.9f };	//캐릭터를 어디로 전송시킬거냐
		char mapMSG[128] = { "개미굴1" };

		portal[0].isExist = true;
		portal[0].x = portalinfoX[0];
		portal[0].y = portalinfoY[0];
		portal[0].msg_x = portalinfoMSGX[0];
		portal[0].msg_y = portalinfoMSGY[0];
		sprintf_s(portal[0].map, "%s", mapMSG);
		portal[0].rect = RectMake(portal[0].x, portal[0].y, 89, 257);
		portal[0].ani_portal->start(); //애니메이션 재생
	}
}

float Map::mapExplorer(float Ex, float Ey, float Rich)
{
	for (int i = Ey-10; i < Ey + Rich; i++)
	{
		COLORREF mapColor = GetPixel(IMAGEMANAGER->findImage(currentMapland)->getMemDC(), Ex, i);

		if (GetRValue(mapColor) == 255 && GetGValue(mapColor) == 0 && GetBValue(mapColor) == 255)
		{
			return (float)i;
		}
	}
}