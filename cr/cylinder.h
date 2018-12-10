#ifndef MY_Cylinder_H
#define MY_Cylinder_H

#include "object.h"
#include "vec3d.h"

class Cylinder : public Object
{
public:
    vec3 centre;
    double r, h;
    vec3 v;

public:
    Cylinder(vec3 c, double _r):centre(c), r(_r), h(0) {}
    bool collide(Car);
    bool collide(vec3, vec3);
    void refresh();
};

bool Cylinder::collide(vec3 a, vec3 b) {
    double dis = 0;
    if (dot(a-b, a-centre)<0) {
        dis = (a-centre).length();

    }
    else if (dot(b-a, b-centre)<0) {
        dis = (b-centre).length();

    }
    else {
        vec3 t = unit_vector(a-b);
        t = vec3(t.y(), t.x(), t.z());
        dis = std::abs(dot(t, centre-a));

    }
    return (r<dis);
}

bool Cylinder::collide(Car c) {
    //int flag = 0;
    double h = c.getH();
    double w = c.getW();
    vec3 pos = c.getPos();
    vec3 dir = c.getDir();
    vec3 a1 = pos + dir*(h/2);
    vec3 a2 = pos - dir*(h/2);
    vec3 b1 = a1 + rot90(dir)*(w/2);
    vec3 b2 = a1 - rot90(dir)*(w/2);
    vec3 b3 = a2 + rot90(dir)*(w/2);
    vec3 b4 = a2 - rot90(dir)*(w/2);
    return collide(b1, b2) || collide(b1, b3) || collide(b3, b4) || collide (b2, b4);

}

void Cylinder::refresh() {

    
}


#endif