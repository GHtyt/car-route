#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <algorithm>
//#include "map.h"

#define pi 3.1415926

const int car_len = 3;          //车长
const double acc = 10;          //油门加速度
const double break_acc = -20;    //刹车加速度
const double time_slice = 0.1;  //时间片



int main()
{
    
    //MyMap* m = new MyMap();
    //Car* c = new Car(1, 1, 1, vec3(0,1,0), vec3(-1,0,0));
    //m->c.setWheel(810);
    //m->c.turn_ang = 90;
    //m->c.setAcceleration(0);
    //m->c.setVelocity(1);
    char fileName[50];
    std::ifstream fin;
    std::cout << "Enter a name of File:";
    std::cin.getline(fileName, 50);
    fin.open(fileName, std::ios::in);/*打开文件*/
    if(!fin.is_open()){
        std::cout<<"open file is error"<< std::endl;
        exit(1);
    }
    double ang, gas, bre;
    int type;
    int t;
    double v = 0; //线速度
    double as = 0; //角速度
    
    while(!fin.eof()) {
        /*fin >> t;  //时间
        fin >> ang; //方向盘 -90-90
        fin >> gas; //油门 0—1
        fin >> bre; //刹车 -1-0*/
        type = 0;
        gas = bre = 0;
        t = 0;
        ang = 0;

        fin >> type;
        printf("type: %d\n", type);
        fin >> gas;
        printf("gas: %f\n", gas);
        fin >> ang;
        printf("ang: %f\n", ang);
        fin >> t;
        printf("time: %d\n", t);
        
        if (type == 0)
            gas = bre = 0;
        else if (type == 2)
            bre = gas;
        
        printf("%d %f %f %f\n", t, ang, gas, bre);


        //std::cout << t << std::endl;  
        double ac = 0; //加速度
        if (bre != 0)  //优先刹车
            ac = bre * break_acc;
        else
            ac = gas * acc;
        printf("acc: %f\n", ac);
        double r = (ang == 0) ? 0 : car_len/sin(ang / 180 * pi);
        for (int i = 0; i < t; ++i) {
            // 计算线速度角速度
            v = (v+ac*time_slice > 0) ? v+ac*time_slice : 0;
            as = (r == 0) ? 0 : v / r; 

            std::cout << "xiansudu: " << v << std::endl;     
            std::cout << "jiaosudu: " << as << std::endl;         


        }
        //std::cout << a << std::endl;
    }

    //for (int i = 0; i < 120; ++i){
        //printf("%f %f\n", m->c.pos.x(), m->c.pos.y());
        //printf("%f %f\n", (m->c.pos+m->c.dir).x(), (m->c.pos+m->c.dir).y());
        //m->refresh();

    //}

}