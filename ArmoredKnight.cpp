#include "stdafx.h"
#include "ArmoredKnight.h"


HRESULT ArmoredKnight::init()
{
	//아머드 나이트
	_enemy._enemyimg = IMAGEMANAGER->addFrameImage("ArmoredKnight_Move", "Castlevania/Image/MonsterImage/ArmoredKnight/State_Move.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ArmoredKnight_Dead", "Castlevania/Image/MonsterImage/ArmoredKnight/State_Death.bmp", 423, 399, 2, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("ArmoredKnight_Attack01", "Castlevania/Image/MonsterImage/ArmoredKnight/State_Attack_01_update.bmp", 3993, 584, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ArmoredKnight_Attack02", "Castlevania/Image/MonsterImage/ArmoredKnight/State_Attack_02_update.bmp", 4650, 594, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ArmoredKnight_Attack03", "Castlevania/Image/MonsterImage/ArmoredKnight/State_Attack_03_update.bmp", 5300, 485, 11, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("ArmoredKnight_AttackEffect02", "Castlevania/Image/MonsterImage/ArmoredKnight/State_Attack_Effect.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ArmoredKnight_AttackEffect03", "Castlevania/Image/MonsterImage/ArmoredKnight/State_Attack_Effect_02.bmp", 960, 576, 8, 2, true, RGB(255, 0, 255));
	
	_enemy._chaseX = 10;
	_enemy._chaseCount = 10;
	_enemy._frameX = 0;
	_enemy._maxX = 300;
	_enemy._minX = 50;
	_enemy._speed = 3;
	_enemy._viewRange = 200;
	_enemy._attackRange = 150;

	_enemy._frameCount = 0;
	_enemy._ptX = _enemy._initX;
	_enemy._enemyState = ENEMY_PATROL;

	_idleCount = 0;

	return S_OK;
}

void ArmoredKnight::release()
{
}

void ArmoredKnight::update()
{
	_enemy._frameCount++;

	float _rangeRcLeft;

	if (_enemy._enemyState != ENEMY_NONACTIVE)
	{
		if (_enemy._isLeft)
		{
			_rangeRcLeft = _enemy._ptX - _enemy._viewRange + 20;
			_enemy._rangeRc = RectMake(_rangeRcLeft, _enemy._initY + 88, _enemy._viewRange, _enemy._rec.bottom - _enemy._rec.top);

		}
		if (!_enemy._isLeft)
		{
			_rangeRcLeft = _enemy._ptX + _enemy._viewRange - 100;
			_enemy._rangeRc = RectMake(_rangeRcLeft, _enemy._initY + 88, _enemy._viewRange, _enemy._rec.bottom - _enemy._rec.top);
		}

		/*if (isCollision(_playerMg->getPlayerRect(), _enemy._rangeRc))
		{
			setEnemyState(ENEMY_ATTACK);
		}*/

		if (_enemy._enemyState == ENEMY_ATTACK)
		{
			if (_enemy._isLeft)
			{
				_enemy._attackRc = RectMake(_rangeRcLeft + 30, _enemy._initY + 168, _enemy._attackRange, 30);

			}
			if (!_enemy._isLeft)
			{
				_enemy._attackRc = RectMake(_rangeRcLeft - 30, _enemy._initY + 168, _enemy._attackRange, 30);
			}
		}

		if ((_enemy._isCollsion && _enemy._enemyState != ENEMY_STAY) && (_enemy._isCollsion && _enemy._enemyState != ENEMY_DELAY))
		{
			setEnemyState(ENEMY_ATTACK);
		}
	}

	
	

	switch (_enemy._enemyState)
	{
		case ENEMY_STAY:
		{
			_enemy._imgkeyName = "ArmoredKnight_Move";
			_idleCount++;

			if (_idleCount == 100 && _enemy._isLeft)
			{
				_idleCount = 0;
				_enemy._isLeft = false;
				setEnemyState(ENEMY_PATROL);
			}

			if (_idleCount == 100 && !_enemy._isLeft)
			{
				_idleCount = 0;
				_enemy._isLeft = true;;
				setEnemyState(ENEMY_PATROL);
			}
		}
		break;

		case ENEMY_DELAY:
		{
			_enemy._imgkeyName = "ArmoredKnight_Move";
			_idleCount++;

			if (_enemy._isLeft)
			{
				_enemy._ptX -= 2;
			}
			else if(!_enemy._isLeft)
			{
				_enemy._ptX += 2;
			}
			if (_idleCount% 7 == 0)
			{
				if (_enemy._isLeft)
				{
					_enemy._frameX--;
					if (_enemy._frameX <= 0)
					{
						_enemy._frameX = 7;
					}
				}
				else if (!_enemy._isLeft)
				{
					_enemy._frameX++;
					if (_enemy._frameX >= 7)
					{
						_enemy._frameX = 0;
					}
				}
			}
			if (_idleCount == 100)
			{
				_idleCount = 0;
				setEnemyState(ENEMY_CHASE);
			}
		}
		break;

		case ENEMY_PATROL:
		{
			_enemy._imgkeyName = "ArmoredKnight_Move";

			if (_enemy._frameCount == 15)
			{
				_enemy._frameCount = 0;

				if (_enemy._isLeft)
				{
					_enemy._frameX--;
					if (_enemy._frameX <= 0)
					{
						_enemy._frameX = 7;
					} 
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX++;
					if (_enemy._frameX >= 7)
					{
						_enemy._frameX = 0;
					}
				}
			}

			if (!_enemy._isLeft && ((_enemy._maxX + _enemy._initX) >= _enemy._ptX))
			{
				_enemy._ptX += 2;
				if ((_enemy._maxX + _enemy._initX) <= _enemy._ptX)
				{
					setEnemyState(ENEMY_STAY);
				}
			}

			if (_enemy._isLeft && (_enemy._initX - _enemy._maxX) <= _enemy._ptX)
			{
				_enemy._ptX -= 2;
				if ((_enemy._initX - _enemy._maxX) >= _enemy._ptX)
				{
					setEnemyState(ENEMY_STAY);
				}
			}
		}
		break;

		case ENEMY_ATTACK:
		{
			_enemy._imgkeyName = "ArmoredKnight_Attack01";

			if (_enemy._isLeft)
			{
				if (_enemy._frameCount == 7)
				{
					_enemy._frameCount = 0;
					_enemy._frameX--;
					_enemy._ptX -= 20;
					if (_enemy._frameX <= 0)
					{
						_enemy._enemyState = ENEMY_DELAY;
						//break;
					}
				}
			}

			if (!_enemy._isLeft)
			{
				if (_enemy._frameCount == 7)
				{
					_enemy._frameCount = 0;
					_enemy._frameX++;
					_enemy._ptX += 20;
					if (_enemy._frameX >= 10)
					{
						_enemy._enemyState = ENEMY_DELAY;
						//break;
					}
				}
			}

		}
		break;

		//case ENEMY_ATTACK02:
		//{
		//	_enemy._imgkeyName = "ArmoredKnight_Attack02";

		//	if (_enemy._isLeft)
		//	{
		//		if (_enemy._frameCount == 5)
		//		{
		//			_enemy._frameCount = 0;
		//			_enemy._frameX--;
		//			_enemy._ptX -= 20;
		//			if (_enemy._frameX <= 0)
		//			{
		//				_enemy._enemyState = ENEMY_CHASE;
		//				//break;
		//			}
		//		}
		//	}

		//	if (!_enemy._isLeft)
		//	{
		//		if (_enemy._frameCount == 5)
		//		{
		//			_enemy._frameCount = 0;
		//			_enemy._frameX++;
		//			_enemy._ptX += 20;
		//			if (_enemy._frameX >= 9)
		//			{
		//				_enemy._enemyState = ENEMY_CHASE;
		//				//break;
		//			}
		//		}
		//	}

		//}
		//break;

		case ENEMY_CHASE:
		{

			_enemy._imgkeyName = "ArmoredKnight_Move";

			if (_enemy._frameCount == 15)
			{
				_enemy._frameCount = 0;

				if (_enemy._isLeft)
				{
					_enemy._frameX--;
					if (_enemy._ptX >= 350)
					{
						_enemy._ptX -= 10;
					}
					else if (_enemy._ptX < 350)
					{
						_enemy._isLeft = false;
					}

					if (_enemy._frameX <= 0)
					{
						_enemy._frameX = 7;
					}
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX++;

					if (_enemy._ptX <= 6290)
					{
						_enemy._ptX += 10;
					}
					else if(_enemy._ptX > 6290)
					{
						_enemy._isLeft = true;
					}

					if (_enemy._frameX >= 7)
					{
						_enemy._frameX++;
						_enemy._frameX = 0;
					}
				}
			}
		}
		break;

		case ENEMY_DEAD:
		{
			_enemy._imgkeyName = "ArmoredKnight_Dead";
			if (_enemy._frameCount == 50)
			{
				_enemy._frameCount = 0;
				if (_enemy._isLeft)
				{
					_enemy._frameX--;
					if (_enemy._frameX < 0)
					{
						setEnemyState(ENEMY_NONACTIVE);
					}
				}

				if (!_enemy._isLeft)
				{
					_enemy._frameX++;
					if (_enemy._frameX > 1)
					{
						setEnemyState(ENEMY_NONACTIVE);
					}
				}
			}
		}
		break;
	}

	

	_enemy._rec = RectMake(_enemy._ptX + 20, _enemy._initY + 88, 80, 200);
	sprintf_s(_buffer, "current EnemyFrameX: %d", _enemy._frameX);
}

void ArmoredKnight::render()
{
	//CAMERA->rectangle(getMemDC(), _enemy._rec);
	//CAMERA->rectangle(getMemDC(), _enemy._rangeRc);

	if (_enemy._enemyState != ENEMY_NONACTIVE)
	{
		if (_enemy._enemyState != ENEMY_DEAD)
		{
			if (_enemy._enemyState != ENEMY_ATTACK)
			{
				CAMERA->frameRender(getMemDC(), IMAGEMANAGER->findImage(_enemy._imgkeyName), _enemy._ptX, _enemy._initY, _enemy._frameX, _enemy._isLeft);
			}
			else if (_enemy._enemyState == ENEMY_ATTACK || _enemy._enemyState == ENEMY_ATTACK02)
			{
				//CAMERA->rectangle(getMemDC(), _enemy._attackRc);

				CAMERA->frameRender(getMemDC(), IMAGEMANAGER->findImage(_enemy._imgkeyName), _enemy._ptX - 140, _enemy._initY, _enemy._frameX, _enemy._isLeft);
			}
		}
		
		if (_enemy._enemyState == ENEMY_DEAD)
		{
			if (_enemy._isLeft)
			{
				CAMERA->frameRender(getMemDC(), IMAGEMANAGER->findImage(_enemy._imgkeyName), _enemy._ptX - 70, _enemy._initY + 90, _enemy._frameX, _enemy._isLeft);
			}
			if (!_enemy._isLeft)
			{
				CAMERA->frameRender(getMemDC(), IMAGEMANAGER->findImage(_enemy._imgkeyName), _enemy._ptX - 35, _enemy._initY + 90, _enemy._frameX, _enemy._isLeft);
			}
		}
	}
	

	//TextOut(getMemDC(), 10, 250, _buffer, strlen(_buffer));
	//_enemy._enemyimg->frameRender(getMemDC(), _enemy._ptX, _enemy._initY, _enemy._frameX, _enemy._isLeft);
}

void ArmoredKnight::setEnemyState(tagEnemyState _enemyState)
{
	_enemy._enemyLastState = _enemy._enemyState;
	_enemy._enemyState = _enemyState;

	if (_enemy._enemyLastState != _enemy._enemyState)
	{
		_enemy._frameCount = 0;

		switch (_enemyState)
		{
			case ENEMY_DELAY:
			{
				_idleCount = 0;
				if (_enemy._isLeft)
				{
					_enemy._frameX = 7;
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX = 0;
				}
			}
			break;

			case ENEMY_STAY:
			{
				if (_enemy._isLeft)
				{
					_enemy._frameX = 7;
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX = 0;
				}
			}
			break;

			case ENEMY_PATROL:
			{
				if (_enemy._isLeft)
				{
					_enemy._frameX = 7;
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX = 0;
				}
			}
			break;

			
			case ENEMY_ATTACK:
			{
				//_enemy._ptX = _enemy._initX - 100;
				if (_enemy._isLeft)
				{
					_enemy._frameX = 10;
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX = 0;
				}
				/*if (_enemy._enemyLastState == ENEMY_PATROL)
				{
					if (_enemy._isLeft)
					{
						_enemy._frameX = 10;
					}
					if (!_enemy._isLeft)
					{
						_enemy._frameX = 0;
					}
				}*/
			}
			break;

			case ENEMY_ATTACK02:
			{
				if (_enemy._isLeft)
				{
					_enemy._frameX = 9;
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX = 0;
				}
			}
			break;

			case ENEMY_CHASE:
			{
				if (_enemy._isLeft)
				{
					_enemy._frameX = 7;
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX = 0;
				}
			}
			break;

			case ENEMY_DEAD:
			{
				if (_enemy._isLeft)
				{
					_enemy._frameX = 1;
				}
				if (!_enemy._isLeft)
				{
					_enemy._frameX = 0;
				}
			}
			break;

			case ENEMY_NONACTIVE:
			{

			}
			break;
		}
	}
}

