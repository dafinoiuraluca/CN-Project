#define BLYNK_TEMPLATE_ID "TMPL4pYwGO9gG"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "2_xB3r6D0SJ69pRPnMprFEVcpqvxyUok"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <BlynkSimpleStream.h>
#include <SoftwareSerial.h>

SoftwareSerial DebugSerial(2,3);

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup() {
  DebugSerial.begin(1200);
  Serial.begin(9600);
  Blynk.begin(Serial,BLYNK_AUTH_TOKEN);
//  DebugSerial.println("Blynk initialized");
  if (!accel.begin()) {
    DebugSerial.println("No valid sensor found");
    while (1);
  }
  DebugSerial.println("Sensor initialized");
}

void loop() {
  DebugSerial.println("Is running!");
  Blynk.run(); // Execute Blynk functions
  
  sensors_event_t event;
  accel.getEvent(&event);

  DebugSerial.print("X: ");
  DebugSerial.print(event.acceleration.x);
  DebugSerial.print(" Y: ");
  DebugSerial.print(event.acceleration.y);
  DebugSerial.print(" Z: ");
  DebugSerial.print(event.acceleration.z);
  DebugSerial.println(" m/s^2");

  Blynk.virtualWrite(A5, event.acceleration.x);
  Blynk.virtualWrite(A4, event.acceleration.y);
  Blynk.virtualWrite(V2, event.acceleration.z);

  delay(500);
}
