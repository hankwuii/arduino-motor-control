#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include "motor_server/mysrv.h"

ros::NodeHandle nh;
using motor_server::mysrv

ros::ServiceClient<mysrv::Request, mysrv::Response> client("mysrv_srv");

std_msgs::Int16 str_msg;
std_msgs::float32 int_msg;
ros::Publisher chatter("chatter", &str_msg);

const int stepPin = 5;
const int dirPin = 4;
const int enPin = 8;
int16 direction;
float32 angle;

void setup() {
  nh.initNode();
  nh.ServiceClient(client);
  nh.advertise(chatter);

  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
}

void loop() {
  mysrv::Request req;
  mysrv::Response res;
  client.call(req, res);
  
  digitalWrite(dirPin,HIGH); //CW
  
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(1000);
  }
  delay(1000);
}
