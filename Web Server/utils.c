#include "utils.h"

/**
 * Logs messages to the console with a timestamp and log level.
 * Example:
 *   log_message("INFO", "Server started successfully");
 */
void log_message(const char *level, const char *message) {
    time_t now;
    time(&now);
    struct tm *time_info = localtime(&now);
    
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    printf("[%s] [%s] %s\n", time_str, level, message);
}

/**
 * Prints an error message and exits the program.
 * Example:
 *   error_exit("Failed to initialize Winsock");
 */
void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

/**
 * Trims leading and trailing whitespace from a string.
 * Example:
 *   char test[] = "  hello  ";
 *   trim_whitespace(test);
 *   printf("|%s|\n", test);  // Output: |hello|
 */
void trim_whitespace(char *str) {
    char *end;

    // Trim leading spaces
    while (*str == ' ') str++;

    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;

    // Null terminate the trimmed string
    *(end + 1) = '\0';
}
