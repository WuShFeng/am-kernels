#include "trap.h"

#define SPI_BASE 0x10001000
#define SPI_TX0 (*(volatile uint32_t *)(SPI_BASE + 0x00))
#define SPI_CTRL (*(volatile uint32_t *)(SPI_BASE + 0x10))
#define SPI_DIV (*(volatile uint32_t *)(SPI_BASE + 0x14))
#define SPI_SS (*(volatile uint32_t *)(SPI_BASE + 0x18))

#define CTRL_ASS (1 << 13)
#define CTRL_GO (1 << 8)
#define SS_BITREV (1 << 7)

typedef unsigned char uint8_t;

static uint8_t reverse_byte(uint8_t b) {
  b = ((b & 0xF0) >> 4) | ((b & 0x0F) << 4);
  b = ((b & 0xCC) >> 2) | ((b & 0x33) << 2);
  b = ((b & 0xAA) >> 1) | ((b & 0x55) << 1);
  return b;
}

static uint8_t spi_bitrev(uint8_t data) {
  SPI_TX0 = data << 8 | 0xff;
  SPI_DIV = 0;
  SPI_SS = SS_BITREV;
  SPI_CTRL = CTRL_ASS | 16;
  SPI_CTRL |= CTRL_GO;
  while (SPI_CTRL & CTRL_GO)
    ;
  return SPI_TX0 & 0xFF;
}

int main() {
  // exhaustive 0..255 sweep
  for (int v = 0; v < 256; v++)
    check(spi_bitrev((uint8_t)v) == reverse_byte((uint8_t)v));

  return 0;
}
