#include <util/TimeHandler.hpp>

time_t TimeHandler::Update()
{
    static time_t then_us = 0;
    now_us = mcu_get_time_since_boot_us();
    delta_us = now_us - then_us;
    then_us = now_us;
    return delta_us;
}