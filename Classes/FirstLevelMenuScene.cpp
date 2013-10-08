/*
 * FirstLevelMenuScene.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: ADIC
 */

#include "FirstLevelMenuScene.h"
#include "HelloWorldScene.h"

FirstLevelMenuScene::FirstLevelMenuScene(bool bPortrait)
{
	CCScene::init();
}

void FirstLevelMenuScene::onEnter()
{
	CCScene::onEnter();

    CCMenuItemImage* pBackItem = CCMenuItemImage::create(
    		"back.png",
    		"back_big.png",
    		this,
    		menu_selector(FirstLevelMenuScene::ManiMenuCallback));
    CCMenu* pMenu =CCMenu::create(pBackItem, NULL);

    CCSize backSize = pBackItem->getContentSize();

    pMenu->setPosition(ccp(backSize.width, backSize.height));

    addChild(pMenu, 1);
}

void FirstLevelMenuScene::ManiMenuCallback(CCObject* pSender)
{
	CCScene* pScene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
