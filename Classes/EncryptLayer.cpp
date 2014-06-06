#include "EncryptLayer.h"
#include "Tool/rc4Encrypt/RC4EncryptTool.h"
#include "Tool/CBFileTool.h"
#include "Tool/CBFolderTool.h"
#include <string>
#include <vector>
#include <fstream>

using namespace cocos2d;


cocos2d::CCScene* EncryptLayer::scene()
{
	CCScene *scene = CCScene::create();
	EncryptLayer *layer = EncryptLayer::create();
	scene->addChild(layer);
	return scene;
}

EncryptLayer::EncryptLayer()
	: m_menu(NULL)
	, m_labelPrompt(NULL)
{

}

EncryptLayer::~EncryptLayer()
{
	CC_SAFE_RELEASE_NULL(m_labelPrompt);
}

bool EncryptLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::create("Click Button To Encrypt Or Decrypt", "Arial", 25);
	label->setPosition(ccp(winSize.width*0.5f, winSize.height*0.75f));
	label->setColor(ccRED);
	this->addChild(label);

	CCMenuItemFont::setFontName("Arial");
	CCMenuItemFont::setFontSize(35);
	CCMenuItemFont* menuItemEncrypt = CCMenuItemFont::create("Encrypt", this, menu_selector(EncryptLayer::menuEncryptTouchUpInside));
	CCMenuItemFont* menuItemDecrypt = CCMenuItemFont::create("Decrypt", this, menu_selector(EncryptLayer::menuDecryptTouchUpInside));
	m_menu = CCMenu::create(menuItemEncrypt, menuItemDecrypt, NULL);
	m_menu->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
	m_menu->setColor(ccBLACK);
	m_menu->alignItemsHorizontallyWithPadding(50);
	this->addChild(m_menu);

	m_labelPrompt = CCLabelTTF::create("Prompt", "Arial", 25);
	m_labelPrompt->retain();
	m_labelPrompt->setPosition(ccp(winSize.width*0.5f, winSize.height*0.25f));
	m_labelPrompt->setColor(ccRED);

	return true;
}

void EncryptLayer::menuEncryptTouchUpInside( cocos2d::CCObject* sender )
{
	m_menu->setTouchEnabled(false);
	this->blinkPrompt("Encrypting");
	this->convertFile(true);
	m_menu->setTouchEnabled(true);
}

void EncryptLayer::menuDecryptTouchUpInside( cocos2d::CCObject* sender )
{
	m_menu->setTouchEnabled(false);
	this->blinkPrompt("Decrypting");
	this->convertFile(false);
	m_menu->setTouchEnabled(true);
}

void EncryptLayer::convertFile( bool isEncrypt )
{
	std::string strPasswordFilePth = CBFileTool::getFullPath("password.txt");
	std::string strPassword = CBFileTool::getFileData(strPasswordFilePth.c_str());

	std::vector<std::string> vecSearchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
	if (vecSearchPaths.size() == 0)
	{
		showPrompt("Read File Error");
		return;
	}

	std::string strFolderFile = "file";
	std::string strFolderFileConvert = "fileConvert";

	std::string strSearchPath = vecSearchPaths[0];
	strSearchPath += strFolderFile;
	std::vector<std::string> vecFilePath = CBFolderTool::AllFilePathInFolder(strSearchPath);

	for (int i=0; i<vecFilePath.size(); i++)
	{
		std::string strFilePath = vecFilePath[i];
		std::string strFileData = CBFileTool::getFileData(strFilePath.c_str());
		if (!strFileData.empty())
		{
			std::string strFileNameTmp = strFilePath.substr(strSearchPath.length(), strFilePath.length());
			std::string::size_type pos = strFileNameTmp.find("\\");
			while(pos != std::string::npos)
			{
				strFileNameTmp.replace(pos, 1, "/");
				pos = strFileNameTmp.find("\\");
			}
			std::string strFilePathSave = strSearchPath + strFolderFileConvert + strFileNameTmp;

			std::string strFileDataConvert = "";
			if (isEncrypt)
			{
				strFileDataConvert = RC4EncryptTool::Encrypt(strFileData.c_str(), strPassword.c_str());
			}
			else
			{
				strFileDataConvert = RC4EncryptTool::Decrypt(strFileData.c_str(), strPassword.c_str());
			}

			CBFileTool::saveFileToFolder(strFileDataConvert.c_str(), strFilePathSave.c_str());
		}
	}

	if (isEncrypt)
	{
		this->showPrompt("Encrypt Finish");
	}
	else
	{
		this->showPrompt("Decrypt Finish");
	}
}

void EncryptLayer::blinkPrompt( const char* prompt )
{
	m_labelPrompt->stopAllActions();
	m_labelPrompt->setString(prompt);
	m_labelPrompt->setOpacity(255);

	this->callFuncPromptDisappear();
	this->addChild(m_labelPrompt);

	CCBlink* blink = CCBlink::create(1.0f, 3);
	CCRepeatForever* repeat = CCRepeatForever::create(blink);
	m_labelPrompt->runAction(repeat);
}

void EncryptLayer::showPrompt( const char* prompt )
{
	m_labelPrompt->stopAllActions();
	m_labelPrompt->setString(prompt);
	m_labelPrompt->setOpacity(0);

	this->callFuncPromptDisappear();
	this->addChild(m_labelPrompt);

	CCFadeIn* fadeIn = CCFadeIn::create(0.2f);
	CCDelayTime* delay = CCDelayTime::create(1.0f);
	CCFadeOut* fadeOut = CCFadeOut::create(0.2f);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(EncryptLayer::callFuncPromptDisappear));
	CCSequence* sequence = CCSequence::create(fadeIn, delay, fadeOut, callFunc, NULL);
	m_labelPrompt->runAction(sequence);
}

void EncryptLayer::callFuncPromptDisappear( void )
{
	if (m_labelPrompt->getParent() != NULL)
	{
		m_labelPrompt->removeFromParent();
	}
}
