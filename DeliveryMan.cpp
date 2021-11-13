#include "DeliveryMan.h"

DeliveryMan::DeliveryMan(const std::string &name, const unsigned int &capacity, const unsigned int &deliveryTime) : maxCapacity(capacity), deliveryTime(deliveryTime), name(name)
{
    this->currentCapacity = maxCapacity;
}

unsigned int DeliveryMan::getDeliveryTime() const
{
    return this->deliveryTime;
}

const std::string &DeliveryMan::getName() const
{
    return this->name;
}

void DeliveryMan::reduceCapacity(const unsigned int &capacityChange)
{
    this->currentCapacity -= capacityChange;
}

void DeliveryMan::reset()
{
    this->currentCapacity = this->maxCapacity;
}

unsigned int DeliveryMan::getCapacity() const
{
    return this->currentCapacity;
}

bool DeliveryMan::operator<(const DeliveryMan &dm) const
{
    return this->maxCapacity < dm.maxCapacity || (this->maxCapacity == dm.maxCapacity && this->deliveryTime > dm.deliveryTime);
}
