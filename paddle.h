/**
  Jason Dietrich
  CSCI 566 
*/

/* paddle.h
 *
 * Represents a paddle in the game.
 *
 */

#ifndef PADDLE_H
#define PADDLE_H

#include "geometry.h"

class Paddle : public Geometry {
private:
public:
    Paddle();
    ~Paddle();
    
    void display();

	// paddle specific stuff

    void translate (float modifier);
    float width, height, moveInc;
};

#endif
