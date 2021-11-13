#pragma once
#include <string>

/**
 * @brief Class that represents a delivery man
 */
class DeliveryMan
{
private:
    /**
     * @brief Current bread vehicle capacity
     */
    unsigned int currentCapacity;
    /**
     * @brief Name of the delivery man
     */
    std::string name;
    /**
     * @brief Maximum bread vehicle capacity
     */
    unsigned int maxCapacity;
    /**
     * @brief Delivery time - Amount of time the delivery man takes to make a delivery after reaching a delivery place
     */
    unsigned int deliveryTime;

public:
    /**
     * @brief Construct a new Delivery Man object
     *
     * @param name name of de delivery man
     * @param capacity Maximum bread vehicle capacity
     * @param deliveryTime Delivery time - Amount of time the delivery man takes to make a delivery after reaching a delivery place
     */
    DeliveryMan(const std::string &name, const unsigned int &capacity, const unsigned int &deliveryTime);

    /**
     * @brief Get the Delivery Time object
     *
     * @return unsigned int
     */
    unsigned int getDeliveryTime() const;

    /**
     * @brief Get the Name of the delivery man object
     *
     * @return const std::string&
     */
    const std::string &getName() const;

    /**
     * @brief Removes capacity from the delivery man
     *
     * @param capacityChange value to be reduced
     */
    void reduceCapacity(const unsigned int &capacityChange);

    /**
     * @brief Reset the vehicle capacity
     */
    void reset();

    /**
     * @brief Get the current bread Capacity of the vehicle
     *
     * @return unsigned int
     */
    unsigned int getCapacity() const;

    /**
     * @brief Checks if a delivery man has less maximum capacity than another
     *
     * @param dm other delivery man to compara
     * @return true if the maximum capacity of \p this is higher than \p dm
     * @return false otherwise
     */
    bool operator<(const DeliveryMan &dm) const;
};
