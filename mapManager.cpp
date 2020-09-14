#include "stdafx.h"
#include "mapManager.h"
#include "playerManager.h"
#include "enemyManager.h"

HRESULT mapManager::init()
{

	////맵
	IMAGEMANAGER->addImage("map01", "Castlevania/Image/MapImage/Map_01.bmp", 1536, 2142, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixelMap01", "Castlevania/Image/PixelMap/Map_01.bmp", 1536, 2142, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map01Sky", "Castlevania/Image/BackGroundImage/Map_01_Cloud_Loop.bmp", 3072, 2142, false, RGB(255,0,255));
	
	IMAGEMANAGER->addImage("map02", "Castlevania/Image/MapImage/Map_02.bmp", 6649, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixelMap02", "Castlevania/Image/PixelMap/Map_02.bmp", 6649, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map02BackGround", "Castlevania/Image/BackGroundImage/Map_02_BackGround.bmp", 6649, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map02BackSky", "Castlevania/Image/BackGroundImage/Map_02_Cloud_Loop.bmp", 6649, 768, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map02Lightning", "Castlevania/Image/MapImage/map_02_Lightning.bmp", 6649, 768, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map02Lightning02", "Castlevania/Image/MapImage/map02_White.bmp", 6649, 768, false, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("map03", "Castlevania/Image/MapImage/Map_03.bmp", 2304, 1389, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixelMap03", "Castlevania/Image/PixelMap/Map_03.bmp", 2304, 1389, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("bossMap", "Castlevania/Image/MapImage/Map_14.bmp", 3072, 1389, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixelMapBoss", "Castlevania/Image/PixelMap/Map_15.bmp", 3072, 1389, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("mapSave", "Castlevania/Image/MapImage/Map_09.bmp", 1024, 831, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixelmapSave", "Castlevania/Image/PixelMap/Map_10.bmp", 1024, 831, true, RGB(255, 0, 255));


	_mapStr = "map01";
	_mapPixelStr = "pixelMap01";

	_stage = MAP01;
	setStage(_stage, 400, 1860);

	_lightningCount = 0;
	_lightningAlphaValue = 255;

	return S_OK;
}

void mapManager::release()
{
	//release();
}

void mapManager::update()
{
	switch (_stage)
	{
		case MAP01:
		{
			if (_player->getPlayerRect().left >= IMAGEMANAGER->findImage("map01")->getWidth())
			{
				setStage(MAP02, 50, 430);
			}
		}
		break;
	
		case MAP02:
		{
			_lightningCount++;

			if (_player->getPlayerRect().left >= IMAGEMANAGER->findImage("map02")->getWidth())
			{
				setStage(MAP03, 50, 320);
			}
			if(_player->getPlayerRect().right <= 0)
			{
				setStage(MAP01, 1530, 1880);
			}
		}
		break;

		case MAP03:
		{
			if (_player->getPlayerRect().left >= IMAGEMANAGER->findImage("map03")->getWidth())
			{
				setStage(MAP04, 50, 480);
			}
			if (_player->getPlayerRect().right <= 0)
			{
				setStage(MAP02, 6649, 430);
			}
		}
		break;

		case MAP04:
		{
			if (_player->getPlayerRect().left >= 1024)
			{
				setStage(MAP05, 50, 360);
			}
			if (_player->getPlayerRect().right <= 0)
			{
				setStage(MAP03, 2250, 360);
			}

			
		}
		break;

		case MAP05:
		{
			if (_player->getPlayerRect().right <= 0)
			{
				setStage(MAP04, 1000, 480);
			}
		}
		break;

	}

	if(_lightningCount % 2 == 0)
	{
		_lightningAlphaValue -= 1;
	}
	if (_lightningAlphaValue <= 0)
	{
		_lightningAlphaValue = 255;
	}

	CAMERA->setX(_player->getCenterX());
	CAMERA->setY(_player->getCenterY() - 150);
}

void mapManager::render()
{
	if (_stage == MAP01)
	{
		CAMERA->render(getMemDC(), IMAGEMANAGER->findImage("map01Sky"),0,0);
	}

	if (_stage == MAP02)
	{
		CAMERA->render(getMemDC(), IMAGEMANAGER->findImage("map02BackSky"), 0, 0);
		CAMERA->render(getMemDC(), IMAGEMANAGER->findImage("map02BackGround"), 0, 0);
		if (_lightningCount >= 100)
		{
			CAMERA->alphaRender(getMemDC(), IMAGEMANAGER->findImage("map02Lightning02"), 0, 0, _lightningAlphaValue);
		}
	}
	CAMERA->render(getMemDC(), IMAGEMANAGER->findImage(_mapStr), 0, 0);
	//CAMERA->render(getMemDC(), IMAGEMANAGER->findImage(_mapPixelStr), 0, 0);

	if (_stage == MAP04)
	{
		TextOut(getMemDC(), IMAGEMANAGER->findImage("mapSave")->getWidth() / 2 - 50, IMAGEMANAGER->findImage("mapSave")->getHeight() / 2, "저장하려면 up키, 불러오려면 F1", strlen("저장하려면 up키, 불러오려면 F1"));
	}
}

void mapManager::setStage(tagMap _map, float _initPositionX, float _initPositionY)
{
	_stage = _map;

	switch (_stage)
	{
		case MAP01:
		{
			_mapStr = "map01";
			_mapPixelStr = "pixelMap01";
		}
		break;

		case MAP02:
		{
			_mapStr = "map02";
			_mapPixelStr = "pixelMap02";
		}
		break;

		case MAP03:
		{
			_mapStr = "map03";
			_mapPixelStr = "pixelMap03";
		}
		break;

		case MAP04:
		{
			_mapStr = "mapSave";
			_mapPixelStr = "pixelmapSave";
		}
		break;

		case MAP05:
		{
			_mapStr = "bossMap";
			_mapPixelStr = "pixelMapBoss";
		}
		break;
	}

	_player->setPlayerCenterX(_initPositionX);
	_player->setPlayerCenterY(_initPositionY);

	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, IMAGEMANAGER->findImage(_mapStr)->getWidth() - WINSIZEX, IMAGEMANAGER->findImage(_mapStr)->getHeight() - WINSIZEY);
}
