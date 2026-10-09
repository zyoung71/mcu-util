#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <hardware/spi.h>

struct SPISharedConfig
{
    uint8_t sck_pin;
    uint8_t tx_mosi_pin;
    uint8_t rx_miso_pin;

    inline SPISharedConfig(uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin)
        : sck_pin(sck_pin), tx_mosi_pin(tx_pin), rx_miso_pin(rx_pin){}

    bool operator==(const SPISharedConfig& config) const;
};

template<>
struct std::hash<SPISharedConfig>
{
    size_t operator()(const SPISharedConfig&) const noexcept;
};

// Automatic control over chip select pins
class SPIDevice
{
private:
    // All devices that share the same pins are added to a group
    static std::unordered_map<SPISharedConfig, std::vector<uint8_t>> spi_device_map;
    
    // might memory pack this later
    const SPISharedConfig config;
    const uint8_t cs_pin;

public:
    SPIDevice(const SPISharedConfig& config, uint8_t cs_pin);
    SPIDevice(uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t cs_pin);

    void Prioritize();
};