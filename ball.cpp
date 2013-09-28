#include "ball.h"

Ball::Ball()
{
	size = .125;
	vertices = new vec4 [4];
	
	vertices[0] = (vec4 (0, 0, -0.1, 1.0));
	vertices[1] = (vec4 (0, size, -0.1, 1.0));
	vertices[2] = (vec4 (size, size, -0.1, 1.0));
	vertices[3] = (vec4 (size, 0, -0.1, 1.0));

	origin[0] = 0.0;
	origin[1] = 0.0;
	origin[2] = 0.0;

	velocity.x = 0.0;
	velocity.y = -0.1;
}

Ball::~Ball()
{
	delete [] vertices;
}

void Ball::display()
{

}