#include <stdio.h>
#include <string.h>

int main() {
  char buffer[20];
  char *token;
  char *tokens[25];

  int tokenCount = 0;

  while (1) {
    if (fgets(buffer, sizeof(buffer), stdin)) {

      if (*buffer == 'q') {
        break;
      }

      tokenCount = 0;
      token = strtok(buffer, " ");

      while (token != NULL) {
        tokens[tokenCount] = token;
        token = strtok(NULL, " ");
        tokenCount++;
      }

      for (int i = 0; i < tokenCount; ++i) {
        printf("%s\n", tokens[i]);
      }

    } else {
      printf("Error, can't read input");
    }
  }

  printf("made it here\n");
}
