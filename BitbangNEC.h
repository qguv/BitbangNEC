/* Code in this bitbang NEC library was born in a NEC (Japanese) Infrared code
 * sending library for the Arduino originally written by David L. Jones
 * www.eevblog.com, originally licensed Creative Commons CC BY (thanks Dave!)
 * and explained through a video [1]. Extended to support standard NEC with
 * address and command redundancy, among other things.
 *
 * [1]: http://www.youtube.com/watch?v=BUvFGTxZBG8
 */

#define ir_carrier_us 562 // length of the carrier bit in microseconds

void ir_setup(int);
void ir_carrier(unsigned int);
void ir_send_nec(int, int);
