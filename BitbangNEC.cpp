/* Code in this bitbang NEC library was born in a NEC (Japanese) Infrared code
 * sending library for the Arduino originally written by David L. Jones
 * www.eevblog.com, originally licensed Creative Commons CC BY (thanks Dave!)
 * and explained through a video [1]. Extended to support standard NEC with
 * address and command redundancy, among other things.
 *
 * [1]: http://www.youtube.com/watch?v=BUvFGTxZBG8
 */

#include "Arduino.h"
#include "BitbangNEC.h"

#define ir_carrier_us 562 // length of the carrier bit in microseconds

int ir_led_pin = 3;

void ir_setup(int user_ir_led_pin) {
  ir_led_pin = user_ir_led_pin;
  pinMode(ir_led_pin, OUTPUT);
  digitalWrite(ir_led_pin, LOW);
}

/* Ouput the 38KHz carrier frequency for the required time in microseconds.
 * This is timing critial and just do-able on an Arduino using the standard I/O
 * functions. If you are using interrupts, ensure they disabled for the
 * duration. NOTE: digitalWrite takes about 3.5us to execute, so we need to
 * factor that into the timing.
 */
void ir_carrier(unsigned int time_us) {
  for (int i = 0; i < (time_us / 26); i++) {

    // on for 13us (9us + digitalWrite), half the carrier frequnecy
    digitalWrite(ir_led_pin, HIGH);
    delayMicroseconds(9);

    // off for 13us (9us + digitalWrite), half the carrier frequnecy
    digitalWrite(ir_led_pin, LOW);
    delayMicroseconds(9);
  }
}

// Sends the IR code in "short" (non-extended) NEC format, see http://www.sbprojects.com/knowledge/ir/nec.php
void ir_send_nec(int address, int command) {

  unsigned long nec_code = (address  << (8 * 3)) +
                           (~address << (8 * 2)) +
                           (command  << (8 * 1)) +
                           (~command << (8 * 0));

  // send the leading pulse; 9ms carrier then 4.5ms silence
  ir_carrier(9000);
  delayMicroseconds(4500);

  for (unsigned long bitmask = 1UL << ((8 * 4) - 1); bitmask; bitmask >>= 1) {

    // turn on the carrier for one bit time
    ir_carrier(ir_carrier_us);

    // the bit is tramsmitted via length of intervening silence
    // HIGH is 3x carrier time
    if (bitmask & nec_code) {
      delayMicroseconds(3 * ir_carrier_us);

    // a LOW is 1x carrier time
    } else {
      delayMicroseconds(ir_carrier_us);
    }
  }

  // send a single STOP bit
  ir_carrier(ir_carrier_us);
}
