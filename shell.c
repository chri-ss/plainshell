#include <stdio.h>
#include <string.h>

int main() {
  char buffer[20];
  char *tokens[25];

  while (1) {
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
      char *token = strtok(buffer, " ");
      printf("%s", buffer);

    } else {
      printf("Error, can't read input");
    }
  }
}
