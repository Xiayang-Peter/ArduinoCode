#include <MD_Parola.h>     //DISPLAY
#include <MD_MAX72XX.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  //define hardware spi pins for display
#define MAX_DEVICES 4
#define CS_PIN 10

//MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES); //new configuret for display

#define DATA_PIN 11             //reserve for software spi pins setting
#define CLK_PIN 12
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


void setup() {  
  myDisplay.begin();                            //DISPALY setups 
  myDisplay.displayClear();                            
  // Set the brightness of the display ( from 0-15):
  myDisplay.setIntensity(0);
}


void loop() {
  myDisplay.setTextAlignment(PA_LEFT);
  myDisplay.print("Hello");
  delay(2000);
  myDisplay.setTextAlignment(PA_RIGHT);
  myDisplay.print("VScode");
  delay(2000);
}
