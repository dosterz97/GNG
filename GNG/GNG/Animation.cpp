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

		frames.push_back(IntRect(134, 600, 20, 30));
		frames.push_back(IntRect(5, 601, 20, 30));
		frames.push_back(IntRect(39, 599, 20, 30));
		frames.push_back(IntRect(72, 600, 20, 30));
		frames.push_back(IntRect(102, 600, 20, 30));
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

void Animation::setAnimationType(AnimationType t) {
	if (t != aType) {
		aType = t;
	}
}

AnimationType Animation::getAnimationType() {
	return aType;
}

IntRect Animation::getCurrentFrame() {
	return frames.at(currentFrame);
}
