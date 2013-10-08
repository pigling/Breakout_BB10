/*
 * FirstLevelMenuScene.h
 *
 *  Created on: Sep 24, 2013
 *      Author: ADIC
 */

#ifndef FIRSTLEVELMENUSCENE_H_
#define FIRSTLEVELMENUSCENE_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;


class FirstLevelMenuScene : public CCScene
{
public:
	FirstLevelMenuScene(bool bPortrait = false);
	virtual void onEnter();

	virtual void runThisScene() = 0;


	// callback for back to the homescreen menu page
	virtual void ManiMenuCallback(CCObject* pSender);
};

typedef CCLayer* (*NEWTESTFUNC)();
#define TESTLAYER_CREATE_FUNC(className) \
static CCLayer* create##className() \
{ return new className(); }

#endif /* FIRSTLEVELMENUSCENE_H_ */
