#include "esp_log.h"
#include <time.h>
   
typedef struct {
    char* message;
    time_t date;
} log_message_t; 

void logMessage(char* message)
{
    time_t currentTime;
    time(&currentTime);
    ESP_LOGI("MAIN", "%s", message);
    //log_message_t logMessage = {.message=message, .date=currentTime};
}
