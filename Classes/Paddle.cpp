#include "Paddle.h"
#include "constant.h"
#include "GameAreaDef.h"

static CCPoint PADDLE_RECT = ccp(54.0f, 18.0f);



Paddle::Paddle(void)
{
	leftMost = GameAreaDef::getGameAreaLeftMost();
	rightMost = GameAreaDef::getGameAreaRightMost();
}

Paddle::~Paddle(void)
{
}

CCRect Paddle::rect()
{
    CCPoint s = ccpMult(PADDLE_RECT, SCALE_FACTOR);
    return CCRectMake(-s.x / 2, -s.y / 2, s.x, s.y); //scale rect of paddle
}

Paddle* Paddle::paddleWithTexture(CCTexture2D* aTexture)
{
    Paddle* pPaddle = new Paddle();
    pPaddle->initWithTexture( aTexture );
    pPaddle->setScale(SCALE_FACTOR); //scale paddle sprite
    pPaddle->autorelease();

    return pPaddle;
}

bool Paddle::initWithTexture(CCTexture2D* aTexture)
{
    if( CCSprite::initWithTexture(aTexture) ) 
    {
        m_state = kPaddleStateUngrabbed;
    }
    
    return true;
}

void Paddle::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void Paddle::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}    

bool Paddle::containsTouchLocation(CCTouch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Paddle::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (m_state != kPaddleStateUngrabbed) return false;
    if ( !containsTouchLocation(touch) ) return false;
    
    m_state = kPaddleStateGrabbed;
    return true;
}

void Paddle::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get CCSets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
    
    CCAssert(m_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
    
    CCPoint touchPoint = touch->getLocation();
    
    if (touchPoint.x >= rightMost-rect().size.width/2)
    {
    	setPosition(ccp(rightMost-rect().size.width/2, getPosition().y));
    	//CCLog("%f %f %f", rightMost, rect().size.width/2, touchPoint.x);
    }
    else if (touchPoint.x <= leftMost+rect().size.width/2)
    {
    	setPosition(ccp(leftMost+rect().size.width/2, getPosition().y));
    }
    else
    {
    	setPosition( ccp(touchPoint.x, getPosition().y) );
    }
}

CCObject* Paddle::copyWithZone(CCZone *pZone)
{
    this->retain();
    return this;
}

void Paddle::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCAssert(m_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
    
    m_state = kPaddleStateUngrabbed;
} 

void Paddle::touchDelegateRetain()
{
    this->retain();
}

void Paddle::touchDelegateRelease()
{
    this->release();
}
