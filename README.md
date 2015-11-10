# BitbangNEC

_It at least sort of works on my hardware_

### Installation

```bash
cd $yourarduinofolder/libraries
git clone --depth=1 https://github.com/qguv/BitbangNEC.git
```

### Usage

If I have an IR LED on pin 12 and I want to send the command 0x33 to a receiver with address 0xff:

```c
void setup() {
  ir_setup(12);
}

void loop() {
  ir_send_nec(0xff, 0x33);
}
```

It's actually that easy.

If you run into timing trouble (no command received or the wrong command consistantly received, even the wrong device triggering), play with the first line of the header file:

```c
#define ir_carrier_us 562 // length of the carrier bit in microseconds
```

Good luck!
