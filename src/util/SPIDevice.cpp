#include <unordered_map>
#include <util/SPIDevice.hpp>
#include <hardware/gpio.h>

std::unordered_map<SPISharedConfig, std::vector<uint8_t>> SPIDevice::spi_device_map;

bool SPISharedConfig::operator==(const SPISharedConfig &config) const
{
    return (spi_inst == config.spi_inst) &&
        (sck_pin == config.sck_pin) &&
        (tx_mosi_pin == config.tx_mosi_pin) &&
        (rx_miso_pin == config.rx_miso_pin);
}

size_t std::hash<SPISharedConfig>::operator()(const SPISharedConfig& config) const noexcept
{
    const uint32_t* pack_ptr = reinterpret_cast<const uint32_t*>(config.sck_pin);
    uint32_t bytes = *pack_ptr & 0x00FFFFFF;

    size_t hash = reinterpret_cast<size_t>(config.spi_inst);
    hash ^= bytes;

    hash = (hash ^ 61) ^ (hash >> 16);
    hash += (hash << 3);
    hash ^= (hash >> 4);
    hash *= 0x27D4EB2D;
    hash ^= (hash >> 15);

    return hash;
}

SPIDevice::SPIDevice(const SPISharedConfig& config, uint8_t cs_pin)
    : config(config), cs_pin(cs_pin)
{
    if (!spi_device_map.try_emplace(config, std::vector<uint8_t>{cs_pin}).second)
    {
        // if list of CS pins on this SPI pin config exists:
        spi_device_map.at(config).push_back(cs_pin);
    }   
}

SPIDevice::SPIDevice(spi_inst_t* spi_inst, uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t cs_pin)
    : SPIDevice(SPISharedConfig(spi_inst, sck_pin, tx_pin, rx_pin), cs_pin)
{
}

void SPIDevice::Prioritize()
{
    for (uint8_t pin : spi_device_map.at(config))
    {
        gpio_put(pin, 1); // Pull all high to disable them.
    }

    gpio_put(cs_pin, 0); // Activate this one.
}