#include "ofMain.h"
#include "ofApp.h"

#define DISPLAY_MODE OF_WINDOW // Can be OF_WINDOW or OF_FULLSCREEN

//========================================================================
int main( ){
	ofSetupOpenGL(1024, 768, DISPLAY_MODE); // setup the GL context
	//ofSetFrameRate(12); 

	// runs apps
	ofRunApp(new BrickBreakerGame());

}
