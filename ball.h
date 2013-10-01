/**
  Jason Dietrich
  CSCI 566 
*/

/* ball.h
 *
 * Represents a ball.
 * 
 */

#ifndef BALL_H
#define BALL_H
#include "geometry.h"

class Ball : public Geometry
{
private:
public:
    Ball();
    ~Ball();

    void display();

    float size;

    // (X/Y) component velocity 
    vec2 velocity;

	// ball specific functions
};

#endif
