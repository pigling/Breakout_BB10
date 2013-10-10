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
	inline BallStatus getBallStatus(BonusType bonusType) { return &m_ballStatus[bounsType]; };

	static GameDirector* sharedGameDirector();
private:
	BallStatus m_ballStatus[BONUS_COUNT];

};

#endif /* GAMEDIRECTOR_H_ */
