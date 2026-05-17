#include "rgbController.hpp"



void RGBController::setColor(uint8_t temp) {
    switch (this->getZone(temp))
    {
    case Zone::COLD: 
        zone = Zone::COLD;
        apply_color_percentage(zone);
        break;
    case Zone::COMFORTABLE: 
        zone = Zone::COMFORTABLE;
        apply_color_percentage(zone);
        break;
    case Zone::WARM: 
        zone = Zone::WARM;
        apply_color_percentage(zone);
        break;
    case Zone::HOT: 
        zone = Zone::HOT;
        apply_color_percentage(zone);
        break;
    }
}

Zone RGBController::getZone(uint8_t temp) {
    if      (temp < 22) return Zone::COLD;
    else if (temp < 25) return Zone::COMFORTABLE;
    else if (temp < 28) return Zone::WARM;
    else                return Zone::HOT;
}

void RGBController::apply_color_percentage(Zone zone)
{
    if (zone == Zone::COLD)
    {
        this->red = 0 * MAX_BRIGHTNESS;
        this->green = 0.1 * MAX_BRIGHTNESS;
        this->blue = 0.9 * MAX_BRIGHTNESS;
    }
    else if (zone == Zone::COMFORTABLE)
    {
        this->red = 0.1 * MAX_BRIGHTNESS;
        this->green = 0.2 * MAX_BRIGHTNESS;
        this->blue = 0.7 * MAX_BRIGHTNESS;
    }
    else if (zone == Zone::WARM)
    {
        this->red = 0.3 * MAX_BRIGHTNESS;
        this->green = 0.2 * MAX_BRIGHTNESS;
        this->blue = 0.5 * MAX_BRIGHTNESS;
    }
    else // HOT zone
    {
        this->red = 0.9 * MAX_BRIGHTNESS;
        this->green = 0.1 * MAX_BRIGHTNESS;
        this->blue = 0.0 * MAX_BRIGHTNESS;
    }
}
