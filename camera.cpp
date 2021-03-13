#include "stdafx.h"
#include "camera.h"
#include "gameNode.h"

camera::camera()
{
}

camera::~camera()
{
}

HRESULT camera::init()
{

	key = 1;
	fq = cnt = 0;
	course = camY = camX = X = 0.0f;
	p = 0.02f;

	return S_OK;

}

void camera::release()
{
}

void camera::cam(float followX, float followY, float re, bool getamped, int left, int right, float view, float p2)
{
	if (p > 1.0f) p = 1.0f;
	if (p2 > 1.0f) p2 = 1.0f;

	if (!getamped && course != 0.0f) course += (0.0 - course) * p2;

	KEYMANAGER->setKeyDown(left, false);
	KEYMANAGER->setKeyDown(right, false);

	if (KEYMANAGER->isOnceKeyDown(left))		key = -1;
	else if (KEYMANAGER->isOnceKeyDown(right))	key = 1;

	if (getamped)
	{
		course += ((view * key) - course) * p2;
	}

	X += ((followX - X) - WINSIZEX / 2) * p;
	camY += ((followY - camY + re) - WINSIZEY / 2) * p;

	camX = X + course;

	if (camX <= 0) camX = 0;
	if (camX >= _backBuffer->getWidth() - WINSIZEX) camX = _backBuffer->getWidth() - WINSIZEX;
	if (camY <= 0) camY = 0;
	if (camY >= _backBuffer->getHeight() - WINSIZEY) camY = _backBuffer->getHeight() - WINSIZEY;

	if (fq != 0)
	{
		Quake_cam(q, fq);
	}

}

void camera::Quake_cam(float angle, int quake)
{
	cnt = cnt % 2;

	if (!cnt)
	{
		reverse = !reverse;
	}

	agle = angle + (reverse * -180.0f);

	camX += cosf(agle * (PI / 180.0f)) * quake;
	camY += -sinf(agle * (PI / 180.0f)) * quake;

	fq--;
	if (fq <= 0) fq = 0;

	cnt++;

}