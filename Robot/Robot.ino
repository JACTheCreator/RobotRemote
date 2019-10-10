#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

ESP8266WebServer server(80);

/***************************************
 *      Access Point Credentials       *
 ***************************************/
const char* ap_ssid = "RemoteFalcon";
const char* ap_password = "";
/***************************************
 ***************************************/
 
/***************************************
 *         MOTOR DECLARATIONS          *
 ***************************************/
const uint8_t LEFT_MOTOR_IN1 = D1;
const uint8_t LEFT_MOTOR_IN2 = D2;
const uint8_t LEFT_MOTOR_PWM = D0;

const uint8_t RIGHT_MOTOR_IN1 = D6;
const uint8_t RIGHT_MOTOR_IN2 = D7;
const uint8_t RIGHT_MOTOR_PWM = D5;
/***************************************
 ***************************************/

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  
  WiFi.softAP(ap_ssid, ap_password);
  
  server.on("/move", handleRobotMovement); 
  
  server.begin();

  /***************************************
   *               MOTOR                 *
   ***************************************/
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);

  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  /***************************************
   ***************************************/
}

void loop()
{
  server.handleClient();
}

void handleRobotMovement() 
{ 
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");

  /**
   *  Handling GET Request
   */
  if (server.hasArg("plain") == false)
  { 
    return;
  }

  /**
   *  Handling POST Request
   */
  String robotAction = server.arg("plain");
  Serial.println(robotAction);
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(robotAction);

  String direction = root["direction"].as<String>();
  uint8_t speed = root["speed"].as<uint8_t>();
  
  moveRobot(direction, speed);

  server.send(200, "application/json", "{\"msg\": \"Success\" }");
}

void moveRobot(String direction, uint8_t speed)
{
  setSpeed(speed);
  if(direction == "FORWARD")
  {
    forward();
    Serial.println("forward");
  }
  else if(direction == "REVERSE")
  {
    reverse();
    Serial.println("reverse");
  }
  else if(direction == "LEFT")
  {
    left();
    Serial.println("left");
  }
  else if(direction == "RIGHT")
  {
    right();
    Serial.println("right");
  }
  else if(direction == "STOP")
  {
    stop();
    Serial.println("stop");
  }
}

void forward()
{
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, HIGH);
  
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, HIGH);
}

void reverse()
{

  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);

  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}

void left()
{
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);

  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, HIGH);
}

void right()
{
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, HIGH);

  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}

void stop()
{
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);

  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
  
  setSpeed(0);
}       

void setSpeed(uint8_t speed)
{
 analogWrite(LEFT_MOTOR_PWM, speed);
 analogWrite(RIGHT_MOTOR_PWM, speed);
}   
