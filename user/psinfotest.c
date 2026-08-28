#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid1, pid2, pid3;

  printf("=== Process Hierarchy Test ===\n");

  // Create child
  pid1 = fork();

  if (pid1 < 0) {
    printf("fork failed\n");
    exit(1);
  }

  if (pid1 == 0) {
    // Child
    printf("Child created: PID=%d\n", getpid());

    // Create grandchild
    pid2 = fork();

    if (pid2 < 0) {
      printf("grandchild fork failed\n");
      exit(1);
    }

    if (pid2 == 0) {
      // Grandchild
      printf("Grandchild created: PID=%d\n", getpid());

      // Create great-grandchild
      pid3 = fork();

      if (pid3 < 0) {
        printf("great-grandchild fork failed\n");
        exit(1);
      }

      if (pid3 == 0) {
        // Great-grandchild
        printf("Great-grandchild created: PID=%d\n", getpid());

        // Keep it alive so psinfo() can see it.
        pause(20);
        exit(0);
      }

      // Keep grandchild alive.
      pause(20);
      wait(0);
      exit(0);
    }

    // Keep child alive.
    pause(20);
    wait(0);
    exit(0);
  }

  // Original parent
  printf("Parent: PID=%d, Child=%d\n", getpid(), pid1);

  // Give all descendants time to be created.
  pause(3);

  printf("\nCalling psinfo()...\n");
  psinfo();

  wait(0);
  exit(0);
}
