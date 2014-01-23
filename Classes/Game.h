#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "Decal.h"
#include "ATile.h"
#include "Unit.h"
using namespace std;
class Game : public cocos2d::Layer
{
public:
	bool ready;
	float counter;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	vector<ATile *> tileList;
	vector<Decal *> decalList;

	Unit * player;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void draw();
    // a selector callback
    void menuCloseCallback(Object* pSender);
	virtual void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};

#endif // __HELLOWORLD_SCENE_H__
