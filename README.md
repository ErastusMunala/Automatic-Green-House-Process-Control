# MOBIUS
 open serial communication protocol
How the system works:

The system has a master(arduino uno) which communicates with the ESP8266(Node MCU) serially. the ESP sends the values to the server where it is retrieved by Visual Basic with a GUI
the master has an RS485 MODBUS chip. each slave has an ATmega 328 and an RS485 chip. so master RS485 gives the slave RS485 instructions to communicate with the ATmega 328 and obtain the values from the sensors and instructions to also switch ON/OFF the fan or the motor(pump).
The GUI has been developed using Visual Basic
Created by: Erastus Munala, @munalaerastus@gmail.com
Date: 22/7/2019
