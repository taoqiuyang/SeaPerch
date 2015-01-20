/*
SeaPerch Remote Control Test

Author: Qiuyang Tao
Electronic Team - Embeded System Group
Virtical Integrated Project - RoboSense
Georgia Institute of Technology

=================Description================================================
Read the joystick value from ADC, encode and send to serial port 1


================= How to use ===============================================


*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

enum Joystick { VERTICAL_PIN = 13,  HORIZONTAL_PIN = 14, PUSHBUTTON = 52};
const int joystickMidPoint_X = 505;
const int joystickMidPoint_Y = 515;

String Serial_1_data_recieved = "";
String Serial_2_data_recieved = "";
int Serial2_received_data_status=0;  //0 for no valid data, 1 for valid data received

float normalized_joystick_X,normalized_joystick_Y,checksum;
int joystick_button,Motor1,Motor2,Motor3,Motor4,Motor5;

float robot_battery_voltage;


int connectButton=22; 

void setup()
{
  lcd.begin(16, 2);
  
  pinMode(PUSHBUTTON,INPUT);
  digitalWrite(PUSHBUTTON,HIGH);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  
  /*Serial2.print("$"); //Set the module
  Serial2.print("$");
  Serial2.print("$");  
  delay(100);  
  Serial2.println("C,000666682F4B"); //pairing with module2
  lcd.print("Connecting Robot...");
  delay(6000);
  lcd.clear();*/
}


void loop(){
   /*if (digitalRead(connectButton)==1){
   Serial2.print("$"); //Set the module
   Serial2.print("$");
   Serial2.print("$");  
   delay(100);  
   Serial2.println("C,000666682F4B"); //pairing with module2
   delay(6000);
 }*/
 
  normalized_joystick_X = processJoystick_X();
  normalized_joystick_Y = processJoystick_Y();
  joystick_button = !digitalRead(PUSHBUTTON);

  Motor1 = 0;
  Motor2 = 0;
  Motor3 = 0;
  Motor4_Motor5_differential_and_limit_current();
  checksum = normalized_joystick_X+normalized_joystick_Y+joystick_button+Motor1+Motor2+Motor3+Motor4+Motor5;
  Serial_2_send_data();
  delay(20);
  
  
  Serial_2_get_data_and_decode();
  
  serialDisplay();
  LCD_Display();
  /*while (Serial2.available()) {
    int received = Serial2.read();
    Serial.write(received); 
  }*/
  
  //Serial.print(Serial2_received_data_status);
}

void serialDisplay(){
  Serial.print("Battery Voltage: ");
  Serial.print(robot_battery_voltage);
  Serial.println(" V");
}

void LCD_Display(){
  lcd.setCursor(0, 0);
  lcd.print("Battery Voltage:");
    lcd.setCursor(0, 1);
  lcd.print(robot_battery_voltage);
  lcd.print(" V");
  
}


void Motor4_Motor5_differential_and_limit_current(){
  float limit=0.6;
  float x= (normalized_joystick_X-1)*limit;
  float y= (normalized_joystick_Y-1)*limit;
  float m4,m5;
  
  m4=x+y;
  m5=x-y;
  if (m4>limit){m4=limit;}
  if (m4<-1.0*limit){m4=-1.0*limit;}
  if (m5> limit){m5=limit;}
  if (m5<-1.0*limit){m5=-1.0*limit;}

  Motor4 = (int)((m4+1)*255);
  Motor5 = (int)((m5+1)*255);
  
}

void Serial_2_send_data(){
  Serial2.flush() ;
  Serial2.print("#");

  Serial2.print(normalized_joystick_X,3);  
  Serial2.print(",");
  Serial2.print(normalized_joystick_Y,3); 
  Serial2.print(",");
  Serial2.print(joystick_button); 
  Serial2.print(",");
  Serial2.print(Motor1/100); 
  Serial2.print((Motor1-(Motor1/100)*100)/10); 
  Serial2.print(Motor1%10); 
  Serial2.print(",");
  Serial2.print(Motor2/100); 
  Serial2.print((Motor2-(Motor2/100)*100)/10); 
  Serial2.print(Motor2%10); 
  Serial2.print(",");
  Serial2.print(Motor3/100); 
  Serial2.print((Motor3-(Motor3/100)*100)/10); 
  Serial2.print(Motor3%10); 
  Serial2.print(",");
  Serial2.print(Motor4/100); 
  Serial2.print((Motor4-(Motor4/100)*100)/10); 
  Serial2.print(Motor4%10); 
  Serial2.print(",");
  Serial2.print(Motor5/100); 
  Serial2.print((Motor5-(Motor5/100)*100)/10); 
  Serial2.print(Motor5%10); 
  Serial2.print(",");
  Serial2.print(checksum,3);
  
  Serial2.print("\n");
}

void Serial_2_get_data_and_decode(){
  if ( Serial2.available() > 0){
    Serial_2_data_recieved = Serial2.readStringUntil('\n');
    //Serial.println(Serial_2_data_recieved);
    //Serial.println(Serial_2_data_recieved.length());
    String  head = Serial_2_data_recieved.substring(0,1);  //if there is a valid start signal "#"
    if (head.equals("#") && (Serial_2_data_recieved.length()==42)){  //decompose the received string
      String str_normalized_joystick_X = Serial_2_data_recieved.substring(1,6);
      String str_normalized_joystick_Y = Serial_2_data_recieved.substring(7,12);
      String str_joystick_button = Serial_2_data_recieved.substring(13,14);
      String str_Motor1 = Serial_2_data_recieved.substring(15,18);
      String str_Motor2 = Serial_2_data_recieved.substring(19,22);
      String str_Motor3 = Serial_2_data_recieved.substring(23,26);
      String str_Motor4 = Serial_2_data_recieved.substring(27,30);
      String str_Motor5 = Serial_2_data_recieved.substring(31,34);
      String str_checksum = Serial_2_data_recieved.substring(35);

      //convert string to numerical value
      char buf1[str_normalized_joystick_X.length()];
      str_normalized_joystick_X.toCharArray(buf1,str_normalized_joystick_X.length()+1);
      float temp_normalized_joystick_X=atof(buf1);
      char buf2[str_normalized_joystick_Y.length()];
      str_normalized_joystick_Y.toCharArray(buf2,str_normalized_joystick_Y.length()+1);
      float temp_normalized_joystick_Y=atof(buf2);
      int temp_joystick_button = str_joystick_button.toInt();
      int temp_Motor1 = str_Motor1.toInt();
      int temp_Motor2 = str_Motor2.toInt();
      int temp_Motor3 = str_Motor3.toInt();
      int temp_Motor4 = str_Motor4.toInt();
      int temp_Motor5 = str_Motor5.toInt();
      char buf3[str_checksum.length()];
      str_checksum.toCharArray(buf1,str_checksum.length()+1);
      float temp_checksum=atof(buf1);

      //calculate checksum
      float sum_of_received_data=temp_normalized_joystick_X+temp_normalized_joystick_Y+temp_joystick_button+temp_Motor1+temp_Motor2+temp_Motor3+temp_Motor4+temp_Motor5;

      //if data is valid
      if (sum_of_received_data==temp_checksum){  
        robot_battery_voltage= temp_normalized_joystick_X+10;
        //normalized_joystick_Y= temp_normalized_joystick_Y;
        //joystick_button = temp_joystick_button;
       // Motor1=temp_Motor1;
        //Motor2=temp_Motor2;
        //Motor3=temp_Motor3;
        //Motor4=temp_Motor4;
       // Motor5=temp_Motor5;

        Serial2_received_data_status=1;
      }
    }
  } 
}


double processJoystick_X(){
  double normalized_X,processed_X;
  int    horizontal;
  horizontal = analogRead(HORIZONTAL_PIN);
  delay(0.1);
  //-----------------normalize----------------
  //map the ADC reading to [-1, 1] 
  if (horizontal<joystickMidPoint_X-1){
    normalized_X = 1.0*(joystickMidPoint_X-horizontal)/joystickMidPoint_X;
  }
  if (horizontal>joystickMidPoint_X+1){
    normalized_X = -1.0*(horizontal-joystickMidPoint_X)/(1023-joystickMidPoint_X);
  }
  if (normalized_X>1){
    normalized_X = 1;
  }
  if (normalized_X<-1){
    normalized_X = -1;
  }
  //-----------------apply curve--------------
  processed_X  = normalized_X+1;
  return processed_X;
}

double processJoystick_Y(){
  double normalized_Y,processed_Y;
  int    vertical;
  vertical = analogRead(VERTICAL_PIN);
  delay(0.1);
  //-----------------normalize----------------
  //map the ADC reading to [-1, 1] 
  if (vertical<joystickMidPoint_Y-1){
    normalized_Y = -1.0*(joystickMidPoint_Y-vertical)/joystickMidPoint_Y;
  }
  if (vertical>joystickMidPoint_Y+1){
    normalized_Y = 1.0*(vertical-joystickMidPoint_Y)/(1023-joystickMidPoint_Y);
  }
  if (normalized_Y>1){
    normalized_Y = 1;
  }
  if (normalized_Y<-1){
    normalized_Y = -1;
  }
  //-----------------apply curve--------------
  processed_Y  = normalized_Y+1;
  return processed_Y;
}
