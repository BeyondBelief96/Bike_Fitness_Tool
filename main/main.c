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
#include "bike_timer.h"
#include "hall_sensor.h"



/*Main task of program*/
static void Bike_Tool_Task(void *arg)
{
    xDelay = 1000 / portTICK_PERIOD_MS;

    while(1)
    {
        prev_timer_value = *curr_timer_value;
        timer_get_counter_time_sec(TIMER_GROUP_0, TIMER_0, curr_timer_value);
        hall_sensor_value = hall_sensor_read();
        uint32_t voltage = esp_adc_cal_raw_to_voltage((uint32_t) hall_sensor_value, characteristics);
        printf("%d", voltage);
        printf("\n");
        vTaskDelay(xDelay);
        printf("%d:%d:%d""\n", (int) hour,(int) min, (int) *curr_timer_value);
    } 
}

/*Main Method of Program*/
void app_main(void)
{
    /* Analog to Digital Converter Config */
    adc1_configuration_t adc_config = {
        ADC_WIDTH_BIT_12,
        ADC1_CHANNEL_0,
        ADC_ATTEN_DB_0
    };

    timer_queue = xQueueCreate(10, sizeof(timer_event_t));
    curr_timer_value = (double*)malloc(4 * sizeof(double));
    characteristics = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    Initialize_Timer(TIMER_GROUP_0, TIMER_0, TIMER_ALARM_EN, TIMER_AUTORELOAD_EN, TIMER_ALARM_VALUE);
    configure_adc_1(adc_config);
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, adc_config.adc_attenuation, adc_config.bit_width, DEFAULT_VREF, characteristics);
    xTaskCreate(Bike_Tool_Task, "Bike_Tool_Task", 2048, NULL, 5, NULL);
}
