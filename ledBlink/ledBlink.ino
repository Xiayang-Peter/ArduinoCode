int LED = 12;
int LED2 = 10;
int input = 11;
int val = 0;

void setup() {
pinMode(LED,OUTPUT);
pinMode(LED2,OUTPUT);
pinMode(input,INPUT);
Serial.begin(9600);
}

void loop() {
  val = digitalRead(input);   // read the input pin
  Serial.print(input);
  if (val != 1){
      digitalWrite(LED, HIGH);
    } 
    else{
      digitalWrite(LED,LOW);
    }
  delay(100);
}
