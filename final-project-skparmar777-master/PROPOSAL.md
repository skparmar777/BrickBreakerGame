# Project Proposal
For my project, I'm proposing a ***Brick-Breaker Game***!

## Background Behind the Idea
A little bit of background behind my choice: When I first started messing around with programming, I tried to make a brick-breaker game in JavaScript, and it was a complete mess. I messed with the game for hours, but I couldn't get the graphics and motion to act the way I wanted. When I found out about the final project, the snake game reminded me of retro game idea, which turned my mind towards brick breaker. I want to create a brick-breaker game that has legit motion behind the ball and how it moves.

## Libraries
The main library pushing this project is SDL (http://www.libsdl.org/).

### About SDL (taken from their website above)
Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. It is used by video playback software, emulators, and popular games including Valve's award winning catalog and many Humble Bundle games.
SDL officially supports Windows, Mac OS X, Linux, iOS, and Android. Support for other platforms may be found in the source code.
SDL is written in C, works natively with C++, and there are bindings available for several other languages, including C# and Python.
SDL 2.0 is distributed under the zlib license. This license allows you to use SDL freely in any software.

### OpenGL and Direct3D
OpenGL (https://www.opengl.org/).
Direct3D (https://msdn.microsoft.com/en-us/library/windows/desktop/hh769064(v=vs.85).aspx)
Direct3D is a low-level API for drawing primitives with the rendering pipeline or performing parallel operations with the compute shader.
OpenGL is a rendering library. SDL uses OpenGL and Direct3D.

## The Goal
What I'm trying to do is use SDL for the setup and graphics of the game. The game itself involves paddle movements, ball movements, and collisions between the ball and bricks. Collisions can be calculated using math/angles. The player will try to clear the board of all bricks by shooting the ball at them and hitting them. The player will also move the paddle to make sure the ball does not fall out of the bottom of the screen. If I have time, I intend to add more levels; when the player clears all the bricks off the screen, the screen refreshes and generates a new level. To extend the game further, I may have different bricks be different colors, so certain brick colors take more hits to break.
