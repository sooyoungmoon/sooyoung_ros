
#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <std_msgs/String.h>
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Vector3Stamped.h"
#include "mavros_msgs/State.h"

int dest_x = 10;
int dest_y = 10;
int dest_z = 10;
int da = 15; // default altitude
//int phase; // phase of the UAV in the path

mavros_msgs::State current_state;

geometry_msgs::PoseStamped current_location;

// callback function definitions

void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

void pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
	current_location = *msg;
}

int main(int argc, char **argv) { 

  ros::init(argc, argv, "pub_setpoints_pos");
  ros::NodeHandle nh;
 
  // check for arguments (destination postion - lat, lon, alt
/*
  if (argc !=4)
  {
    printf("usage - <exe file name destination-lat destination-lon destination-alt ");
    return -1;
  }

  dest_x = atoi(argv[1]);

  dest_y = atoi(argv[2]);

  dest_z = atoi(argv[3]);
*/

  


  // publisher
   ros::Publisher pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);

  // subscriber
  ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
 
  ros::Subscriber pos_sub = nh.subscribe<geometry_msgs::PoseStamped>("mavros/position", 10, pose_cb);

  // set publishing rate

  ros::Rate rate(20.0);

  nh.setParam("default_altitude", da);

  // wait for FCU connection

  while (ros::ok() && current_state.connected)
  {
    ros::spinOnce();
    rate.sleep();
  }

  // message construction

  geometry_msgs::PoseStamped pose;

  pose.pose.position.x = dest_x;

  pose.pose.position.y = dest_y;

  pose.pose.position.z = dest_z;
    
 while (ros::ok())
 {

    pos_pub.publish(pose);
    ros::spinOnce();
    rate.sleep();
 
 }

 return 0; 
} 
