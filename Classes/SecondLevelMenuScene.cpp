/*
 * SecondLevelMenuScene.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: ADIC
 */

#include "SecondLevelMenuScene.h"
#include "GameMenuScene.h"

SecondLevelMenuScene::SecondLevelMenuScene(bool bPortrait)
{
	CCScene::init();
}

void SecondLevelMenuScene::onEnter()
{
	CCScene::onEnter();

    CCMenuItemImage* pBackItem = CCMenuItemImage::create(
    		"back.png",
    		"back_big.png",
    		this,
    		menu_selector(SecondLevelMenuScene::ManiMenuCallback));
    CCMenu* pMenu =CCMenu::create(pBackItem, NULL);

    CCSize backSize = pBackItem->getContentSize();

    pMenu->setPosition(ccp(backSize.width, backSize.height));

    addChild(pMenu, 1);

}

void SecondLevelMenuScene::ManiMenuCallback(CCObject* pSender)
{
	CCScene* pScene = GameMenuLayer::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

