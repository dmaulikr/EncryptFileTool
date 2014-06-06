#include "AppDelegate.h"
#include "EncryptLayer.h"


USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);
	pDirector->setDisplayStats(false);
	pDirector->setAnimationInterval(1.0 / 60);
	pEGLView->setDesignResolutionSize(480, 320, kResolutionFixedWidth);

	CCScene *pScene = EncryptLayer::scene();
	pDirector->runWithScene(pScene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{

}

void AppDelegate::applicationWillEnterForeground()
{

}
