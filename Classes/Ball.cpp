#include "Ball.h"
#include "Paddle.h"
#include "GameAreaDef.h"

static CCPoint BALL_RECT = ccp(12.0f, 12.0f);

Ball::Ball(void) : m_shadow(NULL)
{
}

Ball::~Ball(void)
{
}

float Ball::radius()
{
	return BALL_RECT.x*SCALE_FACTOR/2; //scale the radius of ball
    //return getTexture()->getContentSize().height * SCALE_FACTOR / 2;
}

Ball* Ball::ballWithTexture(CCTexture2D* aTexture, CCRect rect)
{
    Ball* pBall = new Ball();
    pBall->initWithTexture(aTexture, rect);
    pBall->setScale(SCALE_FACTOR); //scale the ball
    CCLog("%f", pBall->boundingBox().size.width);
    //pBall->autorelease();


    CCSprite* shadow = new CCSprite();
    shadow->initWithFile("gfx/ball_shadow.png");
    pBall->addChild(shadow);
    shadow->autorelease();
    shadow->setPosition(ccp(10, -10));

    return pBall;
}

void Ball::move(float delta)
{
    this->setPosition( ccpAdd(getPosition(), ccpMult(m_velocity, delta)) );

    if (getPosition().x > GameAreaDef::getBallMoveRect().getMaxX() - radius())
    {
        setPosition( ccp( GameAreaDef::getBallMoveRect().getMaxX() - radius(), getPosition().y) );
        m_velocity.x *= -1;
    }
    else if (getPosition().x < GameAreaDef::getBallMoveRect().getMinX() + radius())
    {
        setPosition( ccp(GameAreaDef::getBallMoveRect().getMinX() + radius(), getPosition().y) );
        m_velocity.x *= -1;
    }

    if (getPosition().y > GameAreaDef::getScoreRect().getMinY() - radius())
    {
    	setPosition(ccp(getPosition().x, GameAreaDef::getScoreRect().getMinY()-radius()));
    	m_velocity.y *= -1;
    }
    else if (getPosition().y < GameAreaDef::getFingerTouchRect().getMinY() + radius())
    {
    	setPosition(ccp(getPosition().x, GameAreaDef::getFingerTouchRect().getMinY()+radius()));
    	m_velocity.y *= -1;
    }
}

void Ball::collideWithPaddle(Paddle* paddle)
{
    CCRect paddleRect = paddle->rect();
    paddleRect.origin.x += paddle->getPosition().x;
    paddleRect.origin.y += paddle->getPosition().y;

    float lowY  = paddleRect.getMinY();
    float midY  = paddleRect.getMidY();
    float highY = paddleRect.getMaxY();

    float leftX  = paddleRect.getMinX();
    float rightX = paddleRect.getMaxX();

    if (getPosition().x > leftX && getPosition().x < rightX) {

        bool hit = false;
        float angleOffset = 0.0f;

        if (getPosition().y <= highY + this->boundingBox().size.height)
        {
            setPosition( ccp(getPosition().x, highY + this->boundingBox().size.height) );
            hit = true;
            angleOffset = (float)M_PI / 2;
            //CCLog("%f, %f, %f", getPosition().y, highY, radius());
        }


        if (hit)
        {
            float hitAngle = ccpToAngle(ccpSub(paddle->getPosition(), getPosition())) + angleOffset;

            float scalarVelocity = ccpLength(m_velocity) * 1.05f;
            float velocityAngle = -ccpToAngle(m_velocity) + 0.5f * hitAngle;

            m_velocity = ccpMult(ccpForAngle(velocityAngle), scalarVelocity);
        }
    }
}

void Ball::setBallColor(BallColor color)
{
	setTextureRect(CCRectMake(color*12, 0, 12, 12));
}

void Ball::draw()
{
	CCSprite::draw();
}
