#include "paddle.h"

Paddle::Paddle()
{
	width = .25;
	height = .0125;
	moveInc = .0125;
	vertices = new vec4[4];

	vertices[0] = vec4 (0, 0, 0, 1.0);
	vertices[1] = vec4 (width, 0, 0, 1.0);
	vertices[2] = vec4 (width, -height, 0, 1.0);
	vertices[3] = vec4 (0, -height, 0, 1.0);

	origin[0] = 0.0;
	origin[1] = 0.0;
	origin[2] = 0.0;
}

Paddle::~Paddle()
{
	delete [] vertices;
}

void Paddle::display()
{

}

void Paddle::translate (float modifier)
{
	origin[Xaxis] += (modifier*moveInc);
}