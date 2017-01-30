# Cost Effective Parking Gate Controller

This project emphasizes about a new approach in the field of parking gate system.
Atmel based microcontroller is used to control the whole operation. 
The new design eliminates the use of any physical devices, buttons and knobs to open the parking gate. 
The objective is to detect only the automobile and open the gate from inside the parking space and an IR remote is used to open the gate from outside. The system is designed using Arduino microcontroller embedded system and the design is done using its Integrated Development Environment and embedded C.

Components used:

System is designed to auto detect the car and open the sliding gate if the car is exiting from the parking lot.
Ultrasonic sensors are used to detect the car.
IR remote is used as the secondary input to open the gate.
Motor driver is used to run the motor which in turn moves the gate.
Through Beam sensor is used to detect the obstacles in the path of the gate.
OLED display is interfaced.

Working:

If the car is exiting from the parking space then it has to move in the region of the ultrasonic sensors for the detection of the car, two ultrasonic sensors are used for this design which can be modified.
When the ultrasonic sensors become active, a logic high signal is sent to the Microcontroller which generates a signal and sends it to the motor.
The gate opens.
If there is an obstacle and the gate is in closing position then, the gate opens upon the detection of the obstacle by the through beam sensor.
If the car is entering into the parking space then an IR remote is used to open the gate.

Tools used:

Arduino IDE is used.
VPython is used to simulate the design.
