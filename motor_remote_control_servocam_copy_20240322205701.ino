// Inclue this libary
#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BTSerial(A0, A1);   // RX | TX

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position

//#define light_FR  14    //LED Front Right   pin A0 for Arduino Uno
//#define light_FL  15    //LED Front Left    pin A1 for Arduino Uno
//#define light_BR  16    //LED Back Right    pin A2 for Arduino Uno
//#define light_BL  17    //LED Back Left     pin A3 for Arduino Uno
//#define horn_Buzz 18    //Horn Buzzer       pin A4 for Arduino Uno

AF_DCMotor motor_fl(1); //front_left
AF_DCMotor motor_bl(2); //bl
AF_DCMotor motor_br(3); //br
AF_DCMotor motor_fr(4); //front_right

int command; //Int to store app command state.
int speedCar = 255; // Initial car speed set 0 to 255.
boolean lightFront = false;
boolean lightBack = false;
//boolean horn = false;

void setup()
{
  pinMode(A3, OUTPUT);                       // This pin will pull the HC-05 pin 34 (KEY pin) HIGH to switch module to AT mode.  
  digitalWrite(A3, HIGH);                    // If you're using the "button method" to reach AT mode, then this doesn't matter
  Serial.begin(115200);                       // This is the serial communication between the PC and the Arduino
  BTSerial.begin(9600);                    // HC-05 default speed in AT command mode is 38400

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}




void forward()
{
  motor_fl.run(FORWARD);
  motor_bl.run(FORWARD);
  motor_br.run(FORWARD);
  motor_fr.run(FORWARD);
    motor_fl.setSpeed(speedCar);
  motor_bl.setSpeed(speedCar);
  motor_br.setSpeed(speedCar);
  motor_fr.setSpeed(speedCar);
}

void backward()
{
  motor_fl.run(BACKWARD);
  motor_bl.run(BACKWARD);
  motor_br.run(BACKWARD);
  motor_fr.run(BACKWARD);
  motor_fl.setSpeed(speedCar);
  motor_bl.setSpeed(speedCar);
  motor_br.setSpeed(speedCar);
  motor_fr.setSpeed(speedCar);
}
void left()
{
  motor_fl.run(FORWARD);
  //motor_bl.run(RELEASE);
  motor_bl.run(FORWARD);
  motor_br.run(RELEASE);
  motor_fr.run(RELEASE);
  motor_fl.setSpeed(speedCar);
  motor_fr.setSpeed(speedCar);
}
void right()
{
  motor_fl.run(RELEASE);
  motor_bl.run(RELEASE);
  motor_br.run(FORWARD);
  motor_fr.run(FORWARD);
  motor_bl.setSpeed(speedCar);
  motor_br.setSpeed(speedCar);
}

void forwardRight()
{
  motor_fl.run(FORWARD);
  motor_bl.run(FORWARD);
  motor_br.run(FORWARD);
  motor_fr.run(RELEASE);
  
  motor_fl.setSpeed(speedCar);
  motor_bl.setSpeed(speedCar);
  motor_br.setSpeed(speedCar);
}

void forwardLeft()
{
  motor_fl.run(FORWARD);
  motor_bl.run(FORWARD);
  motor_br.run(RELEASE);
  motor_fr.run(FORWARD);
  
  motor_fl.setSpeed(speedCar);
  motor_bl.setSpeed(speedCar);
  motor_fr.setSpeed(speedCar);
}
void backwardRight()
{
  motor_fl.run(BACKWARD);
  motor_bl.run(BACKWARD);
  motor_br.run(BACKWARD);
  motor_fr.run(RELEASE);
     motor_fl.setSpeed(speedCar);
  motor_bl.setSpeed(speedCar);
  motor_br.setSpeed(speedCar);
}
void backwardLeft()
{
  motor_fl.run(BACKWARD);
  motor_bl.run(BACKWARD);
  motor_br.run(RELEASE);
  motor_fr.run(BACKWARD);
  motor_fl.setSpeed(speedCar);
  motor_bl.setSpeed(speedCar);
  motor_fr.setSpeed(speedCar);
}
void Stop()
{
  motor_fl.run(RELEASE);
  motor_bl.run(RELEASE);
  motor_br.run(RELEASE);
  motor_fr.run(RELEASE);
}
void rotate_right()
{
  pos+=10;

}
void rotate_left()
{
  pos-=10;
}
void zero_pos(){
  pos = 0;
}


void loop(){
  
     // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available()>0){
    command = BTSerial.read();
    Serial.write(command);
  }
  // Keep reading from Arduino Serial Monitor and send to HC-05
//  if (Serial.available()){
  //  BTSerial.write(Serial.read());
  //}


//f (Serial.available() > 0) {
//  command = Serial.read();
//  Stop();       //Initialize with motors stopped.

//if (lightFront) {digitalWrite(light_FR, HIGH); digitalWrite(light_FL, HIGH);}
//if (!lightFront) {digitalWrite(light_FR, LOW); digitalWrite(light_FL, LOW);}
//if (lightBack) {digitalWrite(light_BR, HIGH); digitalWrite(light_BL, HIGH);}
//if (!lightBack) {digitalWrite(light_BR, LOW); digitalWrite(light_BL, LOW);}
//if (horn) {digitalWrite(horn_Buzz, HIGH);}
//if (!horn) {digitalWrite(horn_Buzz, LOW);}

switch (command) {
case 'F':forward(); Serial.println("Forward");break;
case 'B':backward();break; Serial.println("Backward");break;
case 'L':left();break;
case 'R':right();break;
case 'I':forwardRight();break;
case 'G':forwardLeft();break;
case 'J':backwardRight();break;
case 'H':backwardLeft();break;
case 'S':Stop();break;
case '0':speedCar = 0;break;
case '1':speedCar = 25;break;
case '2':speedCar = 50;break;
case '3':speedCar = 75;break;
case '4':speedCar = 100;break;
case '5':speedCar = 125;break;
case '6':speedCar = 150;break;
case '7':speedCar = 175;break;
case '8':speedCar = 200;break;
case '9':speedCar = 225;break;
case 'q':speedCar = 255;break;
case 'w': rotate_right();command='p';;break;
case 'e': rotate_left();command='p';;break;
case 'z': zero_pos(); command='p';;break;
//case 'V':horn = true;break;
//case 'v':horn = false;break;
//}
}
myservo.write(pos);
delay(50);

}