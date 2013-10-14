/*
 * Brick.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: ADIC
 */

#include "Brick.h"
#include "Ball.h"
#include "GameDirector.h"

static CCPoint BRICK_RECT = ccp(40.0f, 20.0f);

enum Tag
{
	TagShadow = 1,
};

Brick::Brick()
{

}

Brick::~Brick()
{

}

CCRect Brick::rect()
{
	CCPoint s = ccpMult(BRICK_RECT, BRICK_SCALE_FACTOR);
	return CCRectMake(-s.x/2, -s.y/2, s.x, s.y);
}

Brick* Brick::createBrick(CCTexture2D* aTexture)
{
	Brick* pBrick = new Brick();
	pBrick->initWithTexture(aTexture);
	pBrick->setTextureRect(CCRectMake(BRICK_RECT.x, 0, BRICK_RECT.x, BRICK_RECT.y));
	pBrick->setScale(BRICK_SCALE_FACTOR);
	pBrick->autorelease();

	return pBrick;
}

void Brick::setBrickStatu(BrickType type)
{
	m_brickType = type;
	if (type == BRICK_INVISIBLE)
	{
		setVisible(false);
		return;
	}
	setTextureRect(CCRectMake(type*BRICK_RECT.x, 0, BRICK_RECT.x, BRICK_RECT.y));
	setVisible(true);
}

bool Brick::collideWithBall(Ball* ball)
{
	if (boundingBox().intersectsRect(ball->boundingBox()))
		return true;
	else
		return false;
}

void Brick::brickCrashedByBall(Ball* ball)
{
	//remove shadow

}

