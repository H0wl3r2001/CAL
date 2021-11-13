#include "DeliveryPlace.h"

DeliveryPlace::DeliveryPlace(const Time &deliveryTime, const std::string &name, const unsigned int &breadQuantity, const unsigned int &maxPrecendence, const unsigned int &maxDelay) : name(name), deliveryTime(deliveryTime), breadQuantity(breadQuantity)
{
    this->minimumTime = deliveryTime - maxPrecendence;
    this->maximumTime = deliveryTime + maxDelay;
}

DeliveryPlace::DeliveryPlace(const Time &deliveryTime, const std::string &name, const unsigned int &breadQuantity) : DeliveryPlace(deliveryTime, name, breadQuantity, 10, 30) {}

DeliveryPlace::DeliveryPlace(const Time &deliveryTime, const std::string &name) : DeliveryPlace(deliveryTime, name, 0, 10, 30) {}

DeliveryPlace::DeliveryPlace() {}

std::string DeliveryPlace::getNameAndTimeWindow() const
{
    return this->name + "\n" + "[" + this->minimumTime.to_string() + ", " + this->maximumTime.to_string() + "]";
}

std::string DeliveryPlace::getName() const
{
    return this->name;
}

Time DeliveryPlace::getIdealTime() const
{
    return this->deliveryTime;
}

Time DeliveryPlace::getMinTime() const
{
    return this->minimumTime;
}

Time DeliveryPlace::getMaxTime() const
{
    return this->maximumTime;
}

unsigned int DeliveryPlace::getBreadQuatity() const
{
    return this->breadQuantity;
}

bool DeliveryPlace::inTime(const Time &t) const
{
    return t <= this->maximumTime;
}

std::ostream &operator<<(std::ostream &os, const DeliveryPlace &dp)
{
    os << dp.name << " - [" << dp.minimumTime << ", " << dp.maximumTime << "]";
    return os;
}
