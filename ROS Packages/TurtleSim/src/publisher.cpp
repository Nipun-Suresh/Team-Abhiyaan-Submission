#include "myheader.h"

using namespace std;

geometry_msgs::Twist vel_msg;

void iniVel(double vx,double vy);

int main(int argc,char** argv)
{
    ros::init(argc,argv,"publisher");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);
    const double vx=0.8;
    //initialize x0,y0
    ros::Publisher vel_pub=n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",100);
    
    iniVel(vx,0);
    while(Coord::isFar)
    {
        vel_pub.publish(vel_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    iniVel(vx,4*vx);
    while(!(Coord::isFar))
    {
        vel_pub.publish(vel_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    iniVel(vx,0);
    double t0=ros::Time::now().toSec(),t1;
    while (t1-t0<2)
    {
        vel_pub.publish(vel_msg);
        t1=ros::Time::now().toSec();
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    iniVel(0,0);
    while (ros::ok())
    {
        vel_pub.publish(vel_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}

void iniVel(double vx,double vy)
{
    vel_msg.linear.x=vx;
    vel_msg.linear.y=vy;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;
    vel_msg.angular.z=0;
}