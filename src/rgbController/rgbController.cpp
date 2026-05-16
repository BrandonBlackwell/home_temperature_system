#include "rgbController.hpp"



void RGBController::setColor(uint8_t temp) {
    switch (this->getZone(temp))
    {
    case Zone::COLD: zone = Zone::COLD;
        break;
    case Zone::COMFORTABLE: zone = Zone::COMFORTABLE;
        break;
    case Zone::WARM: zone = Zone::WARM;
        break;
    case Zone::HOT: zone = Zone::HOT;
        break;
    }
}

Zone RGBController::getZone(uint8_t temp) {
    if      (temp < 22) return Zone::COLD;
    else if (temp < 25) return Zone::COMFORTABLE;
    else if (temp < 28) return Zone::WARM;
    else                return Zone::HOT;
}
