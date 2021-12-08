#!/bin/bash
export DISPLAY=:0
cd catkin_ws
source ./devel/setup.bash
sudo chmod 666 /dev/ttyTHS0
echo "localization set to $1"
roslaunch zed_wrapper zed.launch svo_file:=/home/freaks/recording3.svo  & sleep 6 &&roslaunch rtab_node zed_rtabmap.launch localization:=$1 rgbd_odometry:=$1  && fg  & sleep 6 &&roslaunch navig nav.launch && fg

