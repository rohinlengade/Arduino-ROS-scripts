
// ROS Arduino interfacing for Amazon vacuum suction cups end effector
// Commands to execute in terminals (3 seperate terminals or 3 tabs)
// rosrun rosserial_python serial_node.py
// rostopic echo /state

// To turn the Vacuum ON and OFF
// rostopic pub Vacuum std_msgs/Empty --once
// rostopic pub Air std_msgs/Empty --once

// Make necessary imports
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

// Define parameters
const int rpin_vac = 9; // vacuum valve
const int rpin_air = 8; // Vent valve
String usrIP; // user input as string




// Instantiate the node handle
ros::NodeHandle nh;

// Publisher
std_msgs::String ValState;
ros::Publisher ValveState("state", &ValState);

char VacState[11] = "Vacuum ON!";
char AirState[12] = "Vacuum OFF!";

// Callback functions
// Vacuum valve
void VacValve(const std_msgs::Empty& toggle_msg) {
  digitalWrite(rpin_vac, HIGH);
  digitalWrite(rpin_air, HIGH);
  delay(500);
  Serial.println("Actuating vacuum ON");
  digitalWrite(rpin_vac, LOW);
  digitalWrite(rpin_air, HIGH);
  ValState.data = VacState;
}
// Air valve
void AirValve(const std_msgs::Empty& toggle_msg) {
  digitalWrite(rpin_vac, HIGH);
  digitalWrite(rpin_air, HIGH);
  delay(500);
  Serial.println("Actuating vacuum ON");
  digitalWrite(rpin_vac, HIGH);
  digitalWrite(rpin_air, LOW);
  delay(1000);
  digitalWrite(rpin_vac, HIGH);
  digitalWrite(rpin_air, HIGH);
  ValState.data = AirState;
}

// Subscriber
ros::Subscriber<std_msgs::Empty>Vac("Vacuum", &VacValve);
ros::Subscriber<std_msgs::Empty>Air("Air", &AirValve);



void setup() {
  // put your setup code here, to run once:

  // Define pin mode
  pinMode(rpin_vac, OUTPUT);
  pinMode(rpin_air, OUTPUT);

  digitalWrite(rpin_vac, HIGH);
  digitalWrite(rpin_air, HIGH);

  // Initialize ROS stuff
  nh.initNode();  
  nh.subscribe(Vac);
  nh.subscribe(Air);
  nh.advertise(ValveState);

}

void loop() {
  // put your main code here, to run repeatedly:

  /*// Ensure both valves are closed
  digitalWrite(rpin_vac, HIGH);
  digitalWrite(rpin_air, HIGH);

  Serial.println("Enter 1 to turn ON and 0 to tunr OFF");

  while(Serial.available() == 0) {}
  usrIP = Serial.readString();

  if (usrIP == '1') {
     //Ensure both valves are closed and actuate vacuum valve
    digitalWrite(rpin_vac, HIGH);
    digitalWrite(rpin_air, HIGH);
    delay(500);
    Serial.println("Actuating vacuum ON");
    digitalWrite(rpin_vac, LOW);
    digitalWrite(rpin_air, HIGH);
  }
  else if (usrIP == '0') {
    // Ensure both valves are closed and actuate air valve
    digitalWrite(rpin_vac, HIGH);
    digitalWrite(rpin_air, HIGH);
    delay(500);
    Serial.println("Actuating vacuum OFF");
    digitalWrite(rpin_vac, HIGH);
    digitalWrite(rpin_air, LOW);
  }
  else {
    // Ensure both valves are closed
    Serial.println("Invalid command");
    digitalWrite(rpin_vac, HIGH);
    digitalWrite(rpin_air, HIGH);
  }*/

  ValveState.publish( &ValState);
  nh.spinOnce();
  delay(1);

}
