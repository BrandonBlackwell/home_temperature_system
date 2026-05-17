#include <cstdint>
#include <unordered_map>

enum class Zone {
  COLD,
  COMFORTABLE,
  WARM,
  HOT
};

class RGBController {
  static constexpr float MAX_BRIGHTNESS = 255.0f;
  public:
    Zone zone = Zone::COMFORTABLE;
    const uint8_t red_pin;
    const uint8_t green_pin;
    const uint8_t blue_pin;
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;

    RGBController(
      const uint8_t red_pin = 9, 
      const uint8_t green_pin = 10, 
      const uint8_t blue_pin = 11
    ):
      red_pin(red_pin), 
      green_pin(green_pin),  
      blue_pin(blue_pin)
      {};
    
    ~RGBController() = default;

    // TODO: This should be float
    void setColor(uint8_t temp);
    
  private:
    // TODO: This should be float
    Zone getZone(uint8_t temp);

    void apply_color_percentage(Zone zone);
};