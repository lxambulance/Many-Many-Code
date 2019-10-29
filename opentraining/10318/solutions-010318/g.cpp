#include <stdlib.h>
#include <algorithm>
#include <cstdio>
#include <cstring>

int curv;

void move(int to) {
  printf("%d\n", to);
  fflush(stdout);
  char buf[10];
  scanf("%s", buf);
  if (!strcmp(buf, "yes")) 
    curv = to;
}

int main() {
  curv = 0;

  int to = 2;
  move(1);
  while (curv != 1) {
    move(to);
    if (curv == to) {
      move(1);
    } 
    to++;
  }
}
