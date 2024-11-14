#include <SoftwareSerial.h>
SoftwareSerial ArduinoSlave(10, 11);

int sensorVal = 0, oldSensorVal = 0;
int buttonState = 0, oldButtonState = 0;

void setup() {
  Serial.begin(9600);
  ArduinoSlave.begin(9600);
  pinMode(A0, INPUT);  
  pinMode(3, INPUT);   
}

void loop() {
  sensorVal = analogRead(A0);
  buttonState = digitalRead(3);
  
  if (oldSensorVal != sensorVal || buttonState != oldButtonState) {
    Serial.println("MASTER SENDING");
    
    String dataToSend = String(sensorVal) + ";" + String(buttonState);
    ArduinoSlave.println(dataToSend);
    
    Serial.print("Photoresistor: ");
    Serial.println(sensorVal);
    Serial.print("Button: ");
    Serial.println(buttonState);

    oldSensorVal = sensorVal;
    oldButtonState = buttonState;
  }

  delay(500);  
}
