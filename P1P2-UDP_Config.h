/*  Settings for P1P2 UDP gateway
    for network parameters see separate file
*/


// Packet forwarding to Serial and UDP
//
// #define RAW_UDP           // The format of Serial input and output is always HEX as string (e.g. HEX 0x0A is represented as "0A" or "0a" string)
                          // By default, UDP input and output is also sent/received as string representation.
                          // If you want to use raw HEX for both UDP output (data) and UDP input (commands), define RAW_UDP
const byte forwardedPacketsRange[] = { 0x10, 0x16}; // Range of packet types which will be forwarded to Serial and UDP outputs.
                                              // Note: packet type 0xB8 (counters) is always forwarded.
                                              // Range { 0x10, 0x16} covers all useful and iinteresting data from Daikin Altherma Hybrid and Daikin Altherma LT. 
                                              // Expand the range if you want to test on other units.
                                              // forwardedPacketsRange[] should include savedPacketsRange[]
const byte savedPacketsRange[] = { 0x10, 0x16};   // Range of packet types which will be saved. 
                                                  // These packet types will be forwarded to Serial and UDP only if their payload changes or after DATA_RESEND_PERIOD
                                                  // Only packets sent by the heat pump or the main controller can be saved. Packets sent by external controllers are never saved.

// Memory settings
//
#define SAVED_HISTORY_BYTES 200      // max #bytes saved to store packet payloads (should be >= 1; 196 bytes is sufficient for savedPacketsRange[] = { 0x10, 0x16})
#define COMMANDS_QUEUE 10            // max number of Serial or UDP commands stored in queue
#define COMMANDS_QUEUE_BYTES 64      // max #bytes of Serial or UDP commands stored in queue

// Timeouts
//
#define DATA_TIMEOUT 60000          // Timeout for receiving data via P1P2 bus
#define DATA_RESEND_PERIOD 60000    // Period for resending payload from saved packets (see savedPacketsRange[]) and counter data (packet type 0xB8)
#define CONTROLLER_TIMEOUT 20000    // Timeout for connecting as external controller (timeout starts after receiving first data)
#define CONTROLLER_RETRY_PERIOD 600000     // Retry connecting as external controller after this period


// Advanced settings: packet write delays
//
#define PACKET_30_DELAY 100     // Time delay for responding to packet type 0x30 (connecting as external controller), should be larger than any response of other external controllers (which is typically 25-80 ms)
#define PACKET_30_THRESHOLD 5   // Number of 00Fx30 messages to be unanswered before we feel safe to act as external controller
#define PACKET_3X_DELAY  50     // Time delay for replying to packets type 0x3X (other than 0x30), should preferably be a bit larger than any regular response from external controllers (which is typically 25 ms)
#define PACKET_B8_DELAY 9       // The request for packet type 0xB8 (counters) is inserted at PACKET_B8_DELAY ms after the 400012* response
                                // This works for systems were the usual pause between 400012* and 000013* is around 47ms (+/- 20ms timer resolution)
                                // PACKET_B8_DELAY needs to be selected carefully to avoid bus collission between the 4000B8* response and the next 000013* request
                                // A value around 9ms works for my system; use with care, and check your logs

// #define DEBUG           // Print debug info to serial:
                           //     - settings
                           //     - packet type 0x35, 0x36 and 0x3A parameters and their values
                           //       using this format <packet type>: <param number>: <param value>
                           
