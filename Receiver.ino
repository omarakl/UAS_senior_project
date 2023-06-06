#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(9, 10); // creating a RF object and assigning CE and CSN pins to 9 and 10
const byte address[6] = "00001";  // this address is unique, it should be the same at the transmitter and receiver

// every servo motor needs a Servo object

Servo servo1; // first servo object
Servo servo2; // second servo object
Servo servo3; // third servo object
Servo servo4; // fourth servo object

Servo motor1;





int servo_pin1 = 2; // first servo pin
int servo_pin2 = 3; // second servo pin
int servo_pin3 = 4; // third servo pin
int servo_pin4 = 5; // fourth servo pin
int motor_pin = 7; // throttle pin


void setup() {

  Serial.begin(9600);   
  radio.begin();  // begin the operation of the chip (NRF24L01 module)
  radio.openReadingPipe(0, address);  // open a pipe for reading
  radio.setPALevel(RF24_PA_MIN); // @ref RF24_PA_MIN (0) | -18 dBm | -6 dBm | -12 dBm |
  radio.startListening(); // starts lestining on the pipe that was opened for reading
  
  servo1.attach(servo_pin1); // attach first servo
  servo2.attach(servo_pin2); // attach second servo
  servo3.attach(servo_pin3); // ...
  servo4.attach(servo_pin4); // ...
  motor1.attach(motor_pin);


}

void loop() {

  // checks if there are bytes available to read
 if (radio.available()) {

    int data[5]; // create data array with four elements
    radio.read(&data, sizeof(data)); // read data via NRF24L01

    int motor_speed = data[0];

    int servo_angle1 = data[2]; // moves the flaps with y-axis of R joystick
    int servo_angle2 = data[2]; // moves the flaps with y-axis of R joystick - left flap

    int servo_angle3 = data[3]; // moves the ruddervators with x-axis of R joystick - right ruddervator
    int servo_angle4 = data[3]; // moves the ruddervators with x-axis of R joystick



    int mapped_motor_speed = map(motor_speed, 0, 1023, 0, 255); // maps joystick value to a value between 0 and 180
  



    servo1.write(servo_angle1); // move first servo to angle
    servo2.write(servo_angle2 ); // move second servo to angle
    servo3.write(servo_angle3); // move third servo to angle
    servo4.write(servo_angle4); // move fourth servo to angle


    
    motor1.write(mapped_motor_speed); // controls the speed of the brushless motor


  }
}

