#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;
class Quadtree
{
public:
	Quadtree();
	Quadtree(int pLevel, FloatRect pBounds);
	~Quadtree();

	void clear();
	void split();
	int getIndex(Sprite* sprite);
	void insert(Sprite* sprite);
	vector<Sprite*>* retrieve(vector<Sprite*>* returnObjects, Sprite* sprite);

private:
	const int MAX_OBJECTS = 30;
	const int MAX_LEVELS = 5;

	int level;
	vector<Sprite*> objects;
	FloatRect bounds;
	Quadtree* nodes[4];
};

