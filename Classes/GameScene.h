/*
 * GameScene.h
 *
 *  Created on: Sep 26, 2013
 *      Author: ADIC
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class Ball;
class Paddle;
class Brick;


class GameScene : public CCScene
{
public:
	GameScene();
	virtual void runThisTest();

	virtual void menuCallback(CCObject* pSender);
};



class GameLayer : public CCLayer
{
private:
	Ball* m_ball;
	Paddle* m_paddle;
	Brick* m_brick;
	CCPoint m_ballVelocity;

public:
	GameLayer();
	~GameLayer();

	void addBrick(CCPoint point);

	void update(float delta);
};

#endif /* GAMESCENE_H_ */
