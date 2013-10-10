/*
 * GameDirector.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: ADIC
 */

#include <stdlib.h>
#include <time.h>
#include "GameDirector.h"

USING_NS_CC;

static GameDirector* s_GameDirector = NULL;

GameDirector::GameDirector()
{

}

GameDirector::~GameDirector()
{
	s_GameDirector = NULL;
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
	resetAllBallStatus();
	resetGameScore();
}

void GameDirector::logicUpdate()
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
				m_ballStatus[i].periodInFrame--;
				if (!m_ballStatus[i].periodInFrame) //time out
				{
					m_ballStatus[i].isEnabled = false;
				}
			}
		}
	}
}

void GameDirector::setGameStatus(BonusType type)
{
	int fps = int(1.0f/CCDirector::sharedDirector()->getSecondsPerFrame());
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
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
		}
		break;

	case STICKY_PADDLE:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[GHOSTLY_PADDLE].isEnabled)
			{
				m_ballStatus[GHOSTLY_PADDLE].isEnabled = false;
				m_ballStatus[GHOSTLY_PADDLE].periodInFrame = 0;
			}
			if (m_ballStatus[FROZEN_PADDLE].isEnabled)
			{
				m_ballStatus[FROZEN_PADDLE].isEnabled = false;
				m_ballStatus[FROZEN_PADDLE].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
		}
		break;

	case ENERGY_BALL:
		if (!m_ballStatus[type].isEnabled)
		{
			if (m_ballStatus[EXPLOSIVE_BALL].isEnabled)
			{
				m_ballStatus[EXPLOSIVE_BALL].isEnabled = false;
				m_ballStatus[EXPLOSIVE_BALL].periodInFrame = 0;
			}
			if (m_ballStatus[WEAK_BALL].isEnabled)
			{
				m_ballStatus[WEAK_BALL].isEnabled = false;
				m_ballStatus[WEAK_BALL].periodInFrame = 0;
			}
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 5*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 5*fps;
		}
		break;

	case BONUS_FLOOR:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 10*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 10*fps;
		}
		break;

	case WEAPON:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 5*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 5*fps;
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
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
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
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
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
			m_ballStatus[type].periodInFrame = 10*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 10*fps;
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
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
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
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
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
			m_ballStatus[type].periodInFrame = 1*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 1*fps;
		}
		break;

	case LIGHTS_OUT:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
		}
		break;

	case CHAOS:
		if (!m_ballStatus[type].isEnabled)
		{
			m_ballStatus[type].isEnabled = true;
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
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
			m_ballStatus[type].periodInFrame = 20*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 20*fps;
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
			m_ballStatus[type].periodInFrame = 5*fps;
		}
		else
		{
			m_ballStatus[type].periodInFrame += 5*fps;
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
				m_ballStatus[i].periodInFrame += 7*fps;
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

