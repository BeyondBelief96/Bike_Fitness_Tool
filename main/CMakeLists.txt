idf_component_register(SRCS "main.c" "bike_timer/bike_timer.c" "adc/hall_sensor.c"
                    REQUIRES esp_adc_cal
                    INCLUDE_DIRS "." "bike_timer/include" "adc/include")