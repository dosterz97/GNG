#include "stdafx.h"
#include "Animation.h"


Animation::Animation(MobType m) {
	mType = m;

	switch (mType) {
	case arthur:
		hasThrowing = true;
		hasDucking = true;
		hasWalking = true;
		hasJumping = true;

		//stand
		frames.push_back(IntRect(134, 600, 20, 30));

		//walking
		frames.push_back(IntRect(5, 601, 20, 30));
		frames.push_back(IntRect(39, 599, 20, 30));
		frames.push_back(IntRect(72, 600, 20, 30));
		frames.push_back(IntRect(102, 600, 20, 30));

		//throw
		frames.push_back(IntRect(5, 633, 20, 30));
		frames.push_back(IntRect(38, 638, 20, 25));

		//crouch
		frames.push_back(IntRect(230, 609, 20, 21));

		//crouch throw
		frames.push_back(IntRect(70, 640, 20, 22));
		frames.push_back(IntRect(106, 642, 20, 25));

		//jump
		frames.push_back(IntRect(38, 638, 20, 25));
		frames.push_back(IntRect(38, 638, 20, 25));

		break;
	default:
		break;
	}
}

Animation::Animation() {
}

Animation::~Animation() {
}

void Animation::setFrame(int newFrame) {
	currentFrame = newFrame;
	if (currentFrame >= frames.size())
		currentFrame = 0;
}

void Animation::nextFrame() {
	currentFrame++;
	if (currentFrame >= frames.size())
		currentFrame = 0;
}

int Animation::getFrameIndex() {
	return currentFrame;
}

void Animation::setAnimationType(AnimationType t) {
	aType = t;
}

AnimationType Animation::getAnimationType() {
	return aType;
}

IntRect Animation::getCurrentFrame() {
	return frames.at(currentFrame);
}
