void Print_To_LCD()
{

  lcd.setCursor(0, 0);
  if (ma_mapped < 1.25)
  { // With no analog in and pin grounded
    lcd.print("* 4-20mA Generator *");
  }
  else
  {
    lcd.print("** Analog Tester **");
  }
  lcd.setCursor(0, 1);
  lcd.print("Device  :");
  lcd.setCursor(10, 1);
  if (ma_mapped < 1.25)
  {
    lcd.print("No Device ");
  }
  else
  {
    lcd.print(ma_mapped);
    lcd.print("mA  ");
  }
  // lcd.print(arduinovoltage);

  // lcd.print(arduinovoltage);

  lcd.setCursor(0, 2);
  lcd.print("Generate:");
  lcd.setCursor(10, 2);
  if (current_mA < 1)
  {
    lcd.print("0.00mA ");
  }
  else
  {
    lcd.print(current_mA);
    lcd.print("mA   ");
  }

  lcd.setCursor(0, 3);
  lcd.print("Supply  :");
  lcd.setCursor(10, 3);
  lcd.print(loadvoltage);
  lcd.print("V ");
}
