#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo2; 
Servo myservo3; 
Servo myservo4; 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  myservo.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
// attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
} 
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023,0,180); 
  val = map(val, 0, 180,20,160);   // scale it to use it with the servo (value between 0 and 180) 
  
  if ((val<100)&&(val>80)){val=90;}
  myservo.write(val);
  myservo2.write(val);  // sets the servo position according to the scaled value 
  myservo3.write(val);
  myservo4.write(val);
  Serial.println(val);
  delay(15);                           // waits for the servo to get there 
} 
