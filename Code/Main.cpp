#include <Servo.h>

// Define pins for sensors
#define MQ135_PIN A0
#define METAL_DETECTOR_PIN A1
#define PROXIMITY_SENSOR_PIN A3
#define MQ4_PIN A4
#define TRIG_PIN 2 // TRIG pin
#define ECHO_PIN 4 // ECHO pin

// Create Servo object
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int IR_sensor_val = 0;

void setup() {
  // Start the serial connection 
  Serial.begin(9600);

  // Attach the servo to pin
  servo1.attach(6);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(5);
  pinMode(6, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(5, INPUT);
//INPUTS DATA, GIVES DATA TO ARDUINO
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(METAL_DETECTOR_PIN, INPUT);
  pinMode(PROXIMITY_SENSOR_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);
  pinMode(MQ4_PIN, INPUT);
}

void loop() {

  // Read values from the sensors
  int mq4_val = analogRead(MQ4_PIN);
  int mq135_val = analogRead(MQ135_PIN);
  int metal_detector_val = digitalRead(METAL_DETECTOR_PIN);
  int proximity_sensor_val = digitalRead(PROXIMITY_SENSOR_PIN);
  int Ultrasonic_sensor_val = digitalRead(ECHO_PIN);
  //Sends a SonicBoom to Detect Objects
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  //Calculate the distance
  long duration = pulseIn(ECHO_PIN, HIGH);
  Ultrasonic_sensor_val = duration*0.034/2;

  if (Ultrasonic_sensor_val <= 8) {
    Serial.println(Ultrasonic_sensor_val);
  } else {
    Serial.println(Ultrasonic_sensor_val);
  

  delay(500);
}
  
  Serial.print("MQ135 Value: ");
  Serial.println(mq135_val);
  Serial.print("MQ4 Value: ");
  Serial.println(mq4_val);
  Serial.print("Metal Detector Value: ");
  Serial.println(metal_detector_val);
  Serial.print("Proximity Sensor Value: ");
  Serial.println(proximity_sensor_val);

  delay(500); 
//NON-BIODEGRADABLE  
  mq4_val = analogRead(A4);
  mq135_val = analogRead(A0);
  proximity_sensor_val = digitalRead(A3);
  metal_detector_val = digitalRead(A1);
  Ultrasonic_sensor_val = duration*0.034/2;
//Conditions
  if (Ultrasonic_sensor_val <= 20 && proximity_sensor_val == 0 && metal_detector_val == 1 ) {
    // NON-BIODEGRADABLE
    servo4.write(60);  // Open Servo1 
    delay(500);
    servo2.write(0);    
    servo3.write(0);    
    servo1.write(0);    
  } 
  else if (Ultrasonic_sensor_val <= 20 && proximity_sensor_val == 1 && metal_detector_val == 0 ) {
    //RECYCLABLE
    servo3.write(60);  // Open Servo3
    delay(500);
    servo1.write(0);    
    servo2.write(0);    
    servo4.write(0);    
  } 
else if (Ultrasonic_sensor_val <= 20 && proximity_sensor_val == 1 && metal_detector_val == 1 ) {
  //BIODEGRADABLE
    servo2.write(60);  // Open Servo2
    delay(500);
    servo1.write(0);     
    servo3.write(0);    
    servo4.write(0);    
    
  } 
  else {
    //Close all servos
    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    servo4.write(0);
  }

  delay(15);  // Delay for stability and to prevent rapid changes
}
