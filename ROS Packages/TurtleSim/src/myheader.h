#include "ros/ros.h"
#include <stdlib.h>
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include <cmath>
#include "geometry_msgs/Twist.h"
#define SAFE_DIST 2

class Coord
{
    double x,y;
    public:
    static double x0,y0;
    static bool isFar;
    Coord(double a,double b)
    {x=a;y=b;}
    double dist()
    {
        double a=x-x0,b=y-y0;
        double res= sqrt(a*a + b*b);
        return res;
    }
};


bool Coord::isFar = 1;
double Coord::x0 = 0;
double Coord::y0 = 0;