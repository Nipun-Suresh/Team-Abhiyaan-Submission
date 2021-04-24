#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc,char** argv)
{
    ros::init(argc,argv,"node2");
    ros::NodeHandle n;
    
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("autonomy",100);
    ros::Rate loop_rate(1);
    
    while (ros::ok())
    {
        
        std_msgs::String msg;
        std::stringstream ss;
        ss<<"Fueled By Autonomy";
        msg.data=ss.str();
        
        chatter_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
