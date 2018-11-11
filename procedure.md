# Procedure for creating the telepresence research platform 


### Install Rasperian 

### To get on a WPA WiFi network, follow
[these](https://jackbdu.wordpress.com/2017/04/01/interactive-media-arts-capstone-technical-documentation/)
instructions


### To blink an LED on Arduino via serial port from Raspberry Pi using Python

Put this in a python file e.g. testSerial.py

    import serial, time
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=.1)

    while True:
        print "On"
        arduino.write("H")
        time.sleep(1) 
        print "Off"
        arduino.write("L")
        time.sleep(1) 


### Install Interaction Engine (Thanks to Nik Martelaro!)

    git clone https://github.com/nikmart/interaction-engine.git


### To prevent screen blanking 

    vi /etc/lightdm/lightdm.conf 

and add

    [SeatDefaults]
    xserver-command=X -s 0 -dpms


### To install ngrok 

    wget https://bin.equinox.io/c/4VmDzA7iaHb/ngrok-stable-linux-arm.zip
    unzip ngrok-stable-linux-arm.zip

### to run ngrok

    ./ngrok http 8000

will create an http tunnel to this machine at port 8000 (must have a server
at this port). The URL for this tunnel will be displayed e.g.

    Forwarding                    http://28ca197e.ngrok.io -> localhost:8000

### To start the node server 

    cd interaction-engine
    node server.js /dev/ttyACM0 

### To Install the Video Streaming with Flask Example by Eric Chio

    git clone https://github.com/log0/video_streaming_with_flask_example.git

install opencv-python, which requires building from source according to

    https://www.pyimagesearch.com/2017/09/04/raspbian-stretch-install-opencv-3-python-on-your-raspberry-pi/

Note this is for Raspbian stretch. If you have other Raspbian, the same author
has written instructions for other versions.

How do you know what version of Raspbian you have?

    cat /etc/os-release

Step #4: Python 2.7 or Python 3?

I installed for python 2.7. How do you know what version of python you have?

    python --version

note that this build takes a good few hours. When finally it succeeds test the
build (again this is described in the steps) but I had to add an extra step:

    export PYTHONPATH=/usr/local/lib/python2.7/site-packages:$PYTHONPATH
		python
		import cv2

Now that you're done installing opencv-python, you can finish Eric's
instructions:

    pip install flask

and then run the video streaming example

		cd video_streaming_with_flask_example
    export PYTHONPATH=/usr/local/lib/python2.7/site-packages:$PYTHONPATH
		python main.py

This streams on port 5000 so browse there to see the video

#### To move stream video on port 80

		cd video_streaming_with_flask_example
		vi main.py

the last line says

    app.run(host='0.0.0.0', debug=True)

modify it to say

    app.run(host='0.0.0.0', port=80, debug=True)

Note that now you have to run as root:

		sudo python main.py

this looked great, but we couldn't figure out how to get 
buttons to respond, probably since the video stream is in a tight
while loop. (if we commented out the video while loop, buttons worked fine)
so instead we researched other webcams with controls and found James Poole's
[Raspberry Pi Web Controlled Robot With Video
Stream](http://jamespoole.me/2016/04/29/web-controlled-robot-with-video-stream/)
which worked, so see procedure below

### To install James Poole's
[Raspberry Pi Web Controlled Robot With Video
Stream](http://jamespoole.me/2016/04/29/web-controlled-robot-with-video-stream/)

Install motion the usual way

    sudo apt-get install motion

but I found it necessary to make the following changes to 

    /etc/motion/motion.conf

		$ diff stock_motion.conf modified_motion.conf 
		11c11
		< daemon off
		---
		> daemon on
		107c107
		< framerate 2
		---
		> framerate 90
		501c501
		< stream_maxrate 1
		---
		> stream_maxrate 100
		504c504
		< stream_localhost on
		---
		> stream_localhost off
		537c537
		< webcontrol_localhost on
		---
		> webcontrol_localhost off

Important! Turn off saving motion images or it will save every frame that
differs which is a lot :

	# target_dir /var/lib/motion
  target_dir /dev/null


and proceed with James' instructions. After cloning James' WebControlledRobot
repository,
we added sending a byte to the arduino whenever a button is pressed, in
app.py:

    import serial
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=.1)
    ...
    if changePin == 1:
			arduino.write("F")
    ...

finally, we followed Quintin change to index.html that will always use the local server ip fork [here](https://github.com/qbalsdon/WebControlledRobot/blob/feature/index_use_local_ip/templates/index.html)

