#ifndef MY_CAR_H
#define MY_CAR_H

#include <algorithm>
#include "vec3d.h"
#include "clock.h"

#define pi 3.1415926
#define epsilon 3
#define MAX_WHEEL_ANG 45
#define MAX_TURN_ANG 90
#define MAX_SPEED 100
#define MAX_R 100

class Car{
public:
    double h, w;
    double tire_len;
    double v;
    vec3 dir;
    vec3 pos;
    double acc; //acceleration
    double turn_ang;
    double wheel_ang;
    Clock c;

public:
    Car() {};
    Car(double _h, double _w, double tl, vec3 _dir, vec3 _pos):h(_h), w(_w), tire_len(tl), v(0), dir(_dir), pos(_pos), acc(0), wheel_ang(0) { dir.make_unit_vector(); }

public:
    void refresh(int);
    void refresh2(double);
    inline double getAngle(double ang) {return ang / 180 * pi;}
    inline void setWheel(double ang) { wheel_ang = ang; }
    inline void setAcceleration(double ac) { acc = ac; } 
    inline void setVelocity(double vel) { v = vel; } 
    inline void getTurndir();
    inline vec3 getCentre(double);
    inline double getSpeed() {return v + c.tslice * acc; }
    inline double getH() {return h;}
    inline double getW() {return w;}
    inline vec3 getDir() {return dir;}
    inline vec3 getPos() {return pos;}
    inline double getTurnradius();
};


inline void Car::getTurndir()
{
    //printf("inline ta : %f\n", turn_ang);
    double goal_dir = wheel_ang / 9;
    if (goal_dir < turn_ang)
        turn_ang = std::max(turn_ang - MAX_WHEEL_ANG/c.tslice, goal_dir);
            
    if (goal_dir > turn_ang)
        turn_ang = std::min(turn_ang + MAX_WHEEL_ANG/c.tslice, goal_dir);

    if (turn_ang > MAX_TURN_ANG)
        turn_ang = MAX_TURN_ANG;
    
    if (turn_ang < -MAX_TURN_ANG)
        turn_ang = -MAX_TURN_ANG;
    //printf("inline ta : %f\n", turn_ang);
}

inline vec3 Car::getCentre(double r)
{
    /*if (turn_ang > 0)
        return pos + rot(dir, pi/2) * r;
    if (turn_ang < 0)
        return pos + rot(dir, -pi/2) * r;*/
    return pos + rot(dir, pi/2) * r;
}

inline double Car::getTurnradius()
{
    double ang = getAngle(turn_ang);
    //printf("ang: %f", sin(ang));
    return tire_len / sin(ang);
}

void Car::refresh(int t)
{
    for (int i = 0; i < t; ++i) {
        double dis = v * c.tslice + 1/2 * acc * c.tslice * c.tslice;
        //getTurndir();

        //printf("ta : %f\n", turn_ang);
        if (std::abs(turn_ang) < epsilon) {
            pos += dir * dis;
            //std::cout << "dir" << dir << std::endl;
        }
        else {
            double r = getTurnradius();    
            //printf("v:%f %f\n", v, v/r);        
            
            //printf("ang: %f\n", turn_ang);
            //printf("radius: %f\n", r);
            vec3 cent = getCentre(r);
            //std::cout << cent << std::endl;
            double ang = dis / (r);
            pos = cent + rot(pos - cent, ang);
            dir = rot(dir, ang);
        }

        v += acc * c.tslice;
        //printf("acc: %f v: %f\n", acc, v);

    }
}

void Car::refresh2(double r)
{
    
        double dis = v * c.tslice + 1/2 * acc * c.tslice * c.tslice;
        //getTurndir();

        //printf("ta : %f\n", turn_ang);
        /*if (std::abs(turn_ang) < epsilon) {
            pos += dir * dis;
            printf("here\n");
            //std::cout << "dir" << dir << std::endl;
        }
        else {  */          
            
            //printf("ang: %f\n", turn_ang);
            //printf("radius: %f\n", r);
        //printf("dis: %f\n", dis);
        if (std::abs(r) > MAX_R || std::abs(r) < 1e-5){
            pos += dir * dis;

        }
        else {
            vec3 cent = getCentre(r);
            //printf("r: %f center: ", r);
            //cent.print();
            //std::cout << cent << std::endl;
            double ang = dis / (r);
            pos = cent + rot(pos - cent, ang);
            dir = rot(dir, ang);
            //printf("len: %f\n", (pos-cent).length());
        }
        //}

        v += acc * c.tslice;
        //printf("acc: %f v: %f\n", acc, v);

    
}



#endif