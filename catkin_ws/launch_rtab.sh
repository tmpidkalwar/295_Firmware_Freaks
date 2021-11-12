#!/bin/bash
cd catkin_ws
source ./devel/setup.bash
sudo chmod 666 /dev/ttyTHS2
echo "localization set to $1"
roslaunch zed_wrapper zed.launch & sleep 6 &&roslaunch rtab_node zed_rtabmap.launch localization:=$1  & sleep 6 &&roslaunch navigation nav.launch && fg

