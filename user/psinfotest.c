#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid1, pid2;

  printf("=== Process Hierarchy Test ===\n");

  pid1 = fork();

  if (pid1 < 0) {
    printf("fork failed\n");
    exit(1);
  }

  if (pid1 == 0) {
    // Child process
    printf("Child created: PID=%d\n", getpid());

    pid2 = fork();

    if (pid2 < 0) {
      printf("grandchild fork failed\n");
      exit(1);
    }

    if (pid2 == 0) {
      // Grandchild process
      printf("Grandchild created: PID=%d\n", getpid());

      // Keep grandchild alive so psinfo() can see it.
      pause(20);
      exit(0);
    }

    // Keep child alive so psinfo() can see it.
    pause(20);
    wait(0);
    exit(0);
  }

  // Original parent process
  printf("Parent: PID=%d, Child=%d\n", getpid(), pid1);

  // Give child and grandchild time to be created.
  pause(2);

  printf("\nCalling psinfo()...\n");
  psinfo();

  wait(0);
  exit(0);
}
