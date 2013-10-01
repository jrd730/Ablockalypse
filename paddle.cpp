#include "paddle.h"

Paddle::Paddle()
{
	width = .25;
	height = .0225;
	moveInc = .0325;
	vertices.resize(4);

	vertices[0] = vec4 (0, 0, 0, 1.0);
	vertices[1] = vec4 (width, 0, 0, 1.0);
	vertices[2] = vec4 (width, -height, 0, 1.0);
	vertices[3] = vec4 (0, -height, 0, 1.0);

	colors.resize (4);
	colors[0] = vec4 (1.0, 0, 0, 1.0);
	colors[1] = vec4 (0, 1.0, 0, 1.0);
	colors[2] = vec4 (0, 0, 1.0, 1.0);
	colors[3] = vec4 (0, 0, 0, 1.0);

	origin = vec3 (0, -0.85, 0);
}

Paddle::~Paddle()
{
	
}

void Paddle::display()
{

}

void Paddle::translate (float modifier)
{
	origin[Xaxis] += (modifier*moveInc);
}