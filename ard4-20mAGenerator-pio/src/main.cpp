#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_SR.h>
#include <TimeLib.h>
#include <Adafruit_INA219.h>
#include <eRCaGuy_NewAnalogRead.h>
#include <EEPROMex.h>
#include <JC_Button.h>

// A4 = (SDA)
// A5 = (SCL)

#define BUTTON_PIN 12
#define PULLUP true
#define INVERT true
#define DEBOUNCE_MS 0
Button myBtn(BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);

Adafruit_INA219 ina219;

LiquidCrystal_SR lcd(2, 4, 3);
//                   |  |  |___ Latch Pin
//                   |   \_____ Clock Pin
//                    \________ Data/Enable Pin

byte bitsOfResolution = 12;         // commanded over sampled resolution
unsigned long numSamplesToAvg = 20; // number of samples AT THE OVER SAMPLED RESOLUTION that you want to take and average
ADC_prescaler_t ADCSpeed = ADC_DEFAULT;

unsigned long previousMillis = 0;

float shuntvoltage = 0.0; // From INA219
float busvoltage = 0.0;   // From INA219
float current_mA = 0.0;   // From INA219
float loadvoltage = 0.0;  // From INA219

float arduinovoltage = 0.0; // Voltage calculation from A0 pin

unsigned long A0analogReading = 0;

byte analogIn = A0;

int ShuntLow = 0;
int ShuntMax = 0;

float ma_mapped = 0.0; // Map voltage from A0 to 4-20mA

#include <calibrate.h>
#include <Interval.h>
#include <LCD_Print.h>
#include <Save_to_eeprom.h>

void setup()
{
  adc.setADCSpeed(ADCSpeed);
  adc.setBitsOfResolution(bitsOfResolution);
  adc.setNumSamplesToAvg(numSamplesToAvg);

  // pinMode(12, INPUT_PULLUP);

  uint32_t currentFrequency;
  ina219.begin();
  // ina219.setCalibration_16V_400mA();
  // ina219.setCalibration_16V_30mA();
  ina219.setCalibration_32V_2A();
  // ina219.setCalibration_32V_1A();

  lcd.begin(20, 4); // initialize the lcd

  lcd.clear();
  lcd.home(); // go home
  lcd.print("********************");
  lcd.setCursor(0, 1);
  lcd.setCursor(0, 1);
  lcd.print("*");
  lcd.print("  Design & Build  ");
  lcd.setCursor(19, 1);
  lcd.print("*");
  lcd.setCursor(0, 2);
  lcd.print("*");
  lcd.setCursor(1, 2);
  lcd.print("      PIETER      ");
  lcd.setCursor(19, 2);
  lcd.print("*");
  lcd.setCursor(1, 3);
  lcd.setCursor(0, 3);
  lcd.print("*");
  lcd.print("   BEZUIDENHOUT   ");
  lcd.setCursor(19, 3);
  lcd.print("*");

  ShuntLow = EEPROM.readInt(20);
  ShuntMax = EEPROM.readInt(22);

  A0analogReading = adc.newAnalogRead(analogIn); // Letting the analog reading initialise

  delay(15000);
  lcd.clear();
}

void loop()
{
  myBtn.read();
  // while the button is pressed, take calibration readings:
  while (myBtn.isPressed())
  {
    calibrate();
    myBtn.read();
  }
  if (myBtn.wasReleased())
  {
    Save();
  }

  unsigned long currentMillis = millis();
  const long interval = 100;

  //&&&&&&&&&&&&&&&&& Read I2C devices at intervals and do some calculations &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    Interval();
    Print_To_LCD();
  }
}
