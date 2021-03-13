#pragma once
#include "singletonBase.h"

class camera : public singletonBase <camera>
{
private:
	int key, agle, fq, cnt;
	float X, camX, camY, course, q, p;

	bool reverse;

public:

	camera();
	~camera();

	HRESULT init();
	virtual void release();

	void cam(float followX, float followY, float re, bool getamped, int left, int right, float view, float p2);
	void Quake_cam(float angle, int quake);

	float getcamX() { return camX; }
	float getcamY() { return camY; }
	void setMapChange(float _p) { p = _p; }

	void Quake(float angle, int quake) { fq = quake; q = angle; }

};