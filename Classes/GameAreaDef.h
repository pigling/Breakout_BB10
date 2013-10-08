/*
 * GameAreaDef.h
 *
 *  Created on: Oct 8, 2013
 *      Author: ADIC
 */

#ifndef GAMEAREADEF_H_
#define GAMEAREADEF_H_
#include "cocos2d.h"

USING_NS_CC;

class GameAreaDef
{
public:
	static CCRect getFingerTouchRect();
	static CCRect getBallMoveRect();
	static CCRect getAdDisplayRect();
	static CCRect getScoreRect();

	static float getGameAreaLeftMost();
	static float getGameAreaRightMost();

private:
	static void lazyInit();
	static CCRect touchRect;
	static CCRect BallMoveRect;
	static CCRect AdDisplayRect;
	static CCRect ScoreRect;
};

#endif /* GAMEAREADEF_H_ */
