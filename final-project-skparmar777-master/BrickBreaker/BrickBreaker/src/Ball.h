#pragma once
#include "ofMain.h"

class Ball
{
public:
	Ball();
	double getX();
	double getY();
	double getRadius();
	ofVec2f getDirection();
	ofRectangle getRect();
	void setX(int new_x);
	void setY(int new_y);
	void setDirection(int x, int y);
private:
	//coordinates of ball in space
	double x;
	double y;
	double radius;
	ofVec2f direction;
	ofRectangle rect;

	
};


