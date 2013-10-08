/*
 * SecondLevelMenuScene.h
 *
 *  Created on: Sep 26, 2013
 *      Author: ADIC
 */

#ifndef SECONDLEVELMENUSCENE_H_
#define SECONDLEVELMENUSCENE_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SecondLevelMenuScene : public CCScene
{
public:
	SecondLevelMenuScene(bool bPortrait = false);
	virtual void onEnter();

	virtual void runThisScene() = 0;

	// callback for back to the homescreen menu page
	virtual void ManiMenuCallback(CCObject* pSender);
};

typedef CCLayer* (*NEWTESTFUNC)();
#define TESTLAYER_CREATE_FUNC(className) \
static CCLayer* create##className() \
{ return new className(); }


#endif /* SECONDLEVELMENUSCENE_H_ */
