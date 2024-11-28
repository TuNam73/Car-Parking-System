#include <Arduino.h>
#include "secrets/wifi.h"
#include "wifi_connect.h"
#include <WiFiClientSecure.h>
#include "ca_cert_emqx.h"
#include "secrets/mqtt.h"
#include <PubSubClient.h>
#include "MQTT.h"
#include "LCD_DISPLAY.h"
#include <ESP32Servo.h>

Servo servo1; //Control entry
Servo servo2; //Control exit

//Pin of HC-SR04
const int trigPin1 = 2; //Entry
const int echoPin1 = 4; 
const int trigPin2 = 12; //Exit
const int echoPin2= 14;

//Pin of Servo
const int servoPin1 = 15; //Entry
const int servoPin2 = 13; //Exit

long duration; 
float distanceCm;
long current_time = 0;
long current_time_print = 0;
int vehicleCount = 0;
boolean check_open = false;

namespace
{
    const char *ssid = WiFiSecrets::ssid;
    const char *password = WiFiSecrets::pass;
    const char *client_id = (String("esp32-client") + WiFi.macAddress()).c_str();

    WiFiClientSecure tlsClient;
    PubSubClient mqttClient(tlsClient);

    const char *vehicle_count_topic = "home/vehicles_count";

    const char *handle_entry_topic  = "home/entry";
    const char *handle_exit_topic   = "home/exit";
}


float Read_HC_SR04(const int trigPin, const int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void handleDoor(Servo& servo, const int trigPin, const int echoPin, int directCount) {
  static int previousAngle1 = -1;
  static int previousAngle2 = -1;
  static unsigned long openTime1 = 0; 
  static unsigned long openTime2 = 0; 

  float distanceCm = Read_HC_SR04(trigPin, echoPin);

  int& previousAngle = (&servo == &servo1) ? previousAngle1 : previousAngle2;
  unsigned long& openTime = (&servo == &servo1) ? openTime1 : openTime2;
  const char* door = (&servo == &servo1) ? "First" : "Second";
  const char* handle_door_topic = (&servo == &servo1) ? handle_entry_topic : handle_exit_topic;

  // Phat hien co xe 
  if (distanceCm > 0 && distanceCm <= 15) {
    if (previousAngle != 90) {
      servo.write(90);
      previousAngle = 90;
      vehicleCount += directCount;
      Serial.print("Vehicle Count: ");
      Serial.println(vehicleCount);
      check_open = true;
      openTime = millis();

      mqttClient.publish(vehicle_count_topic, String(vehicleCount).c_str(), false);
      mqttClient.publish(handle_door_topic, String(check_open).c_str(), false);

    } 
    //Truong hop xe 2 di ngay sau xe 1 khi cua van mo
    else if (previousAngle == 90 && millis() - openTime >= 5000) {
      openTime = millis();
      vehicleCount += directCount; 
      Serial.print("New Vehicle Detected. Vehicle Count: ");
      Serial.println(vehicleCount);

      mqttClient.publish(vehicle_count_topic, String(vehicleCount).c_str(), false);
      mqttClient.publish(handle_door_topic, String(check_open).c_str(), false);

    }
    if (millis() - current_time_print >= 2000) {
      current_time_print = millis();
      Serial.print("---OPEN----the ");
      Serial.print(door);
      Serial.println("door"); 
    }
  }

  //Close door
  if (previousAngle == 90 && (millis() - openTime >= 10000)) {
    servo.write(180);
    previousAngle = 180;
    check_open = false;

    mqttClient.publish(handle_door_topic, String(check_open).c_str(), false);

    Serial.print("---CLOSE---the ");
    Serial.print(door);
    Serial.println("door");
  }
}

void statusDoor(Servo& servo1, const int trigPin1, const int echoPin1, int directCount1,
                Servo& servo2, const int trigPin2, const int echoPin2, int directCount2){

  handleDoor(servo1, trigPin1, echoPin1, 1);
  handleDoor(servo2, trigPin2, echoPin2, -1);
}

void mqttCallback(char *topic, uint8_t *payload, unsigned int length)
{
  char message[length+1];
  for (unsigned int i = 0; i < length; i++) {
    message[i] = (char) payload[i];
  }
  message[length] = '\0';

  if (strcmp(topic, handle_entry_topic) == 0) {
    if (String(message) == "true") {
      Serial.println("Open command received");
      servo1.write(90);
    }  
    else if (String(message) == "false") {
      Serial.println("Close command received ");
      servo1.write(180);
    }
  }

  else if (strcmp(topic, handle_exit_topic) == 0){
    if (String(message) == "true") {
      Serial.println("Open command received");
      servo2.write(90);
    }
    else if (String(message) == "false"){
      Serial.println("Close command received");
      servo2.write(180);
    }
  }
}


void setup() {
  Serial.begin(115200); // Starts the serial communication
  delay(10);
  setup_wifi(ssid, password); 
  tlsClient.setCACert(ca_cert); 
  mqttClient.setCallback(mqttCallback);
  mqttClient.setServer(EMQX::broker, EMQX::port);
  //Set up pin of HC-SR04: trig:out, echo:in
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT); 
  //init lcd
  lcd.init();                     
  lcd.backlight();
  lcd.setContrast(80);
  //attach servo
  servo1.attach(servoPin1, 500, 2400);
  servo2.attach(servoPin2, 500, 2400);
}

void loop() {
  MQTT::reconnect(mqttClient, client_id, EMQX::username, EMQX::password, handle_entry_topic, handle_exit_topic);
  mqttClient.loop();
  statusDoor(servo1, trigPin1, echoPin1, 1,
             servo2, trigPin2, echoPin2, -1);
  LCD_display::LCD_display();
}
