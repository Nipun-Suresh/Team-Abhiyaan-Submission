#include "ros/ros.h"
#include "std_msgs/String.h"

char finalMsg[40] = {'\0'};

void callback1(const std_msgs::String::ConstPtr& msg) //for team abhiyaan topic
{
    std::strcpy(finalMsg,msg->data.c_str());
}
void callback2(const std_msgs::String::ConstPtr& msg) //for autonomy topic
{
    std::strcat(finalMsg,msg->data.c_str());
    ROS_INFO("[%s]", finalMsg);
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"node3");
    ros::NodeHandle n;
    
    ros::Subscriber sub1 = n.subscribe<std_msgs::String>("team_abhiyaan",100,callback1);
    ros::Subscriber sub2 = n.subscribe<std_msgs::String>("autonomy",100,callback2);    
    ros::spin();

    return 0;
}