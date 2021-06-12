#ifndef BIKETIMER_H
#define BIKETIMER_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "esp_types.h"
#include "esp_int_wdt.h"
#include "esp_task_wdt.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"

#define TIMER_DIVIDER 16                            //  Hardware timer clock divider
#define TIMER_SCALE (TIMER_BASE_CLK / TIMER_DIVIDER) // convert counter value to seconds 

typedef struct
{    
    int type;
    int timer_group;
    int timer_index;
    uint timer_count;
} timer_event_t;

xQueueHandle timer_queue; /* Timer interrupt callback handle */
extern double TIMER_ALARM_VALUE;
double* curr_timer_value; /* Pointer to hold current value of timer */
double prev_timer_value; /* variable to hold previous timer value */
double min; /* variable to store minutes for timer value */
double hour; /* variable to store hour for timer value */

/* Timer Intterupt Method */
void IRAM_ATTR timer_interrupt(void *para);

/* Method to initialize timer */
void Initialize_Timer(int timer_group, int timer_index, bool enable_alarm, bool alarm_auto_reload, double timer_alarm_interval);


#endif // !BIKETIMER_H

