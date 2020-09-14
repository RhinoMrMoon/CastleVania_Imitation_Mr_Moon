#include "stdafx.h"
#include "enemyManager.h"
#include "mapManager.h"
#include "playerManager.h"

#include "enemyMob.h"
#include "ArmoredKnight.h"

HRESULT enemyManager::init()
{

	//몬스터 이미지

	//스켈레톤
	IMAGEMANAGER->addFrameImage("Skeleton_Move", "Castlevania/Image/MonsterImage/Skeleton/Skeleton_Red_Move3.bmp", 531, 235, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Skeleton_Dead", "Castlevania/Image/MonsterImage/Skeleton/Skeleton_Red_Death2.bmp", 664, 235, 10, 2, true, RGB(255, 0, 255));


	
	//머맨
	IMAGEMANAGER->addFrameImage("Merman_Idle", "Castlevania/Image/MonsterImage/Merman/State_Fire.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Merman_Move", "Castlevania/Image/MonsterImage/Merman/State_Move.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Merman_Death", "Castlevania/Image/MonsterImage/Merman/State_Death.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Merman_Diving", "Castlevania/Image/MonsterImage/Merman/State_Diving.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Merman_Swim", "Castlevania/Image/MonsterImage/Merman/State_Swim.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Merman_AttackEffect", "Castlevania/Image/MonsterImage/Merman/Merman_Bullet.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));


	//ArmoredKnight* _armoredKnight[ARMOREDKNIGHTMAX] = { new ArmoredKnight, new ArmoredKnight, new ArmoredKnight };

	

	for (int i = 0; i < ARMOREDKNIGHTMAX; i++)
	{
		_armoredKnight[i] = new ArmoredKnight;
	}

	_armoredKnight[0]->setInitPosition(2030, 394, false);
	_armoredKnight[1]->setInitPosition(2530, 394, true);
	_armoredKnight[2]->setInitPosition(3030, 394, false);
	_armoredKnight[3]->setInitPosition(3530, 394, true);
	_armoredKnight[4]->setInitPosition(4030, 394, false);
	_armoredKnight[5]->setInitPosition(4530, 394, true);
	_armoredKnight[6]->setInitPosition(5030, 394, false);
	_armoredKnight[7]->setInitPosition(5530, 394, true);
	_armoredKnight[8]->setInitPosition(1000, 394, true);

	for (int i = 0; i < ARMOREDKNIGHTMAX; i++)
	{
		_armoredKnight[i]->init();
		_vEnemys.push_back(_armoredKnight[i]);
	}

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	_frameCount++;
	

	/**/
	switch (_mapMg->getStage())
	{
		case MAP01:
		{

		}
		break;

		case MAP02:
		{
			/*for (int i = 0; i < _vEnemys.size(); i++)
			{
				_vEnemys[i]->update();
			}*/

			for (int i = 0; i < ARMOREDKNIGHTMAX; i++)
			{
				_armoredKnight[i]->update();
			}

			float _playerRcCenterX = (_playerMg->getPlayerRect().left + _playerMg->getPlayerRect().right) / 2;
			float _playerRcCenterY = (_playerMg->getPlayerRect().top + _playerMg->getPlayerRect().bottom) / 2;

			for (int i = 0; i < ARMOREDKNIGHTMAX; i++)
			{
				if (checkPointInRect(_armoredKnight[i]->getEnemyRangeRect(), _playerRcCenterX, _playerRcCenterY) && _armoredKnight[i]->getEnemyState() == ENEMY_PATROL)
				{
					_armoredKnight[i]->setEnemyState(ENEMY_ATTACK);
					break;
				}
				if (checkPointInRect(_armoredKnight[i]->getEnemyRangeRect(), _playerRcCenterX, _playerRcCenterY) && _armoredKnight[i]->getEnemyState() == ENEMY_CHASE)
				{
					_armoredKnight[i]->setEnemyState(ENEMY_ATTACK);
					break;
				}
			}

			for (int i = 0; i < ARMOREDKNIGHTMAX; i++)
			{
				if ((isCollision(_armoredKnight[i]->getEnemyRect(), _playerMg->getPlayerAttackRect()) && _armoredKnight[i]->getEnemyState() != ENEMY_NONACTIVE)
					&& (isCollision(_armoredKnight[i]->getEnemyRect(), _playerMg->getPlayerAttackRect()) && _armoredKnight[i]->getEnemyState() != ENEMY_DEAD))
				{
					_armoredKnight[i]->setEnemyState(ENEMY_DEAD);
					break;
				}
			}
				

				

				/*if (checkPointInRect(_armoredKnight[i]->getEnemyRangeRect(), _playerRcCenterX, _playerRcCenterY))
				{
					_armoredKnight[i]->setEnemyState(ENEMY_ATTACK);
					break;
				}*/


				/*if (isCollision(_armoredKnight[i]->getEnemyAtkRect(), _playerMg->getPlayerRect()))
				{
					if (_armoredKnight[i]->getEnemyIsLeft())
					{
						_playerMg->setPlayerAngle(PI * 0.75f);
						_playerMg->setPlayerState(HEART);
						break;
					}
					else if (!_armoredKnight[i]->getEnemyIsLeft())
					{
						_playerMg->setPlayerAngle(PI /4);
						_playerMg->setPlayerState(HEART);
						break;
					}
				}*/
			
		}
		break;

		case MAP03:
		{

		}
		break;

		case MAP04:
		{

		}
		break;
	}
	
	

	//sprintf_s(_buffer1, "current EnemyFrameX :%d", _armoredKnight->getEnemyFrameX());
}

void enemyManager::render()
{
	switch (_mapMg->getStage())
	{
		case MAP01:
		{

		}

		case MAP02:
		{
			for (int i = 0; i < _vEnemys.size(); i++)
			{
				_vEnemys[i]->render();
			}
		}
		break;

		case MAP03:
		{

		}

		case MAP04:
		{

		}

	}
	
	//TextOut(getMemDC(), 10, 200, _buffer1, strlen(_buffer));
}

void enemyManager::enemyPlayerCollsion()
{
	float _playerRcCenterX = (_playerMg->getPlayerRect().left + _playerMg->getPlayerRect().right) / 2;
	float _playerRcCenterY = (_playerMg->getPlayerRect().top + _playerMg->getPlayerRect().bottom) / 2;
	
	// 다 break 걸리면 한마리만 체크하는 건가요???
	for (int i = 0; i < _vEnemys.size(); i++)
	{
		if (checkPointInRect(_vEnemys[i]->getEnemyRangeRect(), _playerRcCenterX, _playerRcCenterY)) // 만약 충돌했으면
		{
			_vEnemys[i]->setIsCollsion(true);
			// break;
		}
		else if (!checkPointInRect(_vEnemys[i]->getEnemyRangeRect(), _playerRcCenterX, _playerRcCenterY)) // 만약 충돌하지 않았으면
		{
			_vEnemys[i]->setIsCollsion(false);
			// break;
		}
		
	}
}



////플레이어 피격 판정
//void enemyManager::getDamage()
//{
//	for (int i = 0; i < _vEnemys.size(); i++) // 마지막 녀석의 공격 유무가 최종 공격 유무 값
//	{
//		if (isCollision(_playerMg->getPlayerRect(), _vEnemys[i]->getEnemyAtkRect()))
//		{
//			_playerDamage = true;
//		}
//		if (!isCollision(_playerMg->getPlayerRect(), _vEnemys[i]->getEnemyAtkRect()))
//		{
//			_playerDamage = false;
//		}
//	}
//}
//
//bool enemyManager::getEnemyIsLeft() // 마지막 녀석의 방향 값이 최종 방향 값
//{ 
//	for (int i = 0; i < _vEnemys.size(); i++)
//	{
//		if (_vEnemys[i]->getEnemyIsLeft())
//		{
//			_enemyIsLeft = true;
//		}
//		if (!_vEnemys[i]->getEnemyIsLeft())
//		{
//			_enemyIsLeft = false;
//		}
//	}
//	return _enemyIsLeft; 
//}

//void enemyManager::enemyPlayerAttackCollsion()
//{
//	float _playerRcCenterX = (_playerMg->getPlayerRect().left + _playerMg->getPlayerRect().right) / 2;
//	float _playerRcCenterY = (_playerMg->getPlayerRect().top + _playerMg->getPlayerRect().bottom) / 2;
//
//	// 다 break 걸리면 한마리만 체크하는 건가요???
//	for (int i = 0; i < _vEnemys.size(); i++)
//	{
//		if (checkPointInRect(_vEnemys[i]->getEnemyAtkRect(), _playerRcCenterX, _playerRcCenterY)) // 만약 충돌했으면
//		{
//			_vEnemys[i]->setIsAttackCollsion(true);
//			// break;
//		}
//		else if (!checkPointInRect(_vEnemys[i]->getEnemyAtkRect(), _playerRcCenterX, _playerRcCenterY)) // 만약 충돌하지 않았으면
//		{
//			_vEnemys[i]->setIsAttackCollsion(false);
//			// break;
//		}
//	}
//}