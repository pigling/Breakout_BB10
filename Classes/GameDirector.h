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

USING_NS_CC;

class Brick;
class Ball;
class Extra;

class GameDirector
{
public:
	GameDirector();
	virtual ~GameDirector();

	void init();
	void logicUpdate(float delta);
	void setGameStatus(BonusType bonusType);
	void resetAllBallStatus();

	void addBall(Ball* ball);
	void addBrick(Brick* brick);
	void addExtra(Extra* extra);

	void removeBall(Ball* ball);
	void removeBrick(Brick* brick);
	void removeExtra(Extra* extra);

	inline BallStatus* getBallStatus(BonusType bonusType) { return &m_ballStatus[bonusType]; };

	inline void addGameScore(int score) { m_gameScore += score; };
	inline void resetGameScore() { m_gameScore = 0; };
	inline unsigned int getGameScore() { return m_gameScore; };

	inline CCArray* getArrayBalls() { return m_arrayBalls; };
	inline CCArray* getArrayBricks() { return m_arrayBricks; };
	inline CCArray* getArrayExtras() { return m_arrayExtras; };

	static GameDirector* sharedGameDirector();
private:
	BallStatus m_ballStatus[BONUS_COUNT];
	unsigned int m_gameScore;
	CCArray* m_arrayBalls;
	CCArray* m_arrayBricks;
	CCArray* m_arrayExtras;


};

#endif /* GAMEDIRECTOR_H_ */
