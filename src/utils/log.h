#pragma once

#define LOG(fmt, ...) do { \
    char buf[128]; \
    snprintf(buf, sizeof(buf), (fmt) __VA_OPT__(,) __VA_ARGS__); \
    logMessage(buf); \
} while (0)

void logMessage(char* message);
