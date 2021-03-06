# Journal

## Monday November 5 2018

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

## Tuesday November 6 2018

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


## Thursday November 8 2018

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

it finished successfully!

ok, now

    cd video_streaming_with_flask_example/
		pip install flask
		python main.py

damn!

		ImportError: No module named cv2

and indeed, it fails the test at the end of the install:

		pi@raspberrypi:~ $ source ~/.profile
		pi@raspberrypi:~ $ workon cv2
		(cv2) pi@raspberrypi:~ $ python
		Python 2.7.13 (default, Sep 26 2018, 18:42:22)
		[GCC 6.3.0 20170516] on linux2
		Type "help", "copyright", "credits" or "license" for more information.
		>>> import cv2
		Traceback (most recent call last):
			File "<stdin>", line 1, in <module>
		ImportError: No module named cv2

just to be sure

    ls -l /usr/local/lib/python2.7/site-packages/cv2.so

yes it's real

this helped

		export PYTHONPATH=/usr/local/lib/python2.7/site-packages:$PYTHONPATH

Oh! It works!

		pi@raspberrypi:~/video_streaming_with_flask_example $ python main.py 
		 * Serving Flask app "main" (lazy loading)
		 * Environment: production
			 WARNING: Do not use the development server in a production environment.
			 Use a production WSGI server instead.
		 * Debug mode: on
		 * Running on http://0.0.0.0:5000/ (Press CTRL+C to quit)
		 * Restarting with stat
		 * Debugger is active!
		 * Debugger PIN: 264-815-227
		10.225.50.110 - - [08/Nov/2018 08:23:16] "GET / HTTP/1.1" 200 -
		10.225.50.110 - - [08/Nov/2018 08:23:16] "GET /video_feed HTTP/1.1" 200 -
		10.225.50.110 - - [08/Nov/2018 08:23:17] "GET /favicon.ico HTTP/1.1" 404 -


so then I just browse to the rpi (10.225.41.191) at port 5000

	10.225.41.191:5000 and there is the video!

this is with a webcam. It does not like the pi camera. leave this for later.


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


## Friday November 9 2018

moved python/flask streaming webcam to port 80. this will allow ngrok to
function. procedure is described in "procedures.md"

added a button, although it doesn't do anything yet. this was simply
adding this to the body in templates/index.html

		<button>Left</button>

now I need to figure out how to call a function

It looks like this line does that:

	<button onclick="servos.move('T', -10)">Up</button>

and then there is a script below. I'm not sure how much I need so let's use it
all:

	<script>
		var servos;
		$( document ).ready(function() {
			servos = moveServos();
		});
		function moveServos() {
			// Store some settings, adjust to suit
			var panPos = 70, 
				tiltPos = 90, 
				tiltMax = 170, 
				tiltMin = 45, 
				panMax = 170, 
				panMin = 20;
			return {
				move:function(servo, adjustment) {
					var value;
					if(servo == 'P') {
						if(!((panPos >= panMax && adjustment > 0) || (panPos <= panMin && adjustment < 0))) {
							// Still within allowed range, "schedule" the movement
							panPos += adjustment;
						}
						value = panPos + 'P';
					}
					else if(servo == 'T') {
						if(!((tiltPos >= tiltMax && adjustment > 0) || (tiltPos <= tiltMin && adjustment < 0))) {
							// Still within allowed range, "schedule" the movement
							tiltPos += adjustment;
						}
						value = tiltPos + 'T';
					}
					// Use AJAX to actually move the servos
					$.get('http://PI_IP_ADDRESS/servos.rpy?value=' + value);
				},
			}
		}
	</script>



.....

yet another attempt using 

	http://jamespoole.me/2016/04/29/web-controlled-robot-with-video-stream/

first had to get motion to work. that required changes to
/etc/motion/motion.conf 

I also did

	sudo systemctl enable motion

but I don't know if that was necessary. Next I did

	git clone https://github.com/JamesPoole/WebControlledRobot

that gives me buttons but no video.

got it working! See changes in procedures and actual files

## Saturday November 10 2018

bring up system and see if I can get multiple viewers of the video stream

motion should start automatically. which port?

	$ sudo netstat -alp | grep 8081
	unix  3      [ ]         STREAM     CONNECTED     8081     384/lightdm

well I don't know what that is but when I browse to 

	http://10.225.41.191:8081/

I get the video stream

so now let's see if I can browse from many places

well it's inconclusive. i could connect from many but it froze in all but the
first after awhile

now if i want to move that video stream to ngrok i need to put it on port 80.
where is that controlled?

	sudo vi /etc/motion/motion.conf
	sudo service motion stop
	sudo service motion start

interesting it's not working. so perhaps i shouldn't worry about that now 
put it back at 8081 and figure out ngrok - can fix that later.

ok next up: ngrok
actually next up: lunch
and perhaps i should do ngrok from home since my ccard is there

so next item was to bring up the other server automatically

    python app.py

now that's spitting out all kind of debugging so will that cause trouble? I
don't know. let's try the simple way by putting it into /etc/rc.local

    python /home/pi/WebControlledRobot/app.py

and this is on port 8001

why is it not stopping after the delay in arduino? with print i see i'm only
sending one char.

test using screen

	sudo apt-get install screen
	screen /dev/ttyACM0 9600

to exit screen

	<CTRL>A \

indeed after sending one char it stays on forever. why is that? isn't my
arduino code stopping after 30 msec? check the code. 

oh duh. I delay, but I don't stop:

	case 'E':
        turnLeft (80);
        delay(500);
        break;

my bad

## Sunday November 11 2018

today

1. remove the delay - that slows things down. if the robot goes wild, someone
	 has to flip the switch. possibly add an extension
2. return the reverse button
3. ngrok

also I notice the disk is filling. might be time to get rid of stuff, if I'm
sure we don't need it

removed some stuff got it from 80% down to 73%

removed delay, noticed that video feed is not running. wonder why. rebooted.

how to handle arduino coming up on different USB port?

oh did i remove the wrong video streaming stuff? No, that used the motion
packet. Is motion running? How can I tell?

	$ systemctl is-active motion
	active

also i keep getting logged out - what's up?

video works now but I didn't do anything

now run the python script -- it's ok

next, add reverse. added to index.html, now add to app.py


ok i'm confused. time to document the motion:

arduino:

	F = move Forward
	R = move Reverse
	E = turn lEft
	I = turn rIght
	anything else = stop

index.html

	1 = left
	2 = forward
	3 = right
	4 = reverse
	5 = stop

app.py

	1 = E
	2 = F
	3 = I
	4 = R
	else = S


ok it works -- quickly scp files and commit

save this to save time

	cd /home/michael/gits/mine/telepresence/src/WebControlledRobot
	scp pi@10.225.41.191:WebControlledRobot/app.py .
	scp pi@10.225.41.191:WebControlledRobot/templates/index.html templates

right-o. what was next?

1. test that it starts the programs automatically
2. ngrok
3. automatically find arduino usb port
4. center the stop and reverse buttons (low priority)
5. ask craig if can avoid redrawing screen after pressing a button

this seems to work but it's not in the running code yet:

	arduino_ports = [
			p.device
			for p in serial.tools.list_ports.comports()
			if 'Arduino' in p.description
	]

	def findArduino():
		if not arduino_ports:
			raise IOError("No Arduino found")
		if len(arduino_ports) > 1:
			warnings.warn('Multiple Arduinos found - using the first')
		print("found arduino at")
		print(arduino_ports[0])
		arduino = serial.Serial(arduino_ports[0])

rebooting to test if programs start automatically

yep it's fine

ok on to ngrok

1. i paid the $60 and upgraded
2. got my token, and ran this on the pi:

     ./ngrok authtoken 39BX6nY7cqFsyf53sHWyJ_4xNW8tFh8c1RpCjVB9bLX 

I think now I can automatically use ngrok with the custom domain

	./ngrok http -subdomain=robonica 80

which should tunnel port 80 (i.e. http) of robonica.ngrok.io to the robot at
port 80

(oh and by the way I need to move the python app to port 80 - that's in
app.py)

and if this works then start ngrok on boot 

oh duh i have the cardboard covering the camera...

uh oh ngrok tunnel doesn't pass the video feed...

I can create an ngrok config file to bring up multiple tunnels 
I think if I tunnel the video as well it should be OK BUT
I ngrok will only tunnel one of three protocols: tcp, http, and tls

but http will always look for port 80 and my image server can not be on port
80 because the web server is on that port and i can't have two servers on one
port

but ngrok does have an address field. how does it work?

now
			./ngrok http -subdomain=robonica 80
reports
			http://robonica.ngrok.io -> localhost:80
	

but i don't think that helps

ok forget ngrok

tinyurl was able map the internal ip address

	tinyurl.com/robonica

but the video feed dies sometimes. 

	systemctl is-active motion

shows it's active. let's try stopping and starting

	sudo service motion stop
	sudo service motion start

oh wait it's detecting and saving all motion! can prevent saving motion by
starting it wtih 

	motion -m

but how do I set that in the configuration file? perhaps this

	vi /etc/motion/motion.conf
	# target_dir /var/lib/motion
	target_dir /dev/null

restart service and see

	tail -f /var/log/motion/motion.log
	ls /var/lib/motion

so far so good. now let's see if it stays up longer.

so need to copy this config file back to git

	cd /home/michael/gits/mine/telepresence/src/WebControlledRobot
	scp pi@10.225.41.191:/etc/motion/motion.conf .
