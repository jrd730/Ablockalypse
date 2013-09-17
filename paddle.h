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

	// private vars

public:
    Paddle();
    ~Paddle();
    void display();

	// paddle specific stuff
};

#endif
