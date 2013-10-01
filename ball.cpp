#include "ball.h"

Ball::Ball()
{
	size = .025;
	
	vertices.resize (4);
	vertices[0] = vec4 (0, 0, 0, 1.0);
	vertices[1] = vec4 (0, size, 0, 1.0);
	vertices[2] = vec4 (size, size, 0, 1.0);
	vertices[3] = vec4 (size, 0, 0, 1.0);

	colors.resize (4);
	colors[0] = vec4 (1.0, 0, 0, 1.0);
	colors[1] = vec4 (0, 1.0, 0, 1.0);
	colors[2] = vec4 (0, 0, 1.0, 1.0);
	colors[3] = vec4 (0, 0, 0, 1.0);

	origin = vec3 (0, 0, 0);

	velocity.x = 0.008;
	velocity.y = -0.02;
}

Ball::~Ball()
{

}

void Ball::display()
{

}