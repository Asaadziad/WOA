#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "headers/logger.h"

void log(LOG_TYPE type, const char* message) {
    SYSTEMTIME lt;
    char buffer[1024] = {0};
    GetLocalTime(&lt);
    char* log_type;
    switch(type) {
    case  LOG_INFO:
      log_type = "INFO";
      break;
    case  LOG_ERROR:
      log_type = "ERROR";
      break;
    case  LOG_WARNING:
      log_type = "WARNING";
      break;
    }
    
    sprintf(buffer, "[%d-%d-%d %02d:%02d:%02d] %s: %s", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, log_type, message);

    fprintf(stderr, "%s", buffer);
}
