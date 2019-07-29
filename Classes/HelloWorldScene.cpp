/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	//auto menu = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	////auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	//if (label == nullptr)
	//{
	//    problemLoading("'fonts/Marker Felt.ttf'");
	//}
	//else
	//{
	//    // position the label on the center of the screen
	//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
	//                            origin.y + visibleSize.height - label->getContentSize().height));

	//    // add the label as a child to this layer
	//    this->addChild(label, 1);
	//}

	// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");
	//if (sprite == nullptr)
	//{
	//	//problemLoading("'HelloWorld.png'");
	//}
	//else
	//{
	//	// position the sprite on the center of the screen
	//	//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//	// add the sprite as a child to this layer
	//	this->addChild(sprite, 0);
	//}
	int audioID;
	audioID = experimental::AudioEngine::play2d("bgm.mp3");
	centerPos = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 stationPos = centerPos + Vec2(0, 170.0f);
	Vec2 trainStartPos = Vec2(visibleSize.width + 400.0f, centerPos.y + 50.0f);

	//field_green
	field = Sprite::create("bg_field_green.jpg");
	field->setPosition(centerPos);
	field->setScale(1.3f);
	this->addChild(field);

	//sheet_blue
	sheet_blue = Sprite::create("picknick_sheet.png");
	sheet_blue->setPosition(centerPos - Vec2(0,100));
	sheet_blue->setOpacity(0.0f);
	this->addChild(sheet_blue);
	//dedede
	dedede = Sprite::create("dedede.png");
	dedede->setScale(0.2f);
	dedede->setPosition(centerPos + Vec2(-200, -50));
	dedede->setOpacity(0.0f);
	this->addChild(dedede);

	//wady
	wady = Sprite::create("w_run.png");
	wady->setScale(0.2f);
	wady->setPosition(centerPos + Vec2(200, -50));
	wady->setOpacity(0.0f);
	this->addChild(wady);

	//station_back
	bg_Station_back = Sprite::create("bg_station_back.png");
	bg_Station_back->setPosition(centerPos);
	bg_Station_back->setScale(0.8f);
	this->addChild(bg_Station_back);

	//kirby
	kirby = Sprite::create("kirby.png");
	kirby->setPosition(stationPos);
	kirby->setScale(0.3f);
	kirby->setRotation(-15.0f);
	this->addChild(kirby);

	//train
	Sprite* train = Sprite::create("train.png");
	train->setPosition(trainStartPos);
	this->addChild(train);

	//station_front
	bg_Station_front = Sprite::create("bg_station_front.png");
	bg_Station_front->setPosition(centerPos);
	bg_Station_front->setScale(0.8f);
	this->addChild(bg_Station_front);

	//lunchbox_humburg
	lunchbox_humburg = Sprite::create("lunchbox_humburg.png");
	lunchbox_humburg->setPosition(centerPos + Vec2(-150, -100));
	lunchbox_humburg->setScale(0.3);
	lunchbox_humburg->setOpacity(0.0f);
	this->addChild(lunchbox_humburg);
	//lunchbox_cute
	lunchbox_cute = Sprite::create("lunchbox_cute.png");
	lunchbox_cute->setPosition(centerPos + Vec2(150, -100));
	lunchbox_cute->setScale(0.3);
	lunchbox_cute->setOpacity(0.0f);
	this->addChild(lunchbox_cute);




	//KirbyActions
	JumpTo* jump = JumpTo::create(5.0f, kirby->getPosition(), 10.0f, 5);
	ScaleBy* frontRun = ScaleBy::create(5.0f, 0.8f);
	RotateTo* rotate_right = RotateTo::create(2.0f, 15.0f);
	RotateTo* rotate_left = RotateTo::create(2.0f, -15.0f);
	RotateTo* rotate_remove = RotateTo::create(1.0f, 0.0f);
	Sequence* rotation = Sequence::create(rotate_right, rotate_left, nullptr);
	Repeat* rotate_rep = Repeat::create(rotation, 3);
	Spawn* trainRide = Spawn::create(jump, frontRun, nullptr);
	FadeOut* fadeOut = FadeOut::create(1.0f);
	Sequence* trainWaitRide = Sequence::create(rotate_rep, rotate_remove, trainRide, fadeOut, nullptr);
	kirby->runAction(trainWaitRide);


	//trainActions
	MoveTo* trainMove1 = MoveTo::create(10.0f, Vec2(centerPos.x, trainStartPos.y));
	DelayTime* trainDelay = DelayTime::create(10.0f);
	MoveBy* trainMove2 = MoveBy::create(10.0f, Vec2(-1500, 0));
	FadeOut* sceneEnd = FadeOut::create(3.0f);
	CallFunc* bg_sceneEnd = CallFunc::create(CC_CALLBACK_0(HelloWorld::SceneEnd, this));
	CallFunc* nextSceneStart = CallFunc::create(CC_CALLBACK_0(HelloWorld::NextScene, this));

	Spawn* sceneEnd_All = Spawn::create(sceneEnd, bg_sceneEnd, nullptr);
	Sequence* trainAct = Sequence::create(trainMove1, trainDelay, trainMove2, sceneEnd_All, nextSceneStart ,nullptr);
	train->runAction(trainAct);
	

	this->scheduleUpdate();
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::SceneEnd() {
	FadeOut* act = FadeOut::create(3.0f);
	bg_Station_back->runAction(act);
	bg_Station_front->runAction(act->clone());
}

void HelloWorld::NextScene() {
	FadeIn* bg_fadeIn = FadeIn::create(3.0f);
	sheet_blue->runAction(bg_fadeIn);
	lunchbox_humburg->runAction(bg_fadeIn->clone());
	lunchbox_cute->runAction(bg_fadeIn->clone());
	dedede->runAction(bg_fadeIn->clone());
	wady->runAction(bg_fadeIn->clone());


	kirby->setScale(0.01f);
	kirby->setPosition(centerPos);
	FadeIn* kirby_in = FadeIn::create(2.0f);
	ScaleTo* kirby_zoom = ScaleTo::create(2.0f, 0.25f);
	Spawn* kirby_nextAct = Spawn::create(kirby_in, kirby_zoom, nullptr);
	
	kirby->runAction(kirby_nextAct);
}
