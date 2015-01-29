/*
SeaPerch Remote Control Test

Author: Qiuyang Tao
Electronic Team - Embeded System Group
Virtical Integrated Project - RoboSense
Georgia Institute of Technology

=================Connections================================================
RX2, TX2 --> Bluetooth module
A0  --> Key input from LCD button shield
A13 --> Joystick Vertical
A14 --> Joystick Horizontal
D52 --> Joystick button


================= How to use ===============================================


*/
#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include "MotorSpecs.h"

//Joystick-----------------------------
enum Joystick {
    VERTICAL_PIN = 13, HORIZONTAL_PIN = 14, PUSHBUTTON = 52
};
const int joystickMidPoint_X = 505;
const int joystickMidPoint_Y = 515;
int joystick_button;

//Motors------------------------------
const int motorCount = 5;
void sendMotorSpec(int motorSpec);
MotorSpecs *motorSpecs;

//Serial Comm-------------------------
String Serial_1_data_recieved = "";
String Serial_2_data_recieved = "";
int Serial2_received_data_status = 0;  //0 for no valid data, 1 for valid data received
float checksum;

//Data feedback-----------------------
float robot_battery_voltage;


//LCD key shield------------------------
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
int adc_key_in;
int NUM_KEYS = 5;
int adc_key_val[5] ={50, 200, 400, 600, 800 };
int key=-1;
int oldkey=-1;
char msgs[5][16] = {"Right ",
                    "Up    ",               
                    "Down  ",
                    "Left  ",
                    "Select" };
                    



void setup() {
  //LCD welcome screen-------------
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gatech VIP");
    lcd.setCursor(0,1);
    lcd.print("SeaPerch Project");
    delay(2000);
    lcd.clear();
    
  //initializaion------------------
    pinMode(PUSHBUTTON, INPUT);
    digitalWrite(PUSHBUTTON, HIGH);

    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);

    motorSpecs = new MotorSpecs(motorCount);
    motorSpecs->setMotor(0, 0);
    motorSpecs->setMotor(1, 0);
    motorSpecs->setMotor(2, 0);
}


void loop() {
  
    //Detect key pressed on LCD sheild----------------------
    adc_key_in = analogRead(0);
    key = get_key(adc_key_in); 
    if (key != oldkey)   // if keypress is detected
   {
     delay(50);  // wait for debounce time
     adc_key_in = analogRead(0);    // read the value from the sensor 
     key = get_key(adc_key_in);    // convert into key press
     if (key != oldkey)    
     {   
       lcd.setCursor(0, 1);
       oldkey = key;
       if (key >=0)
       {
           lcd.print(msgs[key]);              
       }
     }
   }
   delay(1000);
   //--------------------------------------------------------  
    
    motorSpecs->setNormalized_joystick_X(processJoystick(HORIZONTAL_PIN, joystickMidPoint_X));
    motorSpecs->setNormalized_joystick_Y(processJoystick(VERTICAL_PIN, joystickMidPoint_Y));
    joystick_button = !digitalRead(PUSHBUTTON);

    Motor4_Motor5_differential_and_limit_current();
    checksum = motorSpecs->getNormalized_joystick_X() + motorSpecs->getNormalized_joystick_Y() + joystick_button;
    for (int i = 0; i < motorCount; i++) {
        checksum += motorSpecs->getMotor(i);
    }

    serial_2_send_data();
    delay(20);


    serial_2_get_data_and_decode();

    serialDisplay();
    lcdDisplay();
    /*while (Serial2.available()) {
      int received = Serial2.read();
      Serial.write(received);
    }*/

    //Serial.print(Serial2_received_data_status);
}



void serialDisplay() {
    Serial.print("Battery Voltage: ");
    Serial.print(robot_battery_voltage);
    Serial.println(" V");
}

void lcdDisplay() {
    lcd.setCursor(0, 0);
    lcd.print("Battery Voltage:");
    lcd.setCursor(0, 1);
    lcd.print(robot_battery_voltage);
    lcd.print(" V");
}


void Motor4_Motor5_differential_and_limit_current() {
    float limit = 0.6;
    float x = (motorSpecs->getNormalized_joystick_X() - 1) * limit;
    float y = (motorSpecs->getNormalized_joystick_Y() - 1) * limit;
    float m4, m5;

    m4 = x + y;
    m5 = x - y;
    if (m4 > limit) {m4 = limit;}
    if (m4 < -1.0 * limit) {m4 = -1.0 * limit;}
    if (m5 > limit) {m5 = limit;}
    if (m5 < -1.0 * limit) {m5 = -1.0 * limit;}

    motorSpecs->setMotor(3, (int) ((m4 + 1) * 255));
    motorSpecs->setMotor(4, (int) ((m5 + 1) * 255));
}

void serial_2_send_data() {
    Serial2.flush();
    Serial2.print("#");

    Serial2.print(motorSpecs->getNormalized_joystick_X(), 3);
    Serial2.print(",");
    Serial2.print(motorSpecs->getNormalized_joystick_Y(), 3);
    Serial2.print(",");
    Serial2.print(joystick_button);
    Serial2.print(",");
    for (int i = 0; i < motorCount; i++) {
        sendMotorSpec(motorSpecs->getMotor(i));
    }
    Serial2.print(checksum, 3);

    Serial2.print("\n");
}

void sendMotorSpec(int motorSpec) {
    Serial2.print(motorSpec / 100);
    Serial2.print((motorSpec - (motorSpec / 100) * 100) / 10);
    Serial2.print(motorSpec % 10);
    Serial2.print(",");
}

void serial_2_get_data_and_decode() {
    if (Serial2.available() > 0) {
        Serial_2_data_recieved = Serial2.readStringUntil('\n');
        //Serial.println(Serial_2_data_recieved);
        //Serial.println(Serial_2_data_recieved.length());
        String head = Serial_2_data_recieved.substring(0, 1);  //if there is a valid start signal "#"
        if (head.equals("#") && (Serial_2_data_recieved.length() == 42)) {  //decompose the received string
            String str_normalized_joystick_X = Serial_2_data_recieved.substring(1, 6);
            String str_normalized_joystick_Y = Serial_2_data_recieved.substring(7, 12);
            String str_joystick_button = Serial_2_data_recieved.substring(13, 14);
            String str_Motor1 = Serial_2_data_recieved.substring(15, 18);
            String str_Motor2 = Serial_2_data_recieved.substring(19, 22);
            String str_Motor3 = Serial_2_data_recieved.substring(23, 26);
            String str_Motor4 = Serial_2_data_recieved.substring(27, 30);
            String str_Motor5 = Serial_2_data_recieved.substring(31, 34);
            String str_checksum = Serial_2_data_recieved.substring(35);

            //convert string to numerical value
            char buf1[str_normalized_joystick_X.length()];
            str_normalized_joystick_X.toCharArray(buf1, str_normalized_joystick_X.length() + 1);
            float temp_normalized_joystick_X = atof(buf1);
            char buf2[str_normalized_joystick_Y.length()];
            str_normalized_joystick_Y.toCharArray(buf2, str_normalized_joystick_Y.length() + 1);
            float temp_normalized_joystick_Y = atof(buf2);
            int temp_joystick_button = str_joystick_button.toInt();
            int temp_Motor1 = str_Motor1.toInt();
            int temp_Motor2 = str_Motor2.toInt();
            int temp_Motor3 = str_Motor3.toInt();
            int temp_Motor4 = str_Motor4.toInt();
            int temp_Motor5 = str_Motor5.toInt();
            char buf3[str_checksum.length()];
            str_checksum.toCharArray(buf1, str_checksum.length() + 1);
            float temp_checksum = atof(buf1);

            //calculate checksum
            float sum_of_received_data = temp_normalized_joystick_X + temp_normalized_joystick_Y + temp_joystick_button + temp_Motor1 + temp_Motor2 + temp_Motor3 + temp_Motor4 + temp_Motor5;

            //if data is valid
            if (sum_of_received_data == temp_checksum) {
                robot_battery_voltage = temp_normalized_joystick_X + 10;
                //normalized_joystick_Y= temp_normalized_joystick_Y;
                //joystick_button = temp_joystick_button;
                // Motor1=temp_Motor1;
                //Motor2=temp_Motor2;
                //Motor3=temp_Motor3;
                //Motor4=temp_Motor4;
                // Motor5=temp_Motor5;

                Serial2_received_data_status = 1;
            }
        }
    }
}

double processJoystick(int pinId, int midPoint) {
    double normalized;
    int rawValue = analogRead(pinId);
    delay(0.1);
    //-----------------normalize----------------
    //map the ADC reading to [-1, 1]
    if (rawValue < joystickMidPoint_X - 1) {
        normalized = 1.0 * (midPoint - rawValue) / midPoint;
    }
    if (rawValue > joystickMidPoint_X + 1) {
        normalized = -1.0 * (rawValue - midPoint) / (1023 - midPoint);
    }
    if (normalized > 1) {
        normalized = 1;
    }
    if (normalized < -1) {
        normalized = -1;
    }
    //-----------------apply curve--------------
    return normalized + 1;
}

// Convert ADC value from keypad to key number
int get_key(unsigned int input)
{
    int k;
    for (k = 0; k < NUM_KEYS; k++)
    {
      if (input < adc_key_val[k])
      {
        return k;
      }
    }   
    if (k >= NUM_KEYS)k = -1;  // No valid key pressed
    return k;
}
