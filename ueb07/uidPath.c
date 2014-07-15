#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void) {
  uid_t u;
  u = getuid();
  printf("UID is:\t\t%d\n", u);

  char* path = getenv("PATH");
  printf("PATH is:\t%s\n", path);
}
