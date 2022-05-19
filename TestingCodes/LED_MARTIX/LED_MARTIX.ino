
/// all the changes to hardware/hardwarepins will needs to updates to the README//// 


#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

// config hardware spi pins and display type:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// reserve code for software spi config:
// #define DATA_PIN 11
// #define CLK_PIN 13
// MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


void setup() {
  myDisplay.begin();
  myDisplay.displayClear();
  // Set the brightness of the display (0-15):
  myDisplay.setIntensity(0);
  myDisplay.displayText("Hello, Visual Studio code !", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  //myDisplay.setTextAlignment(PA_CENTER);
  //myDisplay.print("Hello");
  //delay(2000);
  //myDisplay.setTextAlignment(PA_CENTER);
  //myDisplay.print("Visual studio code");
  //delay(2000);
  if (myDisplay.displayAnimate()) {
  myDisplay.displayReset();
  }
}
