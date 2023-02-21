void Interval()
{

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = (busvoltage + (shuntvoltage / 1000)) + 0.71;

  A0analogReading = adc.newAnalogRead(analogIn);
  arduinovoltage = (5.0 * A0analogReading);

  ma_mapped = map(arduinovoltage, ShuntLow, ShuntMax, 40, 200) / 10.0;

  if (shuntvoltage >= -0.10 && shuntvoltage <= -0.01)
  {
    current_mA = 0;
    busvoltage = 0;
    loadvoltage = 0;
    shuntvoltage = 0;
  }
}
