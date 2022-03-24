int LED = 12;
int input = 11;
int val = 0;

void setup() {
pinMode(LED,OUTPUT);
pinMode(input,INPUT);
Serial.begin(9600);
}

void loop() {
  val = digitalRead(input);   // read the input pin
  Serial.print(input);
  while val != 1{
      digitalWrite(LED, val);
    } 
}