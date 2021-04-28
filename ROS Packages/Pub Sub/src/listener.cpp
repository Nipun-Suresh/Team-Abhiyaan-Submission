/*

The listener is a subscriber node, that subscribes to the topics published by the other 2 nodes
Once the message is received, the strings are stored and appended to print final message

*/

#include "ros/ros.h"
#include "std_msgs/String.h"

char finalMsg[40] = {'\0'}; //to store final message

void callback1(const std_msgs::String::ConstPtr& msg) //for team abhiyaan topic
{
    std::strcpy(finalMsg,msg->data.c_str());    //message published by /team_abhiyaan topic
}
void callback2(const std_msgs::String::ConstPtr& msg) //for autonomy topic
{
    std::strcat(finalMsg,msg->data.c_str());    //message published by /autonomy topic is appended
    ROS_INFO("[%s]", finalMsg);
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"listener");
    ros::NodeHandle n;
    
    //subscriber objects created
    ros::Subscriber sub1 = n.subscribe<std_msgs::String>("team_abhiyaan",100,callback1);
    ros::Subscriber sub2 = n.subscribe<std_msgs::String>("autonomy",100,callback2);    
    ros::spin();

    return 0;
}
