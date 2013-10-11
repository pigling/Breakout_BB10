/*
 * Extra.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: ADIC
 */

#include "Extra.h"
#include "Paddle.h"
#include "GameDirector.h"


static CCPoint EXTRA_RECT = ccp(40.0f, 20.0f);

enum TAG {
	TagShadow = 1,
};

Extra::Extra()
{

}

Extra::~Extra()
{

}

Extra* Extra::createExtra(CCTexture2D* aTexture)
{
	Extra* pExtra = new Extra();
	pExtra->initWithTexture(aTexture);
	pExtra->setTextureRect(CCRectMake(EXTRA_RECT.x, 0, EXTRA_RECT.x, EXTRA_RECT.y));
	pExtra->setScale(BRICK_SCALE_FACTOR);
	pExtra->autorelease();

	CCSprite* pShadow= CCSprite::create("gfx/bricks.png", CCRectMake(6*EXTRA_RECT.x, 0, EXTRA_RECT.x, EXTRA_RECT.y));
	pShadow->setScale(BRICK_SCALE_FACTOR);
	pExtra->addChild(pShadow, TagShadow);
	pShadow->autorelease();

	return pExtra;
}

void Extra::setBonusType(BonusType type)
{
	m_bonus = type;
	setTextureRect(CCRectMake(EXTRA_RECT.x*type, 0, EXTRA_RECT.x, EXTRA_RECT.y));
}

void Extra::draw()
{
	CCSprite* shadow = (CCSprite*)(getChildByTag(TagShadow));
	shadow->setPosition(ccp(getPosition().x+boundingBox().size.width/2, getPosition().y-boundingBox().size.height/2));
	this->draw();
	shadow->draw();
}

bool Extra::collidewithPaddle(Paddle* paddle)
{
	if (boundingBox().intersectsRect(paddle->boundingBox()))
	{
		//GameDirector::sharedGameDirector()->setGameStatus(m_bonus);
		return true;
	}
	return false;
}
