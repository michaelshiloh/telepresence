# telepresence
A robotic telepresence research project


A simple motorized platform (which I'll call a "robot" here although it has no autonomy and I don't like using the word "robot" for a device with no autonomy) with an onboard Linux computer (Raspberry Pi) and bidirectional audio and video capabilities (screen/camera, loudspaker/microphone). 


The computer runs a web server. Remote visitors access the robot's URL (e.g. from a browser on their phone) and are are presented with a basic teleconferencing system: the image from the camera on the phone is visible on the screen of the robot, and the image from the camera on the robot is visible on the screen of the phone. Similarly with the audio. 


In addition, navigation buttons on the website (visible on the phone) allow the remote visitor to drive the robot around.


The purpose of this project is to create a simple telepresence platform that can be easily expanded by the Interactive Media community of the New York University Abu Dhabi, and indeed by any interested persons at NYUAD.


My hope is that by creating an accessible platform outside of traditional engineering laboratories the range of projects and applications may be expanded

Journal (maybe this will move elsewhere later)
______

Tuesday November 6

Easier! use the [interaction engine](https://github.com/nikmart/interaction-engine)

first, connect rpi to nyu network using [Jack's document](https://jackbdu.wordpress.com/2017/04/01/interactive-media-arts-capstone-technical-documentation/)  


1. Get the MD4 hash of the password by running the command below:  

    $ echo -n 'YOUR_REAL_PASSWORD' | iconv -t utf16le | openssl md4

1. Open wpa_supplicant.conf with your favorite text editor:

    $ sudo vi /etc/wpa_supplicant/wpa_supplicant.conf

1. Append the following text to the file:

    network={   
    ssid="nyu"   
    priority=1   
    proto=RSN   
    key_mgmt=WPA-EAP   
    pairwise=CCMP   
    auth_alg=OPEN   
    eap=PEAP   
    identity="the_netid"   
    password=hash:the_hashed_password   
    phase1="peaplabel=0"   
    phase2="auth=MSCHAPV2"   
    }  

1. Remember to run the following command to clean up history for security reason:

    $ history -w    
    $ history -d    



next, set up an ssh server on the pi so I don't need to type everything there

    Enter sudo raspi-config in a terminal window.  
    Select Interfacing Options.  
    Navigate to and select SSH.  
    Choose Yes.  
    Select Ok.  
    Choose Finish.  

now install interaction engine

1. 


______

Monday November 5

craig is using this
https://www.hackster.io/bportaluri/web-controlled-led-animations-with-raspberry-pi-and-arduino-112025
to create his alexa controlled neopixel displays. inside is a raspberry pi and
arduino, same as us. i took a look at the rpi software
(https://github.com/bportaluri/AlaWeb) and it's a python program running on
top of flask. flask is a super light weight web server framework. AlaWeb has
all this fancy stuff for controlling animated light displays, but it should be
possible to remove that and just use the framework to create navigation
buttons that will send the commands to arduino (forward, reverse, turn left,
turn right) which will then activate the motors appropriately. I'll look at
this further tomorrow.  ______
