#ifndef MY_CLOCK_H
#define MY_CLOCK_H

#define TIME_SLICES 0.1

class Clock{
    double time;
public:
    static double tslice; //s 

public:
    Clock():time(0) {}

    inline void next() { time ++; }
    double getTime() { return time; }
    double getRealTime() { return time * tslice; }

};
double Clock::tslice = 0.1;


#endif