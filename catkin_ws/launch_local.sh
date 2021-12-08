#!/bin/bash
export DISPLAY=:0
cd catkin_ws
source ./devel/setup.bash
sudo chmod 666 /dev/ttyTHS0
roslaunch zed_wrapper zed.launch & sleep 6 &&roslaunch nav_pkg nav.launch && fg
