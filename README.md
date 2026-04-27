# Fake Robot Mover (C++)

## Description
This is a ROS2 package that simulates a fake robot mover using publishers and subscribers.

## Features
- Publisher node (talker)
- Subscriber node (listener)
- Simple movement simulation

## Installation
```bash
cd ~/ros2_ws1
colcon build
source install/setup.bash

ros2 run fake_robot_mover talker
ros2 run fake_robot_mover listener
