#ifndef MY_SPHERE_H
#define MY_SPHERE_H

#include "object.h"
#include "vec3d.h"

class Sphere{
public:
    vec3 centre;
    double r;

public:
    bool collide(Object);

};

//bool Sphere::collide(Car c)


#endif