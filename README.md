# MSE110 PROJECT VIDEOS

MSE 110, "Mechatronics Design 1", served as an intro to robotics and embedded software. The course consisted primarily of four projects conducted in groups of three. The robotics kit used was the LEGO MINDSTORMS EV3. Completed in my first term at SFU, this course was extremely useful towards gaining skills in group work and time management, and to scratch the surface of embedded software. 



# Project 1: Line Follower (ROBOTC)

The first project involved assembling and programming a robot to follow a line, using a PID (proportional, integral, and derivative functions) controller.

The task to be performed by the robot is described as following:

1) given an initial position, follow the line
2) if an obstacle (a plastic cube) is sensed by the robot to be within 10cm, to robot should stop and make an audible "beep" for two seconds
   
   If the line is green:
   a) the robot continues to move towards the object
   b) the robot picks up the object and moves it about 10cm away from the line
   c) the robot returns to the line and continues forward

   If the line is blue:
   a) the robot should make a 180 degree turn and return to its starting position



# Project 2: Line Follower (MicroPython)

The second project consisted of the same requirements of the first project, but written in MicroPython instead.



# Project 3: Noisy Barcode Reader (MATLAB and ROBOTC)

The third project involved re-assembling the robot to be able to scan a barcode (standard code 39), corresponding to a single ASCII alphabet character (A -> Z).

The task to be performed by the robot is described as following:

1) a light sensor attached to the robot scans the barcode
2) the sensor data is saved to a data-log
3) convert the data-log to a csv file
4) import the csv file to MATLAB
5) read and plot the values
6) using a MAA (moving average algorithm) from scratch, filter the "noisy" light sensor values
7) use a derivative function from scratch to detect edges in the plot (edges of the white/black regions in the barcode)
8) using the inbuilt function "Findpeaks", find the index of each start and end region in the barcode
9) once width and colour of each region is determined, create a lookup table for each corresponding ASCII character
10) display ASCII character in command window




# Project 4: Maze Solver (ROBOTC)

The fourth and final project required the robot to traverse a maze to find the "cheese", and then return home using the shortest path possible.
   
   
