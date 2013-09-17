/* game.cpp
 *
 * Implementation of Game class.
 *
 */

#include "game.h"
#include <cstdlib>
#include <GL/glut.h>

// static initializer
Game* Game::callbackInstance(NULL);

Game::Game() {
}

Game::Game(int* argcp, char** argv) {
    init(argcp, argv);
}

Game::~Game() {
	// do any cleanup
}

void Game::init(int* argcp, char** argvp) {
	// GLUT init code here...
    glutInit(argcp, argvp);
}

void Game::initGame() {
    if (callbackInstance == NULL)     {
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
	// display code here...
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
	// keyboard code here...
}

void Game::keyboardWrapper(unsigned char keycode, int x, int y) {
    callbackInstance->keyboard(keycode, x, y);
}

// game specific functions here...




