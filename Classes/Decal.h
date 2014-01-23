

#include "cocos2d.h"
#include <vector>
USING_NS_CC;
using namespace std;

class Decal {
	
public:
	int counter;
	int type;
	int width, height;
	int x;
	int y;
	bool visible;
	float windmag;
	float freq;
	Point position;

	class ATile * tile;
	enum types {DEFAULT, PALM, DEBRIS, PINE, TREE1, TREE2, TREE3, GRASS, GOLD, ROCK, TALLROCK, WHEAT, POPPY};
	class Game * g;

	Decal(int type, Game * g, int index, float height, ATile * tile);
	Decal();
	void setPosition(Point p);
	cocos2d::Sprite * sprite;
	void update();
};


