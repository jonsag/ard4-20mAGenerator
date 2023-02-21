void calibrate()
{

  current_mA = ina219.getCurrent_mA();

  A0analogReading = adc.newAnalogRead(analogIn);
  arduinovoltage = (5.0 * A0analogReading);

  // record the minimum sensor value
  if (current_mA == 4.00)
  {
    ShuntLow = arduinovoltage;
  }

  // record the maximum sensor value
  if (current_mA == 20.00)
  {
    ShuntMax = arduinovoltage;
  }
  lcd.setCursor(0, 0);
  lcd.print("   Calibrate Shunt  ");

  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.setCursor(10, 1);
  lcd.print(current_mA);
  lcd.print("mA   ");

  lcd.setCursor(0, 2);
  lcd.print("Min Val: ");
  lcd.setCursor(10, 2);
  lcd.print(ShuntLow);
  lcd.print("     ");

  lcd.setCursor(0, 3);
  lcd.print("Max Val: ");
  lcd.setCursor(10, 3);
  lcd.print(ShuntMax);
  lcd.print("     ");
}

// 1590
// 8105

// 1610
// 8080
