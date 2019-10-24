# Robot Remote
A simple bot that can be controlled via a mobile app.

## Components List
| Quantity      | Component                | 
| ------------- |:------------------------:|
| 2             | DC Motor   | 
| 1             | NodeMCU v1.0              | 
| 1             | L298N H-Bridge      | 
| 1             | Tank Chasis              | 
| 1             | Power Supply              | 

## Wired Diagram
![alt text](https://github.com/JACTheCreator/RobotRemote/blob/master/Robot/wire%20diagram/wire%20diagram.png
 "Wired Diagram")
 
## How Does The Communication work between The Mobile App and Bot?
 When the bot is powered, it will create an Access Point named **RemoteFalcon**. With the Access Point established, 
 the bot will now be able to receive POST request on URL: 198.168.4.1:80/move to move the bot in a desired direction.
 The Mobile App makes a POST Request to the URL above with following JSON body to make the bot move:
 
 #### FORWARD
 ```JSON
{
  "direction": "FORWARD",
  "speed": 255
}
```

 #### BACK
 ```JSON
{
  "direction": "BACK",
  "speed": 255
}
```

 #### LEFT
 ```JSON
{
  "direction": "LEFT",
  "speed": 255
}
```

#### RIGHT
```JSON
{
  "direction": "RIGHT",
  "speed": 255
}
```

#### STOP
```JSON
{
  "direction": "STOP",
}
```

#### NB: Please not that the **SPEED** of the bot is a values between **0 and 255**. The speed provided of the JSON is also **optional**. Everything in the JSON is case sensitivity..
