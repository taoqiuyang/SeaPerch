const int SLIDE_POT_PIN = 15;
int slide_pot_value;
int depth_motor ;

void setup() {
  Serial.begin(9600); 
}


void loop() {
  slide_pot_value = analogRead(SLIDE_POT_PIN);            
  depth_motor = map(slide_pot_value,0,1023,-255,255);

  Serial.print("depth_motor = " );                       
  Serial.println(depth_motor);        

  delay(500);                     
}
