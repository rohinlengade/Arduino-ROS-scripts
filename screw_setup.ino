#include <ros.h>

//Arduino ROS code to control screwdriving set-up

//Note: The set-up uses two actuators that needs to be swapped depending on the inclination required

// To-Do?: Can we have ROS commands an Serial Monitor commands in the same file???
// To-Do?: Experiment and adjust the delays

//--------------------------------------------------------------------------------------------------

//Make necessary imports
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

//Define parameters
const int rpin1 = 2;
const int rpin2 = 3;
const int rpin3 = 4;
const int rpin4 = 5;
String usrIP;

//--------------------------------------------------------------------------------------------------

//Instantiate node handle
ros::NodeHandle nh;

//Publisher
std_msgs::String ActState;
ros::Publisher ActuatorState("state", &ActState);

char sm0[10] = "0 degrees";
char sm30[11] = "30 degrees";
char bg60[11] = "60 degrees";
char bg90[11] = "90 degrees";
char bg120[12] = "120 degrees";

//callback function

//Zero degrees
void s0(const std_msgs::Empty& toggle_msg) {
  digitalWrite(rpin1, LOW);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, LOW);
  digitalWrite(rpin4, HIGH);
  delay(6000);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);
  ActState.data = sm0;
}
//Thirty degrees
void s30(const std_msgs::Empty& toggle_msg) {
  digitalWrite(rpin1, LOW);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, LOW);
  digitalWrite(rpin4, HIGH);
  delay(6000);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);
  delay(500);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, LOW);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, LOW);
  delay(2000);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);
  ActState.data = sm30;
}
//Sixty degrees
void b60(const std_msgs::Empty& toggle_msg) {
  digitalWrite(rpin1, LOW);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, LOW);
  digitalWrite(rpin4, HIGH);
  delay(6000);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);
  delay(500);
  ActState.data = bg60;
}
//Ninety degrees
void b90(const std_msgs::Empty& toggle_msg) {
  digitalWrite(rpin1, LOW);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, LOW);
  digitalWrite(rpin4, HIGH);
  delay(6000);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);
  delay(500);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, LOW);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, LOW);
  delay(2000);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);
  ActState.data = bg90;
}
//One-Twenty degrees
void b120(const std_msgs::Empty& toggle_msg) {
  digitalWrite(rpin1, LOW);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, LOW);
  digitalWrite(rpin4, HIGH);
  delay(6000);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);
  delay(500);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, LOW);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, LOW);
  delay(4000);
  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);
  ActState.data = bg120;
}

//subscriber
ros::Subscriber<std_msgs::Empty>sa0("Zero degrees", &s0);
ros::Subscriber<std_msgs::Empty>sa30("Thirty degrees", &s30);
ros::Subscriber<std_msgs::Empty>ba60("Sixty degrees", &b60);
ros::Subscriber<std_msgs::Empty>ba90("Ninety degrees", &b90);
ros::Subscriber<std_msgs::Empty>ba120("One-Twenty degrees", &b120);

//--------------------------------------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:

  //Define PinMode
  pinMode(rpin1, OUTPUT);
  pinMode(rpin2, OUTPUT);
  pinMode(rpin3, OUTPUT);
  pinMode(rpin4, OUTPUT);

  digitalWrite(rpin1, HIGH);
  digitalWrite(rpin2, HIGH);
  digitalWrite(rpin3, HIGH);
  digitalWrite(rpin4, HIGH);

  //Initialize ROS stuff
  nh.initNode();
  nh.subscribe(sa0);
  nh.subscribe(sa30);
  nh.subscribe(ba60);
  nh.subscribe(ba90);
  nh.subscribe(ba120);
  nh.advertise(ActuatorState);
}

void loop() {
  // put your main code here, to run repeatedly:

  ActuatorState.publish( &ActState);
  nh.spinOnce();
  delay(1);
}
