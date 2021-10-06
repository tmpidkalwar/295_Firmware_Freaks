# 295_Firmware_Freaks

To launch navigation with only local rolling window map using zed point cloud
1. roslaunch zed_wrapper zed.launch
2. roslaunch navigation_exp nav.launch

To launch with both global(rtabmap) and local map(pointcloud)
1. roslaunch zed_wrapper zed.launch
2. roslaunch rtabmap_node zed_rtabmap.launch
3. roslaunch navigation nav.launch
