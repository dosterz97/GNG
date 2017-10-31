#include "stdafx.h"
#include "Quadtree.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

Quadtree::Quadtree() {
}

Quadtree::Quadtree(int pLevel, FloatRect pBounds) {
	level = pLevel;
	bounds = pBounds;
	for (int i = 0; i < 4; i++) {
		nodes[i] = new Quadtree();
	}
}

Quadtree::~Quadtree() {
}

//clears the quadtree and its subnodes
void Quadtree::clear() {
	objects.clear();
	objects.shrink_to_fit();
	for (int i = 0; i < 4; i++) {
		if (nodes[i] != NULL) {
			nodes[i]->clear();
			nodes[i] = NULL;
		}
	}
}

//splits into 4 more nodes
void Quadtree::split() {
	int subWidth = (int)(bounds.width / 2);
	int subHeight = (int)(bounds.height / 2);
	int x = (int)bounds.left;
	int y = (int)bounds.top;

	nodes[0] = new Quadtree(level + 1, FloatRect(x + subWidth, y, subWidth, subHeight));
	nodes[1] = new Quadtree(level + 1, FloatRect(x, y, subWidth, subHeight));
	nodes[2] = new Quadtree(level + 1, FloatRect(x, y + subHeight, subWidth, subHeight));
	nodes[3] = new Quadtree(level + 1, FloatRect(x + subWidth, y + subHeight, subWidth, subHeight));
}


/*
* Determine which node the object belongs to. -1 means
* object cannot completely fit within a child node and is part
* of the parent node
*/
int Quadtree::getIndex(Sprite* sprite) {
	int index = -1;
	FloatRect pRect = sprite->getGlobalBounds();
	double verticalMidpoint = bounds.left + (bounds.width / 2);
	double horizontalMidpoint = bounds.top + (bounds.height / 2);

	// Object can completely fit within the top quadrants
	bool topQuadrant = (pRect.top < horizontalMidpoint && pRect.top + pRect.height <= horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (pRect.top > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (pRect.left < verticalMidpoint && pRect.left + pRect.width <= verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (pRect.left > verticalMidpoint) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant) {
			index = 3;
		}
	}

	return index;
}

void Quadtree::insert(Sprite* sprite)
{
	if (nodes[0] != NULL) {
		int index = getIndex(sprite);

		if (index != -1) {
			nodes[index]->level = level + 1;
			nodes[index]->insert(sprite);
			return;
		}
	}
	objects.push_back(sprite);

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
		if (nodes[0] == NULL) {
			split();
		}

		int i = 0;
		while (i < objects.size()) {
			int index = getIndex(objects.at(i));
			if (index != -1) {
				nodes[index]->level = level + 1;
				nodes[index]->insert(objects.at(i));
				objects.erase(objects.begin() + i);
				objects.shrink_to_fit();
			}
			else {
				i++;
			}
		}
	}
}

void Quadtree::printQuadtree() {
	for (int i = 0; i < level; i++)
		cout << "  ";
	cout << objects.size() << " number of items on level " << level << endl;

	for (int k = 0; k < objects.size(); k++) {
		for (int i = 0; i < level; i++)
			cout << "  ";
		cout << "x,y " << objects.at(k)->getGlobalBounds().left << "," << objects.at(k)->getGlobalBounds().top << endl;
	}

	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < level; i++)
			cout << "  ";
		if (nodes[k] == NULL) {
			cout << k << " node is NULL" << endl;
		}
		else {
			cout << k << " node isn't NULL" << endl;
			nodes[k]->printQuadtree();
		}
	}
}

vector<Sprite*>* Quadtree::retrieve(vector<Sprite*>* returnObjects, Sprite* sprite)
{
	int index = getIndex(sprite);

	//player is in one of the midpoint lines
	//return null and check with the entire array
	if (index == -1 && level == 0) {
		return NULL;
	}

	if (index != -1 && nodes[0] != NULL) {
		nodes[index]->retrieve(returnObjects, sprite);
	}
	else if(index == -1 && nodes[0] != NULL) {
		for (int k = 0; k < 4; k++) {
			for (int i = 0; i < nodes[k]->objects.size(); i++)
				returnObjects->push_back(nodes[k]->objects.at(i));
		}
	}

	for(int i = 0; i < objects.size(); i++) 
		returnObjects->push_back(objects.at(i));

	return returnObjects;
}