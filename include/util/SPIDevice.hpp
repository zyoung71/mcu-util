#pragma once

#include <cstdint>

#include <platform/gpio.h>

// Automatic control over chip select pins
class SPIDevice
{
private:
    const uint8_t cs_pin;

    bool active_if_gpio_high; // utility in cases where chip select pins are shared or pass thru hardware logic

public:
    inline SPIDevice(uint8_t cs_pin, bool active_if_gpio_high = false)
        : cs_pin(cs_pin), active_if_gpio_high(active_if_gpio_high) {}

    inline void Select() const
    {
        mcu_gpio_put(cs_pin, active_if_gpio_high);
    }
    inline void Deselect() const
    {
        mcu_gpio_put(cs_pin, !active_if_gpio_high);
    }
};