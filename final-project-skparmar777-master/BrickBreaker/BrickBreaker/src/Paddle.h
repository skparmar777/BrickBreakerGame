#pragma once
#include "ofMain.h"
class Paddle
{
public:

	Paddle();
	ofRectangle getPaddle();
	ofVec2f getPosition();
	void setNewPosition(int x_pos);
	int getHeight();
private:
	ofRectangle paddle;
	ofVec2f newPosition;
	ofVec2f oldPosition;
	ofVec2f direction;
	int height = ofGetWindowHeight() * .1;
	int width = ofGetWindowWidth() /3;
};

