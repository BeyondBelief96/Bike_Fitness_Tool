#ifndef HALLSENSOR_H
#define HALLSENSOR_H

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
#include "driver/adc_common.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define DEFAULT_VREF    1100  

esp_adc_cal_characteristics_t* characteristics;
int hall_sensor_value;
int adc1_value;
TickType_t xDelay;

typedef struct {
    adc_bits_width_t bit_width;
    adc1_channel_t adc1_channel;
    adc_atten_t adc_attenuation;
} adc1_configuration_t;

void configure_adc_1(adc1_configuration_t config);

int read_adc1(adc1_channel_t channel);

#endif