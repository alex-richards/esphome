#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "esphome/components/xiaomi_ble/xiaomi_ble.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
namespace mi_band_4 {

struct ParseResult {
  optional<float> steps;
  int raw_offset;
};

class MiBand4 : public Component, public esp32_ble_tracker::ESPBTDeviceListener {
 public:
  void set_address(uint64_t address) { address_ = address; }

  bool parse_device(const esp32_ble_tracker::ESPBTDevice &device) override;

  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  void set_steps(sensor::Sensor *steps) { steps_ = steps; }

 protected:
  uint64_t address_;
  sensor::Sensor *steps_{nullptr};

  optional<ParseResult> parse_header(const esp32_ble_tracker::ServiceData &service_data);
  bool parse_message(const std::vector<uint8_t> &message, ParseResult &result);
  bool report_results(const optional<ParseResult> &result, const std::string &address);
};

}  // namespace mi_band_4
}  // namespace esphome

#endif
