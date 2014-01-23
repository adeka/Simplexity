#include "Game.h"
Decal::Decal(){
	type = types::DEFAULT;
}
Decal::Decal(int type,  Game * g, int index, float height, ATile * tile){
		Decal::type = type;
		Decal::g = g;
		Decal::tile = tile;
		auto colorOffset = rand() % 1;
		Color3B c = Color3B(255 - colorOffset,255 - colorOffset,255 - colorOffset);

		switch( type ) {
		case types::DEFAULT:
			//sprite = Sprite::create("water.png");
			break;
		case types::PINE:
			sprite = Sprite::create("pine.png");
			sprite->setScale(.7 + (rand()%30)/100.0);
			sprite->setAnchorPoint(Point(.5,.2));
			//sprite->setAnchorPoint(Point(sprite->getPositionX(), sprite->getPositionY() - sprite->getBoundingBox().size.height/2));
			break;
		case types::WHEAT:
			sprite = Sprite::create("wheat.png");
			sprite->setAnchorPoint(Point(.5,0));
			break;
		case types::DEBRIS:
			sprite = Sprite::create("debris.png");
			break;
		case types::TREE1:
			sprite = Sprite::create("tree.png");
			break;
		case types::TREE2:
			sprite = Sprite::create("tree2.png");
			break;
		case types::TREE3:
			sprite = Sprite::create("tree3.png");
			break;
		case types::GRASS:
			sprite = Sprite::create("grass.png");
			break;
		case types::GOLD:
			sprite = Sprite::create("gold.png");
			break;
		case types::ROCK:
			sprite = Sprite::create("rock.png");
			sprite->setScale(1.0 - (rand()%30)/100.0);
			break;
		case types::TALLROCK:
			sprite = Sprite::create("tallrock.png");
			//sprite->setScale(1.0 - (rand()%30)/100.0);
			break;
		case types::POPPY:
			sprite = Sprite::create("poppy.png");
			//sprite->setScale(1.0 - (rand()%30)/100.0);
			sprite->setAnchorPoint(Point(.5,0));
			break;
		case types::PALM:
			sprite = Sprite::create("palm.png");
			//sprite->setScale(1.0 - (rand()%30)/100.0);
			sprite->setAnchorPoint(Point(.5,.2));
			break;
		}

		auto height2 = 50 - height;
		//if(height2 > 0) sprite->setColor(Color3B(c.r - height2,c.g - height2,c.b - height2));
		if(type == types::PINE || type == types::PALM){
			//sprite->setAnchorPoint(Point(sprite->getPositionX(), sprite->getPositionY() - sprite->getBoundingBox().size.height/2));
			sprite->setPosition(Point(tile->sprite->getPositionX(),tile->sprite->getPositionY()));
		}
		else if(type == types::WHEAT || type == types::POPPY){
			sprite->setPosition(Point(tile->sprite->getPositionX(),tile->sprite->getPositionY() - 60));
		}
		else{
			sprite->setPosition(Point(tile->sprite->getPositionX(),tile->sprite->getPositionY() + 100));
		}
		sprite->setZOrder(4097 - index);
		g->addChild(sprite);
		width = sprite->getBoundingBox().size.width;
		height = sprite->getBoundingBox().size.height;
		visible = false;
		counter = rand() % 10 * 1.0;
		windmag = 0.0;
		freq = 25.0;
}
void Decal::update(){
	counter++;
	if(type == types::GRASS || type == types::TREE1	|| type == types::TREE2 || type == types::TREE3){
	sprite->setSkewY(sin(counter/freq)*(10.0/windmag));
	}
	else if(type == types::PINE || type == types::WHEAT || type == types::POPPY || type == types::PALM){
	sprite->setSkewX(sin(counter/freq)*(10.0/windmag));
	}
}
void Decal::setPosition(Point p){
	sprite->setPosition(p);
	position = p;

}