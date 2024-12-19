#!/usr/bin/env pybricks-micropython


from pybricks.ev3devices import Motor, ColorSensor, UltrasonicSensor
from pybricks.parameters import Port
from pybricks.tools import wait
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile
from pybricks.hubs import EV3Brick
import time

ev3 = EV3Brick()


# Initialize the motors.
left_motor = Motor(Port.A)
right_motor = Motor(Port.B)

# Initialize the  sensor.
light_sensor = ColorSensor(Port.S3)
distance_sensor=UltrasonicSensor(Port.S2)



# Initialize the drive base.
robot = DriveBase(left_motor, right_motor, wheel_diameter=55.5, axle_track=104)


target_value = 22


DRIVE_SPEED = 80; 

error=0; 
integral=0;
lasterror=0; 
flag_dist=0;


kp=11.9;
kd=1.6;
ki=0.0000125;




while True:

    error = light_sensor.reflection() - target_value

    
    integral = error + integral;
    derivative = error - lasterror;
    steering_value=(kp * error) + (ki * integral) + (kd * derivative);
    
 
  
    robot.drive(DRIVE_SPEED, steering_value)
    lasterror=error;
    
  
        

    
    if(flag_dist==0):
        if(distance_sensor.distance()<=110):
            flag_dist=flag_dist+1;
            robot.turn(10)
            color=light_sensor.color();
            robot.drive(0,0)
            ev3.speaker.beep(frequency=100, duration=2000)
            wait(4)
            print(color)
            if(color==color.GREEN):    
                robot.turn(-10)
                robot.straight(100)
                wait(1000)
                robot.turn(45)
                robot.straight(120)
                robot.straight(-120)
                robot.turn(-45)
                error = light_sensor.reflection() - target_value 
                integral = error + integral;
                derivative = error - lasterror;
                steering_value=(kp * error) + (ki * integral) + (kd * derivative);
                robot.drive(DRIVE_SPEED, steering_value)
                lasterror=error;
                
                
            elif(color==color.BLACK):
                robot.straight(-16)
                robot.turn(136)
                wait(100)
               


