import serial #Import Serial Library
from visual import * #Import all the vPython library
 
arduinoSerialData = serial.Serial('com7', 9600) #Create an object for the Serial port. Adjust 'com11' to whatever port your arduino is sending to.

gate_reference_1=box(length=10, height=4, width=2, color=color.red,material=materials.wood, pos=(0,0,0))
gate_reference_2=box(length=10, height=4, width=2, color=color.blue,material=materials.rough, pos=(10,0,2))
support_1=box(width=30, length=2, height=6, color=color.white, material=materials.wood, pos=(-6.2,-1,5))
support_1=box(width=30, length=2, height=6, color=color.white, material=materials.wood, pos=(16.2,-1,5))
floo=box(length=20, height=2, width=30, color=color.white, material=materials.wood, pos=(5,-3,5))
sensor_1=box(length=1, height=2, width=2, color=color.magenta,material=materials.rough, pos=(-3,-1,18))
sensor_2=box(length=1, height=2, width=2, color=color.magenta,material=materials.rough, pos=(-3,-1,15))
sensor_3=cylinder(radius=0.5, length=2,color=color.yellow,material=materials.rough, pos=(-3,-1.5,-2))

label(pos=(0,2,0), text='SUPPORT')
label(pos=(10,2,0), text='GATE')
label(pos=(-3,0,18), text='ULTRASONIC#1')
label(pos=(-3,0,15), text='ULTRASONIC#2')
label(pos=(-3,-1,-2), text='PHOTOELECTRIC SENSOR')

while (1==1):  #Create a loop that continues to read and display the data
    rate(20)#Tell vpython to run this loop 20 times a second
    if (arduinoSerialData.inWaiting()>0):  #Check to see if a data point is available on the serial port
        myData = arduinoSerialData.readline() #Read the distance measure as a string
        print myData #Print the measurement to confirm things are working
        distance = float(myData) #convert reading to a floating point number
        gate_reference_2.pos=(distance,0,2) #Change the length of your measuring rod to your last measurement
