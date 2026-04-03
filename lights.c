#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"


static alt_u8 estado_sw75 = 0;
static alt_u8 estado_sw53 = 0;
static alt_u8 estado_sw31 = 0;
static alt_u16 minutos = 1;
static alt_u8 decenas_seg = 5;
static alt_u8 unidades_seg = 9;

static const alt_u16 rot_der[8] = {
0x8765, 0x1876, 0x2187, 0x3218,
0x4321, 0x5432, 0x6543, 0x7654
};

static const alt_u16 rot_izq[8] = {
0x1234, 0x2345, 0x3456, 0x4567,
0x5678, 0x6781, 0x7812, 0x8123
};

void delay_0_2s() { usleep(55 * 1000); }
void delay_1s() { usleep(275 * 1000); }

void sw0() {
IOWR(LEDS_BASE, 0, 0xFFFF);
delay_1s();
}

void sw1() {
    alt_u16 display;

    display = (minutos << 8) | (decenas_seg << 4) | unidades_seg;
    IOWR(LEDS_BASE, 0, display);
    delay_0_2s();


    if (unidades_seg > 0) {
        unidades_seg--;
    } else {
        unidades_seg = 9;
        if (decenas_seg > 0) {
            decenas_seg--;
        } else {
            decenas_seg = 5;
            if (minutos > 0) {
                minutos--;
            } else {
                minutos = 1;
                decenas_seg = 5;
                unidades_seg = 9;
            }
        }
    }
}

void sw31() {
IOWR(LEDS_BASE, 0, rot_izq[estado_sw31]);
delay_1s();

estado_sw31++;
if (estado_sw31 >= 8) estado_sw31 = 0;
}

void sw53() {
IOWR(LEDS_BASE, 0, rot_der[estado_sw53]);
delay_1s();

estado_sw53++;
if (estado_sw53 >= 8) estado_sw53 = 0;
}

void sw75() {
switch (estado_sw75) {
case 0:
IOWR(LEDS_BASE, 0, 0x1234);
delay_1s();
estado_sw75 = 1;
break;

case 1:
IOWR(LEDS_BASE, 0, 0xFFFF);
delay_1s();
estado_sw75 = 2;
break;

case 2:
IOWR(LEDS_BASE, 0, 0x5678);
delay_1s();
estado_sw75 = 3;
break;

case 3:
default:
IOWR(LEDS_BASE, 0, 0xFFFF);
delay_1s();
estado_sw75 = 0;
break;
}
}

int main() {
alt_u16 sw;

printf("Hello from Nios II! (Adaptado)\n");

while (1) {
sw = IORD(SWITCHES_BASE, 0) & 0xFF;

if ((sw & 0xFE) == 0x00) {
sw0();
}
else if ((sw & 0xFE) == 0x02) {
sw1();
}
else if ((sw & 0xFA) == 0x0A) {
sw31();
}
else if ((sw & 0xE8) == 0x28) {
sw53();
}
else if ((sw & 0xA0) == 0xA0) {
sw75();
}
else {
sw0();
}
}

return 0;
}
