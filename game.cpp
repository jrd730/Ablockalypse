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
    paddle = new Paddle ();
    init(argcp, argv);
}

Game::~Game() {
	delete ball;
    delete paddle;
}

void Game::init(int* argcp, char** argvp) {
    glutInit(argcp, argvp);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (480, 480);
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow ("Ablockalypse");
    glutSetWindowTitle("Ablockalypse");
    glutSetIconTitle("Ablockalypse");
    
    glewExperimental = GL_TRUE;
    glewInit ();

    // do shader stuff here...
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    vPosition = glGetAttribLocation( program, "vPosition" );
    vColor = glGetAttribLocation( program, "vColor" );
    xlate = glGetUniformLocation( program, "xlate" );

    initGeometry (paddle);
    initGeometry (ball);
    initBricks ();

    glEnable( GL_DEPTH_TEST );
    glClearColor(0, 0, 0, 0); 
}

void Game::initGeometry (Geometry* g)
{
    glGenVertexArrays( 1, &g->vao );
    glBindVertexArray( g->vao );

    GLuint buffer;
    glGenBuffers (1, &buffer);
    glBindBuffer (GL_ARRAY_BUFFER, buffer);
    
    glBufferData (GL_ARRAY_BUFFER, (g->vertices.size()*sizeof(vec4))+(g->colors.size()*sizeof(vec4)),
        NULL, GL_STATIC_DRAW);

    glBufferSubData 
        (GL_ARRAY_BUFFER, 0, g->vertices.size()*sizeof(vec4), &g->vertices[0]);
    
    glBufferSubData
        (GL_ARRAY_BUFFER, g->vertices.size()*sizeof(vec4),
            g->colors.size()*sizeof(vec4), &g->colors[0]);

    glEnableVertexAttribArray ( vPosition );
    glVertexAttribPointer ( vPosition, 4, GL_FLOAT, GL_FALSE, 0, 
        BUFFER_OFFSET(0));

    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                            BUFFER_OFFSET(g->vertices.size()*sizeof(vec4)));
}

void Game::initGame() {
    if (callbackInstance == NULL){
        callbackInstance = this;
    }
	// game init code here...
    score = 0;
    numBricks = 48;
    lives = 3;
    paused = false;
    initBricks ();
}

void Game::initBricks ()
{
    bricks.clear ();
    bricks.resize (numBricks);

    vec3 start (-1.0, 0.75, 0);
    float xInc = .125;
    float yInc = .125;

    for (unsigned i = 0; i < bricks.size (); ++i){
        bricks[i] = Brick (start);
        initGeometry (&bricks[i]);
        start.x += xInc;
        if (start.x > (1.0 - bricks[i].size)) {
            start.x = -1;
            start.y -= yInc; 
        }
    }
}

void Game::registerCallbacks() {
    glutTimerFunc (150, timerWrapper, 0);
    glutDisplayFunc(displayWrapper);
    //glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);
}

void Game::run() {
    initGame();
    registerCallbacks();
    glutMainLoop();
}

void Game::updateBall (Ball* b)
{
    vec3 newPos ( (b->origin.x+b->velocity.x), (b->origin.y+b->velocity.y), 0);

    // check for collision with paddle
    if ((newPos.x >= paddle->origin.x+paddle->vertices[0].x) && 
        (newPos.x <= paddle->origin.x+paddle->vertices[1].x) && 
        (newPos.y <= paddle->origin.y+paddle->vertices[0].y) && 
        (newPos.y >= paddle->origin.y+paddle->vertices[2].y)){

        b->velocity.y = -b->velocity.y;

        // impart a slight x velocity component change based on 
        // where the ball strikes the paddle
        float modifier = newPos.x - (paddle->origin.x+(paddle->width/2) );
        modifier /= paddle->width;
        modifier /= 30.0;
        b->velocity.x += modifier;

        //b->velocity = normalize (b->velocity)/10.0;
    }

    // check for collision with bricks
    for (unsigned i=0; i < bricks.size(); ){
        COLLISION_STATUS status = getCollisionStatus (b, newPos, &bricks[i]);
        if (status != NO_COLLISION){
            bricks.erase (bricks.begin()+i);
            score += 50;
        }
        else{
            ++i;
        }
    }

    // check for collision with walls
    if (newPos.x >= 1){
        newPos.x = 1;
        b->velocity.x = -b->velocity.x;
    }
    else if (newPos.x <= -1){
        newPos.x = -1;
        b->velocity.x = -b->velocity.x;
    }
    else if (newPos.y >= 1){
        newPos.y = 1;
        b->velocity.y = -b->velocity.y;
    }
    else if (newPos.y <= -1){
        if (lives > 0){
            lives--;
            b->origin = vec3 (0, 0, 0);
            return;
        }
    }
    b->origin = newPos;
}

COLLISION_STATUS 
Game::getCollisionStatus (Ball* b, vec3 &pos, const Brick* r){
    if (b->velocity.x >= 0){
        if (b->velocity.y >= 0){
            if (pointInRegion(pos, r)){
                b->velocity.y = -b->velocity.y;
                pos.y = r->origin.y;
                return COLLIDES_BOTTOM;
            }
        }
        else{
            if (pointInRegion(pos, r)){
                b->velocity.y = -b->velocity.y;
                pos.y = r->origin.y+r->size;
                return COLLIDES_TOP;
            }
        } 
    }
    else{
        if (b->velocity.y >= 0){
            if (pointInRegion(pos, r)){
                b->velocity.y = -b->velocity.y;
                pos.y = r->origin.y;
                return COLLIDES_BOTTOM;
            }
        }
        else{
            if (pointInRegion(pos, r)){
                b->velocity.y = -b->velocity.y;
                pos.y = r->origin.y+r->size;
                return COLLIDES_TOP;
            }   
        } 
    }
    return NO_COLLISION;
}

bool Game::pointInRegion (const vec3 &pos, const Brick* r)
{
    if (pos.x >= (r->origin.x + r->vertices[0].x) &&
        pos.x <= (r->origin.x + r->vertices[2].x) &&
        pos.y >= (r->origin.y + r->vertices[0].y) &&
        pos.y <= (r->origin.y + r->vertices[1].y))
    {
        return true;
    }
    return false;
}

void Game::display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    displayGeometry(ball, GL_TRIANGLE_FAN);
    displayGeometry(paddle, GL_LINE_LOOP);

    for (unsigned i = 0; i < bricks.size (); ++i){
        displayGeometry (&bricks[i], GL_TRIANGLE_FAN);
    }

    glutSwapBuffers();
}

void Game::displayGeometry(Geometry* g, GLenum mode) {
    glUniform3fv (xlate, 1, g->origin);
    glBindVertexArray (g->vao);
    glDrawArrays (mode, 0, 4);
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
            if (!paused){paddle->translate (-1.0);}
        break;

        case 'd':
            if (!paused) {paddle->translate (1.0);}
        break;

        case 'p':
            paused = !paused;
        break;
    }
}

void Game::keyboardWrapper(unsigned char keycode, int x, int y) {
    callbackInstance->keyboard(keycode, x, y);
}

void Game::timer (int val)
{
    //cout << "val: " << val << endl;
    stringstream ss("");
    ss << "Ablockalypse v0.1 Score: " << score << " Balls Left: " << lives;
    glutSetWindowTitle(ss.str().c_str());

    if (!paused){
        updateBall(ball);
    }

    glutPostRedisplay();
    glutTimerFunc (40, timerWrapper, 0);
}

void Game::timerWrapper(int val)
{
    callbackInstance->timer(val);
}


