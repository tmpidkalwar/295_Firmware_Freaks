#!/bin/bash
cd catkin_ws
source ./devel/setup.bash
sudo chmod 666 /dev/ttyTHS2
roslaunch zed_wrapper zed.launch & sleep 6 &&roslaunch navigation_exp nav.launch && fg

