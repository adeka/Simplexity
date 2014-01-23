

#include "cocos2d.h"
#include <vector>
USING_NS_CC;
using namespace std;

class Unit {
	
public:
	int counter;

	int width, height;

	int x;
	int y;

	Point position;

	class ATile * tile;
	class Game * g;

	Unit(Game * g, int index, ATile * tile);
	Unit();
	void setPosition(Point p);
	cocos2d::Sprite * sprite;
	void update();
};


