#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint_PID, Input_PID, Output_PID;
//Specify the links and initial tuning parameters
double Kp=5;
double Ki=0.00;
double Kd=1;

PID myPID(&Input_PID, &Output_PID, &Setpoint_PID, Kp, Ki, Kd, DIRECT);

void setup()
{
  Serial.begin(9600);

  Input_PID = 1000; //1atm=1000mbar
  Setpoint_PID = 1500; 
  myPID.SetOutputLimits(-255, 255);
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input_PID = analogRead(0);
  Input_PID = map(Input_PID, 0, 1024, 1480, 1520);
  myPID.Compute();
  
  //outputPID=output_PID+255;  //map [-255-255] to [0-510]
  
  Serial.print("In: ");
  Serial.print(Input_PID);
  Serial.print("  SetPoint: ");
  Serial.print(Setpoint_PID);
  Serial.print("  Out: ");
  Serial.println(Output_PID);
}


