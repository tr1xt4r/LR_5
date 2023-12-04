#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

int executeCommand(char *command) {
    int result = system(command);
    printf("Exit code: %d\n", result);
    return result;
}

void getInput(char *input, size_t maxLength) {
    if (fgets(input, maxLength, stdin) == NULL) {
        printf("Error reading input.\n");
        exit(1);
    }
    input[strcspn(input, "\n")] = '\0';  // Remove the newline character.
}

void Main() {
    char input[MAX_INPUT_LENGTH];

    printf("Enter commands (type 'exit' to quit):\n");

    while (1) {
        printf("> ");
        getInput(input, sizeof(input));

        if (strcmp(input, "exit") == 0) {
            break;
        }

        char *token = strtok(input, ";");

        while (token != NULL) {
            printf("Executing command: %s\n", token);
            int result = executeCommand(token);
            token = strtok(NULL, ";");
        }
    }
}

int main() {
    Main();
    return 0;
}
