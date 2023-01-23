/*
  Modbus RTU Server LED

  This sketch creates a Modbus RTU Server with a simulated coil.
  The value of the simulated coil is set on the LED

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the Modbus RTU server
     - Y connected to A/Y of the Modbus RTU client
     - Z connected to B/Z of the Modbus RTU client
     - Jumper positions
       - FULL set to OFF
       - Z \/\/ Y set to OFF

*/

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

//const int ledPin = LED_BUILTIN;
#define ledPin 9
#define ledPin1 10
#define temperature A0
#define humidity A1
#define moisture A2


void setup() {
  Serial.begin(9600);

  Serial.println("Modbus RTU Server LED");

  // start the Modbus RTU server, with (slave) id 1
  if (!ModbusRTUServer.begin(1, 9600)) {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }

  // configure the LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);
  // configure a two  coils at address 0x00
  ModbusRTUServer.configureCoils(0x00, 2);
  //configure 5 holding registers at addres 0
  ModbusRTUServer.configureHoldingRegisters(0x00,5);
}

void loop() {
  // poll for Modbus RTU requests
  ModbusRTUServer.poll();

  // read the current value of the coil
  int coilValue = ModbusRTUServer.coilRead(0x00);
  int coilValue1 = ModbusRTUServer.coilRead(0x01);

  //read holding registers 
  ModbusRTUServer.holdingRegisterWrite(0x00,analogRead(temperature));
  ModbusRTUServer.holdingRegisterWrite(0x01,analogRead(humidity));
  ModbusRTUServer.holdingRegisterWrite(0x02,analogRead(moisture));
  
  if (coilValue) 
  {
    // coil value set, turn LED on
    digitalWrite(ledPin, HIGH);
  } else {
    // coild value clear, turn LED off
    digitalWrite(ledPin, LOW);
  }
  if (coilValue1) 
  {
    // coil value set, turn LED on
    digitalWrite(ledPin1, HIGH);
  } else {
    // coild value clear, turn LED off
    digitalWrite(ledPin1, LOW);
  }
}
