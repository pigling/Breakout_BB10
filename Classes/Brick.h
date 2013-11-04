/*
 * Brick.h
 *
 *  Created on: Oct 8, 2013
 *      Author: ADIC
 */

#ifndef BRICK_H_
#define BRICK_H_

#include "cocos2d.h"
#include "constant.h"

USING_NS_CC;

class Ball;

class Brick : public CCSprite
{
public:
	Brick();
	~Brick();


	void setBrickStatu(BrickType type);

	static Brick* createBrick(CCTexture2D* aTexture);
	CCRect rect();

	bool collideWithBall(Ball* ball);
	void brickCrashedByBall(Ball* ball);

	void callbackRemoveBrick();

	inline void setBonusType(BonusType type) { m_bonusType = type; };
	inline BonusType getBonusType() { return m_bonusType; };

	inline BrickType getBrickType() { return m_brickType; };
private:
	BrickType m_brickType;
	BonusType m_bonusType;
};

#endif /* BRICK_H_ */
