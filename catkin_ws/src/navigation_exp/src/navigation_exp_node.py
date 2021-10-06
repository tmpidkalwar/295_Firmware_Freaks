#!/usr/bin/python
import time
import serial

from geometry_msgs.msg import Twist

import rospy
import math
import struct
import string

print("\n initializing serial port")
serial_port = serial.Serial(
    port="/dev/ttyTHS2",
    baudrate=115200,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
)
# Wait a second to let the port initialize
time.sleep(1)

class navigation_exp_node:
    def __init__(self):
        print("\n\nInitializing Velocity transmitter\n\n")
        rospy.init_node('navigation_exp_node')
        rospy.Subscriber('/cmd_vel', Twist, callback=self.cmd_vel_callback)
        self.steering_angle = None
        self.desire_velocity = None
        rospy.spin()
        #while(1):
        #    serial_port.write("abc")
        #    time.sleep(1)

    def cmd_vel_callback(self, data):
        print(data.angular.z)
        print(data.linear.x)
        data.angular.z=10
        data.linear.x=10
        self.steering_angle =  data.angular.z
        self.desire_velocity = data.linear.x * 2.237
        self.steering_angle=round(self.steering_angle)
        self.desire_velocity=round(self.desire_velocity)
        #print(serial_port.read())
        string = b''
        values=(self.steering_angle,self.desire_velocity)
        for i in values:
            string += struct.pack('!B',i)

        serial_port.write(string)




if __name__ == "__main__":
    try:
        navigation_exp_node()
    except rospy.ROSInterruptException:
        pass
