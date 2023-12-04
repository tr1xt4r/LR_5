#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 127

void print_help() {
    printf("Simplified Command Processor\n");
    printf("Options:\n");
    printf("-h or --help: Display this help message\n");
    printf("-b or --buffer <size>: Specify buffer size (default is %d)\n", DEFAULT_BUFFER_SIZE);
}

void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int execute_command(const char *command) {
    int result = system(command);
    if (result != 0) {
        printf("Error executing the command. Return code: %d\n", result);
    }
    return result;
}

void process_commands(const char *username, int buffer_size) {
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    while (1) {
        printf("[%s]$", username);
        if (fgets(buffer, buffer_size, stdin) == NULL) {
            break;
        }

        remove_newline(buffer);

        if (strcmp(buffer, "stop") == 0) {
            printf("Program termination\n");
            break;
        }

        printf("Your command: %s\n", buffer);
        execute_command(buffer);
    }

    printf("Wait 3 seconds...\n");
    sleep(3);
    system("clear");
    free(buffer);
}

int main(int argc, char *argv[]) {
    char username[51];
    int buffer_size = DEFAULT_BUFFER_SIZE;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if ((strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) && i + 1 < argc) {
            buffer_size = atoi(argv[i + 1]);
            if (buffer_size <= 0) {
                printf("Invalid buffer size. Using the default size: %d\n", DEFAULT_BUFFER_SIZE);
                buffer_size = DEFAULT_BUFFER_SIZE;
            }
        }
    }

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        perror("Error reading username");
        return 1;
    }

    remove_newline(username);

    printf("You are working with the command processor, %s\n", username);

    process_commands(username, buffer_size);

    return 0;
}
