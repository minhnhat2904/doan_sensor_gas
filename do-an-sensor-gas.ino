#include <EEPROM.h>
#include <SoftwareSerial.h>


#define DIGITAL_PIN_INPUT_GAS_STATUS 8  
#define ANALOG_PIN_INPUT_GAS_AMOUNT  A0  
#define DIGITAL_PIN_OUTPUT_BELL_RING  11
#define DIGITAL_PIN_OUTPUT_FAN 13 

const int COMMAND_ON = 49;
const int COMMAND_OFF = 48;

bool bellAlreadyRinging = false;

int gasAmount ;

void setup() {
  Serial.begin(9600); 
  pinMode(DIGITAL_PIN_INPUT_GAS_STATUS, INPUT);
  pinMode(DIGITAL_PIN_OUTPUT_FAN, OUTPUT);
  pinMode(DIGITAL_PIN_OUTPUT_BELL_RING, OUTPUT);
}

void loop() {
  sendGasValueThroughSerial();
  readIncomingSerialMessage();
  
  if(gasAmount >= 400){
    digitalWrite(DIGITAL_PIN_OUTPUT_FAN,HIGH);
  } else{
    digitalWrite(DIGITAL_PIN_OUTPUT_FAN,LOW);
  }
  delay(1500); 
}

void sendGasValueThroughSerial(){
  gasAmount = analogRead(ANALOG_PIN_INPUT_GAS_AMOUNT);
  Serial.println(gasAmount);
}

void readIncomingSerialMessage(){
  if (Serial.available()) {
    int inByte = Serial.read();
    if(inByte == COMMAND_ON && bellAlreadyRinging == false){
      turnOnBell();
      bellAlreadyRinging = true;
    }
    if(inByte == COMMAND_OFF && bellAlreadyRinging == true){
      turnOffBell();
      bellAlreadyRinging = false;
    }
  }
}

void turnOnBell(){
  digitalWrite(DIGITAL_PIN_OUTPUT_BELL_RING,HIGH);
}

void turnOffBell(){
  digitalWrite(DIGITAL_PIN_OUTPUT_BELL_RING,LOW);
}
