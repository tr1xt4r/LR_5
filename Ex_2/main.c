#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int num_handlers;
volatile int received_signals = 0;

void signal_handler(int signum) {
    static int count = 0;
    count++;
    received_signals++;
    printf("Handler %d: Delaying for 1 second. Signal %d received.\n", count, signum);
    sleep(1);

    if (received_signals >= num_handlers) {
        printf("Received the desired number of signals. Stopping further signal handlers.\n");
        signal(SIGINT, SIG_DFL);  // Reset the handler to the default behavior
    }
}

void print_usage(const char *program_name) {
    printf("Usage: %s <number_of_handlers>\n", program_name);
}

int install_signal_handlers() {
    for (int i = 1; i <= num_handlers; i++) {
        if (signal(SIGINT, signal_handler) == SIG_ERR) {
            perror("Error registering handler for SIGINT");
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    num_handlers = atoi(argv[1]);

    if (num_handlers < 1) {
        printf("Number of handlers should be greater than 0.\n");
        return 1;
    }

    if (install_signal_handlers() != 0) {
        return 1;
    }

    printf("Waiting for process termination handlers. PID = %d\n", getpid());

    while (received_signals < num_handlers) {
        // Continue running until the desired number of signals have been received.
    }

    return 0;
}
