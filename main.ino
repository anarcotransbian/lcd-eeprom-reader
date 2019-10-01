/***
 * 
 * The setup of pins & wires are mostly identical to the one @ www.arduino.cc/en/Tutorial/HelloWorld,
 * however instead of a potentiometer, there is simply a 2k ohm resistor wired from negative in its place.
 * 
 ***/
 
#include <LiquidCrystal.h>
#include <EEPROM.h>

// hardcode whether or not we want to have serial output
// (for example, if not plugged into computer, it would be unnecessary)
const bool serial = true;

// setup Liquid Crystal Display
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// setup vars for reading EEPROM as given from www.arduino.cc/en/Tutorial/EEPROMRead
int address = 0;
byte value;

// prototypes
void lcdTop(String);  // prints to the top line of the LCD
void lcdBot(String);  // same, but bottom line

void setup() {
  lcd.begin(16, 2); // 16 long, 2 high
  if (serial) {
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for a serial port to connect. Needed for native USB port only
    }
  }
}

void loop() {
  // read a byte from the current addr of the eeprom
  value = EEPROM[address];

  if (serial) {
    Serial.print(String(address, DEC) + ", 0x" + String(address, HEX) + ": ");
    Serial.print("0x" + String(value, HEX));
    Serial.println();
  }

  lcdTop(String(address, DEC) + ", 0x" + String(address, HEX));
  lcdBot("0x" + String(value, HEX));

  // Advance to next addr, when at end restart @ beginning
  address = address + 1;
  if (address == EEPROM.length()) {
    if (serial) {
      Serial.println("Reached end, restarting");
    }
    
    lcdTop("Reached end of size");
    lcdBot("Starting over at 0");
    address = 0;
    delay(500); // make the delay two seconds to read
  }
  delay(1500);
  lcd.clear();
}

void lcdTop(String input) {
  // sets cursor to the beginning of the top line
  lcd.setCursor(0, 0);
  lcd.print(input);
}

void lcdBot(String input) {
  // sets cursor to the beginning of the bottom line
  lcd.setCursor(0, 1);
  lcd.print(input);
}
