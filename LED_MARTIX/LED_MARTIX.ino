#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

// Create a new instance of the MD_MAX72XX class:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// For software SPI you also need to specify the DATA_PIN and the CLK_PIN connections:
// #define DATA_PIN 11
// #define CLK_PIN 13

// Create a new instance of the MD_MAX72XX class:
// MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


void setup() {
  // Intialize the object:
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(0);
  // Clear the display:
  myDisplay.displayClear();
}

void loop() {
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.print("Hello");
  delay(2000);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.print("VScode");
  delay(2000);

 // myDisplay.setTextAlignment(PA_CENTER);
//  myDisplay.setInvert(true);
//  myDisplay.print("Invert");
//  delay(2000);

}
