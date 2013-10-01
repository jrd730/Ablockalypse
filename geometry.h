/**
  Jason Dietrich
  CSCI 566 
*/

/* Geometry.h
 *
 * Base class for geometric objects.
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include "Angel.h"
using namespace std;

enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };

class Geometry {
private:

    // common state variables

public:
    Geometry();
    virtual ~Geometry();

    /*
       Pure virtual function to display the Geometry. Classes
       inheriting from Geometry need to provide a definition
       for display().
    */
    virtual void display() = 0;

    // points that make up the shape of the object
    vector <vec4> vertices;

    // color values to apply to each vertex
    vector <vec4> colors;

    // offset amount for the vertices 
    vec3 origin;

    // every object that will be drawn needs its own vertex array object
    GLuint vao;

    // setters, getters, common behaviors
};

#endif
