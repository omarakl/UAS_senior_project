#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // creaing RF24 object and assigning CE and CSN pins to 9 and 10
const byte address[6] = "00001";  // unique address between transmitter and receiver

int joy_x_pin = A0; // X-axis pin
int joy_y_pin = A1; // Y-axis pin
int joy_x_pin_2 = A2; // X-axis pin of the new joystick
int joy_y_pin_2 = A3; // Y-axis pin of the new joystick

void setup() {
  Serial.begin(9600);  
  radio.begin();  // begin the operation of the chip (NRF24L01 module)
  radio.openWritingPipe(address); // open a pipe for writing
  radio.setPALevel(RF24_PA_MIN); // @ref RF24_PA_MIN (0) | -18 dBm | -6 dBm | -12 dBm |
  radio.stopListening(); // Stop listening for incoming messages, and switch to transmit mode.
}

void loop() {
  int joy_x = analogRead(joy_x_pin); // read X-axis of first joystick
  int joy_y = analogRead(joy_y_pin); // read Y-axis of first joystick

  joy_x = map(joy_x, 0, 1023, 0, 180); // map X-axis of first joystick to servo angle
  joy_y = map(joy_y, 0, 1023, 0, 180); // map Y-axis of first joystick to servo angle
  
  int joy_x_2 = analogRead(joy_x_pin_2); // read X-axis of second joystick
  int joy_y_2 = analogRead(joy_y_pin_2); // read Y-axis of second joystick

  joy_x_2 = map(joy_x_2, 0, 1023, 0, 180); // map X-axis of second joystick to servo angle
  joy_y_2 = map(joy_y_2, 0, 1023, 0, 180); // map Y-axis of second joystick to servo angle

  int data[4] = {joy_x, joy_y, joy_x_2, joy_y_2}; // create data array with four elements
  radio.write(&data, sizeof(data)); // send data via NRF24L01 send data via NRF24L0
  
}
