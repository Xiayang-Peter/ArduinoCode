
/// all the changes to hardware/hardwarepins will needs to updates to the README//// 

#include <MD_MAX72xx.h>
#include <SPI.h>

#define IMMEDIATE_NEW   0     // if 1 will immediately display a new message
#define USE_POT_CONTROL 1
#define PRINT_CALLBACK  0

#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   12  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS

// SPI hardware interface
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Scrolling parameters
#if USE_POT_CONTROL
#define SPEED_IN  A5
#else
#define SCROLL_DELAY  75  // in milliseconds
#endif // USE_POT_CONTROL

#define CHAR_SPACING  1 // pixels between characters

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  75
uint8_t curMessage[BUF_SIZE] = { "Welcome to Selwyn Open night " };
uint8_t newMessage[BUF_SIZE];
bool newMessageAvailable = false;

uint16_t  scrollDelay;  // in milliseconds

//Bluetooth
#include <SoftwareSerial.h> //BLUETOOTH
SoftwareSerial ble_device(3,4);
String str_ii = "";  //set bleinput value
int ii_0 = 0;
String DisplayContext = "";




void readSerial(void)
{
  static uint8_t  putIndex = 0;

  while (Serial.available())
  {
    newMessage[putIndex] = (char)Serial.read();
    if ((newMessage[putIndex] == '\n') || (putIndex >= BUF_SIZE-3)) // end of message character or full buffer
    {
      // put in a message separator and end the string
      newMessage[putIndex++] = ' ';
      newMessage[putIndex] = '\0';
      // restart the index for next filling spree and flag we have a message waiting
      putIndex = 0;
      newMessageAvailable = true;
    }
    else if (newMessage[putIndex] != '\r')
      // Just save the next char in next location
      putIndex++;
  }
}

void scrollDataSink(uint8_t dev, MD_MAX72XX::transformType_t t, uint8_t col)
// Callback function for data that is being scrolled off the display
{
#if PRINT_CALLBACK
  Serial.print("\n cb ");
  Serial.print(dev);
  Serial.print(' ');
  Serial.print(t);
  Serial.print(' ');
  Serial.println(col);
#endif
}

uint8_t scrollDataSource(uint8_t dev, MD_MAX72XX::transformType_t t)
// Callback function for data that is required for scrolling into the display
{
  static uint8_t* p = curMessage;
  static enum { NEW_MESSAGE, LOAD_CHAR, SHOW_CHAR, BETWEEN_CHAR } state = LOAD_CHAR;
  static uint8_t  curLen, showLen;
  static uint8_t  cBuf[15];
  uint8_t colData = 0;    // blank column is the default

#if IMMEDIATE_NEW
  if (newMessageAvailable)  // there is a new message waiting
  {
    state = NEW_MESSAGE;
    mx.clear(); // clear the display
  }
#endif

  // finite state machine to control what we do on the callback
  switch(state)
  {
    case NEW_MESSAGE:   // Load the new message
      memcpy(curMessage, newMessage, BUF_SIZE);	// copy it in
      newMessageAvailable = false;    // used it!
      p = curMessage;
      state = LOAD_CHAR;
      break;

    case LOAD_CHAR: // Load the next character from the font table
      showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
      curLen = 0;
      state = SHOW_CHAR;

      // if we reached end of message, opportunity to load the next
      if (*p == '\0')
      {
        p = curMessage;     // reset the pointer to start of message
#if !IMMEDIATE_NEW
        if (newMessageAvailable)  // there is a new message waiting
        {
          state = NEW_MESSAGE;    // we will load it here
          break;
        }
#endif
      }
      // !! deliberately fall through to next state to start displaying

    case SHOW_CHAR: // display the next part of the character
      colData = cBuf[curLen++];
      if (curLen == showLen)
      {
        showLen = CHAR_SPACING;
        curLen = 0;
        state = BETWEEN_CHAR;
      }
      break;

    case BETWEEN_CHAR: // display inter-character spacing (blank columns)
      colData = 0;
      curLen++;
      if (curLen == showLen)
        state = LOAD_CHAR;
      break;

    default:
      state = LOAD_CHAR;
  }

  return(colData);
}

 void scrollText(void)
{
  static uint32_t	prevTime = 0;

  // Is it time to scroll the text?
  if (millis()-prevTime >= scrollDelay)
  {
    mx.transform(MD_MAX72XX::TSL); // scroll along - the callback will load all the data
    prevTime = millis();      // starting point for next time
  }
}

uint16_t getScrollDelay(void)
{
#if USE_POT_CONTROL
  uint16_t  t;

  t = analogRead(SPEED_IN);
  t = map(t, 0, 1023, 25, 250);

  return(t);
#else
  return(SCROLL_DELAY);
#endif
}

void setup()
{
  mx.begin();
  mx.setShiftDataInCallback(scrollDataSource);
  mx.setShiftDataOutCallback(scrollDataSink);

#if USE_POT_CONTROL
  pinMode(SPEED_IN, INPUT);
#else
  scrollDelay = SCROLL_DELAY;
#endif

  newMessage[0] = '\0';

  Serial.begin(115200);
  ble_device.begin(9600);                                         //BLE setups

  Serial.print("\n[MD_MAX72XX Message Display]\nType a message for the scrolling display\nEnd message line with a newline");
  
  ///bluetooth
  ble_cmd("AT+NAMEtest1","Device Name: "); // change and printout device name
  /*
  ble_cmd("AT+LADDR","Address: "); // printout BLE address
  ble_cmd("AT+CHAR","Char UUID: "); // printout character UUID
  ble_cmd("AT+VERSION","Version: "); // module version
  ble_cmd("AT+RESET","Reset: "); // reset module
  str_ii = "";
  delay(500);
  */


}

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

void loop(){
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
    DisplayContext +=str_ii;
    ble_device.print(DisplayContext);
    DisplayContext = "";
    str_ii = "";
    }
  }


  scrollDelay = getScrollDelay();
  readSerial();
  scrollText();
}

