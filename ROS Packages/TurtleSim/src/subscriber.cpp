#include "myheader.h"
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
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"subscriber");
    ros::NodeHandle n;
    Coord::x0 = 5.4445; Coord::y0 = 5.4445;
    //ros::Subscriber turtle_sub=n.subscribe("/turtle1/pose",1000,iniCallback);
    //ros::spinOnce();

    while (ros::ok())
    {
        ros::Subscriber turtle_sub=n.subscribe("/turtle2/pose",1000,callback);
        ros::spinOnce();
    }

    return 0;
}
