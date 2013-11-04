/*
 * GameDirector.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: ADIC
 */

#include <stdlib.h>
#include <time.h>
#include "GameDirector.h"
#include "Ball.h"
#include "Brick.h"
#include "Extra.h"
#include "Paddle.h"


static GameDirector* s_GameDirector = NULL;

GameDirector::GameDirector() : m_arrayBalls(NULL),
		m_arrayBricks(NULL), m_arrayExtras(NULL), m_paddle(NULL)
{

}

GameDirector::~GameDirector()
{
	CCObject* pObject;
	if (m_arrayBalls)
	{
		CCARRAY_FOREACH(m_arrayBalls, pObject)
		{
			Ball* ball = (Ball*)pObject;
			ball->removeFromParent();
		}
		m_arrayBalls->release();
		m_arrayBalls = NULL;
	}
	if (m_arrayBricks)
	{
		CCARRAY_FOREACH(m_arrayBricks, pObject)
		{
			Brick* brick = (Brick*)pObject;
			brick->removeFromParent();
		}
		m_arrayBricks->release();
		m_arrayBricks = NULL;
	}
	if (m_arrayExtras)
	{
		CCARRAY_FOREACH(m_arrayExtras, pObject)
		{
			Extra* extra = (Extra*)pObject;
			extra->removeFromParent();
		}
		m_arrayExtras->release();
		m_arrayExtras = NULL;
	}
	if (m_paddle)
	{
		m_paddle = NULL;
	}
	if(s_GameDirector)
	{
		s_GameDirector = NULL;
	}
}

GameDirector* GameDirector::sharedGameDirector()
{
	if (!s_GameDirector)
	{
		srand(time(NULL)); //random seed
		s_GameDirector = new GameDirector();
		s_GameDirector->init();
	}
	return s_GameDirector;
}

void GameDirector::init()
{
	m_arrayBalls = CCArray::create();
	if (m_arrayBalls)
		m_arrayBalls->retain();
	m_arrayExtras = CCArray::create();
	if (m_arrayExtras)
		m_arrayExtras->retain();
	m_arrayBricks = CCArray::create();
	if (m_arrayBricks)
		m_arrayBricks->retain();
	resetAllBallStatus();
	resetGameScore();
}

void GameDirector::logicUpdate(float delta)
{
	//check the relationship between different bonus types
	//check if the bonus bit available as time passed

	//float fps = 1.0f/CCDirector::sharedDirector()->getSecondsPerFrame;
	for (unsigned int i = 0; i < sizeof(m_ballStatus)/sizeof(*m_ballStatus); i++)
	{
		//some bonuses have no time limit while others have
		if (i == SCORE_200 || i == SCORE_500 || i == SCORE_1000 || i == SCORE_2000 || i == SCORE_5000 || i == SCORE_10K)
			continue;
		else if (i == SHRINK_PADDLE || i == EXPAND_PADDLE)
			continue;
		else if (i == EXTRA_BALL)
			continue;
		else if (i == JOKER)
			continue;
		else if (i == RESET)
			continue;
		else if (i == TIME_ADD)
			continue;
		else if (i == RANDOM_EXTRA)
			continue;

		if (m_ballStatus[i].isEnabled)
		{
			if (m_ballStatus[i].periodInFrame)
			{
				m_ballStatus[i].periodInFrame -= delta;
				if (!m_ballStatus[i].periodInFrame <= 0.0f) //time out
				{
					m_ballStatus[i].isEnabled = false;
				}
			}
		}
	}

	CCObject* pObject;
	CCARRAY_FOREACH(m_arrayBalls, pObject)
	{
		Ball* ball = (Ball*)pObject;
		ball->move(delta);
		ball->collideWithPaddle(m_paddle);
		//check collision between ball and brick
		CCObject* pObject1;
		CCARRAY_FOREACH(m_arrayBricks, pObject1)
		{
			Brick* brick = (Brick*)pObject1;

			if (brick->boundingBox().intersectsRect(ball->boundingBox()))
			{
				//first to check ball status
				//then to check brick associated bonus
				//for strong brick, the ball will only crash brick after some hits
				if (m_ballStatus[ENERGY_BALL].isEnabled) //energy ball, crash brick immdiately
				{
					CCLog("Energy Ball");

				}
				else if (m_ballStatus[EXPLOSIVE_BALL].isEnabled) //explosive ball, need explosive effect
				{
					CCLog("Explosive Ball");
				}
				else if (m_ballStatus[WEAK_BALL].isEnabled) //weak ball, 40% chance not to crash ball
				{
					CCLog("Weak Ball");
				}
				else if (m_ballStatus[CHAOS].isEnabled) //chaos, ball reflected randomly
				{
					CCLog("Chaos");
				}
				//for normal status, brick crashed by ball
				//brick->brickCrashedByBall(ball);
				CCPoint velocity = ball->getVelocity();
				if (brick->boundingBox().getMinX()+ball->radius() < ball->getPositionX() < brick->boundingBox().getMaxX()-ball->radius())
				{
					float yvector = ball->getPositionY()-brick->getPositionY();
					if (yvector*velocity.y < 0) //make sure the ball moves away from brick
					{
						velocity.y *= -1;
						//brick crashed by ball
						brick->brickCrashedByBall(ball);
					}
				}
				else if (brick->boundingBox().getMinX()+ball->radius() == ball->getPositionX() || brick->boundingBox().getMaxX()-ball->radius() == ball->getPositionX())
				{
					if (brick->boundingBox().getMaxY()+ball->radius() == ball->getPositionY() || brick->boundingBox().getMinY()-ball->radius() == ball->getPositionY())
					{
						velocity = ccpMult(velocity, -1.0f);
						brick->brickCrashedByBall(ball);
					}
					else
					{
						float xvector = ball->getPositionX()-brick->getPositionX();
						if (xvector*velocity.x < 0) //make sure the ball moves away from brick
						{
							velocity.x *= -1;
							brick->brickCrashedByBall(ball);
						}
					}
				}
				ball->setVelocity(velocity);
			}
		}
	}

	CCARRAY_FOREACH(m_arrayExtras, pObject)
	{
		Extra* extra = (Extra*)pObject;
		extra->move(delta);
		extra->collidewithPaddle(m_paddle);
	}
}

void GameDirector::setGameStatus(BonusType type)
{
	switch(type)
	{
	case SCORE_200:
		addGameScore(200);
		break;
	case SCORE_500:
		addGameScore(500);
		break;
	case SCORE_1000:
		addGameScore(1000);
		break;
	case SCORE_2000:
		addGameScore(2000);
		break;
	case SCORE_5000:
		addGameScore(5000);
		break;
	case SCORE_10K:
		addGameScore(10000);
		break;

	case END_OF_RAINBOW:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case STICKY_PADDLE:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[GHOSTLY_PADDLE].isEnabled)
			{
				m_ballStatus[GHOSTLY_PADDLE].isEnabled = false;
				m_ballStatus[GHOSTLY_PADDLE].periodInFrame = 0.0f;
			}
			if (m_ballStatus[FROZEN_PADDLE].isEnabled)
			{
				m_ballStatus[FROZEN_PADDLE].isEnabled = false;
				m_ballStatus[FROZEN_PADDLE].periodInFrame = 0.0f;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case ENERGY_BALL:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[EXPLOSIVE_BALL].isEnabled)
			{
				m_ballStatus[EXPLOSIVE_BALL].isEnabled = false;
				m_ballStatus[EXPLOSIVE_BALL].periodInFrame = 0.0f;
			}
			if (m_ballStatus[WEAK_BALL].isEnabled)
			{
				m_ballStatus[WEAK_BALL].isEnabled = false;
				m_ballStatus[WEAK_BALL].periodInFrame = 0.0f;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 5.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 5.0f;
		}
		break;

	case BONUS_FLOOR:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 10.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 10.0f;
		}
		break;

	case WEAPON:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 5.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 5.0f;
		}
		break;

	case SPEED_DOWN:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[SPEED_UP].isEnabled)
			{
				m_ballStatus[SPEED_UP].isEnabled = false;
				m_ballStatus[SPEED_UP].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case SPEED_UP:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[SPEED_DOWN].isEnabled)
			{
				m_ballStatus[SPEED_DOWN].isEnabled = false;
				m_ballStatus[SPEED_DOWN].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case EXPLOSIVE_BALL:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[ENERGY_BALL].isEnabled)
			{
				m_ballStatus[ENERGY_BALL].isEnabled = false;
				m_ballStatus[ENERGY_BALL].periodInFrame = 0;
			}
			if (m_ballStatus[WEAK_BALL].isEnabled)
			{
				m_ballStatus[WEAK_BALL].isEnabled = false;
				m_ballStatus[WEAK_BALL].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 10.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 10.0f;
		}
		break;

	case BONUS_MAGNET:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[MALUS_MAGNET].isEnabled)
			{
				m_ballStatus[MALUS_MAGNET].isEnabled = false;
				m_ballStatus[MALUS_MAGNET].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case MALUS_MAGNET:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[BONUS_MAGNET].isEnabled)
			{
				m_ballStatus[BONUS_MAGNET].isEnabled = false;
				m_ballStatus[BONUS_MAGNET].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case FROZEN_PADDLE:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[STICKY_PADDLE].isEnabled)
			{
				m_ballStatus[STICKY_PADDLE].isEnabled = false;
				m_ballStatus[STICKY_PADDLE].periodInFrame = 0;
			}
			if (m_ballStatus[GHOSTLY_PADDLE].isEnabled)
			{
				m_ballStatus[GHOSTLY_PADDLE].isEnabled = false;
				m_ballStatus[GHOSTLY_PADDLE].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 1.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 1.0f;
		}
		break;

	case LIGHTS_OUT:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case CHAOS:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case GHOSTLY_PADDLE:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[STICKY_PADDLE].isEnabled)
			{
				m_ballStatus[STICKY_PADDLE].isEnabled = false;
				m_ballStatus[STICKY_PADDLE].periodInFrame = 0;
			}
			if (m_ballStatus[FROZEN_PADDLE].isEnabled)
			{
				m_ballStatus[FROZEN_PADDLE].isEnabled = false;
				m_ballStatus[FROZEN_PADDLE].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20.0f;
		}
		break;

	case WEAK_BALL:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[EXPLOSIVE_BALL].isEnabled)
			{
				m_ballStatus[EXPLOSIVE_BALL].isEnabled = false;
				m_ballStatus[EXPLOSIVE_BALL].periodInFrame = 0;
			}
			if (m_ballStatus[ENERGY_BALL].isEnabled)
			{
				m_ballStatus[ENERGY_BALL].isEnabled = false;
				m_ballStatus[ENERGY_BALL].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 5.0f;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 5.0f;
		}
		break;

	case RESET:
		resetAllBallStatus();
		break;

	case TIME_ADD:
		for (unsigned int i = 0; i < sizeof(m_ballStatus)/sizeof(*m_ballStatus); i++)
		{
			if (m_ballStatus[i].isEnabled)
			{
				m_ballStatus[i].periodInFrame += 7.0f;
			}
		}
		break;

	case RANDOM_EXTRA:
		int i = sizeof(m_ballStatus)/sizeof(*m_ballStatus);
		setGameStatus(BonusType(rand()%i));
		break;

	}
}

void GameDirector::resetAllBallStatus()
{
	for (unsigned int i = 0; i < sizeof(m_ballStatus)/sizeof(*m_ballStatus); i++)
	{
		m_ballStatus[i].isEnabled = false;
		m_ballStatus[i].periodInFrame = 0;
	}
}

void GameDirector::addBall(Ball* ball)
{
	if (m_arrayBalls)
	{
		m_arrayBalls->addObject(ball);
	}
}

void GameDirector::addBrick(Brick* brick)
{
	if (m_arrayBricks)
	{
		m_arrayBricks->addObject(brick);
	}
}

void GameDirector::addExtra(Extra* extra)
{
	if (m_arrayExtras)
	{
		m_arrayExtras->addObject(extra);
	}
}

void GameDirector::removeBall(Ball* ball)
{
	if (m_arrayBalls)
		m_arrayBalls->removeObject(ball);
}

void GameDirector::removeBrick(Brick* brick)
{
	if (m_arrayBricks)
	{
		m_arrayBricks->removeObject(brick);
	}
}

void GameDirector::removeExtra(Extra* extra)
{
	if (m_arrayExtras)
		m_arrayExtras->removeObject(extra);
}

void GameDirector::addPaddle(Paddle* paddle)
{
	m_paddle = paddle;
}
