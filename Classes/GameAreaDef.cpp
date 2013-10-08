/*
 * GameAreaDef.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: ADIC
 */

#include "GameAreaDef.h"


//for Blackberry Z10 (768x1280) or Z30 (720x1280)
//the whole game scene is 720x1280, from top to bottom of screen
//720x50 for advertisement service API integration
//720x130 for lives, scores, extras indication, etc.
//720x960 for real breakout game area (ball movement area)
//720x140 for finger touch movement area
//CCRect RECT_TOUCH_AREA = CCRectMake(0, 0, 720, 140);
//CCRect RECT_GAME_AREA = CCRectMake(0, 141, 720, 1100);
//CCRect RECT_SCORE_AREA = CCRectMake(0, 1101, 720, 1230);

CCRect GameAreaDef::touchRect;
CCRect GameAreaDef::BallMoveRect;
CCRect GameAreaDef::ScoreRect;
CCRect GameAreaDef::AdDisplayRect;


void GameAreaDef::lazyInit()
{
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CCSize visSize = pEGLView->getVisibleSize();
	CCPoint pointOrigin = pEGLView->getVisibleOrigin();

	if (touchRect.size.width == 0.0f && touchRect.size.height == 0.0f)
	{
		touchRect.size.width = 720;
		touchRect.size.height = 140;
		touchRect.origin.x = (visSize.width-touchRect.size.width)/2+pointOrigin.x;
		touchRect.origin.y = 0;
	}

	if (BallMoveRect.size.width == 0.0f && BallMoveRect.size.height == 0.0f)
	{
		BallMoveRect.size.width = 720;
		BallMoveRect.size.height = 960;
		BallMoveRect.origin.x = (visSize.width-touchRect.size.width)/2+pointOrigin.x;
		BallMoveRect.origin.y = touchRect.getMaxY()+1;
	}

	if (ScoreRect.size.width == 0.0f && ScoreRect.size.height == 0.0f)
	{
		ScoreRect.size.width = 720;
		ScoreRect.size.height = 130;
		ScoreRect.origin.x = (visSize.width-touchRect.size.width)/2+pointOrigin.x;
		ScoreRect.origin.y = BallMoveRect.getMaxY()+1;
	}

	if (AdDisplayRect.size.width == 0.0f && AdDisplayRect.size.height == 0.0f)
	{
		AdDisplayRect.size.width = 720;
		AdDisplayRect.size.height = 50;
		AdDisplayRect.origin.x = (visSize.width-touchRect.size.width)/2+pointOrigin.x;
		AdDisplayRect.origin.y = ScoreRect.getMaxY();
	}
}

CCRect GameAreaDef::getFingerTouchRect()
{
	lazyInit();
	return touchRect;
}

CCRect GameAreaDef::getBallMoveRect()
{
	lazyInit();
	return BallMoveRect;
}

CCRect GameAreaDef::getScoreRect()
{
	lazyInit();
	return ScoreRect;
}

CCRect GameAreaDef::getAdDisplayRect()
{
	lazyInit();
	return AdDisplayRect;
}

float GameAreaDef::getGameAreaLeftMost()
{
	lazyInit();
	return BallMoveRect.getMinX();
}

float GameAreaDef::getGameAreaRightMost()
{
	lazyInit();
	return BallMoveRect.getMaxX();
}
