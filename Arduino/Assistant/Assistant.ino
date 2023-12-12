#define BLYNK_TEMPLATE_ID "TMPL4zyq9qFHm"
#define BLYNK_TEMPLATE_NAME "Accelerometer"
#define BLYNK_AUTH_TOKEN "RQBEnlqqYWynaQH2jPpaPWp-mNiI156B"

#define BLYNK_PRINT Serial

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <BlynkSimpleMKR1000.h>

char auth[] = "RQBEnlqqYWynaQH2jPpaPWp-mNiI156B";
char ssid[] = "";
char pass[] = ""; 

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(0x53);

int sensorPin = A2;
int BPM;
unsigned long lastTime = 0;
unsigned int beats = 0;

void setup() {
  BPM=0;
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  if(!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while(1);
  }
}

void loop() {
  Blynk.run();
  
  sensors_event_t event;
  accel.getEvent(&event);
  
  Blynk.virtualWrite(V0, event.acceleration.x);  
  Blynk.virtualWrite(V1, event.acceleration.y);
  Blynk.virtualWrite(V2, event.acceleration.z);  
  if (abs(event.acceleration.x) > 9 || abs(event.acceleration.y) > 9 || (event.acceleration.z) > 9) {
    Blynk.virtualWrite(V3, "Patient has fallen!");
  }
  else {
    Blynk.virtualWrite(V3, "Patient is haapy!");
  }

  int sensorValue = analogRead(sensorPin);
//  Serial.println(sensorValue);
  if (sensorValue > 300) {
    beats++;
  }
  
  unsigned long currentTime = millis();

  if ((currentTime - lastTime) >= 15000) {
    int heartRate = beats * 4;
    Blynk.virtualWrite(V4, heartRate);
    Serial.println(heartRate);

    beats = 0;
    lastTime = currentTime;
  }

  delay(1000);
}
