#include <SoftwareSerial.h>
SoftwareSerial ArduinoMaster(10, 11);
#define ledPin 12

String msg = "";
int ledVal = 0;
int sensorVal = 0, oldSensorVal = 0;
int buttonState = 0, oldButtonState = 0;

void setup() {
  Serial.begin(9600);
  ArduinoMaster.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  readMasterPort();
  convertMsgToCmd();
  
  
  if (sensorVal != oldSensorVal || buttonState != oldButtonState) {
    if(sensorVal < 20) {
      Serial.println("ALERT: BAIXA LUMINOSIDADE");
    }
    
    if(buttonState == 1){
      digitalWrite(ledPin, HIGH);
      return;
    }


    
    ledVal = map(sensorVal, 0, 1023, 0, 255);
    
    
    
    ArduinoMaster.print(ledVal);
    analogWrite(ledPin, ledVal);
    oldSensorVal = sensorVal;
  }
}

void readMasterPort() {
  while (ArduinoMaster.available()) {
    delay(10);
    if (ArduinoMaster.available() > 0) {
      char c = ArduinoMaster.read(); 
      msg += c; 
    }
  }
  ArduinoMaster.flush();
}

void convertMsgToCmd() {
  if (msg.length() > 0) {
    Serial.print("message length: ");
    Serial.println(msg.length());
    
    int separatorIndex = msg.indexOf(';'); 

    if (separatorIndex != -1) {
      
      String sensorString = msg.substring(0, separatorIndex);
      sensorVal = sensorString.toInt();
      
      String buttonString = msg.substring(separatorIndex + 1);
      buttonState = buttonString.toInt();

      Serial.print("Received Photoresistor: ");
      Serial.println(sensorVal);
      Serial.print("Received Button State: ");
      Serial.println(buttonState);
    }

    msg = ""; 
  }
}

