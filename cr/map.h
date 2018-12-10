#ifndef MY_MAP_H
#define MY_MAP_H

#include <vector>
#include <fstream>
#include "car.h"
#include "cylinder.h"


class MyMap{
public:
    Car c;
    //std::vector<int> a;
    std::vector<Object> obs;

public:
    MyMap():c(Car(1, 1, 1, vec3(0,1,0), vec3(-1,0,0))) {}
    MyMap(Car _c):c(_c) {}
    void addObs(Object o) {obs.push_back(o);}
    void refresh();
    void buildFromFile(char*);
};

void MyMap::refresh() {
    c.refresh(1);
    for (int i = 0; i < obs.size(); ++i)
        obs[i].refresh();

}

void MyMap::buildFromFile(char* fileName) {
    std::ifstream fin;
    fin.open(fileName, std::ios::in);
    
    if(!fin.is_open()){
        std::cout<<"open file is error"<< std::endl;
        exit(1);
    }
    double x,y,r;
    while(!fin.eof()) {
        fin >> x;
        fin >> y;
        fin >> r;
        addObs(Cylinder(vec3(x, y, 0), r));
    }
}


#endif