#include "Ball.h"

//constructor
Ball::Ball()
{
	radius = ofGetWindowHeight() * .05;
	x = (ofGetWindowWidth() / 2) - (radius / 2);
	y = (ofGetWindowHeight() * .9) - radius - 10;
	srand(time(0));
	int dir_x = -3;
	int dir_y = -3;
	direction.set(dir_x, dir_y);
	rect = ofRectangle(x, y, radius, radius);

}

//getters
double Ball::getX() {
	return x;
}
double Ball::getY() {
	return y;
}
double Ball::getRadius() {
	return radius;
}
ofVec2f Ball::getDirection(){
	return direction;
}
ofRectangle Ball::getRect() {
	return rect;
}

//setters
void Ball::setX(int new_x) {
	x = new_x;
}
void Ball::setY(int new_y) {
	y = new_y;
}
void Ball::setDirection(int x, int y) {
	direction.set(x, y);
}
