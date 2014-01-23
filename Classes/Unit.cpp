#include "Game.h"

//#include "ATile.h"
Unit::Unit(){
	//type = types::DEFAULT;
}
Unit::Unit(Game * g, int index, ATile * tile){
		Unit::g = g;
		Unit::tile = tile;
		auto colorOffset = rand() % 1;
		Color3B c = Color3B(255 - colorOffset,255 - colorOffset,255 - colorOffset);

		/*
		CCAnimation *animation = CCAnimation::create();

		// load image file from local file system to CCSpriteFrame, then add into CCAnimation
		for (int i = 1; i < 15; i++)
		{
			char szImageFileName[128] = {0};
			sprintf(szImageFileName, "Images/grossini_dance_%02d.png", i);
			animation->addSpriteFrameWithFileName(szImageFileName);  
		}
		
		animation->setDelayPerUnit(2.8f / 14.0f); // This animation contains 14 frames, will continuous 2.8 seconds.
		animation->setRestoreOriginalFrame(true); // Return to the 1st frame after the 14th frame is played. 

		CCAnimate *action = CCAnimate::create(animation);
		*/

		sprite = Sprite::create("unit.png");
		sprite->setPosition(tile->position);
		//sprite->runAction(action);  // run action on sprite object

		auto height2 = 50 - height;

		sprite->setZOrder(5000);
		g->addChild(sprite);

		width = sprite->getBoundingBox().size.width;
		height = sprite->getBoundingBox().size.height;

		counter = rand() % 10 * 1.0;

}
void Unit::update(){
	counter++;

}
void Unit::setPosition(Point p){
	sprite->setPosition(p);
	position = p;

}