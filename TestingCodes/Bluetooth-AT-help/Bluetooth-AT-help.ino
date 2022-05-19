
/// all the changes to hardware/hardwarepins will needs to updates to the README//// 



// help menu printout for MLT-BT05
#include <SoftwareSerial.h>

SoftwareSerial ble_device(3,4);

String str_ii = "";
int ii_0 = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  ble_device.begin(9600);
  delay(1000);

  // First, get all available functions from CC2541 firmware
  ble_help();
}

void loop() {
}

void ble_help(){
  ble_device.println("AT+HELP"); // list all AT+ commands
  while (true){ // loop to print all AT+ commands
    char in_char = ble_device.read();
    if (int(in_char)==-1 or int(in_char)==42){continue;}
    str_ii+=in_char;
    if (in_char=='\n'){
      if (str_ii==String('\r')+String('\n')){
        if (ii_0 == 0){
          ii_0 = 1;
          continue;
        }
        break; // break after more than 1 empty carriage return and newline
      }
      Serial.print(str_ii);
      str_ii = "";
    }
  }
}
