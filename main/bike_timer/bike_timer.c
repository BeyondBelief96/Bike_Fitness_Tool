#include "include/bike_timer.h"

uint64_t TIMER_INITIAL_COUNT_VALUE = 0; /* Initial value of timer */
double TIMER_ALARM_VALUE = 60.0; /* value to trigger timer alarm interrupt at */


/* Timer Intterupt Method */
void IRAM_ATTR timer_interrupt(void *para)
{
    timer_spinlock_take(TIMER_GROUP_0);
    int idx = (int) para;

    min =  min + 1;
    if(min == 60.0)
    {
        hour = hour + 1;
    }

    timer_event_t evt; 
    evt.timer_group = 0;
    evt.timer_index = idx;
    evt.timer_count = timer_group_get_counter_value_in_isr(TIMER_GROUP_0, idx);

    timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, idx);
    timer_group_enable_alarm_in_isr(TIMER_GROUP_0, idx);
    xQueueSendFromISR(timer_queue, &evt, NULL);
    timer_spinlock_give(TIMER_GROUP_0);
}

/* Method used to initialize timer */
void Initialize_Timer(int timer_group, int timer_index, bool enable_alarm, bool alarm_auto_reload, double timer_alarm_interval)
{
    timer_config_t timerConfig = 
    {
        .divider = TIMER_DIVIDER, 
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_PAUSE,
        .alarm_en = enable_alarm,
        .auto_reload = alarm_auto_reload
    };

    timer_init(timer_group, timer_index, &timerConfig);
    timer_set_counter_value(timer_group, timer_index, TIMER_INITIAL_COUNT_VALUE);
    timer_set_alarm_value(timer_group, timer_index, TIMER_ALARM_VALUE * TIMER_SCALE);
    timer_enable_intr(timer_group, timer_index);
    timer_isr_register(timer_group, timer_index, timer_interrupt, (void*)timer_index, ESP_INTR_FLAG_IRAM, NULL);
    timer_start(timer_group, timer_index);
}
