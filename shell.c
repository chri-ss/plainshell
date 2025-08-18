#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define buf_size 1024
#define tokens_lim 100

int main() {
  char buffer[buf_size];
  char *token;
  char *tokens[tokens_lim];

  int tokenCount = 0;

  while (1) {
    if (fgets(buffer, sizeof(buffer), stdin)) {

      if (*buffer == 'q') {
        break;
      }

      // tokenize input
      tokenCount = 0;
      token = strtok(buffer, " ");

      while (token != NULL) {
        tokens[tokenCount] = strdup(token);
        token = strtok(NULL, " ");
        tokenCount++;
      }
      tokens[tokenCount] = NULL;

      // fork a new process to run the program in
      int status;
      pid_t childPid = fork();
      pid_t waitResult;

      if (childPid < 0) {
        perror("fail to fork");
        exit(1);
      } else if (childPid == 0) {
        printf("pid = %d\nchild_pid = %d", getpid(), childPid);

        // split arguments from program name
        char *args[tokenCount - 1];

        for (int i = 1; i < tokenCount; i++) {
          args[i - 1] = strdup(tokens[i]);
          printf("%s", args[i]);
        }
        // execute the program if it exists

        execvp(tokens[0], args);
      } else {
        waitResult = waitpid(childPid, &status, WUNTRACED);
        printf("complete\n");
      }

    } else {
      printf("Error, can't read input");
    }
  }
}
