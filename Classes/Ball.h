#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"
#include "constant.h"

class Paddle;
class Brick;

USING_NS_CC;


class Ball : public CCSprite
{
    CCPoint m_velocity;
    CCSprite* m_shadow; //shadow follows the ball

public:
    Ball(void);
    virtual ~Ball(void);

    virtual void draw(void);

    float radius();
    //BOOL initWithTexture(CCTexture2D* aTexture);
    //virtual void setTexture(CCTexture2D* newTexture);
    void move(float delta);
    void collideWithPaddle(Paddle* paddle);
    void setBallColor(BallColor color);


public:
    inline void setVelocity(CCPoint velocity) {m_velocity = velocity;}
    inline CCPoint getVelocity() {return m_velocity;}

public:
    static Ball* ballWithTexture(CCTexture2D* aTexture, CCRect rect);
};

#endif
