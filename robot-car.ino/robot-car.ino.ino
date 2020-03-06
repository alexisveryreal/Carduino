/*
 *  Original Firmware for the "2WD Ultrasonic Motor Robot Car Kit"
 * 
 * Stephen A. Edwards
 * 
 * Hardware configuration:
 *  A pair of DC motors driven by an L298N H bridge motor driver
 *  AN HC-SR04 ultrasonic range sensor mounted atop a small hobby servo
 * 
 * 
 * Additionals edits made by EGG Spring 2020 Team lead team
 * 
 */

 #include <Servo.h>
 Servo servo;

 //Ultrasonic Module Pins
 //const int trigPin = 13;  //10 microsecond high pulse causes chirp, wait 50 us
 //const int echoPin = 12; // Width of high pulse indicates distance

 //Servo motor aims ultrasonic sensor.
// const int servoPin = 11; //PWM output for hobby servo

 // Motor control pins: L298N H bridge
 const int enAPin = 6; // Left motor PWM speed control
 const int in1Pin = 7; // Left motor Direction 1
 const int in2Pin = 5; // Left motor Direction 2
 const int in3Pin = 4; // Right motor Direction 1
 const int in4Pin = 2; // Right motor Direction 2
 const int enBPin = 3; // Right motor PWM speed control

typedef enum Motor{LEFT, RIGHT} Motor;
Motor m;

#define NUM_ANGLES 7
unsigned char sensorAngle[NUM_ANGLES] = {60,70,80,90,100,110,120};
unsigned int distance[NUM_ANGLES];


//Initial configuration
//
// Configure the input and output pins
// Center the servo
// Turn off the motors
// Test the motors
// Scan the surroundings once
//
void setup() {
//  pinMode(trigPin, OUTPUT);
 // pinMode(echoPin, INPUT);
 // digitalWrite(trigPin, LOW);

  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enBPin, OUTPUT);

 // servo.attach(servoPin);
 // servo.write(90);

  //go(LEFT, 0);
  //go(RIGHT, 0);






 // RIGHT CODE HERE IF YOU WANT TO JUST RUN ONCE








//  testMotors();

  
  moveForward(5);
  moveBackward(5);
  moveLeft(1);
  moveRight(1);










  


}

// Main Loop:
// Nothing, unless students want to repeat
// the same steps over and over
void loop(){





  // RIGHT CODE HERE IF YOU WANT TO LOOP












}


// Set motor speed: 255 full ahead, -255 full reverse, 0 stop
void go(Motor m, int speed){
  digitalWrite(m == LEFT ? in1Pin: in3Pin, speed > 0 ? HIGH:LOW);
  digitalWrite(m == LEFT ? in2Pin: in4Pin, speed <= 0 ? HIGH:LOW);
  digitalWrite(m == LEFT ? enAPin: enBPin, speed < 0 ? -speed:speed);
}

// Initial motor test:
// left motor forward then back
// right motor forward then back
void testMotors(){
  static int speed[8] = {128, 255, 128, 0, -128, -255, -128, 0};
  go(RIGHT, 0);

  for(unsigned char i = 0; i < 8; i++){
    go(LEFT, speed[i]), delay(200);
  }

  for(unsigned char i = 0; i < 8; i++){
    go(RIGHT, speed[i]), delay(200);
  }
}

/* moveForward: (moves forward for x seconds)
 *  [Might need to switch motor cables if moveForward not working]
 * 
 *  go() function accepts the speeds in ms, thus multiplying
 *    the seconds that are passed in by 1000 to convert into ms
 *      E.g.,  4 seconds = 4000ms
 *    Note that go runs until told to stop by go(Left,0) || go(Right, 0)
 *  We use the delay() function run the set amount of time wanted, then call go() again to stop.
 *  
 *  This is repeated for each of the four functions below
*/  
void moveForward(unsigned long sec){
  unsigned long interval = 1000;

  sec *= interval;

  go(LEFT, 255);
  go(RIGHT, 255);
  delay(sec);
  go(LEFT, 0);
  go(RIGHT, 0);
    
}

/* 
 * moveBackward: (moves back for x seconds)
 *  same as forward but switched to negative speeds
 *  thus rotating the motors in the opposite direction.
 */
void moveBackward(unsigned long sec){
  unsigned long interval = 1000;

  sec *= interval;

  go(LEFT, -255);
  go(RIGHT, -255);
  delay(sec);
  go(LEFT, 0);
  go(RIGHT, 0);
    
}

/*
 * moveRight: ( Moves right for x seconds)
 * the go function accepts varying levels of speeds
 * 255 is full speed
 * 0 is full STOP
 * 
 */
void moveRight(unsigned long sec){
  unsigned long interval = 1000;

  sec *= interval;

  go(LEFT, 255);
  go(RIGHT, -255);
  delay(sec);
  go(LEFT, 0);
  go(RIGHT, 0);
    
}

/*
 * moveLeft: (Moves left for x seconds)
 *  notice that the left and right values are switched
 *  this is so that when one tire turns forward the other back, for faster turns
 */
void moveLeft(unsigned long sec){
  unsigned long interval = 1000;

  sec *= interval;

  go(LEFT, -255);
  go(RIGHT, 255);
  delay(sec);
  go(LEFT, 0);
  go(RIGHT, 0);
    
}
