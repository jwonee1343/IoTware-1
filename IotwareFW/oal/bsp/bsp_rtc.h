#ifndef BSP_RTC_H
#define BSP_RTC_H

/* includes */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* types */

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} DATE_TIME_T;

/* functions */

bool bsp_init_rtc(void);
bool bsp_set_rtc_time(DATE_TIME_T *dt);
bool bsp_get_rtc_time(DATE_TIME_T *dt);
void bsp_enter_sleepmode(unsigned int delta);
void bsp_enter_stopmode(unsigned int delta);

#endif /* BSP_RTC_H */
