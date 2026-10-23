#pragma once

#include <platform/time.h>

struct TimeHandler
{
private:
    time_t created_us;

public:
    time_t now_us;
    time_t delta_us;

    inline TimeHandler()
        : created_us(mcu_get_time_since_boot_us()), now_us(0), delta_us(0) {}

    inline TimeHandler& operator=(const TimeHandler& other)
    {
        created_us = other.created_us;
        now_us = other.now_us;
        delta_us = other.delta_us;
        return *this;
    }

    // Returns the delta time in microseconds
    time_t Update();

    inline time_t GetGlobalTimeWhenCreated() const
    {
        return created_us;
    }
    inline uint32_t GetDeltaTimeMilliseconds() const
    {
        return delta_us / 1000;
    }
    inline float GetDeltaTimeSeconds() const
    {
        return (float)delta_us * 1e-6f;
    }

};