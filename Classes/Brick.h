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

	void collideWithBall(Ball* ball);
};

#endif /* BRICK_H_ */
