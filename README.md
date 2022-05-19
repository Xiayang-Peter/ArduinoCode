Port configurations for arduino and subsystems for arduino

**RTC Time module (DS1302)**
- // DS1302 CLK/SCLK --> D7     
- // DS1302 DAT/IO --> D6  
- // DS1302 RST/CE --> D5
- // DS1302 VCC1 -->N/A
- // DS1302 VCC2 --> 5v
- // DS1302 GND --> GND
- // DS1302 X1/X2 --> Crystal oscillator
-----------------------------

**Bluetooth module(MLT-BT05)**
- // MLT-BT05 TXD --> D3
- // MLT-BT05 RXD --> D4 
- // MLT-BT05 VCC --> 5v
- // MLT-BT05 GUN --> GUN
------------------------------

**Display module and driver chip(/MAX7219)**
Software SPI pins setup:
-  // CLK_PIN -->  12  
-  // DATA_PIN --> 11 
-  // CS_PIN --> 10  
-  // VCC --> 5v
-  // GUN --> GUN
-- --------------------


