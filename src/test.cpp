#include <iostream>
#include <fstream>

#include "constants.h"
#include "object_simulator.h"

#include <ros/ros.h>
#include <string>

#include <geometry_msgs/PoseStamped.h>

#include <wrappers/matrix/matrix_wrapper.h>
#include <wrappers/matrix/vector_wrapper.h>

using namespace MatrixWrapper;
using namespace BFL;
using namespace std;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test");
    ros::NodeHandle nh;
    ros::Publisher pose_pub = nh.advertise<geometry_msgs::PoseStamped>("/pose", 1);

    ObjectSimulator obj;
    geometry_msgs::PoseStamped msg;
    msg.header.seq = 0;
    ColumnVector input(INPUT_SIZE);
    input(1) = 0.01;
    input(2) = 0.01;
    input(3) = 0.01;

    ros::Rate loop_rate(30);
    while (ros::ok())
    {
      obj.Move(input);
      ColumnVector state(STATE_SIZE);
      state = obj.GetState();
      msg.pose.position.x = state(1);
      msg.pose.position.y = state(2);
      msg.pose.position.z = state(3);
      msg.header.stamp = ros::Time::now();

      pose_pub.publish(msg);
      ros::spinOnce();
      loop_rate.sleep();
      msg.header.seq++;
    }
    return 0;

}
