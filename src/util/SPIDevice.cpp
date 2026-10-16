#include <unordered_map>
#include <util/SPIDevice.hpp>

std::unordered_map<SPISharedConfig, std::vector<uint8_t>> SPIDevice::spi_device_map;

bool SPISharedConfig::operator==(const SPISharedConfig &config) const
{
    // notice we are comparing if at least one is true.
    // if at least one pin is shared, we have to treat all pins shared.
    return (sck_pin == config.sck_pin) ||
        (tx_mosi_pin == config.tx_mosi_pin) ||
        (rx_miso_pin == config.rx_miso_pin);
}

size_t std::hash<SPISharedConfig>::operator()(const SPISharedConfig& config) const noexcept
{
    uint32_t hash = (static_cast<uint32_t>(config.sck_pin) << 16) | 
        (static_cast<uint32_t>(config.tx_mosi_pin) << 8)  | 
        static_cast<uint32_t>(config.rx_miso_pin);

    hash = (hash ^ 61) ^ (hash >> 16);
    hash += (hash << 3);
    hash ^= (hash >> 4);
    hash *= 0x27D4EB2D;
    hash ^= (hash >> 15);

    return (size_t)hash;
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

SPIDevice::SPIDevice(uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t cs_pin)
    : SPIDevice(SPISharedConfig(sck_pin, tx_pin, rx_pin), cs_pin)
{
}

void SPIDevice::PrioritizeDevice() const
{
    for (uint8_t pin : spi_device_map.at(config))
    {
        gpio_put(pin, 1); // Pull all high to disable them.
    }

    gpio_put(cs_pin, 0); // Activate this one.
}