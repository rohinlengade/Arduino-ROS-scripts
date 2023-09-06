// Arduino ROS code to control heatgun for Yaskawa project

// Make the necessary imports
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

// Instantiate ROS handle node
ros::NodeHandle nh;

// Publisher
std_msgs::String OurGunState;
ros::Publisher gunState("state", &OurGunState);

char onState[20] = "The heat gun is ON!";
char offState[21] = "The heat gun is OFF!";

// Callback functions
void ON( const std_msgs::Empty& toggle_msg)
{
  digitalWrite(13, HIGH);
  OurGunState.data = onState;  
}
void OFF( const std_msgs::Empty& toggle_msg)
{
  digitalWrite(13, LOW);
  OurGunState.data = offState;
}

// Subscriber
ros::Subscriber<std_msgs::Empty> gunON("on", &ON);
ros::Subscriber<std_msgs::Empty> gunOFF("off", &OFF);

// Setup
void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(gunON);
  nh.subscribe(gunOFF);
  nh.advertise(gunState);
}

// Loop
void loop()
{
  gunState.publish( &OurGunState)
  nh.spinOnce();
  delay(1);
}