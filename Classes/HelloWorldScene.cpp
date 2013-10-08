#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "FirstLevelMenuScene.h"
#include "GameMenuScene.h"
#include "constant.h"

USING_NS_CC;
using namespace CocosDenshion;

static int HomeScreenMenuCount = sizeof(HomeScreenMenuNames)/sizeof(*HomeScreenMenuNames);

static FirstLevelMenuScene* CreateScene(int nIdx)
{
	CCDirector::sharedDirector()->purgeCachedData();

	FirstLevelMenuScene* pScene = NULL;

	switch (nIdx)
	{
	case SCENE_GAME:
		pScene = new GameMenuScene();
		break;
	case SCENE_HELP:
		break;
	case SCENE_SETTING:
		break;
	case SCENE_ABOUT:
		break;
	}

	return pScene;
}


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSize size = CCDirector::sharedDirector()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    /////////////////////////////
    // 3. add your codes below...

    //title
    CCLabelBMFont* titleFont = CCLabelBMFont::create("Breakout", "futura-48.fnt", 80);
    addChild(titleFont);
    titleFont->setPosition(ccp(size.width/2, size.height-200));

    //add menu
    CCMenu* pItemMenu = CCMenu::create();
    for (int i = 0; i < HomeScreenMenuCount; i++)
    {
    	CCLabelBMFont* label = CCLabelBMFont::create(HomeScreenMenuNames[i].c_str(), "futura-48.fnt", 48);
    	CCMenuItemLabel* pMenu = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::menuCallback));
    	pItemMenu->addChild(pMenu, i+1000);
    	pMenu->setPosition(ccp(size.width/2, size.height-(i+2)*200));
    }
    pItemMenu->setPosition(CCPointZero);
    addChild(pItemMenu, 2);


    setTouchEnabled(true);

    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuCallback(CCObject* pSender)
{
	CCMenuItem* pMenuItem = (CCMenuItem*)(pSender);
	int nIdx = pMenuItem->getZOrder()-1000;

	//create the scene and run it
	FirstLevelMenuScene* pScene = CreateScene(nIdx);
	if (pScene)
	{
		pScene->runThisScene();
		pScene->release();
	}
}
