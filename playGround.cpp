#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);

	_map = new mapManager;
	_player = new playerManager;
	_enemy = new enemyManager;

	_map->setMapPlayerAddressLink(_player);
	_map->setMapEnemyAddressLink(_enemy);
	
	_player->setPlayerMapManagerAddressLink(_map);

	_enemy->setEnemyMapManegerAddressLink(_map);

	_player->setPlayerEnemyManagerAddressLink(_enemy);

	_enemy->setEnemyPlayerManagerAddressLink(_player);


	_map->init();
	_player->init();
	_enemy->init();

	SOUNDMANAGER->addSound("bgm", "Castlevania/[Castlevania]Bloody Tears.mp3", true, true);

	//SOUNDMANAGER->play("bgm", 0.5f);

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
	gameNode::update();

	_map->update();
	_enemy->update();
	_player->update();

	if (KEYMANAGER->isOnceKeyDown(VK_UP) && _map->getStage() == MAP04)
	{
		char temp[128];
		vector<string> vStr;

		vStr.push_back(to_string(_player->getCenterX()));
		vStr.push_back(to_string(_player->getCenterY()));
		vStr.push_back(to_string(_map->getStage()));
		TXTDATA->txtSave("세이브.txt", vStr);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		vector<string> vStr;

		vStr = TXTDATA->txtLoad("세이브.txt");

		if (atoi(vStr[2].c_str()) == 4)
		{
			_map->setStage(MAP04, atoi(vStr[0].c_str()), atoi(vStr[1].c_str()));
		}
		
	}
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	_map->render();
	_enemy->render();
	_player->render();


	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}

