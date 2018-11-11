#######
# Author: James Poole
# Date: 23 April 2016
# jgaple@gmail.com
#
# app.py
#######

from flask import Flask, render_template, request, redirect, url_for, make_response
import motors
import RPi.GPIO as GPIO
import serial
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=.1)

GPIO.setmode(GPIO.BOARD) #set up GPIO

app = Flask(__name__) #set up flask server

#when the root IP is selected, return index.html page
@app.route('/')
def index():

	return render_template('index.html')

#receive which pin to change from the button press on index.html
#each button returns a number that triggers a command in this function
#
#Uses methods from motors.py to send commands to the GPIO to operate the motors
@app.route('/<changepin>', methods=['POST'])
def reroute(changepin):

	changePin = int(changepin) #cast changepin to an int

	if changePin == 1:
		arduino.write("F")
                print("sending F")
	elif changePin == 2:
		arduino.write("E")
                print("sending E")
	elif changePin == 3:
		arduino.write("I")
                print("sending I")
	elif changePin == 4:
		arduino.write("R")
                print("sending R")
	else:
		arduino.write("S")
                print("sending S")


	response = make_response(redirect(url_for('index')))
	return(response)

app.run(debug=True, host='0.0.0.0', port=8001) #set up the server in debug mode to the port 8000
