#include "ros/ros.h"
#include <stdlib.h>
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include <cmath>
#include "geometry_msgs/Twist.h"
#define SAFE_DIST 2

//to check if the subscriber object has received the message (1 - no, 0 - yes)
int ISOK=1;

using namespace std;
const double NINETY = 1.5708; //90 degree in radian

//used to publish information about linear and angular velocity of turtle
geometry_msgs::Twist vel_msg;

class Coord //stores coordinates of turtle
{
    double x,y;
    public:
    //static members that store the position of turtle1
    static double x0,y0;
    //whether turtle2 is far enough from turtle1
    static bool isFar; 
    Coord(double a,double b)
    {x=a;y=b;}
    double dist()   //distance between turtle1 and turtle2
    {
        double a=x-x0,b=y-y0;
        double res= sqrt(a*a + b*b);
        return res;
    }
};


bool Coord::isFar = 1;
double Coord::x0 = 0;
double Coord::y0 = 0;

void iniVel(double vx,double vz);   //initializes linear velocity along x and angular velocity along z
void iniCallback(const turtlesim::Pose& msg)
{
    Coord::x0 = msg.x;
    Coord::y0 = msg.y;
}
void callback(const turtlesim::Pose& msg)
{
    double x=msg.x,y=msg.y;
    Coord obj(x,y);
    if (obj.dist()<SAFE_DIST)
        Coord::isFar=0;
    else
        Coord::isFar=1;
     ISOK=0;    //0 indicates subscriber has been successfully called
}


int main(int argc,char** argv)
{
    ros::init(argc,argv,"publisher");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);
    const double vx=0.8;
    Coord::x0=5.4445;
    Coord::y0=5.4445;
    //initialize x0,y0
    //publisher object created
    ros::Publisher vel_pub=n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",100);
    
    iniVel(vx,0);
    while(Coord::isFar) //turtle2 moves till its too close to turtle1
    {
        vel_pub.publish(vel_msg);
        ros::Subscriber turtle_sub=n.subscribe("/turtle2/pose",1000,callback);
        while (ISOK)
	        ros::spinOnce();
	    ISOK=1;
        loop_rate.sleep();
    }
    
    
    iniVel(0,vx);
    double theta=0;
    double t0=ros::Time::now().toSec();
    double t1=t0;
    while (theta<NINETY)    //turtle rotates 90 degrees
    {
        vel_pub.publish(vel_msg);
        t1=ros::Time::now().toSec();
        theta=vx*(t1-t0);
        loop_rate.sleep();
    }
    
    iniVel(vx,0);
    
    double dist=0;
    t0=ros::Time::now().toSec();
    t1=t0;
    while (dist<2*SAFE_DIST)    //moves upward to some safe distance
    {
        vel_pub.publish(vel_msg);
        t1=ros::Time::now().toSec();
        dist=vx*(t1-t0);
        loop_rate.sleep();
    }
    
    
    iniVel(0,-vx);
    t0=ros::Time::now().toSec();
    t1=t0;
    theta=0;
    while (theta<NINETY)    //turns by 90 degrees in opposite direction to go straight again
    {
        vel_pub.publish(vel_msg);
        t1=ros::Time::now().toSec();
        theta=vx*(t1-t0);
        loop_rate.sleep();
    }
    
    iniVel(vx,0);
    dist=0;
    t0=ros::Time::now().toSec();
    t1=t0;
    while (dist<3*SAFE_DIST)    //moves to a safe distance from turtle1
    {
        vel_pub.publish(vel_msg);
        t1=ros::Time::now().toSec();
        dist=vx*(t1-t0);
        loop_rate.sleep();
    }
    
    iniVel(0,0);
    while (ros::ok())
    {
        vel_pub.publish(vel_msg);
        loop_rate.sleep();
    }
    
    return 0;
}

void iniVel(double vx,double vz)
{
    vel_msg.linear.x=vx;
    vel_msg.linear.y=0;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;
    vel_msg.angular.z=vz;
}
