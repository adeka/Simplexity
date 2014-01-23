#include "Game.h"
//#include "ATile.h"
bool ATile::contains(Sprite * s){
	Point p1 = Point( sprite->getPositionX(),sprite->getPositionY());
	Point p2 = Point( s->getPositionX(),s->getPositionY()  - 110);
	return p1.getDistance(p2) < 90;
}

bool ATile::containsPoint(Point p, int offset){
	Point p1 = Point( sprite->getPositionX(),sprite->getPositionY());
	Point p2 = Point( p.x, p.y - offset);
	return p1.getDistance(p2) < 100;
}

ATile::ATile(int type,  Game * g, int col, int row, int index){
		ATile::type = type;
		ATile::g = g;
		x = col;
		y = row;
		decal = new Decal();
		switch( type ) {
		case types::GRASS:
			sprite = Sprite::create("tile.png");
			break;
		case types::SAND:
			sprite = Sprite::create("pathy.png");
			break;
		case types::BEACH:
			sprite = Sprite::create("sandbank.png");
			break;
		case types::WATER:
			sprite = Sprite::create("water.png");
			sprite->setOpacity(150);
			break;
		case types::ROCK:
			sprite = Sprite::create("rocktile.png");
			//sprite->setOpacity(150);
			break;
		case types::GRASSYROCK:
			sprite = Sprite::create("grassyrock.png");
			//sprite->setOpacity(150);
			break;
		}
		g->addChild(sprite);
		sprite->setZOrder(4096 - index);
		width = sprite->getBoundingBox().size.width;
		height = sprite->getBoundingBox().size.height;
		visible = false;
		if(index%2==0) odd = false;
		else odd = true;
		counter = (float)index;// ? index % 2 == 0 : counter = -index;//rand() % 100;
}
void ATile::update(){
	counter++;
	if(type==types::WATER){
	if(odd){
		sprite->setSkewY(sin(counter/10.0)*3.0);
		sprite->setSkewX(cos(counter/10.0)*3.0);
	}
	else{
		sprite->setSkewY(cos(counter/10.0 - 5.0)*3.0);
		sprite->setSkewX(sin(counter/10.0 - 5.0)*3.0);
	}
	//sprite->setColor
	sprite->setOpacity(150 - sin(counter/100.0)*80.0);
	//sprite->setSkewX(cos(counter/10)*3);
	}
}
void ATile::setPosition(Point p){
	sprite->setPosition(p);
	position = p;

}