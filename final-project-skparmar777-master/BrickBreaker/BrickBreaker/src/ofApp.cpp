#include "ofApp.h"

// Vector of scores
static std::vector<int> scores;

// Vector of top ten scores
static std::vector<int> top_ten_scores;

// Map of Visited Scores
static std::map<int, bool> visited;

// Array of keyboard options
// Defined in ofApp.cpp because putting it in ofApp.h throws an error
const string KEYBOARD_OPTIONS[] = { "Press 'P' to Pause",	
									"Press 'H' to list high scores",
									"Press 'S' to stop and restart the game during gameplay",
									"Press 'R' to reset the game after game is over" };

/** Setup functions */

// Default constructor bc VS was throwing errors if I didn't include it
BrickBreakerGame::BrickBreakerGame() {
}

// Function used for one time setup
// Populates brick vector, creates ball and paddle
void BrickBreakerGame::setup() {
	ofSetBackgroundColor(MAX_RGB, MAX_RGB, MAX_RGB);
	lives = MAX_LIVES;
	ofSetWindowTitle("Brick Breaker: " + std::to_string(lives + 1) + " lives, Score: " + std::to_string(score));
	populateBricks();

	// Load sounds
	paddle_collision.load("Metal_Ri-Diode111-8869_hifi.mp3");
	brick_collision.load("Pop_2-Texavery-8930_hifi.mp3");
	lose_game.load("womp-womp.mp3");

	should_play = true;
}

// Populates brick vector
void BrickBreakerGame::populateBricks() {
	for (int num_brick_cols = 0, x = ADJUSTMENT; num_brick_cols < MAX_COLS; num_brick_cols++) {
		for (int num_brick_rows = 0, y = 0; num_brick_rows < MAX_ROWS; num_brick_rows++) {
			bricks_to_break.push_back(ofRectangle(x, y, game_ball.getRadius() * 2, game_ball.getRadius()));
			y += game_ball.getRadius() + ADJUSTMENT;
		}
		x += game_paddle.getHeight() + ADJUSTMENT;
	}
}

/**draw functions*/

// Draws a dark blue ball
void BrickBreakerGame::drawBall() {
	ofSetColor(BLUE.x, BLUE.y, BLUE.z);
	ofDrawRectRounded(ofRectangle(game_ball.getX(), game_ball.getY(), game_ball.getRadius(), game_ball.getRadius()), game_ball.getRadius());
}

// Draws paddle
void BrickBreakerGame::drawPaddle() {
	ofSetColor(MAROON.x, MAROON.y, MAROON.z);
	ofDrawRectangle(game_paddle.getPaddle());
}

// Goes through vector of bricks, draws each one
void BrickBreakerGame::drawBricks() {
	for (ofRectangle brick : bricks_to_break) {
		ofSetColor(0, 0, 0);
		ofDrawRectangle(brick);
	}
}

// Prints game over
void BrickBreakerGame::drawGameOver() {
	string gameover_message = "Game Over! Your final score is: " + std::to_string(score);
	string lives_message = "You had " + std::to_string(lives) + " lives remaining.";

	ofDrawBitmapString(gameover_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	ofDrawBitmapString(lives_message, ofGetWindowWidth() / 2, (ofGetWindowHeight() / 2) + ADJUSTMENT);

	addScore(score);
	drawTopTenScores();
}

// Draws paused state
void BrickBreakerGame::drawGamePaused() {
	string pause_message = "P to Unpause!";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(pause_message, MESSAGE_X, MESSAGE_Y);
	drawKeyboardOptions();
}

// Draws opening state
void BrickBreakerGame::drawGameOpening() {
	string opening_message = "Welcome to the Brick Breaker Game!";
	string play_message = "Press 'X' to play!";

	ofSetColor(0, 0, 0);
	ofDrawBitmapString(opening_message, MESSAGE_X ,MESSAGE_Y );
	ofDrawBitmapString(play_message, MESSAGE_X, MESSAGE_Y + ADJUSTMENT);
	
	drawKeyboardOptions();
}

// Draws top ten scores
void BrickBreakerGame::drawTopTenScores() {
	string scores_message = "The top ten scores are: ";
	scores_message += '\n';
	for (auto score : top_ten_scores) {
		scores_message += std::to_string(score) + '\n' + " ";
	}
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(scores_message, MESSAGE_X, MESSAGE_Y + 2 * ADJUSTMENT);
}

// Draws keyboard options
void BrickBreakerGame::drawKeyboardOptions() {
	const int OPTIONS_X = ofGetWindowWidth() / 11;
	int OPTIONS_Y = ofGetWindowHeight() / 2;

	for (string option : KEYBOARD_OPTIONS) {
		ofDrawBitmapString(option, OPTIONS_X, OPTIONS_Y);
		OPTIONS_Y += ADJUSTMENT;
	}
}

/** Game state driven functions */

// Resets the game objects to their original state.
void BrickBreakerGame::reset() {
	if (current_state_ == FINISHED) {
		bricks_to_break.clear();	
		populateBricks();
		lives = MAX_LIVES;
		should_play = true;
		score = 0;
	}
	game_ball = Ball();
	game_paddle = Paddle();
	current_state_ = IN_PROGRESS;	
}

void BrickBreakerGame::continueGame() {
	string continue_message = "You have " + std::to_string(lives) + " lives left.";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(continue_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	Sleep(500);
	reset();
}

/** Helper functions */

// Generates random doubles
double BrickBreakerGame::generateRandomDouble(double min, double max){
	double num = (double)rand() / RAND_MAX;
	return min + num * (max - min);
}

// Removes bricks if the ball hits them
bool BrickBreakerGame::hitRectangle(ofRectangle rect) {
	float rect_right = rect.getRight();
	float rect_left = rect.getLeft();
	float rect_top = rect.getTop();
	float rect_bottom = rect.getBottom();

	float ball_x = (float)game_ball.getX();
	float ball_y = (float)game_ball.getY();

	if (ball_x >= rect_left && ball_x <= rect_right
		&& ball_y >= rect_top && ball_y <= rect_bottom) {
		return true;
	}
	return false;
}

// Sets current state to finished if game is over
// Continues game if there are still lives left
void BrickBreakerGame::checkGameOver() {
	if (bricks_to_break.empty() ||
		(game_ball.getY() > game_paddle.getPosition().y + game_ball.getRadius() && lives == 0)) {
		current_state_ = FINISHED;

		// Play effect if lost
		if (!bricks_to_break.empty()) {
			lose_game.play();

			// Make sure effect only plays once
			should_play = false;
		}

		// If player still has lives and bricks to break, continue the game
	} else if (lives > 0 && !bricks_to_break.empty() 
		&& game_ball.getY() > game_paddle.getPosition().y + game_ball.getRadius()) {
		lives--;
		continueGame();
	}
}

// Updates number of lives in window title
void BrickBreakerGame::updateLives() {
	if (lives == 0) {
		ofSetWindowTitle("Brick Breaker: Last Life! Score: " + std::to_string(score));
	}
	else {
		ofSetWindowTitle("Brick Breaker: " + std::to_string(lives + 1) + " lives, Score: " + std::to_string(score));
	}
}

// Goes through brick vector, checks to see if ball intersects any brick, if so: removes brick
void BrickBreakerGame::handleBrickCollisions() {
	srand(time(0));

	for (size_t i = 0; i < bricks_to_break.size(); i++) {
		if (hitRectangle(bricks_to_break[i])) {
			// Play sound
			brick_collision.play();

			// Increment score
			score += SCORE_INCREMENT;

			// Reverse ball's direction
			double new_x = game_ball.getDirection().x;
			double new_y = game_ball.getDirection().y*-1 * generateRandomDouble(MULTIPLIER_MIN, MULTIPLIER_MAX);

			// Make sure ball isn't stuck in same direction
			if (new_x == 0) {
				new_x++;
			}
			if (new_y == 0) {
				new_y++;
			}
			game_ball.setDirection(new_x, new_y);

			// Erases hit brick
			bricks_to_break.erase(bricks_to_break.begin() + (int)i);
		}
	}
}

// Checks to see if there was a collision with the paddle and bounces ball off paddle
void BrickBreakerGame::handlePaddleCollisions() {
	srand(time(0));
	if (hitRectangle(game_paddle.getPaddle())) {
		// Play sound
		paddle_collision.play();

		// Reverse ball's direction
		game_ball.setDirection(game_ball.getDirection().x, game_ball.getDirection().y*-1);
	}
}

// Updates ball position and makes sure the ball isn't stuck
void BrickBreakerGame::updateBallPosition() {
	game_ball.setX(game_ball.getX() + game_ball.getDirection().x);
	game_ball.setY(game_ball.getY() + game_ball.getDirection().y);

	if (game_ball.getX() < 0 || game_ball.getX() > ofGetWidth()) {
		game_ball.setDirection(game_ball.getDirection().x * -1, game_ball.getDirection().y);
	}
	if (game_ball.getY() < 0) {
		game_ball.setDirection(game_ball.getDirection().x, game_ball.getDirection().y * -1);
	}

	// Make sure ball doesn't stagnate
	if (game_ball.getDirection().x == 0) {
		game_ball.setDirection(game_ball.getDirection().x + 1, game_ball.getDirection().y);
	}
	if (game_ball.getDirection().y == 0) {
		game_ball.setDirection(game_ball.getDirection().x, game_ball.getDirection().y + 1);
	}
}

// Function used for paddle movements where the paddle follows the mouse
void BrickBreakerGame::mouseMoved(int x, int y) {
	game_paddle.setNewPosition(x);
}

// Adds score to vector
void BrickBreakerGame::addScore(int curr_score) {
	if (!visited[curr_score]) {
		scores.push_back(curr_score);
		visited[curr_score] = true;
	}
	
	std::sort(scores.begin(), scores.end());
	top_ten_scores.clear();
	
	int count = SCORE_CAPACITY;
	if (count > scores.size()) {
		count = scores.size();
	}

	for (int i = count - 1; i >= 0; i--) {
		top_ten_scores.push_back(scores[i]);
	}
}

/** Gameplay functions */

// Main event loop functions called on every frame
void BrickBreakerGame::update() {
	updateLives();

	if (should_update_) {

		if (current_state_ == IN_PROGRESS) {
			mouseMoved(ofGetMouseX(), ofGetMouseY());

			handleBrickCollisions();
			handlePaddleCollisions();

			checkGameOver();
			updateBallPosition();
		}
	}
	should_update_ = true;
}

// Draws opening page if current state is opening
// Draws pause page if current state is paused
// Draws finished page if game over
// Renders ball, bricks, paddle
void BrickBreakerGame::draw() {
	if (current_state_ == OPENING) {
		drawGameOpening();
	} else if (current_state_ == PAUSED) {
		drawGamePaused();
	}
	else if (current_state_ == FINISHED) {
		drawGameOver();
	}
	drawBricks();
	drawBall();
	drawPaddle();
}

// Event driven functions, called on appropriate user action
// X starts the game
// P pauses/unpauses
// H lists high scores
// R resets the game once it's over
// S stops the game during gameplay
void BrickBreakerGame::keyPressed(int key) {
	int upper_key = toupper(key); // Standardize on upper case

	if (upper_key == 'X' && current_state_ == OPENING) {
		current_state_ = IN_PROGRESS;
	} else if (upper_key == 'P' && current_state_ != FINISHED) {
		// Pause or unpause
		current_state_ = (current_state_ == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
	} else if (upper_key == 'H' && current_state_ != FINISHED) {
		// Pause or unpause
		current_state_ = PAUSED;
		if (current_state_ == PAUSED) {
			drawTopTenScores();
		}
	}
	else if (upper_key == 'R' && current_state_ == FINISHED) {
		reset();
	}
	else if (upper_key == 'S') {
		current_state_ = FINISHED;
		reset();
	}

}