#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>

#include "ofMain.h"
#include "Ball.h"
#include "Paddle.h"

	// Enum to represent the current state of the game
	enum GameState {
		IN_PROGRESS = 0,
		PAUSED,
		FINISHED,
		OPENING
	};

	class BrickBreakerGame : public ofBaseApp {
	private:
		GameState current_state_ = OPENING;		// The current state of the game, used to determine possible actions
		Ball game_ball;							// The object that represents the ball
		Paddle game_paddle;						// The object that represents moveable paddle for keeping the ball from falling
		vector<ofRectangle> bricks_to_break;	// The object that represents the bricks on the screen
		bool should_update_ = true;				// A flag boolean used in the update() function.
		int score = 0;							// The score accumulated from breaking bricks
		int lives;								// lives remaining
		ofSoundPlayer paddle_collision;			// Soundplayer to make collision for paddle
		ofSoundPlayer brick_collision;			// Soundplayer to make collision for brick
		ofSoundPlayer lose_game;				// Soundplayer for losing effect
		bool should_play;

		/** Constants */
		const int MAX_LIVES = 2;									// Max amount of lives
		const int MAX_COLS = 11;									// Brick columns
		const int MAX_ROWS = 5;										// Brick rows
		const int MAX_RGB = 255;									// Max RGB value
		const int SCORE_INCREMENT = 5;								// Amount to increment score when brick is broken
		const int ADJUSTMENT = 15;									// Adjustment amount for situating objects
		const double MULTIPLIER_MIN = 0.5;							// Minimum speed multiplier
		const double MULTIPLIER_MAX = 0.5;							// Max speed multiplier
		const int MESSAGE_X = ofGetWindowWidth() * .6;				// X location for message placement
		const int MESSAGE_Y = ofGetWindowHeight() / 2;				// Y location for message placement
		const ofVec3f BLUE = ofVec3f(0, 51, 102);					// Ball color
		const ofVec3f MAROON = ofVec3f(102, 0, 51);					// Paddle color
		const int SCORE_CAPACITY = 10;								// Number of high scores stored


		// Private helper methods for rendering objects and assisting gameplay
		void addScore(int curr_score);
		void populateBricks();
		void continueGame();
		bool hitRectangle(ofRectangle brick);
		void updateLives();
		void handleBrickCollisions();
		void handlePaddleCollisions();
		void updateBallPosition();
		void drawBall();
		void drawPaddle();
		void drawBricks();
		void drawGameOpening();
		void drawGameOver();
		void drawGamePaused();
		void drawTopTenScores();
		void drawKeyboardOptions();

		// Resets the game objects to their original state.
		void reset();

	public:
		// Function used for one time setup
		void setup();

		// Checks game over
		void checkGameOver();

		// Main event loop functions called on every frame
		void update();
		void draw();

		// Event driven functions, called on appropriate user action
		void keyPressed(int key);

		//Function used for paddle movements where the paddle follows the mouse
		void mouseMoved(int x, int y);

		//default constructor
		BrickBreakerGame();

		//helper method for generating random doubles
		double generateRandomDouble(double min, double max);

	};