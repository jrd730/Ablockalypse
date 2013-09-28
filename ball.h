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

	// private variables and functions

public:
    Ball();
    ~Ball();

    void display();

    float size;
    vec2 velocity;
	// ball specific functions
};

#endif
