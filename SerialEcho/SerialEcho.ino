void setup()  
{
  Serial.begin(2400);
  Serial1.begin(2400);
}

void loop() // run over and over
{
  if (Serial1.available())
    Serial.write(Serial1.read());
  if (Serial.available())
    Serial1.write(Serial.read());
}

