#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc,char** argv)
{
    ros::init(argc,argv,"node1");
    ros::NodeHandle n;
    
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("team_abhiyaan",100);
    ros::Rate loop_rate(1);
    
    while (ros::ok())
    {
        
        std_msgs::String msg;
        std::stringstream ss;
        ss<<"Team Abhiyaan: ";
        msg.data=ss.str();
        
        chatter_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}