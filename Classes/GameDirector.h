/*
 * GameDirector.h
 *
 *  Created on: Oct 9, 2013
 *      Author: ADIC
 */

#ifndef GAMEDIRECTOR_H_
#define GAMEDIRECTOR_H_

#include "constant.h"
#include "cocos2d.h"


class GameDirector
{
public:
	GameDirector();
	virtual ~GameDirector();

	void init();
	void logicUpdate();
	void setGameStatus(BonusType bonusType);
	void resetAllBallStatus();
	inline BallStatus* getBallStatus(BonusType bonusType) { return &m_ballStatus[bonusType]; };

	inline void addGameScore(int score) { m_gameScore += score; };
	inline void resetGameScore() { m_gameScore = 0; };
	inline unsigned int getGameScore() { return m_gameScore; };

	static GameDirector* sharedGameDirector();
private:
	BallStatus m_ballStatus[BONUS_COUNT];
	unsigned int m_gameScore;

};

#endif /* GAMEDIRECTOR_H_ */
