/*
 * Extra.h
 *
 *  Created on: Oct 11, 2013
 *      Author: ADIC
 *
 * This extra class represents the extra-brick sprites when ball hits some bricks associated with extra property
 */

#ifndef EXTRA_H_
#define EXTRA_H_

#include "cocos2d.h"
#include "constant.h"

USING_NS_CC;
class Paddle;

class Extra : public CCSprite
{
	CCSprite* m_shadow; //shadow follows the extra sprite
	CCPoint m_velocity;
	BonusType m_bonus;	//bonus type associated with this extra

public:
	Extra();
	~Extra();

	void setBonusType(BonusType type);
	inline BonusType getBonusType() { return m_bonus; };

	//virtual void draw(void);

	static Extra* createExtra(CCTexture2D* aTexture);
	bool collidewithPaddle(Paddle* paddle);
	void move(float delta);
};

#endif /* EXTRA_H_ */
