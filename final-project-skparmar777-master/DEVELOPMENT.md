# Log of issues/fixes that I came across while working
## Installation
I'm trying to get both openframeworks and SDL 2.0 configured to the project, but I'm unable to add SDL.
A possible fix would be writing the entire project in SDL, but I'm pretty sure the project requirement says it has to be an OF project,
so if I can't get both, I may have to change the libraries used.
### UPDATE 1
If SDL doesn't work, I can use OpenGL. It's compatible with OF, and SDL also uses it. While SDL is made for low level control of graphics, mouse input, joystick input, etc, I really only need the OpenGL part of SDL, not Direct3D also.
### UPDATE 2
Instructors on Piazza told me not to use SDL: using openGL through OF, ofxGUI, and ofxOsc.
Question: are these libraries enough or do I need to add "another significant library"?
Answer: Moderator said this is fine.

## OfApp.h doesn't recognize Brick.h, Ball.h, or Paddle.h
### Fixed!
Visual Studio did not put the files in the right folder so OfApp couldn't find them. Manually moving them fixed it.

## Changed array of Bricks to a vector of bricks
Will remove a Brick from vector if hit by ball

## ofImage png wasn't loading
Changed Brick, Ball, and Paddle to OpenFrameworks Rectangle and Circle objects

## App wasn't displaying: The black console screen opens but the app does not.
I had a infinite for loop in setup, but it works now

## Game threw an exception if ball fell under the Paddle
Score wasn't initialized but the game was trying to access score for the gameOver method. Initializing score fixed this.

## Ball won't bounce off bricks or Paddle
Added cout statements to see if intersect method ever returned true.. it does not??
### UPDATE: It works
I had to write my own logic for detection since the built in Intersects() method isn't working.

# Done
* made all classes (Brick, Ball, Paddle, ofApp)
* removed Brick class because it was too simple to warrant a full class
* made ball and paddle have ofRectangle as a property so Intersect method could be used (sad life :'( when Intersect doesn't work)')
* added scoring if brick is removed
* got paddle to follow mouse movements --> needed to use ofVec2f to get paddle to follow mouse movements
* restricted paddle movement so only x can change --> using ofVec2f, only change the x value of direction
* write physics for ball movement
* make sure ball can fall out of screen from bottom, but not sides or top
* Building Graphical Layout : created all objects and they should theoretically appear on the screen
* Added lives: App screen shows amount of lives at top, if there are bricks and player still has lives, it continues the game.
* remove bricks from the vector if intersection between ball and brick
* get ball to bounce off paddle
* fixed ball physics to make it more smooth
* added sound effects
* added high score list
* added score to top

# Extra Features to extend project in the future (not in current project)
* add full-screen capabilities
