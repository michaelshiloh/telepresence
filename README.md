# telepresence
A robotic telepresence research project


A simple motorized platform (which I'll call a "robot" here although it has no autonomy and I don't like using the word "robot" for a device with no autonomy) with an onboard Linux computer (Raspberry Pi) and bidirectional audio and video capabilities (screen/camera, loudspaker/microphone). 


The computer runs a web server. Remote visitors access the robot's URL (e.g. from a browser on their phone) and are are presented with a basic teleconferencing system: the image from the camera on the phone is visible on the screen of the robot, and the image from the camera on the robot is visible on the screen of the phone. Similarly with the audio. 


In addition, navigation buttons on the website (visible on the phone) allow the remote visitor to drive the robot around.


The purpose of this project is to create a simple telepresence platform that can be easily expanded by the Interactive Media community of the New York University Abu Dhabi, and indeed by any interested persons at NYUAD.


My hope is that by creating an accessible platform outside of traditional engineering laboratories the range of projects and applications may be expanded

Journal (maybe this will move elsewhere later)
______

Monday November 5

craig is using this https://www.hackster.io/bportaluri/web-controlled-led-animations-with-raspberry-pi-and-arduino-112025 to create his alexa controlled neopixel displays. inside is a raspberry pi and arduino, same as us. i took a look at the rpi software (https://github.com/bportaluri/AlaWeb) and it's a python program running on top of flask. flask is a super light weight web server framework. AlaWeb has all this fancy stuff for controlling animated light displays, but it should be possible to remove that and just use the framework to create navigation buttons that will send the commands to arduino (forward, reverse, turn left, turn right) which will then activate the motors appropriately. I'll look at this further tomorrow.
