#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("=== Memory Information Test ===\n");

  printf("Calling meminfo()...\n");
  meminfo();

  exit(0);
}
