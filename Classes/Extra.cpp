/*
 * Extra.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: ADIC
 */

#include "Extra.h"
#include "Paddle.h"
#include "GameDirector.h"
#include "GameAreaDef.h"


static CCPoint EXTRA_RECT = ccp(40.0f, 20.0f);
static float EXTRA_DOWNSPEED = 50.0f;

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

	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("gfx/bricks.png");
	CCSprite* pShadow = new CCSprite();
	pShadow->initWithTexture(texture, CCRectMake(6*EXTRA_RECT.x, 0, EXTRA_RECT.x, EXTRA_RECT.y));
	//CCSprite* pShadow= CCSprite::create("gfx/bricks.png", CCRectMake(6*EXTRA_RECT.x, 0, EXTRA_RECT.x, EXTRA_RECT.y));
	if (pShadow)
	{
		pShadow->setScale(0.8f);
		pExtra->addChild(pShadow, TagShadow);
		pShadow->autorelease();
		pShadow->setPosition(ccp(20, -10));
	}

	return pExtra;
}

void Extra::setBonusType(BonusType type)
{
	m_bonus = type;
	setTextureRect(CCRectMake(EXTRA_RECT.x*type, 0, EXTRA_RECT.x, EXTRA_RECT.y));
}

/*
void Extra::draw()
{
	CCSprite::draw();
}
*/

bool Extra::collidewithPaddle(Paddle* paddle)
{
	if (boundingBox().intersectsRect(paddle->boundingBox()))
	{
		//GameDirector::sharedGameDirector()->setGameStatus(m_bonus);
		removeFromParent();
		GameDirector::sharedGameDirector()->removeExtra(this);
		return true;
	}
	return false;
}

void Extra::move(float delta)
{
	setPositionY(getPositionY()-EXTRA_DOWNSPEED*delta);
	if (getPositionY() < GameAreaDef::getFingerTouchRect().getMinY())
	{
		removeFromParent();
		GameDirector::sharedGameDirector()->removeExtra(this);
	}
}
