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

	// ball specific functions
};

#endif
