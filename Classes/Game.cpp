#include "Game.h"
#include "simplextextures.h"
#include "simplexnoise.h"
USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = Game::create();
    // add layer as a child to scene
    scene->addChild(layer);

	//scene->setZOrder(-9999);
	//layer->setZOrder(-9999);
    // return the scene
    return scene;
}

void Game::draw(){

	//cocos2d::ccDrawColor4F(1.0f, 1.0f, 1.0f, .5f);
	
	/*
	Point p1 = Point(player->sprite->getPositionX() - 130,player->sprite->getPositionY() + 70);
	Point p2 = Point(hook->sprite->getPositionX()+15,hook->sprite->getPositionY() + 25);


	Point pp = Point(p1.getMidpoint(p2).x + p1.getMidpoint(p2).getDistance(player->sprite->getPosition())/2, p1.getMidpoint(p2).y + p1.getMidpoint(p2).getDistance(player->sprite->getPosition())/2);
	Point pp2 = Point(p1.getMidpoint(p2).x - p1.getMidpoint(p2).getDistance(player->sprite->getPosition())/2, p1.getMidpoint(p2).y - p1.getMidpoint(p2).getDistance(player->sprite->getPosition())/2);
	
	Point rp = Point(sin(counter/15)*20,sin(counter/15)*20);

	cocos2d::DrawPrimitives::drawCubicBezier(p1, pp, pp2, p2, 10);
	*/
	
	cocos2d::ccDrawSolidRect(Point(-100,-200), Point(9000,9000), Color4F(0.0,144.0/255.0,255.0/255.0,.4));
	//cocos2d::DrawPrimitives::drawCubicBezier(p1, pp- Point(sin(counter)*10,4), pp2- Point(4,4), p2, 10);
	//cocos2d::DrawPrimitives::drawCubicBezier(p1, pp+ Point(4,4), pp2+ Point(4,4), p2, 10); 
	//cocos2d::ccDrawLine(Point(player->sprite->getPositionX() - 125,player->sprite->getPositionY() + 80), Point(hook->sprite->getPositionX(),hook->sprite->getPositionY() + 70));
}

bool Game::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
	ready = false; 
	
	auto seed = rand();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	this->setTouchEnabled(true); 
	//this->setIsTouchEnabled(true);

    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

	int row = 0;
	int col = 0;
	int offset = 0;
	for(int i = 0; i < 2025; i++){
		//float terrain = marble_noise_2d(2,.8,.01, col, row)*90;
		float terrain = scaled_octave_noise_2d( 3, .1, .05, -90 , 90, col+seed,row+seed);
		ATile * tile;
		if(terrain > 50){
			tile = new ATile(ATile::types::ROCK, this, col, row, i);
		}
		else if(terrain > 30){
			tile = new ATile(ATile::types::SAND, this, col, row, i);
		}
		else if(terrain > 2){
			tile = new ATile(ATile::types::GRASS, this, col, row, i);
		}
		else if(terrain > -8){
			tile = new ATile(ATile::types::GRASSYROCK, this, col, row, i);
		}
		else if(terrain >-20 && terrain < -10){
			tile = new ATile(ATile::types::BEACH, this, col, row, i);
		}
		else{
			//tile = new ATile(ATile::types::GRASS, this, col, row, i);
			tile = new ATile(ATile::types::WATER, this, col, row, i);
		}
		
		//ATile * tile = new ATile(1, this, col, row, i);
		tileList.push_back(tile);

		if( i % 23 == 0 ){
			auto off = tile->width/2;//(sqrt(3.0)/2.0)*sprite->getBoundingBox().size.height/2.0;
			
			if(offset == off){
			offset = 0;
			}
			else offset = off;
			row++;
			col = 0;
			
		}
		
		col++;
		//sprite->setZOrder(
		auto colorOffset = rand() % 1;
		Color3B c = Color3B(255 - colorOffset,255 - colorOffset,255 - colorOffset);
		//sprite->setColor(c);
		/*
		if(tileList.size() > 0){
			sprite->setZOrder(tileList[tileList.size() - 1]->getZOrder() + 1);
		}
		*/
		
		//CCLOG(to_string(sprite->getZOrder()).c_str());
		//sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		float height = scaled_octave_noise_2d( 2, .8, .1, -90 , 120, col,row);
		float treenoise = scaled_octave_noise_2d(2, .5, .11, -20 , 20,col,row);
		//float treenoise = 0;//marble_noise_2d(2,.8,.1, col, row)*20;
		if(tile->type == ATile::types::WATER){
			tile->setPosition(Point((col*tile->width)+ offset,(row*tile->height/4 - 30)));
		}
		else if(tile->type == ATile::types::BEACH){
			tile->setPosition(Point((col*tile->width)+ offset,(row*tile->height/6) + height - 20));
			tile->sprite->setScale(1.2);
		}
		else{
			tile->setPosition(Point((col*tile->width)+ offset,(row*tile->height/6) + height));
		}
		Decal * decal = new Decal();
		if(terrain > 70){
			decal = new Decal(Decal::types::TALLROCK, this, i, treenoise, tile);
		}
		else if(terrain > 62){
			decal = new Decal(Decal::types::ROCK, this, i, treenoise, tile);
		}
		else{
			//CCLOG(to_string(height).c_str());
			auto height2 = 50 - height;
			if(height2 > 0) tile->sprite->setColor(Color3B(c.r - height2,c.g - height2,c.b - height2));
			if(treenoise > 3 && tile->type != ATile::types::WATER){
			//Decal * decal;
			if(treenoise > 12){
				decal = new Decal(Decal::types::POPPY, this, i, treenoise, tile);
			}
			else if(treenoise > 9){
				decal = new Decal(Decal::types::PINE, this, i, treenoise, tile);
			}
			else if(tile->type == ATile::types::BEACH){
				if(treenoise > 5){
					decal = new Decal(Decal::types::PALM, this, i, treenoise, tile);
				}
			}
			else if(treenoise > 8){
					decal = new Decal(Decal::types::TREE1, this, i, treenoise, tile);
			}
			else if(treenoise > 7){
				decal = new Decal(Decal::types::TREE2, this, i, treenoise, tile);
			}
			else if(treenoise > 6){
				decal = new Decal(Decal::types::TREE3, this, i, treenoise, tile);
			}
			else if(treenoise > 2){
				decal = new Decal(Decal::types::GRASS, this, i, treenoise, tile);
			}
		}
		//decal = new Decal(1, this, i, treenoise, tile);
		if(decal->type != Decal::types::DEFAULT){
			decalList.push_back(decal);
		}
		}
	}
	//this->setScale(.6f);
	this->scheduleUpdate();
	this->setScale(.8);
	// this->addTouchListener(); 
	//this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	ready = true;
    return true;
}

void Game::update(float dt){

	//this->setColor(Color3B(255,1,255));
	for(int i = 0; i < decalList.size(); i++){
		decalList[i]->update();
	}
	for(int i = 0; i < tileList.size(); i++){
		tileList[i]->update();
	}
	//CCLOG("YEA");
	POINT p; 
	GetCursorPos(&p);
	Point cp = Point(p.x - this->getPositionX(), Director::getInstance()->getVisibleSize().height - p.y - this->getPositionY() + tileList[0]->sprite->getBoundingBox().size.height/2);
	
	if((GetKeyState(WM_MOUSEWHEEL) & 0x100) != 0){
		//CCLOG("EAAA");
		
	}
	if((GetKeyState(VK_LBUTTON) & 0x100) != 0){
		this->setScale(this->getScale()-.001);
		//CCLOG("DOWN");
		/*
		for(int i = 0; i < tileList.size(); i++){
			if(tileList[i]->sprite->getBoundingBox().containsPoint(cp)){
				//tileList[i]->setColor(ccc3(255,0,0));
				//Sprite* water = Sprite::create("water.png");
				//this->addChild(water);
				//water->setPosition(tileList[i]->getPosition());
				//tileList[i]->removeFromParentAndCleanup(true);
				//tileList[i] = water;
				tileList[i]->sprite->setPositionY(tileList[i]->sprite->getPositionY() - 1);
				Color3B c = tileList[i]->sprite->getColor();
				tileList[i]->sprite->setColor(Color3B(c.r - 1,c.g - 1,c.b - 1));
				//removals.push_back(tileList[i]);
				//tileList[i]->removeFromParentAndCleanup(true);
				//tileList.erase(tileList.begin()+i);
				break;
			}
		}
		*/
	}
	//auto s = Sprite::create("hex.png");
	//this->addChild(s);
	//s->setPosition(Point(p.x, Director::getInstance()->getVisibleSize().height - p.y));

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	if(p.x < origin.x + 100){
		this->setPositionX(this->getPositionX() + 10);
	}
	if(p.x > origin.x + visibleSize.width - 100){
		this->setPositionX(this->getPositionX() - 10);
	}
	if(p.y < origin.y + 100){
		this->setPositionY(this->getPositionY() - 10);
	}
	if(p.y > origin.y + visibleSize.height - 100){
		this->setPositionY(this->getPositionY() + 10);
	}
	/*
	if(ready){
		for(int i = 0; i < tileList.size(); i++){
		
			if(!tileList[i]->visible){
				if(tileList[i]->position.x > 0 && tileList[i]->position.x < 2000){
					tileList[i]->visible = true;
					this->addChild(tileList[i]->sprite);
					
				}
			}
		
		}
	}
	*/
	//if (ScreenToClient(hwnd, &p))
	//{
		//p.x and p.y are now relative to hwnd's client area
	//}
	//this->updateDisplayedColor(Color3B(1,1,1));
}


void Game::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
