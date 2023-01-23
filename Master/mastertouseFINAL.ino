/*
  Modbus RTU Client Toggle

  This sketch toggles the coil of a Modbus RTU server connected via RS485
  on and off every second.

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the Modbus RTU server
     - Y connected to A/Y of the Modbus RTU server
     - Z connected to B/Z of the Modbus RTU server
     - Jumper positions
       - FULL set to OFF
       - Z \/\/ Y set to ON

  created 16 July 2018
  by Sandeep Mistry
*/

#include <ArduinoRS485.h>       // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>      //used for the modbus communication
#include <ArduinoJson.h>        // required to send data serially between the master and node mcu
#include <SoftwareSerial.h>     //we use software serial to communicate with the node mcu
SoftwareSerial s(10,11);        //We use 10, and 11 from master to D6 and D5 at the node MCU
  int pump1=0x00;
  int vent1=0x00;
  int pump2=0x00;
  int vent2=0x00;
  int pump3=0x00;
  int vent3=0x00;

void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  s.begin(9600);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);

 
  
  
  Serial.println("Modbus RTU Client Toggle"); //we print in serial and hence use serial monitor to view the process
  ModbusRTUClient.begin(9600);
  
  // start the Modbus RTU client
 /* if (!ModbusRTUClient.begin(9600)) 
  {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }*/
}

void loop()
{
   StaticJsonBuffer<1000> jsonBuffer; // for passing around and transmitting the information
   JsonObject& root = jsonBuffer.createObject();   //create json objects to send data

  //code

  

  
  
  
 /*// for (slave) id 1: write the value of 0x01, to the coil at address 0x00 
  if (!ModbusRTUClient.coilWrite(1, 0x00, 0x01))
  {
    Serial.print("Failed to write coil! ");
    Serial.println(ModbusRTUClient.lastError());
  }

  ModbusRTUClient.requestFrom(1, HOLDING_REGISTERS, 0x00, 3);  // for (slave) id 1: request values of the first 3 holding registers i.e from 0x00 to 3.
  while (ModbusRTUClient.available()) 
    {
      Serial.println(ModbusRTUClient.read());
     // Serial.print(' ');
    }

    //add code to read holding registers from the slaves and save in json buffer

  // wait for 1 second
  delay(1000);

  // for (slave) id 1: write the value of 0x00, to the coil at address 0x00 
  if (!ModbusRTUClient.coilWrite(1, 0x00, 0x00)) 
  {
    Serial.print("Failed to write coil! ");
    Serial.println(ModbusRTUClient.lastError());
  }

// for (slave) id 2: write the value of 0x00, to the coil at address 0x00 
  if (!ModbusRTUClient.coilWrite(2, 0x00, 0x00)) 
  {
    Serial.print("Failed to write coil! ");
    Serial.println(ModbusRTUClient.lastError());
  }
  // for (slave) id 3: write the value of 0x00, to the coil at address 0x00 
  if (!ModbusRTUClient.coilWrite(3, 0x00, 0x00)) 
  {
    Serial.print("Failed to write coil! ");
    Serial.println(ModbusRTUClient.lastError());
  }
  // wait for 1 second
  delay(1000);*/
  int tempg1=ModbusRTUClient.holdingRegisterRead(1,0x00);
  int humg1=ModbusRTUClient.holdingRegisterRead(1,0x01);
  int moistureg1=ModbusRTUClient.holdingRegisterRead(1,0x02);
  
  int tempg2=ModbusRTUClient.holdingRegisterRead(2,0x00);
  int humg2=ModbusRTUClient.holdingRegisterRead(2,0x01);
  int moistureg2=ModbusRTUClient.holdingRegisterRead(2,0x02);
  
  int tempg3=ModbusRTUClient.holdingRegisterRead(3,0x00);
  int humg3=ModbusRTUClient.holdingRegisterRead(3,0x01);
  int moistureg3=ModbusRTUClient.holdingRegisterRead(3,0x02);

  
  root["tempg1"] = tempg1;
  root["humg1"] = humg1;
  root["moistureg1"] = moistureg1;

  root["tempg2"] = tempg2;
  root["humg2"] = humg2;
  root["moistureg2"] = moistureg2;

  root["tempg3"] = tempg3;
  root["humg3"] = humg3;
  root["moistureg3"] = moistureg3;

  if(s.available()>0)
   {
    root.printTo(s);
   }
  
  if(digitalRead(3)==HIGH)
  pump1=0x01;
  else
  pump1=0x00;

  if(digitalRead(4)==HIGH)
  vent1=0x01;
  else
  vent1=0x00;

  if(digitalRead(5)==HIGH)
  pump2=0x01;
  else
  pump2=0x00;

  if(digitalRead(6)==HIGH)
  vent2=0x01;
  else
  vent2=0x00;

  if(digitalRead(7)==HIGH)
  pump3=0x01;
  else
  pump3=0x00;

  if(digitalRead(8)==HIGH)
  vent3=0x01;
  else
  vent3=0x00;

  

  
  // for (slave) id 1: write the value of 0x01, to the coil at address 0x00 

  ModbusRTUClient.coilWrite(1, 0x00, pump1);
  ModbusRTUClient.coilWrite(1, 0x01, vent1);
  ModbusRTUClient.coilWrite(2, 0x00, pump2);
  ModbusRTUClient.coilWrite(2, 0x01, vent2);
  ModbusRTUClient.coilWrite(3, 0x00, pump3);
  ModbusRTUClient.coilWrite(3, 0x01, vent3);

  
}
