#include <SoftwareSerial.h> //BLUETOOTH
SoftwareSerial ble_device(3,4);
String str_ii = "";  //set bleinput value
int ii_0 = 0;
String DisplayContext = "";

#include <MD_Parola.h>     //DISPLAY
#include <MD_MAX72XX.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  //define hardware spi pins for display
#define MAX_DEVICES 4
#define CS_PIN 10

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES); //new configuret for display

// #define DATA_PIN 11             //reserve for software spi pins setting
// #define CLK_PIN 13
// MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);



void setup() {  
  Serial.begin(115200);
  ble_device.begin(9600);                                         //BLE setups
  delay(100);
  ble_cmd("AT+NAMEtest1","Device Name: "); // change and printout device name
  /*
  ble_cmd("AT+LADDR","Address: "); // printout BLE address
  ble_cmd("AT+CHAR","Char UUID: "); // printout character UUID
  ble_cmd("AT+VERSION","Version: "); // module version
  ble_cmd("AT+RESET","Reset: "); // reset module
  str_ii = "";
  delay(500);
  */

                                     
  myDisplay.begin();                                           //DISPALY setups
  // Set the brightness of the display ( from 0-15):
  myDisplay.setIntensity(0);
  myDisplay.displayClear();
}

//running ble_cmd
String ble_cmd(String cmd_str,String desc_str){
  str_ii = "";
  unsigned long t1 = millis();
  ble_device.println(cmd_str);
  while (true){
    if ((millis()-t1)>2000){ // 2 sec timeout
      return "Err";
    }
    char in_char = ble_device.read();
    if (int(in_char)==-1 or int(in_char)==42){
      continue;
    }
    if (in_char=='\n'){
      return str_ii;
    }
    str_ii+=in_char;
  }
}


void loop() {
  while (ble_device.available()){                              //BLE loop
    char in_char = ble_device.read();
    if (int(in_char)!=-1 and int(in_char)!=42){
      str_ii+=in_char;
    }
    if (in_char=='\n'){
      delay(20);
      String msg = "Msg received: ";
      msg+=str_ii;
      ble_device.print(msg);
      //myDisplay.setTextAlignment(PA_CENTER);                     //DISPLAY loop 
      //myDisplay.print(str_ii);
      //Serial.println(str_ii);
      //delay(2000);
      str_ii = "";
    }
  }
  Serial.println(DisplayContext);
  myDisplay.setTextAlignment(PA_CENTER);                 
  myDisplay.print(DisplayContext);
  delay(2000);
  DisplayContext = "";
}
