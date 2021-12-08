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
    port="/dev/ttyTHS0",
    baudrate=115200,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
)
# Wait a second to let the port initialize
time.sleep(1)

class nav_pkg_node:
    def __init__(self):
        print("\n\nInitializing Velocity transmitter\n\n")
        rospy.init_node('nav_pkg_node')
        rospy.Subscriber('/cmd_vel', Twist, callback=self.cmd_vel_callback)
        self.steering_angle = None
        self.desire_velocity = None
        rospy.spin()
        #while(1):
        #    serial_port.write("abc")
        #    time.sleep(1)

    def cmd_vel_callback(self, data):
        print("angular {0}".format(data.angular.z))
        print("linear {0}".format(data.linear.x))
        temp = 255
        self.steering_angle =  data.angular.z
	self.desire_velocity = data.linear.x
        self.steering_angle=(round(self.steering_angle,2)*100)+100
        self.desire_velocity=(round(self.desire_velocity,2)*100)+10
	print("angular_final {0}".format(self.steering_angle))
        print("linear_final {0}".format(self.desire_velocity))
        #print(serial_port.read())
        string = b''
        values=(temp,self.desire_velocity,self.steering_angle)
        for i in values:
            string += struct.pack('!B',i)

        serial_port.write(string)




if __name__ == "__main__":
    try:
        nav_pkg_node()
    except rospy.ROSInterruptException:
        pass
