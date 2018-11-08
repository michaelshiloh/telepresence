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

