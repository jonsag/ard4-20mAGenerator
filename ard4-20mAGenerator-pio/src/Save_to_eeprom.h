void Save()
{
  EEPROM.updateInt(20, ShuntLow);
  EEPROM.updateInt(22, ShuntMax);
}
