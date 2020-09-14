#include "stdafx.h"
#include "MerMan.h"

HRESULT MerMan::init()
{
	_enemy._enemyimg = IMAGEMANAGER->addFrameImage("Merman_Move", "Castlevania/Image/MonsterImage/Merman/State_Move.bmp", 513, 205, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Merman_Death", "Castlevania/Image/MonsterImage/Merman/State_Death.bmp", 273, 205, 4, 2, true, RGB(255, 0, 255));



	_enemy._frameCount = 0;
	_enemy._ptX = _enemy._initX;
	_enemy._enemyState = ENEMY_PATROL;

	return S_OK;
}

void MerMan::release()
{
}

void MerMan::update()
{
	_enemy._frameCount++;
}

void MerMan::render()
{
}
