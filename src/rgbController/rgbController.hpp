#include <cstdint>

enum class Zone {
  COLD,
  COMFORTABLE,
  WARM,
  HOT
};

class RGBController {
  public:
    Zone zone = Zone::COMFORTABLE;

    RGBController::RGBController(){}
    ~RGBController(){};

    void setColor(uint8_t temp);
    
  private:
    Zone getZone(uint8_t temp);
};