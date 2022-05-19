/// all the changes to hardware/hardwarepins will needs to updates to the README//// 


const int BUTTON = 8;
const int LED = 7;
int BUTTONstate = 0;
Serial.begain(9600);

void setup()
{
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  BUTTONstate = digitalRead(BUTTON);
  if (BUTTONstate == HIGH)
  {
    digitalWrite(LED, HIGH);
  } 
  else{
    digitalWrite(LED, LOW);
  }
}