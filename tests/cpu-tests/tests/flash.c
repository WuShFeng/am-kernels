#include "trap.h"

uint32_t flash_read(uint32_t addr);
int main() {
  for (int i = 0; i < (1 << 24); i++) {
    check(flash_read(i) == i);
  }
  return 0;
}
