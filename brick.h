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
    Brick();
    ~Brick();
    void display();

};

#endif
