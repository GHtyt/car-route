#ifndef MY_ROUTE_H
#define MY_ROUTE_H

#include "vec3d.h"
#include "car.h"

class Route{
public:
    Car *c;
    vec3 p[2];
    vec3 d[2];
    double l;
    vec3 dir;
    double x;
    double a0, a1, a2, a3;

public:
    Route(Car *_c, vec3 x1, vec3 x2, vec3 y1, vec3 y2):x(0), c(_c) {
        /*x1.print();
        x2.print();
        y1.print();
        y2.print();*/
        dir = unit_vector((x2-x1));
        p[0] = x1;
        p[1] = x2;
        l = (x2-x1).length();
        d[0] = vec3(y1.x()*dir.x() + y1.y()*dir.y(), y1.y()*dir.x() - y1.x()*dir.y(), 0);
        d[1] = vec3(y2.x()*dir.x() + y2.y()*dir.y(), y2.y()*dir.x() - y2.x()*dir.y(), 0);
        printf("newroute: %f %f %f %f\n", p[0].length(), p[1].length(), atan(x1.y()/x1.x()), atan(x2.y()/x2.x()));
        //p[0].print();
        //printf("%f\n", p[0].length());
        //p[1].print();
        //printf("%f\n", p[1].length());
        /*d[0].print();
        d[1].print();*/
        
        double f1 = d[0].y()/d[0].x();
        double f2 = d[1].y()/d[1].x();
        a0 = (f1 + f2) / l / l;
        a1 = -(2 * f1 + f2) / l;
        a2 = f1;
        a3 = 0;
        //printf("a: %f %f %f %f\n", a0, a1, a2, a3);
    };
    ~Route() {};

public:
    bool isEnd() {
        vec3 t = c->pos;
        double tmp = dot(t-p[0], dir);
        printf("  tmp: %f %f %f\n", tmp, x, l);
        //printf("tmp: %f \n", l);
        if (tmp < x || tmp > l) return true;
        x = tmp;
        return false;
    }
    double getR() {
        double y, y1, y2;
        //y = a0 * x * x * x + a1 * x * x + a2 * x + a3;
        y1 = 3 * a0 * x * x + 2 * a1 * x + a2;
        y2 = 3 * 2 * a0 * x + 2 * a1;
        
        return - pow((1 + y1 * y1), 1.5) / y2;
        
        
    }

};

class Route2{
public:
    Car *c;
    vec3 p[2];
    vec3 d[2];
    double l;
    vec3 dir;
    double x;
    double a0, a1, a2, a3;
    int ti;
    int tr[5];
    vec3 cen[2];   
    int b0, b1;
    double len[3];

public:    
    Route2(Car *_c, vec3 x1, vec3 x2, vec3 y1, vec3 y2):x(0), c(_c), ti(0) { 
        //y1 = vec3(0,1,0);       
        //y2 = vec3(0,1,0);       
        tr[0] =  100;       
        tr[1] =  20;       
        tr[2] =  10;       
        tr[3] =  5;
        tr[4] =  1;
        dir = unit_vector((x2-x1));
        p[0] = x1;
        p[1] = x2;
        l = (x2-x1).length();
        d[0] = vec3(y1.x()*dir.x() + y1.y()*dir.y(), y1.y()*dir.x() - y1.x()*dir.y(), 0);
        d[1] = vec3(y2.x()*dir.x() + y2.y()*dir.y(), y2.y()*dir.x() - y2.x()*dir.y(), 0);
        /*p[0].print();
        p[1].print();*/
        d[0].print();
        d[1].print();
        b0 = (d[0].y() >= 0)? 1 : -1;
        b1 = (d[0].y() >= 0)? -1 : 1;
        printf("%d %d\n", b0, b1);
        cen[0] = p[0] + b0 * rot90(d[0]) * tr[0];
        cen[1] = p[1] + b1 * rot90(d[1]) * tr[0];
        while ((cen[1]-cen[0]).length() < 2 * tr[ti] && ti <= 3){
            ti ++;
            cen[0] = p[0] + b0 * rot90(d[0]) * tr[ti];
            cen[1] = p[1] + b1 * rot90(d[1]) * tr[ti];
        }
        vec3 dir2 = unit_vector((cen[1]-cen[0]));
        double tl = (cen[1]-cen[0]).length();
        printf("%f %f\n", tl, asin(2*tr[ti]/tl));
        dir2 = rot(dir2, asin(2*tr[ti]/tl));
        len[1] = sqrt(tl * tl - 4 * tr[ti] * tr[ti]);
        len[0] = tr[ti] * acos(dot(dir2, d[0]));
        len[2] = tr[ti] * acos(dot(dir2, d[1]));

        dir2.print();
        printf("%d\n", ti);
        cen[0].print();
        cen[1].print();
        printf("%f %f %f\n", len[0], len[1], len[2]);
        
        double f1 = d[0].y()/d[0].x();
        double f2 = d[1].y()/d[1].x();
        a0 = (f1 + f2) / l / l;
        a1 = -(2 * f1 + f2) / l;
        a2 = f1;
        a3 = 0;
    }
    ~Route2() {}

public:
    bool isEnd() {
        double tmp = x + c->v * TIME_SLICES  + 1/2 * c->acc * TIME_SLICES * TIME_SLICES ;
        if (tmp < x || tmp > len[0] + len[1] + len[2]) return true;
        x = tmp;
        return false;
    }
    double getR() {
        //printf("here %f\n", x);
        //printf("%d %d\n", ti, tr[ti]);
        //printf("len:%f %f %f\n", len[0], len[1], len[2]);
        double R;
        if (x < len[0])
            R = b0 * tr[ti];
        if (x < len[1] + len[0] && x > len[0])
            R = 0;
        if (x > len[1] + len[0])
            R = b1 * tr[ti];
        //printf("R:%f\n", R);
        return R;
        
        
        
    }

};

#endif