#pragma once

#include "cocos2d.h"


class EncryptLayer : public cocos2d::CCLayerColor
{
public:
	EncryptLayer();
	virtual ~EncryptLayer();

	static cocos2d::CCScene* scene();

	virtual bool init();
	CREATE_FUNC(EncryptLayer);

private:

	void menuEncryptTouchUpInside(cocos2d::CCObject* sender);

	void menuDecryptTouchUpInside(cocos2d::CCObject* sender);

	void convertFile(bool isEncrypt);

	void blinkPrompt(const char* prompt);
	void showPrompt(const char* prompt);
	void callFuncPromptDisappear(void);

private:

	cocos2d::CCMenu* m_menu;
	cocos2d::CCLabelTTF* m_labelPrompt;
};