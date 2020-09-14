#pragma once
#include "enemyMob.h"

class MerMan : public enemyMob
{
private:
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

