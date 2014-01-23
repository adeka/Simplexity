

#include "cocos2d.h"
#include <vector>
USING_NS_CC;
using namespace std;

class ATile {
	
public:
	int counter;
	enum types {GRASS, SAND, WATER, BEACH, ROCK, GRASSYROCK};
	int type;
	int width, height;
	int x;
	int y;
	bool visible;
	bool odd;

	class Decal * decal;
	Point position;
	bool contains(Sprite * s);
	bool containsPoint(Point p, int offset);
	class Game * g;

	ATile(int type, Game * g, int col, int row, int index);
	ATile();
	void setPosition(Point p);
	cocos2d::Sprite * sprite;
	void update();
};


