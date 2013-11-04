/*
 * GameScene.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: ADIC
 */

#include "GameScene.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "constant.h"
#include "GameAreaDef.h"
#include "GameDirector.h"
#include <stdlib.h>
#include <time.h>

GameScene::GameScene()
{
	GameLayer* pLayer = new GameLayer();
	addChild(pLayer);
	pLayer->release();
}

void GameScene::menuCallback(CCObject* pSender)
{

}

GameLayer::GameLayer()
{
	//TODO...
	//create game including loading game data from file,

	CCSprite* background = CCSprite::create("gfx/nukeback.png");
	addChild(background);
	float xBck = (GameAreaDef::getBallMoveRect().getMaxX()+GameAreaDef::getBallMoveRect().getMinX())/2;
	float yBck = (GameAreaDef::getBallMoveRect().getMaxY()+GameAreaDef::getBallMoveRect().getMinY())/2;
	background->setPosition(ccp(xBck, yBck));
	background->setScaleY(1.75);

	m_ballVelocity = ccp(40.0f, -400.0f);
	m_ball = Ball::ballWithTexture(CCTextureCache::sharedTextureCache()->addImage("gfx/balls.png"), CCRectMake(0,0,12,12));
	m_ball->setVelocity(m_ballVelocity);
	m_ball->setPosition(ccp(120, 120));
	addChild(m_ball);
	m_ball->retain(); //release from GameDirector
	GameDirector::sharedGameDirector()->addBall(m_ball);

	CCTexture2D* paddleTexture = CCTextureCache::sharedTextureCache()->addImage("gfx/paddle.png");
	m_paddle = Paddle::paddleWithTexture(paddleTexture);
	m_paddle->setTextureRect(CCRectMake(0,0,54,18));
	m_paddle->setPosition(ccp(54, 20));
	addChild(m_paddle);
	m_paddle->retain();
	GameDirector::sharedGameDirector()->addPaddle(m_paddle);

/*
	CCTexture2D* brickTexture = CCTextureCache::sharedTextureCache()->addImage("gfx/bricks.png");
	m_brick = Brick::createBrick(brickTexture);
	m_brick->setBrickStatu(BRICK_GREEN);
	m_brick->setPosition(ccp(100, 200));
	addChild(m_brick);
	m_brick->retain();  //release from GameDirector
	GameDirector::sharedGameDirector()->addBrick(m_brick);
*/
	for (int i = 0; i < 5; i++)
	{
		addBrick(ccp(100+60*i, 600));
	}
	schedule(schedule_selector(GameLayer::update));
}

GameLayer::~GameLayer()
{
	//m_ball->release();
	//m_paddle->release();
	//m_brick->release();
}

void GameLayer::update(float delta)
{
	//this is mainly function to control the whole game
	//it should update components' movement and check interaction between components
	//it should also control the whole game layer display

	GameDirector::sharedGameDirector()->logicUpdate(delta);
	//m_ball->move(delta);
	//m_ball->collideWithPaddle(m_paddle);


	//m_ball->draw();

}

void GameScene::runThisTest()
{
	CCDirector::sharedDirector()->replaceScene(this);
}

void GameLayer::addBrick(CCPoint point)
{
	CCTexture2D* brickTexture = CCTextureCache::sharedTextureCache()->addImage("gfx/bricks.png");
	Brick* brick = Brick::createBrick(brickTexture);
	brick->setBrickStatu(BrickType(rand()%6+BRICK_BROWN));
	brick->setPosition(point);
	addChild(brick);
	//m_brick->retain();
	GameDirector::sharedGameDirector()->addBrick(brick);
}
