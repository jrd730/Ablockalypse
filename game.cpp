/* game.cpp
 *
 * Implementation of Game class.
 *
 */

#include "game.h"
#include <cstdlib>
#include <GL/freeglut.h>

// static initializer
Game* Game::callbackInstance(NULL);

Game::Game() {
}

Game::Game(int* argcp, char** argv) {
    init(argcp, argv);
}

Game::~Game() {
	delete ball;
    delete paddle;
}

void Game::init(int* argcp, char** argvp) {
    glutInit(argcp, argvp);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (480, 480);
    glutCreateWindow ("Ablockalypse");
    glutSetWindowTitle("Ablockalypse");
    glutSetIconTitle("Ablockalypse");
    glEnable( GL_DEPTH_TEST );
    glClearColor(0, 0, 0, 0); 
}

void Game::initGame() {
    if (callbackInstance == NULL){
        callbackInstance = this;
    }

	// game init code here...
}

void Game::registerCallbacks() {
    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);
}

void Game::run() {
    initGame();
    registerCallbacks();
    glutMainLoop();
}

void Game::display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glutSwapBuffers();
}

void Game::displayWrapper() {
    callbackInstance->display();
}

void Game::reshape(int width, int height) {
    // reshape code here...
}

void Game::reshapeWrapper(int width, int height) {
    callbackInstance->reshape(width, height);
}

void Game::keyboard(unsigned char keycode, int x, int y) {
	switch (keycode){
        
    }
}

void Game::keyboardWrapper(unsigned char keycode, int x, int y) {
    callbackInstance->keyboard(keycode, x, y);
}

// game specific functions here...




