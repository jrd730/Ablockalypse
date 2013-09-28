/* game.cpp
 *
 * Implementation of Game class.
 *
 */

#include "game.h"

// static initializer
Game* Game::callbackInstance(NULL);

Game::Game() {
}

Game::Game(int* argcp, char** argv) {
    ball = new Ball ();

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
    
    glewExperimental = GL_TRUE;
    glewInit ();

    // do shader stuff here...
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    xlate = glGetUniformLocation( program, "xlate" );

    // create a vertex array object for the ball
    glGenVertexArrays( 1, &ball_vao );
    glBindVertexArray( ball_vao );

    // create and initialize a buffer object for the ball
    GLuint ballBuffer;
    glGenBuffers (1, &ballBuffer);
    glBindBuffer (GL_ARRAY_BUFFER, ballBuffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof(ball->vertices), 
        NULL, GL_STATIC_DRAW);

    glBufferSubData (GL_ARRAY_BUFFER, 0, sizeof(ball->vertices), ball->vertices);
    
    glEnableVertexAttribArray ( vPosition );
    glVertexAttribPointer ( vPosition, 4, GL_FLOAT, GL_FALSE, 0, 
        BUFFER_OFFSET(0));



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
    glutTimerFunc (150, timerWrapper, 0);
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

    // set ball translation and draw the ball
    glUniform3fv (xlate, 1, ball->origin);
    glBindVertexArray (ball_vao);
    glDrawArrays (GL_TRIANGLE_FAN, 0, 4);

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
        case 'a':

        break;

        case 'd':

        break;
    }
}

void Game::keyboardWrapper(unsigned char keycode, int x, int y) {
    callbackInstance->keyboard(keycode, x, y);
}

void Game::timer (int val)
{
    //cout << "val: " << val << endl;
    glutPostRedisplay();
    glutTimerFunc (150, timerWrapper, 0);
}

void Game::timerWrapper(int val)
{
    callbackInstance->timer(val);
}


