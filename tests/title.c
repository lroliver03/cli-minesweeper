#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int TITLE_MAX;
char buffer[200];

int main(const int argc, const char **argv) {
  srand(time(NULL));

  FILE *fptr = fopen("../config/title.txt", "r");

  if (fptr == NULL) {
    printf("Not able to open file.\n");
    return -1;
  }

  fscanf(fptr, "%d", &TITLE_MAX);
  printf("TITLE_MAX = %d\n\n", TITLE_MAX);

  int title_selected = (rand() % TITLE_MAX);

  while (title_selected >= 0 && fgets(buffer, 200, fptr)) {
    if (buffer[0] == '%') {
      title_selected--;
      continue;
    }
    if (title_selected == 0) printf("%s", buffer);
  }

  fclose(fptr);

  return 0;
}