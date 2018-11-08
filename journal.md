# Journal

## Monday November 5

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

## Tuesday November 6

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
    identity="the_netid"                  <<<<<<<<<<<<<<change this     
    password=hash:the_hashed_password     <<<<<<<<<<<<<<change     
		this
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

1.  git clone https://github.com/nikmart/interaction-engine  
1.  upload the helloYouSketch.ino you your Arduino   

1.1. do this on laptop rather than try to get arduino running on rpi

1. install node

    sudo apt-get install node

1. run server, using correct port

    node server.js /dev/ttyACM0 

1. failed. need to install nodejs and express i did both of these and i'm not sure which one privided the right thing

    curl -sL https://deb.nodesource.com/setup_11.x | sudo -E bash -
    wget https://nodejs.org/dist/v10.13.0/node-v10.13.0-linux-armv7l.tar.xz

1. For some reason 

    /usr/sbin/node: No such file or directory

		but node is correctly installed in /usr/bin so be explicit

   /usr/bin/node server.js /dev/ttyACM0


1. and now can visit from my phone and turn led on and off!

		10.225.41.191:8000

1. So, what remains to do?


1.1. either get arduino to talk to motor controller, or get rpi to talk
directly to motor controller

1.1. modify html code to have four buttons for navigation 

1.1. if we use arduino, create rpi/arduino protocol

1.1. 




## Thursday November 8

Aaron suggests

	Super easy to install: 

	clone here: https://github.com/log0/video_streaming_with_flask_example 
	on command line install the requirements:

    pip install opencv-python
    pip install flask


	Then follow the instructions in the readme for the repo.

many problems so I tried installing opencv from here

	https://www.pyimagesearch.com/2015/02/23/install-opencv-and-python-on-your-raspberry-pi-2-and-b/

got as far as the make which failed but then tried to install opencv again

	sudo apt-get install python-opencv
  153  sudo apt-get install python-scipy
  154  sudo apt-get install ipython

that was no use 

	pip install flask
	git clone https://github.com/log0/video_streaming_with_flask_example.git
	cd video_streaming_with_flask_example
	python main.py

	ImportError: No module named cv2

	sudo pip3 install opencv-python

that worked but 

	$ python main.py
		...
    import cv2
ImportError: No module named cv2
	$ python --version
		Python 2.7.13

Aaron pointed out that there are different instructions depending on which
version of Rasperian is installed.

cat /etc/os-release
	
	VERSION="9 (stretch)"

so try this

	https://www.pyimagesearch.com/2017/09/04/raspbian-stretch-install-opencv-3-python-on-your-raspberry-pi/



..........


while waiting for that to install, i tried to prevent screen blaniking with

	vi /etc/lightdm/lightdm.conf 

and add

	[SeatDefaults]
	xserver-command=X -s 0 -dpms


while waiting install ngrok 
can't find my notes so must start over

	ngrok.
	sign in with my github account

	wget https://bin.equinox.io/c/4VmDzA7iaHb/ngrok-stable-linux-arm.zip
	unzip ngrok-stable-linux-arm.zip
	./ngrok

remember to run interaction_engine need to do this

		cd interaction-engine
    node server.js /dev/ttyACM0 

and to start ngrok do

		./ngrok http 8000

which starts a tunnel from http (port 80) to port 8000

now if i also want to allow ssh can i run two ngrok sessions?


