#include "trap.h"

uint32_t flash_read(uint32_t addr);
volatile uint32_t *xpiBase = (volatile uint32_t *)0x30000000;
int main() {
  for (int i = 0; i < (1 << 24); i += 4) {
    printf("%d\t%d\t%d\n", i, flash_read(i), *(xpiBase + i / 4));
    check(flash_read(i) == i && i == *(xpiBase + i / 4));
  }
  return 0;
}
