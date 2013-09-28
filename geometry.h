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

    vec4* vertices;

    GLfloat origin[3];

    GLuint vao;

    // setters, getters, common behaviors
};

#endif
