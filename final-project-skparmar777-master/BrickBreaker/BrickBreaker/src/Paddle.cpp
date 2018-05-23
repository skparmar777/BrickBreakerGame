#include "Paddle.h"



Paddle::Paddle()
{

	paddle = ofRectangle(oldPosition.x, oldPosition.y, width, height);
	oldPosition.set(ofGetWindowWidth() / 2 - .5*width, (int)ofGetWindowHeight()*.9);
	newPosition = oldPosition;
	direction.set(0, 0);
	
}

ofVec2f Paddle::getPosition() {
	return newPosition;
}
ofRectangle Paddle::getPaddle() {
	return this->paddle;
}
void Paddle::setNewPosition(int x_pos) {
	oldPosition = newPosition;
	//moves only left and right instead of up and down
	newPosition.set(x_pos, newPosition.y);
	direction = newPosition - oldPosition;
	paddle = ofRectangle((int)newPosition.x, (int)newPosition.y, width, height);
}

int Paddle::getHeight() {
	return height;
}
