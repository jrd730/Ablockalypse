/**
  Jason Dietrich
  CSCI 566 
*/

/* brick.h
 *
 * Represents a paddle in the game.
 *
 */

#ifndef BRICK_H
#define BRICK_H

#include "geometry.h"

class Brick : public Geometry {
private:
public:
	Brick ();
    Brick(vec3 position);
    ~Brick();
    void display();

    float size;

};

#endif
