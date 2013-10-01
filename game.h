/**
  Jason Dietrich
  CSCI 566 
*/


/* game.h
 *
 * Represents the game.
 *
 */
#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <iostream>
//#include <GL/freeglut.h>
#include <sstream>
#include <string>

#include "Angel.h"
#include "ball.h"
#include "brick.h"
#include "geometry.h"
#include "paddle.h"

using namespace std;

enum COLLISION_STATUS{
  NO_COLLISION,
  COLLIDES_BOTTOM,
  COLLIDES_TOP,
  COLLIDES_LEFT,
  COLLIDES_RIGHT
};

class Game {
private:
    
    static Game* callbackInstance;
    static void timerWrapper(int);
    static void displayWrapper();
    static void reshapeWrapper(int, int);
    static void keyboardWrapper(unsigned char, int, int);
    
    Game();
    
    void init(int*, char**);
    void initGeometry (Geometry* g);

    void initGame();
    void initBricks();
    void registerCallbacks();

    void timer (int);
    void display();
    void displayGeometry (Geometry* g, GLenum mode);
    void reshape(int, int);
    void keyboard(unsigned char, int, int);

    void updateBall (Ball* b);
    COLLISION_STATUS getCollisionStatus (Ball* b, vec3 &pos, const Brick* r);
    bool pointInRegion (const vec3 &pos, const Brick* r); 

    Ball* ball; // the ball bounces around inside the game area
    vector <Brick> bricks; // array of bricks that must be broken
    Paddle* paddle; // the player controlled paddle, used to bounce the ball around

    GLuint xlate;
    GLuint vPosition;
    GLuint vColor;

    unsigned numBricks;
    unsigned lives;
    unsigned score;
    bool paused;

public:

    Game(int*, char**);
    ~Game();

    void run();

};

#endif
