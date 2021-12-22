// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLPTOQ54hE"
#define BLYNK_DEVICE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "lLy4ErlBo0KE4zhOvMNXOCp5pJGOa0xE"

#include <Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Halo";
char pass[] = "12345qwert";

#define TRIG_PIN  13  // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN  12  // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
#define SERVO_PIN 14  // ESP32 pin GIOP26 connected to Servo Motor's pin
#define DISTANCE_jarak1  50 // centimeters
#define DISTANCE_jarak2  100
#define alarm 25
#define ledkuning 27 
#define ledmerah 26
#define ledhijau 23
Servo servo; // create servo object to control a servo

// The below are variables, which can be changed
float duration_us, distance_cm;

void setup() {
  Blynk.begin(auth, ssid, pass);
  Serial.begin (9600);       // initialize serial port
  pinMode(alarm, OUTPUT);
  pinMode(ledkuning, OUTPUT);
  pinMode(ledmerah, OUTPUT);
  pinMode(ledhijau, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT); // set ESP32 pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set ESP32 pin to input mode
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(0);
}

void loop() {
  Blynk.run();
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if (DISTANCE_jarak1 > distance_cm ){
    servo.write(180); // rotate servo motor to 90 degree
    digitalWrite(alarm,HIGH);
    digitalWrite(ledkuning, LOW);
    digitalWrite(ledmerah, HIGH);
    digitalWrite(ledhijau, LOW);
  }else if (DISTANCE_jarak2 > distance_cm){
    servo.write(90);
    digitalWrite(alarm,LOW);
    digitalWrite(ledmerah, LOW);
    digitalWrite(ledkuning, HIGH);
    digitalWrite(ledhijau, LOW);// rotate servo motor to 0 degree
  }else{
    servo.write(0);
    digitalWrite(alarm,LOW);
    digitalWrite(ledkuning, LOW);
    digitalWrite(ledmerah, LOW);
    digitalWrite(ledhijau, HIGH);
    }
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  Blynk.virtualWrite(V1, distance_cm);

  delay(500);
}
