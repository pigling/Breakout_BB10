/*
 * GameMenuScene.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: ADIC
 */

#include "GameMenuScene.h"
#include "GameScene.h"
#include "cocos2d.h"
#include "constant.h"

static int GameMenuCount = sizeof(GameMenuNames)/sizeof(*GameMenuNames);

void GameMenuScene::runThisScene()
{
	CCLayer* pLayer = new GameMenuLayer();
	pLayer->init();
	pLayer->autorelease();
	addChild(pLayer);

	CCDirector::sharedDirector()->replaceScene(this);
}

void GameMenuLayer::onEnter()
{
	CCLayer::onEnter();

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenu* pMenu = CCMenu::create();

	for (int i = 0; i < GameMenuCount; i++)
	{
		CCLabelBMFont* label = CCLabelBMFont::create(GameMenuNames[i].c_str(), "futura-48.fnt", 48);
		CCMenuItemLabel* menuItem = CCMenuItemLabel::create(label, this, menu_selector(GameMenuLayer::menuCallback));
		pMenu->addChild(menuItem, i+1000);
		menuItem->setPosition(ccp(size.width/2, size.height-(i+1)*200));
	}
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

}

void GameMenuLayer::onExit()
{
	CCLayer::onExit();
}

void GameMenuLayer::menuCallback(CCObject* pSender)
{
	CCMenuItem* menuItem = (CCMenuItem*)(pSender);
	int nIdx = menuItem->getZOrder()-1000;

	if (nIdx == GAME_MENU_START)
	{
		GameScene* pScene = new GameScene();
		pScene->runThisTest();
		pScene->release();
	}
}

CCScene* GameMenuLayer::scene()
{
	CCScene* scene = CCScene::create();

	GameMenuLayer* layer = GameMenuLayer::create();

	scene->addChild(layer);

	return scene;
}
