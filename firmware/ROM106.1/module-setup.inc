/**********************************************************************
 * module-setup.inc
 */

// Initialise relay control GPIO pins.
int rcopins[] = GPIO_RELAY_CONTROL_OUTPUT_PINS;
for (unsigned int i = 0 ; i < ELEMENTCOUNT(rcopins); i++) pinMode(rcopins[i], OUTPUT);
   

/**********************************************************************
 * Clear switchbank status buffer.
 */
N2kResetBinaryStatus(SWITCHBANK_STATUS);

/**********************************************************************
 * If the user has configured a non-default transmit interval and the
 * configured value is reasonable then override the default with the
 * configured value.
 */
if (EEPROM.read(PGN127501_TRANSMIT_INTERVAL_EEPROM_ADDRESS) != 0xff) {
  if (EEPROM.read(PGN127501_TRANSMIT_INTERVAL_EEPROM_ADDRESS) > 0) {
    PGN127501_TRANSMIT_INTERVAL = EEPROM.read(PGN127501_TRANSMIT_INTERVAL_EEPROM_ADDRESS);
  }
}