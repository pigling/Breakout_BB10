/*
 * GameMenuScene.h
 *
 *  Created on: Sep 24, 2013
 *      Author: ADIC
 */

#ifndef GAMEMENUSCENE_H_
#define GAMEMENUSCENE_H_

#include <FirstLevelMenuScene.h>

USING_NS_CC;


class GameMenuScene: public FirstLevelMenuScene
{
public:
	virtual void runThisScene();
};

class GameMenuLayer : public CCLayer
{
public:

	static CCScene* scene();

	virtual void onEnter();
	virtual void onExit();

	void menuCallback(CCObject* pSender);

	CREATE_FUNC(GameMenuLayer);
};

#endif /* GAMEMENUSCENE_H_ */
