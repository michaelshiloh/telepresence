High Priority

Mechanical

1. finish constructing platform  
1. attach all logic hardware:  
1.1. rpi  
1.1. camera (ideally mounted near screen)  
1.1. powered speaker  
1.1. microphone  
1.1. arduino  
1. enclosure for logic electronics
1. enclosure for motor controller
1. place to hold the batteries so they can be removed for charging

Wiring
1. logic hardware
1. power
1. power switches  
1.1. motor power  
1.1. arduino and display power   
1.1. rPi probably doesn't need a power switch because it will be on the portable USB charger  
1.1. Speaker power, unless there is a switch on the speaker or it's the same power as the arduino and display  

Power

1. power system
1.1. 12v gel cell for motors  
1.1. portable USB charger for rPI  
1.1. 9-12 v for display and arduino, either another gel cell or a portable USB charger with a 12V output  
1.1. whatever the speakers need, ideally the same gel cell or a portable USB charger as the arduino and display  

Software

1. write code
1.1. minimal viable project: simple web page allows users to navigate robot, no audio/video  
1.1. make the account with ngrok so that we can publish a permanent URL  

Time permitting

1. Add single direction audio/video, so a remote user can see and hear what the robot is seeing and hearing
1. next step: add the second direction, so the remote user can be seen on the robot's screen and heard on the speakers

nice to have

1. move wheels to the front and casters to the back so it doesn't wobble
1. monitor power and feed to arduino analog inputs to report to rPi

