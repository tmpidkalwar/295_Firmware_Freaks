#include "ros/ros.h"
#include <nav_msgs/Path.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>

void chatterCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{       
        ROS_INFO("I heard: X is %f, Y is %f\n", msg->pose.position.x, msg->pose.position.y);
}       

int main(int argc, char **argv)
{       
	ros::init(argc, argv, "listener");
        ros::NodeHandle n;
        ros::Subscriber sub = n.subscribe("pathPose", 1000, chatterCallback);
        ros::spin();
        return 0;
}
