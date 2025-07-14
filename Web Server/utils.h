#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void log_message(const char *level, const char *message);
void error_exit(const char *message);
void trim_whitespace(char *str);

#endif  

