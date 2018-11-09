# Procedure for creating the telepresence research platform 


### Install Rasperian 

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

### to install video streaming


Install the Video Streaming with Flask Example by Eric Chio:

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
