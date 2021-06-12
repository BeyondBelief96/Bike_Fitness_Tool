#include "include/hall_sensor.h"

void configure_adc_1(adc1_configuration_t config)
{
    adc1_config_width(config.bit_width);
    adc1_config_channel_atten(config.adc1_channel, config.adc_attenuation);
}

int read_adc1(adc1_channel_t channel)
{
    return adc1_get_raw(channel);
}