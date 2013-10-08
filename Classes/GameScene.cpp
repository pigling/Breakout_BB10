/*
 * GameScene.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: ADIC
 */

#include "GameScene.h"
#include "Ball.h"
#include "Paddle.h"
#include "constant.h"

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
	m_ballVelocity = ccp(40.0f, -400.0f);
	m_ball = Ball::ballWithTexture(CCTextureCache::sharedTextureCache()->addImage("gfx/ball.png"), CCRectMake(0,0,12,12));
	m_ball->setVelocity(m_ballVelocity);
	m_ball->setPosition(ccp(120, 120));
	addChild(m_ball);
	m_ball->retain();


	CCTexture2D* paddleTexture = CCTextureCache::sharedTextureCache()->addImage("gfx/paddle.png");
	m_paddle = Paddle::paddleWithTexture(paddleTexture);
	m_paddle->setTextureRect(CCRectMake(0,0,54,18));
	m_paddle->setPosition(ccp(120, 20));
	addChild(m_paddle);
	m_paddle->retain();

	schedule(schedule_selector(GameLayer::update));
}

GameLayer::~GameLayer()
{
	m_ball->release();
	m_paddle->release();
}

void GameLayer::update(float delta)
{
	m_ball->move(delta);
	m_ball->collideWithPaddle(m_paddle);

	m_ball->draw();
}

void GameScene::runThisTest()
{
	CCDirector::sharedDirector()->replaceScene(this);
}
