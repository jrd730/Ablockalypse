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
#include "paddle.h"

using namespace std;

class Game {
private:
    
    static Game* callbackInstance;
    static void timerWrapper(int);
    static void displayWrapper();
    static void reshapeWrapper(int, int);
    static void keyboardWrapper(unsigned char, int, int);
    
    Game();
    
    void init(int*, char**);    
    void initGame();
    void registerCallbacks();

    void timer (int);
    void display();
    void reshape(int, int);
    void keyboard(unsigned char, int, int);

    Ball* ball; // the ball bounces around inside the game area
    Brick** bricks; // array of bricks that must be broken
    Paddle* paddle; // the player controlled paddle, used to bounce the ball around

    GLuint xlate;

    unsigned score;

public:

    Game(int*, char**);
    ~Game();

    void run();

};

#endif
