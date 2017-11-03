#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

enum AnimationType {
	stand, duck, walking, jumping, throwing, climbing, crouchThrowing
};

enum Weapon {
	empty, axe, spear, knife, fire, shield
};

enum Direction {
	left, right, down, up
};

enum MobType {
	arthur, arthurNaked, powerup, zombie
};
class Animation
{
public:
	Animation(MobType m);
	Animation();
	~Animation();

	void setFrame(int newFrame);
	void nextFrame();
	int getFrameIndex();
	void setAnimationType(AnimationType t);
	AnimationType getAnimationType();
	IntRect getCurrentFrame();
	vector<IntRect> frames;


	bool hasStanding = true;
	bool hasWalking = false;
	bool hasJumping = false;
	bool hasDucking = false;
	bool hasThrowing = false;
private:
	int currentFrame = 0;
	MobType mType;
	AnimationType aType;
};

