#include "stdafx.h"
#include "login.h"

HRESULT login::init()
{
	IMAGEMANAGER->addImage("메인화면", "이미지/UI/메인화면/로그인창.bmp", 800, 600, false, NULL);
	IMAGEMANAGER->addImage("설명창", "이미지/UI/메인화면/설명충.bmp", 464, 302, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("게임시작버튼", "이미지/UI/메인화면/게임시작버튼.bmp", 420, 52, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("확인버튼", "이미지/UI/메인화면/확인버튼.bmp", 249, 26, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->findImage("게임시작버튼")->setFrameX(0);
	IMAGEMANAGER->findImage("확인버튼")->setFrameX(0);

	next = 0;

	return S_OK;
}

void login::release()
{
}

void login::update()
{
	if (next == 0)
	{
		RECT start_button = RectMake(330, 350, 140, 52);
		if (PtInRect(&start_button, PointMake(_ptMouse.x, _ptMouse.y)))
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				next = 1;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				IMAGEMANAGER->findImage("게임시작버튼")->setFrameX(2);
			}		
			else
			{
				IMAGEMANAGER->findImage("게임시작버튼")->setFrameX(1);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("게임시작버튼")->setFrameX(0);
		}
	}
	if (next == 1)
	{
		RECT ok_button = RectMake(355, 400, 83, 26);
		if (PtInRect(&ok_button, PointMake(_ptMouse.x, _ptMouse.y)))
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				next = 2;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				IMAGEMANAGER->findImage("확인버튼")->setFrameX(2);
			}		
			else
			{
				IMAGEMANAGER->findImage("확인버튼")->setFrameX(1);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("확인버튼")->setFrameX(0);
		}
	}
}

void login::render()
{
	IMAGEMANAGER->findImage("메인화면")->render(getMemDC());
	IMAGEMANAGER->findImage("게임시작버튼")->frameRender(getMemDC(), 330, 350);
	if (next == 1)
	{
		IMAGEMANAGER->findImage("설명창")->render(getMemDC(), 168, 150);
		IMAGEMANAGER->findImage("확인버튼")->frameRender(getMemDC(), 355, 400);
	}
}
