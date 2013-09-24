/* game.h
 *
 * Represents the game.
 *
 */
#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "brick.h"
#include "paddle.h"

class Game {
private:
    /*
       Because GLUT expects C-style functions to be used with its callback
       mechanism, wrappers are needed in order to register a member function.
       So, we store a pointer to the object to call the member functions on
       in callbackInstance. Then we have some simple static class functions to
       register with GLUT, which will call the corresponding member function on
       the object pointed to by callbackInstance.
    */
    static Game* callbackInstance;
    static void displayWrapper();
    static void reshapeWrapper(int, int);
    static void keyboardWrapper(unsigned char, int, int);
    
    // add more callback wrappers as needed 

    // more member variables here...

    /*
       The default c'tor is private because so command-line args passed in.
    */
    Game();

    /*
       Initialization for GLUT and OpenGL. Takes command-line arguments
       and passes them on to GLUT.
    */
    void init(int*, char**);

    /*
       Initializes the actual game stuff.
    */
    void initGame();

    /*
       Registers our static wrapper callbacks with GLUT.
    */
    void registerCallbacks();

    /*
       Below are the "real" callback functions. These are the ones that
       provide the functionality of the callbacks.
    */
    void display();
    void reshape(int, int);
    void keyboard(unsigned char, int, int);

    Ball* ball; // the ball bounces around inside the game area
    Brick** bricks; // array of bricks that must be broken
    Paddle* paddle; // the player controlled paddle, used to bounce the ball around


public:
    /*
       C'tor that takes command-line arguments, so it can pass them onto GLUT.
    */
    Game(int*, char**);

    /*
       Default d'tor.
    */
    ~Game();

    /*
       Initialization and starts the game, i.e. enters the GLUT main loop.
    */
    void run();

};

#endif
