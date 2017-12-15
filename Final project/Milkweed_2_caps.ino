
#include <Wire.h>
#include <Adafruit_CAP1188.h>



volatile byte interrupt = 0;


// Use I2C, no reset pin!
Adafruit_CAP1188 cap1 = Adafruit_CAP1188();
Adafruit_CAP1188 cap2 = Adafruit_CAP1188();


// Or...Use I2C, with reset pin
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

// Or... Hardware SPI, CS pin & reset pin
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CS, CAP1188_RESET);

// Or.. Software SPI: clock, miso, mosi, cs, reset
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET);

void setup() {
  Serial.begin(9600);
//  Serial.println("CAP1188 test!");
  //  pinMode(3, INPUT);
  // Raise SPI slave select (SS) pins
  // Communication begins when you drop the individual select signals to LOW
  //  digitalWrite(10, HIGH);


  // Initialize the sensor, if using i2c you can pass in the i2c address
  if (!cap1.begin(0x28)) {
//    Serial.println("CAP1188-0x29(cap1) not found");
    while (1);
  }
//  Serial.println("CAP1188-0x29(cap1) found!");



  if (!cap2.begin(0x29)) {
//    Serial.println("CAP1188-0x2B(cap2) not found");
    while (1);
  }
//  Serial.println("CAP1188-0x2B(cap2) found!");

//  Serial.println("CAP1188 found!");
  // Turn off multitouch so only one button pressed at a time
  cap1.writeRegister(0x2A, 0x80);  // 0x2A default 0x80 use 0x41  — Set multiple touches back to off
  cap1.writeRegister(0x41, 0x39);  // 0x41 default 0x39 use 0x41  — Set "speed up" setting back to off
  cap1.writeRegister(0x72, 0x00);  // 0x72 default 0x00  — Sets LED links back to off (default)
  cap1.writeRegister(0x44, 0x41);  // 0x44 default 0x40 use 0x41  — Set interrupt on press but not release
  cap1.writeRegister(0x28, 0x00);  // 0x28 default 0xFF use 0x00  — Turn off interrupt repeat on button hold
  cap2.writeRegister(0x2A, 0x80);  // 0x2A default 0x80 use 0x41  — Set multiple touches back to off
  cap2.writeRegister(0x41, 0x39);  // 0x41 default 0x39 use 0x41  — Set "speed up" setting back to off
  cap2.writeRegister(0x72, 0x00);  // 0x72 default 0x00  — Sets LED links back to off (default)
  cap2.writeRegister(0x44, 0x41);  // 0x44 default 0x40 use 0x41  — Set interrupt on press but not release
  cap2.writeRegister(0x28, 0x00);  // 0x28 default 0xFF use 0x00  — Turn off interrupt repeat on button hold
  uint8_t reg1 = cap1.readRegister( 0x1f ) & 0x0f;
  uint8_t reg2 = cap2.readRegister( 0x1f ) & 0x0f;

  cap1.writeRegister( 0x1f, reg1 | 0x5A);
  cap2.writeRegister( 0x1f, reg2 | 0x5A);
  EIFR = 1; // clear flag for interrupt 1
  attachInterrupt(1, routine_Interrupt_CAP1188, FALLING);
}

void loop() {


  uint8_t touched1 = cap1.touched();
  uint8_t touched2 = cap2.touched();


  if (touched1 == 0 && touched2 == 0) {
    // No touch detected
    return;
  }

  for (uint8_t i = 0; i < 8; i++) {
    if (touched1 & (1 << i)) {
      sendToIsadora(1, i + 9);
    }
    if (touched2 & (1 << i)) {
      sendToIsadora(1, i + 1);
    }

  }
//  Serial.print("Interrupt: ");  Serial.println(interrupt);
  delay(50);
  //End of loop
}

void sendToIsadora(int route, int value) {
  Serial.print(route);
  Serial.print('|');
  Serial.print(value);
  Serial.print(' ');
  delay(10);
}

void routine_Interrupt_CAP1188()  {
  ++interrupt;
}
