/**********************************************************************
 * module-directives.inc
 *
 * Contains #defines for the constant values which characterise our
 * module application and, a little incongruously, declarations for our
 * application functions
 */
  
/**********************************************************************
 * DEVICE INFORMATION
 * 
 * Because of NMEA's closed standard, most of this is fiction. Maybe it
 * can be made better with more research.
 *
 * DEVICE_CLASS and DEVICE_FUNCTION are explained in the document
 * "NMEA 2000 Appendix B.6 Class & Function Codes".
 * 
 * INDUSTRY_GROUP we can be confident about (4 says maritime).
 * 
 * MANUFACTURER_CODE is only allocated to subscribed NMEA members and,
 * unsurprisingly, an anonymous code has not been assigned: 2046 is
 * currently unused, so we adopt that.  
 * 
 * UNIQUE_NUMBER is combined in some way so that together they define
 * a value which must be unique (is some way) on any N2K bus. An easy
 * way to achieve this is just to bump the unique number for every
 * software build. Really this needs (i) understanding and
 * (ii) automating.
 */
#define DEVICE_CLASS 30                 // Electrical Distribution
#define DEVICE_FUNCTION 140             // Load Controller
#define DEVICE_INDUSTRY_GROUP 4         // Maritime
#define DEVICE_MANUFACTURER_CODE 2046   // Currently not allocated.
#define DEVICE_UNIQUE_NUMBER 849        // Bump me?


/**********************************************************************
 * PRODUCT INFORMATIOM
 * 
 * This poorly structured set of values is what NMEA expects a product
 * description to be shoe-horned into.
 */
#define PRODUCT_CERTIFICATION_LEVEL 1
#define PRODUCT_CODE 002
#define PRODUCT_FIRMWARE_VERSION "1.1.0 (Jun 2022)"
#define PRODUCT_LEN 1
#define PRODUCT_N2K_VERSION 2022        // The N2K specification version?
#define PRODUCT_SERIAL_CODE "002-849"   // PRODUCT_CODE + DEVICE_UNIQUE_NUMBER
#define PRODUCT_TYPE "ROM106"           // The product name?
#define PRODUCT_VERSION "1.0 (Mar 2022)"



/**********************************************************************
 * NMEA2000 LIBRARY DEFINITIONS
 *
 * NMEA_TRANSMIT_MESSAGE_PGNS is an initialiser for an array of PGNs
 * which defines the messages transmitted by this firmware. The list
 * must terminate with a zero value.
 *
 * NMEA_PGN_HANDLERS is an initialiser for a jump vector which defines
 * a list of pairs each of which maps a PGN to the function responsible
 * for processing messages of the defined type when they are received
 * over the CAN interface. For example, { 127501L, myFunc }. The list
 * must terminate with the special flag value { 0L, 0 }.
 */
#define NMEA_TRANSMIT_MESSAGE_PGNS { 127501L, 0 }
#define NMEA_PGN_HANDLERS  { { 127502L, handlePGN127502 }, { 0L, 0 } }

/**********************************************************************
 * Aliases for GPIO pins connected to switch inputs. 
 */
#define GPIO_RELAY1_ENABLE GPIO_D23
#define GPIO_RELAY2_ENABLE GPIO_D22
#define GPIO_RELAY3_ENABLE GPIO_D21
#define GPIO_RELAY4_ENABLE GPIO_D20
#define GPIO_RELAY5_ENABLE GPIO_D6
#define GPIO_RELAY6_ENABLE GPIO_D5
#define GPIO_RELAY_SET GPIO_D8
#define GPIO_RELAY_RST GPIO_D9
#define GPIO_RELAY_CONTROL_OUTPUT_PINS { GPIO_RELAY1_ENABLE, GPIO_RELAY2_ENABLE, GPIO_RELAY3_ENABLE, GPIO_RELAY4_ENABLE, GPIO_RELAY5_ENABLE, GPIO_RELAY6_ENABLE, GPIO_RELAY_SET, GPIO_RELAY_RST }

/**********************************************************************
 * Storage location of the transmit interval configuration value.
 */
#define PGN127501_TRANSMIT_INTERVAL_EEPROM_ADDRESS 02

/**********************************************************************
 * Number of milliseconds between checks on switch input channel state.
 */
#define RELAY_PROCESS_INTERVAL 100       // Process relay outputs every n ms

/**********************************************************************
 * Maximum number of entries in the relay operation queue.
 */
#define RELAY_OPERATION_QUEUE_SIZE 10       // Max number of entries

/**********************************************************************
 * Frequency of relay queue processing.
 */
#define RELAY_OPERATION_QUEUE_INTERVAL 20UL

/**********************************************************************
 * Number of milliseconds between regular transmission of PGN 127501.
 */
#define PGN127501_DEFAULT_TRANSMIT_INTERVAL 4000UL

/**********************************************************************
 * Ok, these are declarations, not definitions, but we need to get the
 * jump vector callbacks in the world quite early...
 */
void transmitSwitchbankStatusMaybe(bool force = false);
void transmitPGN127501();
void handlePGN127502(const tN2kMsg &n2kMsg);
